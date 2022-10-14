# coding=utf-8
import logging
from src import rrLib, rrJob
import os
import inspect
from collections import defaultdict, OrderedDict
from flask import json

from src.rrUtils import timeformat, seconds_to_minutes, JobGroupsSnapshot

test = False


def full_stack(wasException):
    import traceback, sys
    exc = sys.exc_info()[0]
    stack = traceback.extract_stack()
    if (wasException):
        stack = stack[:-2]   # last one would be our function full_stack() the one before  logging.error(str(full_stack()))
    else:
        stack = stack[:-1]   # last one would be our function full_stack() the one before  logging.error(str(full_stack()))    
    stack = stack[-6:] #Reduce to 6 entries
    #if exc is not None:  # i.e. an exception is present
     #   del stack[-1]       # remove call of full_stack, the printed exception will contain the caught exception caller instead
    stack= traceback.format_list(stack)
    stack.reverse()
    if wasException:
        trc = 'ERROR Traceback:\n'
    else:
        trc = 'NOT AN ERROR!! Traceback:\n'
    stackstr = trc + ''.join(stack)
    #if exc is not None:
    #     stackstr += '  ' + traceback.format_exc().lstrip(trc)
    return stackstr

class ServerApi:
    job_commands = {"abort": "lAbort", "enable": "lEnable", "disable": "lDisable", "approve": "lApprove",
                    "disapprove": "lDisApprove", "delete": "lDelete"}

    client_commands = {"abort": "cAbort", "enable": "cEnable", "disable": "cDisable", "restart": "cRestartMachine",
                       "WOL": "cWOL", "shutdown": "cShutdownMachine", "commandline": "cCommandLine"}

    def __init__(self, host=None, port=None, verbose=False):
        """
        Instance of RRApi with tcp
        :parameter host: hostname
        :type host: basestring
        :parameter port: port
        :type port: int
        """
        self.clients = None
        self.jobs = None
        self.job_groups = {}
        self.job_groups_filtered = {}
        self.tcp = None
        self.rrServer = ""
        #self.username = None
        self.port = port or 7773

        try:
            # ONLY ONE TCP SHOULD BE OPENED
            self.tcp = rrLib._rrTCP("")
            self.tcp.setVerbose(verbose)
            self.rrServer = host or self.tcp.getRRServer()
            self.tcp.setRemoteLocation()
            logging.info("rrServer is set to "+self.rrServer)
            #logging.info("*****ServerApi::__init__  " + full_stack(False))
            if not self.rrServer or len(self.rrServer) == 0:
                exception = Exception("Unable to get rrServer: " + self.tcp.errorMessage())
                raise exception
            if not self.tcp.setServer(self.rrServer, self.port):
                exception = Exception( "Unable to set rrServer: " + self.tcp.errorMessage())
                raise exception
        except Exception as e:
            logging.error("__init__: "+ str(e))
            return

    def update(self):
        """
        Update RR info
        :return:
        """

        self.fetch_jobs()
        self.fetch_clients()
        self._update_job_groups()
        # TODO MORE

    def set_login(self, username="", password=""):
        """
        IMPORTANT: If you set a password, then the rrServer enables its authorizazion check.
        This means this user MUST exist in RR.
        If you are running this script from your local intranet, you probably do not need a password.
        Please see rrHelp section Usage/External Connections/Security
        :param username:
        :param password:
        :return:
        :rtype: bool
        """

        if not username or not password:
            logging.debug("Login attempt with empty username or password")
            return False, "No User name or PW"

        try:
            username = str(username)
            password = str(password)
            #self.username = username
            self.tcp.setLogin(username, password)
            errorMsg=""
            success=self.tcp.connectAndAuthorize()
            if (not success):
                errorMsg= self.tcp.errorMessage()
                logging.warning("Login issue: " + errorMsg)
            return success, errorMsg
        except AttributeError as e:
            logging.error("Unable to setLogin: " + str(e))
        except Exception as e:
            logging.error("Unknown error setting login: " + str(e))

        return False, "Python Exception"

    def getPassHash(self):
        passHash= self.tcp.getPassA85()
        #logging.debug("getPassHash: "+passHash)
        return passHash

    def set_login_passHash(self, username, passwordA85):
        """

        :param username:
        :type username: basestring
        :param passwordA85:
        :return:
        """

        #logging.debug("set_login_passHash: "+passwordA85)
        try:
            username = str(username)
            #self.username = username
            self.tcp.setLoginA85(username, passwordA85)
        except AttributeError as e:
            logging.error("Unable to setLoginHAsh: " + str(e))
        except Exception as e:
            logging.error("Unknown error setting loginHash: " + str(e))

    def set_login_no_pass(self, username):
        """

        :param username:
        :type username: basestring
        :return:
        """

        try:
            username = str(username)
            self.username = username
            self.tcp.setLogin(username, "")
        except AttributeError as e:
            logging.error("Unable to setLogin: " + str(e))
        except Exception as e:
            logging.error("Unknown error setting login: " + str(e))

    def get_error_message(self):
        """
        Returns the last error message
        :return:
        :rtype: str
        """
        return self.tcp.errorMessage()

    def get_users(self):
        """
        Returns a list of RR users
        :return:
        :rtype: list
        """

        users = set()

        try:
            self.tcp.userGet("X")  # dummy call to fetch users list

            users_no = self.tcp.users.count()

            for i in range(0, users_no):
                users.add(self.tcp.users.at(i).name)

            # Get unregistered users list
            n_jobs = self.jobs.getMaxJobs()
            logging.debug("Number of jobs: " + str(n_jobs))
            for i in range(0, n_jobs):
                users.add(self.jobs.getJobMinInfo_queue(i).userName)

        except Exception as e:
            logging.error("couldn't get users list: "+str(e))

        users_list = list(users)
        users_list.sort(key=lambda v: v.upper())

        return users_list

    @staticmethod
    def get_log_path(name):
        """
        Returns the path of the log file
        :param name:
        :return:
        """

        path = ""
        app_path = "logs"
        system_log_path = os.path.sep.join([os.environ["RR_ROOT"], "sub", "log"])

        if name in os.listdir(app_path):
            path = app_path
        elif name in os.listdir(system_log_path):
            path = system_log_path

        return path

    @staticmethod
    def get_log_file_content(name):
        """
        Returns a log file
        :param name:
        :return:
        """

        content = ""

        app_path = "logs"
        system_log_path = os.path.sep.join([os.environ["RR_ROOT"], "sub", "log"])

        if name in os.listdir(app_path):
            with open(os.path.sep.join([app_path, name])) as f:
                content = f.read()
        elif name in os.listdir(system_log_path):
            with open(os.path.sep.join([system_log_path, name])) as f:
                content = f.read()

        return content.decode('utf-8', 'ignore')

    @staticmethod
    def get_log_files():
        """
        Returns a list of available log file names
        :return:
        :rtype: list
        """

        files = []
        names = os.listdir("logs")
        for n in names:
            if os.path.isfile(os.path.sep.join(["logs", n])):
                files.append(n)

        return files

    @staticmethod
    def get_syslog_files():
        """
        Returns a list of available system log file names
        :return:
        :rtype: list
        """

        files = []

        path = os.path.sep.join([os.environ["RR_ROOT"], "sub", "log"])
        if os.path.exists(path):
            names = os.listdir(path)
            for n in names:
                if os.path.isfile(os.path.sep.join([path, n])):
                    files.append(n)

        return files

    def get_stats(self):
        """
        Returns tcp and mem stats
        :return:
        :rtype: dict
        """

        stats = {}

        try:
            stats["memUsage"] = self.tcp.getMemUsage()/1024/1024
            stats["connectionStats"] = self.tcp.connectionStats()
            stats["connectionStatsJSON"] = json.loads(self.tcp.connectionStatsJSON())
            if not self.tcp.infoGetGlobalInfo():
                stats["infoGlobal"] = self.tcp.errorMessage()
            else:
                stats["infoGlobal"] = self.prettify(self.tcp.infoGlobal())

        except Exception as e:
            logging.error("Error getting stats: "+str(e))

        return stats

    def prettify(self, text):
        """
        Returns list of tables. Each table is a list lines (tr), each line a list of elements (td)
        :param text:
        :type text: str
        :return:
        :rtype: list
        """

        tables = text.split("\n\n")
        out = []

        for table in tables:
            if table == "":
                continue
            rows = table.split("\n")
            table_rows = []

            for i, row in enumerate(rows):
                if row:
                    blocks = row.split("  ")
                    for _ in range(0, blocks.count("")):
                        blocks.remove("")
                    if row.startswith("        "):
                        blocks.insert(0, "")

                    table_rows.append(blocks)

            if table_rows:
                out.append(table_rows)

        return out

    def fetch_clients(self):
        """
        Fetches clients info
        :return:
        :rtype: bool
        """
        try:
            if not self.tcp.clientGetList():
                logging.error("Error getting clients: " + self.tcp.errorMessage())
                return False
            else:
                self.clients = self.tcp.clients
                n_clients = self.clients.count()
                logging.info("Number of clients found: " + str(n_clients))
                return True
                # for i in range(0, nbClients):
                #     cl = self.clients.at(i)
                #     print("\tCpuUsage %6.2f name: %s" % (cl.CPU_Usage, cl.name))
        except AttributeError as e:
            logging.error("Unknown attribute fetching clients: " + str(e))
        except Exception as e:
            logging.error("Unable to fetch clients: " + str(e))

    def get_client_groups(self, update=False):
        """
        Returns a list of client group names
        :return:
        :rtype: list
        """
        groups_set = set()

        if update:
            self.fetch_clients()

        try:
            groups = self.tcp.clientGetGroups()

            for c_idx in range(groups.count):
                groups_set.add(groups.clientGroup(c_idx).getName())

        except Exception as e:
            logging.error("Could not get client groups: " + str(e))

        groups_list = list(groups_set)
        groups_list.sort()

        return groups_list

    def get_clients_by_group(self, group):
        """
        Returns a list of clients in a group
        :param group:
        :type group: str
        :return:
        :rtype: list
        """

        clients = []

        self.update()

        try:
            groups = self.tcp.clientGetGroups()
            matching_group = None
            for g_id in range(groups.count):
                _group = groups.clientGroup(g_id)
                if _group.getName() == group:
                    matching_group = _group
                    break
            if not matching_group:
                logging.warning("Could not find group: " + group)
                return clients

            for c_idx in matching_group.allMemberGlobalIndices().split(","):
                clients.append(self.get_client(int(c_idx)))

        except AttributeError as e:
            logging.error("Error get_clients_by_group(A): " + str(e))
        except Exception as e:
            logging.error("Error get_clients_by_group(E): " + str(e))

        return clients

    def get_client(self, index):
        """
        Get client info dict by index
        :param index:
        :type index: int
        :return:
        :rtype: dict
        """

        # the result of dir(tcp.clients.at(index)) is:
        # ['CPU_Usage', 'GPU_Usage', 'StructureID', 'VariablesID', '__class__', '__delattr__', '__dict__', '__doc__',
        # '__format__', '__getattribute__', '__hash__', '__init__', '__instance_size__', '__module__', '__new__',
        # '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__',
        # '__weakref__', 'isRunningAsService', 'localTextureSpaceUsed', 'loggedUser', 
        # 'maxJobThreads', 'name', 'noUserInteraction', 'tempHDD', 'version']
        # NB the 'version' filed throws a missing python converter exception

        out = OrderedDict()

        try:
            client = self.clients.at(index)

            status_class = self.client_status_to_class(self.clients.clientStatus(index))

            cpu_usage = round(client.CPU_Usage, 2)
            gpu_usage = round(client.GPU_Usage, 2)

            out = {'ID': index, 'CPU_Usage': cpu_usage, 'GPU_Usage': gpu_usage,
                   'StructureID': client.StructureID,
                   'VariablesID': client.VariablesID, 'isRunningAsService': client.isRunningAsService,
                   'localTextureSpaceUsed': client.localTextureSpaceUsed, 'loggedUser': client.loggedUser,
                   'maxJobThreads': client.maxJobThreads,
                   'name': client.name, 'noUserInteraction': client.noUserInteraction, 'tempHDD': client.tempHDD,
                   'version': client.version, 'status': self.clients.clientStatus(index), 'statusClass': status_class}
        except AttributeError as e:
            logging.error("Error get_client(A):" + str(e))
        except Exception as e:
            logging.error("Error get_client(E): "+str(e))

        return out

    def get_client_by_name(self, name):
        """
        Returns client info by name
        :param name:
        :type name: str
        :return:
        """

        out = OrderedDict()

        try:

            for c_idx in range(self.clients.count()):
                _client = self.clients.at(c_idx)
                if _client.name.lower() == name:
                    client = _client
                    break

            status_class = self.client_status_to_class(self.clients.clientStatus(c_idx))

            cpu_usage = round(client.CPU_Usage, 2)
            gpu_usage = round(client.GPU_Usage, 2)

            out = {'ID': c_idx, 'CPU_Usage': cpu_usage, 'GPU_Usage': gpu_usage,
                   'StructureID': client.StructureID,
                   'VariablesID': client.VariablesID, 'isRunningAsService': client.isRunningAsService,
                   'localTextureSpaceUsed': client.localTextureSpaceUsed, 'loggedUser': client.loggedUser,
                   'maxCoresSetForJob': client.maxCoresSetForJob, 'maxJobThreads': client.maxJobThreads,
                   'name': client.name, 'noUserInteraction': client.noUserInteraction, 'tempHDD': client.tempHDD,
                   'version': client.version, 'status': self.clients.clientStatus(c_idx), 'statusClass': status_class}
        except AttributeError as e:
            logging.error("Error get_client_by_name(A): "+str(e))
        except Exception as e:
            logging.error("Error get_client_by_name(E): "+str(e))

        return out

    @staticmethod
    def client_status_to_class(status):
        """
        Transforms the client Status field to a valid CSS class name
        :param status: client status string
        :type status: basestring
        :return:
        :rtype: basestring
        """

        status_words = set(str(status).lower().split(" "))

        if {"off", "shut", "shutdown"} & status_words:
            return "Off"
        elif "idle" in status_words:
            return "Idle"
        elif {"render", "rendering"} & status_words:
            if "successfull" in status_words:
                return "Idle"
            else:
                return "Rendering"
        elif "waiting" in status_words:
            return "Waiting"
        elif {"crashed", "frozen"} & status_words:
            return "Error"
        elif {"disabled", "deactivated", "hours"} & status_words:
            return "Disabled"

        return "Idle"

    def set_job_filter(self, job_filter=None, username="", project="", render_app="",
                       age=0, includes="", filter_mask=None, invert=False):
        """

        :param job_filter: JobFilter instance
        :type job_filter: JobFilter
        :param username: job user name
        :type username: basestring
        :param project: job project
        :type project: basestring
        :param render_app: render application
        :type render_app: basestring
        :param age: jobs age in days (unused)
        :type age: int
        :param includes: includes string
        :type includes: basestring
        :param filter_mask: additive mask 1-2-4-8-16 -> NotRendering-Rendering-Disabled-Waiting-Finished
        :type filter_mask:
        :param invert: invert the includes condition (unused)
        :type invert: bool
        :return:
        """

        if job_filter:
            username = str(job_filter["username"])
            project = str(job_filter["project"])
            render_app = str(job_filter["render_app"])
            age = job_filter["age"]
            includes = str(job_filter["includes"])
            invert = job_filter["invert"]
            filter_mask = job_filter["filter_mask"]
        else:
            username = str(username.replace(JobFilter.ALL_STRING, ""))
            project = str(project.replace(JobFilter.ALL_STRING, ""))
            render_app = str(render_app.replace(JobFilter.ALL_STRING, ""))
            includes = str(includes)

        try:
            if filter_mask is None:
                filter_mask = rrLib._filterIDs.isAll
            self.tcp.jobList_SetFilter3(username, project, render_app, age, includes, invert, filter_mask)
        except AttributeError as e:
            logging.error("Unknown attribute setting jobs filter" + str(e))
        except Exception as e:
            logging.error("Unable to set jobs filter: " + str(e))

    def fetch_jobs(self):
        """
        Fetches jobs for user username
        :return:
        """

        try:
            # if not tcp.jobGetInfoBasic(): //use this command if you do not need the full information about a job
            if not self.tcp.jobList_GetInfo():
                exception = Exception("Error getting jobs: " + self.tcp.errorMessage())
                raise exception
            else:
                self.jobs = self.tcp.jobs
                logging.info("Number of jobs fetched: " + str(self.jobs.getMaxJobs()))
        except Exception as e:
            logging.error("Error fetch_jobs(E):" + str(e))

    def get_job_apps(self):
        """
        Returns a dict of jobs IDs organized by Application
        :return:
        """

        apps_dict = defaultdict(list)

        try:
            n_jobs = self.jobs.getMaxJobs()
            logging.info("Number of jobs: " + str(n_jobs))
            for i in range(0, n_jobs):
                job_id = self.jobs.getJobMinInfo_queue(i).ID
                apps_dict[self.jobs.getJobMinInfo_queue(i).rendererName].append(job_id)
        except Exception as e:
            logging.error("Error get_job_apps(E): "+ str(e))

        return apps_dict

    def get_job_groups(self, update=False, filtered=False):
        """
        Returns a dict of job IDs organized by companyProjects
        :return:
        """

        if update:
            self.update()

        if filtered:
            return self.job_groups_filtered
        else:
            return self.job_groups

    def get_job_groups_snapshot(self, job_filter):
        """
        This method gathers all the infos needed to present a snapshot of the available jobs and render the jobs page
        :param job_filter:
        :type job_filter: JobFilter
        :return:
        :rtype: JobGroupsSnapshot
        """

        snapshot = JobGroupsSnapshot()
        self.set_job_filter(job_filter)

        self.update()

        snapshot.job_groups = self.job_groups
        snapshot.users = self.get_users()
        snapshot.apps = self.get_job_apps()
        snapshot.job_groups_filtered = self.job_groups_filtered

        return snapshot

    def _update_job_groups(self):
        """
        Updates a dict of job IDs organized by companyProjects
        :return:
        """

        groups_dict = defaultdict(list)
        filtered_groups_dict = defaultdict(list)

        try:
            n_jobs = self.jobs.getMaxJobsFiltered()
            logging.debug("Number of jobs - filtered: " + str(n_jobs))
            for i in range(0, n_jobs):
                filtered_groups_dict[self.jobs.getJobMinInfo_filterQueue(i).companyProjectName] \
                    .append(self.jobs.getJobMinInfo_filterQueue(i).ID)

            n_jobs = self.jobs.getMaxJobs()
            logging.debug("Number of jobs: " + str(n_jobs))
            for i in range(0, n_jobs):
                groups_dict[self.jobs.getJobMinInfo_queue(i).companyProjectName] \
                    .append(self.jobs.getJobMinInfo_queue(i).ID)

        except Exception as e:
            logging.error("Error _update_job_groups(E): "+ str(e))

        self.job_groups = groups_dict
        self.job_groups_filtered = filtered_groups_dict

    def get_jobs_by_group(self, group, groups_dict=None, filtered=False):
        """
        Returns a list of job IDs for all the jobs belonging to a group
        :param group: group name
        :param groups_dict: a group dictionary if provided
        :type groups_dict: dict
        :param filtered: if true list only the filtered groups
        :type filtered: bool
        :return:
        :rtype: list
        """

        if not groups_dict:
            if filtered:
                groups_dict = self.job_groups_filtered
            else:
                groups_dict = self.job_groups

        ids = groups_dict[group]
        jobs = []

        try:
            for job_id in ids:
                jobs.append(self.get_job_by_id(job_id))

        except Exception as e:
            logging.error("Error get_jobs_by_group(E) "+ str(e))

        jobs.reverse()  # ID order needs to be reversed so most recent is first

        return jobs

    def get_jobs_by_project(self, project, filtered=False):

        jobs = []

        self.update()

        if filtered:
            groups_dict = self.job_groups_filtered
        else:
            groups_dict = self.job_groups

        if project in groups_dict:
            jobs = self.get_jobs_by_group(project, filtered=filtered)

        return jobs

    def get_job_by_id(self, job_id):
        """
        Get job information @index in queue
        :param job_id:
        :return:
        :rtype: dict
        """

        # the result of dir(jobs.getJobMinInfo_filterQueue(i))
        # ['ID', 'IDmain', 'IDpre', 'IDstr', '__class__', '__delattr__', '__dict__', '__doc__', '__format__',
        #  '__getattribute__', '__hash__', '__init__', '__instance_size__', '__module__', '__new__', '__reduce__',
        #  '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__',
        #  'companyProjectName', 'filterMask', 'm_queueIDAtServer', 'rendererName', 'userName']
        # Where IDmain, IDpre IDstr are methods

        # the result of dir(jobs.getInfoSend(ID)) where ID = jobs.getJobMinInfo_filterQueue(i).ID
        # ['ID', 'IDmain', 'IDpre', 'IDstr', 'IDstrFull', '__class__', '__delattr__', '__dict__', '__doc__',
        # '__format__',
        #  '__getattribute__', '__hash__', '__init__', '__instance_size__', '__module__', '__new__', '__reduce__',
        #  '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__',
        #  'additionalCommandlineParam', 'authStr', 'averageMemoryUsage', 'camera', 'channel', 'channelCount',
        #  'channelExtension', 'channelExtension_set', 'channelFileName', 'channelFileName_set', 'channel_add',
        #  'channel_clear', 'channel_set', 'check_lastExecution', 'clientAssigned', 'clientAssigned_Set', 'clientNeed',
        #  'clientValue_Get', 'clientsRenderingCount', 'companyProjectName', 'customDataSet_Str',
        #  'customDataSet_StrByID',
        #  'customDataSet_UserInfo', 'customData_AllAsString', 'customData_ClearAll', 'customData_NameByID',
        #  'customData_Str', 'customData_StrByID', 'customData_UserInfo', 'customData_maxIDs', 'customOption',
        #  'customOption_Set', 'customOptionsCount', 'customSeqName', 'customSet_Str', 'customSet_StrByID',
        #  'customSet_UserInfo', 'customShotName', 'customVersionName', 'custom_AllAsString', 'custom_ClearAll',
        #  'custom_NameByID', 'custom_Str', 'custom_StrByID', 'custom_UserInfo', 'custom_maxIDs', 'dateSend',
        #  'disabled',
        #  'errorCount', 'errorCountServer', 'fileNumber2jobNumber', 'fileserverTimeDifference',
        #  'fileserverTimeDifferenceOffset', 'foldersearchtime', 'framesDone', 'framesLeft', 'framesPlaceholderFound',
        #  'framesTotal', 'framesTotalNonMulti', 'framesUnAssignedFoundNr', 'getError', 'getLog', 'imageDir',
        #  'imageExtension', 'imageFileName', 'imageFileNameVariables', 'imageFormatOverride', 'imageFramePadding',
        #  'imageHeight', 'imageMulti', 'imagePreNumberLetter', 'imageSingleOutputFile', 'imageStereoL', 'imageStereoM',
        #  'imageStereoR', 'imageWidth', 'infoAnalyse_done', 'infoAnalyse_error', 'infoAnalyse_info',
        #  'infoAnalyse_warning', 'infoAverageClientPS', 'infoAverageClients', 'infoAverageFrameTime',
        #  'infoLastFrameDone', 'infoTotalAborted', 'infoTotalCrashed', 'infoTotalLimitsReached', 'infoTotalSend',
        #  'isRendering', 'jobFilesFolderName', 'jobNumber2fileNumber', 'jobNumber2multiID', 'lastErrorEmail',
        #  'lastInfoChanged', 'lastSettingsChanged', 'layer', 'localTexturesCount', 'localTexturesFile',
        #  'localTexturesSizeMB', 'logCount', 'm_check_interval', 'maxMemoryUsage', 'maxWaitForPreID', 'notifyFinish',
        #  'notifyFinishClientName', 'notifyFinishParam', 'notifyFinishWhen', 'overrideIcon', 'preID', 'prePostCommand',
        #  'prePostCommandCount', 'prePostCommand_Set', 'previewFilenameA', 'previewFilenameRGB',
        #  'previewFilenameThumbnail', 'previewID2FrameNr', 'previewStart', 'priority', 'queueIDAtServer', 'renderApp',
        #  'renderTimeSum_Ghz_h', 'renderTimeSum_PS', 'renderTimeSum_seconds', 'renderTime_remaining_PS',
        #  'renderTime_remaining_seconds', 'renderTime_seconds', 'requiredLicenses', 'rrJobOS', 'rrOption',
        #  'rrOption_Set', 'rrParam', 'rrParam_Set', 'sceneDatabaseDir', 'sceneDisplayName', 'sceneName', 'sceneOS',
        #  'scriptPreviewExecuted', 'seqDivMax', 'seqDivMin', 'seqDivideEnabled', 'seqEnd', 'seqFileOffset',
        #  'seqFrameSet', 'seqIsFloatFrames', 'seqStart', 'seqStep', 'shotgunID', 'splitImageFileInto_DirFileExt',
        #  'status', 'statusAsString', 'structureIDBasics', 'structureIDSend', 'submitMachine', 'timeFinished',
        #  'timeToEnable', 'uiIsChecked', 'userApproved', 'userName', 'variablesIDBasics', 'variablesIDSend',
        #  'waitForPreID', 'waitForPreID_set']

        out = OrderedDict()

        try:
            job = self.jobs.getJobSend(job_id)
            out["IDstr"] = job.IDstr()
            out["sceneDisplayName"] = job.sceneDisplayName()
            out["statusAsString"] = job.statusAsString()

            for field in dir(job):
                try:
                    attr = getattr(job, field)
                    if not (field.startswith("_") or inspect.ismethod(attr)):
                        out[field] = attr
                except Exception as e:
                    logging.warning("Job field " + field + " is not accessible: " + str(e))

            # additional css classes
            out["statusClass"] = (out["statusAsString"]).split(" ")[0]
            out["withClientsClass"] = "withClients" if int(job.clientsRenderingCount) > 0 else ""

            # error icon
            out["errorIcon"] = "empty.png"  # default
            if job.errorCountServer == 0:
                if job.errorCount > 0:
                    out["errorIcon"] = "error_yellow.png"
                elif job.errorCount > 6:
                    out["errorIcon"] = "error_orange.png"
                elif job.errorCount > 14:
                    out["errorIcon"] = "error_red.png"
            elif job.errorCountServer > 0:
                if job.errorCount > 0:
                    out["errorIcon"] = "error_yellowfill.png"
                elif job.errorCount > 6:
                    out["errorIcon"] = "error_orangefill.png"
                elif job.errorCount > 14:
                    out["errorIcon"] = "error_redfill.png"

            # app icon
            # TODO this association is better to be moved to the DB
            out["appName"] = job.renderApp.name
            appname = job.renderApp.name.lower().replace(" ", "").replace("_", "")
            if "maya" in appname:
                out["appIcon"] = "3D02__Maya.png"
            elif "blender" in appname:
                out["appIcon"] = "blender.png"
            elif "cinema4d" in appname:
                out["appIcon"] = "3D05__Cinema4d.png"
            elif "3dsmax" in appname:
                out["appIcon"] = "3D03__3dsMAX_s.png"
            elif "harmony" in appname:
                out["appIcon"] = "2D01__Harmony.png"
            elif "softimage" in appname:
                out["appIcon"] = "3D01__Softimage.png"
            elif "afx" in appname:
                out["appIcon"] = "C12__Afx.png"
            elif "lightwave" in appname:
                out["appIcon"] = "3D04__Lightwave.png"
            elif "houdini" in appname:
                out["appIcon"] = "3D06__Houdini.png"
            elif "terragen" in appname:
                out["appIcon"] = "3D07__Terragen.png"
            elif "modo" in appname:
                out["appIcon"] = "3D08__Modo.png"
            elif "katana" in appname:
                out["appIcon"] = "3D16__Katana.png"
            elif "nuke" in appname:
                out["appIcon"] = "C13__Nuke.png"
            else:
                out["appIcon"] = "empty.png"

            # Timestamps
            out["Until now"] = timeformat(job.renderTime_seconds)
            out["Remaining"] = timeformat(job.renderTime_remaining_seconds)
            out["dateSend"] = job.dateSend.strftime("%b %d, %H:%M:%S")

        except Exception as e:
            logging.error("Error getting JobSend info: " + str(e))

        if 'infoAverageFrameTime' in out and 'infoAverageFrameTime_FramesReturned' in out:
            out['frameTimeString'] = seconds_to_minutes(out['infoAverageFrameTime_FramesReturned']) + " (~ "\
                                     + seconds_to_minutes(out['infoAverageFrameTime']) + ")"

        if 'maxMemoryUsage' in out:
            out['maxMemoryUsageGiB'] = "{0:.1f}".format(out['maxMemoryUsage'] / 1024.0)

        return out

    def send_jobs_command(self, jobs, command, *args, **kwargs):
        """
        Sends a commands to all jobs in list
        :param jobs: job IDs
        :type jobs: list
        :param command: command string
        :type command: basestring
        :return: success or fail (true or false)
        :rtype: bool
        """

        if command.lower() not in self.job_commands:
            message = "Command not implemented: " + command
            logging.error(message)
            return [False, message]

        jobs = map(int, jobs)

        command_id = getattr(rrJob._LogMessage, self.job_commands[command.lower()])

        if 'parameter' in kwargs:
            parameter = kwargs['parameter']
        else:
            parameter = 0

        try:
            if not self.tcp.jobSendCommand(jobs, command_id, parameter):
                message = self.tcp.errorMessage()
                logging.error("Unable to send jobs Command: " + command + "\n" + message)
                return [False, message]
        except Exception as e:
            
            logging.error(str(e))
            return [False, "Unkonwn Error: " + str(e)]

        return [True, ""]

    def send_clients_command(self, clients, command, *args, **kwargs):
        """
        Sends command to list of clients
        :param clients: clients IDs
        :type clients: list
        :param command: command string
        :type command: basestring
        :param args:
        :param kwargs: parameter argument is a string
        :return: success or fail (true or false) and message
        :rtype: [bool, str]
        """

        if command.lower() not in self.client_commands:
            message = "Command not implemented: " + command
            logging.error(message)
            return [False, message]

        command_id = getattr(rrLib._ClientCommand, self.client_commands[command.lower()])

        if 'parameter' in kwargs:
            parameter = kwargs['parameter']
        else:
            parameter = ""

        try:
            if not self.tcp.clientSendCommand(clients, command_id, parameter):
                message = self.tcp.errorMessage()
                logging.error("Unable to send clients Command: " + command + "\n" + message)
                return [False, message]
        except Exception as e:
            logging.error(str(e))
            return [False, "Unkonwn Error: " + str(e)]

        return [True, ""]


session_apis = {}

if __name__ == "__main__":
    server_api = ServerApi()
    from src.rrUtils import JobFilter

    _filter = JobFilter()
    _filter["Finished"] = True
    server_api.set_job_filter(_filter)
