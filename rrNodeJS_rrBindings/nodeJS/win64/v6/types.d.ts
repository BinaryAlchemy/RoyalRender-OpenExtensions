/**
 * @fileOverview Types for the NodeJS C++ Addon for the powerfull Royal Render
 * @author <a href="https://github.com/Novalis15">Robin Dürhager</a>
 * @version 1.0.0
 */

export interface rrBinding {
    /**
     * @description creates a new TCP object for connecting the application with the rrServer
     */
    rrTCP(): libNodeRR2.rrTCP;
    rrGlobal(): rrGlobal.rrGlobal;
    datafiles(): libNodeRR2_datafiles.DataFiles;
    createUserSettings(): libNodeRR2.rrUserSettings;
    createRRJob(): Job.rrJob;
    rrUint64(): Utils.rrUint64;
    _dataIDs: libNodeRR2._EdataIDs;
    _filterIDs: libNodeRR2._EfilterIDs;
    _sortIDs: libNodeRR2._EsortIDs;
}

declare namespace libNodeRR2 {
    interface rrTCP {
        /**
         * @description Requires to call any jobGet..() function.

        */
        readonly jobs: _rrTCPjobList;

        /**
         * @description Requires to call  clientGetList() first.
         */
        readonly clients: _rrTCPclientList;

        /**
         * @description Requires to call userGet() first.
         */
        readonly users: _rrTCPuser;

        // ----- MISC -----

        /**
         * @description This function tries to get the rrServer name or IP from the RR folder in your company. It uses the RR_ROOT environment variable installed by rrWorkstationInstaller. Therefore it does only work in your company. If you want to connect from outside your company, you have to use a DynDNS service.
         */
        getRRServer(): string;

        /**
         * @description Sets the server IP or name for all TCP connections.
         * @param ip The rrServer IP
         * @param port The rrServer port
         * @returns boolean
         */
        setServer(ip: string, port: number): boolean;

            /**
         * @description Sets the login to retrieve any data from the rrServer. This is not required if you have setup a Intranet Whitelist in rrConfig, tab rrLogins.
         * @param user The Username you want to log into
         * @param password the password of the specified user
         */
        setLogin(user: string, password: string): void;

        /**
         * @description If there was any error, then this function will return a non-empty string. Else it will return undefined.
         * @returns An error message for more detail
         */
        errorMessage(): string;

        /**
         * @returns _rrGlobalInfo Object - Global info about the rrServer Application like how many WOlAble Clients there are, etc.
         */
        getGlobalInfo(): _rrGlobalInfo;

        /**
         * @description Returns the current memory usage of _rrTCP.
         * @returns string
         */
        getMemUsage(): number;

        /**
         * @description Information about the last connections.
         */
        connectionStats(): string;

        /**
         * @description Information about the last connections.
         */
        connectionStatsJSON(): string;

        // ----- JOBS -----
        /**
         * @description jobSetFilter() controls which jobs are send from the rrServer. You should always use this if you have a lot of jobs in the queue to reduce network traffic, rrServer workload and python memory usage. Filter is a bit mask of enumeration _filterIDs values. Use | to combine multiple filters.
         * @param jobUserName User name of the searched job
         * @param project Name of the whole Project
         * @param renderApp Name of the renderApp which is used
         * @param jobContains Substring of the searched Jobname
         * @param filterID a _filterID property which mimiks a bit mask - NOT YET IMPLEMENTED IN NODE ADDON
         */
        jobSetFilter(jobUserName?: string, project?: string, renderApp?: string, jobContains?: string, filterID?: number): void;

        /**
         * @description You should call jobSetFilter() first to get only jobs with that you need to reduce network traffic. 1.Retrieves the job info of job with {ID} jobID. If jobID is 0, then it updates all jobs that match the filter. 2. Retrieves _MinInfo of all jobs.
         * @param jobID the JobID of a specific Job you want to fetch from the server
         */
        jobGetInfoBasic(jobID?: Utils.rrUint64): boolean;

        /**
         * @description You should call jobSetFilter() first to get only jobs with that you need to reduce network traffic. 1.Retrieves the job detail of job with {ID} jobID. If jobID is 0, then it updates all jobs that match the filter. 2. Retrieves _MinInfo of all jobs. 
         * @param jobID the JobID of a specific Job you want to fetch from the server - HANGS WHEN USED
         */
        jobGetInfoSend(jobID?: Utils.rrUint64): boolean;

        /**
         * @description jobIDs is a list with JobIDs of jobs that you want to send a command to. Please check errorMessage() if the function returns false.
         * @param jobIDs A JobID Array which describes the jobs you want to send a command to
         * @param commandID The _logMessage enum which describes the command you want to send the jobs
         * @param parameter Additional Parameter for the jobSendCommand function
         * @returns true if the operation succeeded
         */
        jobSendCommand(jobIDs: Utils.rrUint64[], commandID: number, parameter: number): boolean;

        /**
         * @description jobIDs is a list with JobIDs of jobs that you want to change. You need to call rrJob.getClass_SettingsOnly() to get a _SettingsOnly class. This function uses two _SettingsOnly classes. The settings parameter is the one with all the new values you want to set. The changeFlags tells RR which parameters you want to change. E.g. if you want to change the user name for all jobs, but all jobs should keep their sequence start-end. To let RR know that you want to change this value, just assign a value to them. (bool values to true, integer to 1, strings to e.g. "1".) If the function returns false, then please check errorMessage().
         * @param jobID A JobID Array which describes the jobs you want to modify
         * @param settings The new properties for the specified jobs
         * @param changeFlags Defines what should be changed in the specified jobs (e.g.: username, but not job sequence)
         * @returns true if the operation succeeded
         */
        jobModify(jobID: Utils.rrUint64[], settings: Job._SettingsOnly, changeFlags: Job._SettingsOnly): boolean;

        /**
         * @description Submits a new job to the rrServer. We recommend that you use .xml files and use the rrSubmitterconsole. As the rrSubmitterconsole does many checks and conversions. Use this function only if you know all required settings for your jobs (e.g. imageFileNameVariables for Maya jobs) See RR/SDK/external/submit.py for an example script.
         * @param newJob a _JobBasics object which defines the job you want to add to rrServer
         * @param overrideParameter Additional parameters which should be passed to RR when submitted
         * @returns true if the operation succeeded
         */
        jobSubmitNew(newJob: Job._JobBasics, overrideParameter: string): boolean;

        /**
         * @description Returns the time the rrServer had when jobGetInfoBasic() or jobGetInfoSend() was called. If it was copied before the job list was retrieved, then it can be used to check which was changed.
         * @returns The time the rrServer had when jobGetInfoBasic() or jobGetInfoSend() was called.
         */
        lastUpdateJobs_ServerTime(): Date;

        /**
         * @description Returns the time this machine had had when jobGetInfoBasic() or jobGetInfoSend() was called.
         * @returns The time the rrServer had when jobGetInfoBasic() or jobGetInfoSend() was called.
         */
        lastUpdateJobs_OurTime(): Date;

        // ----- CLIENTS -----
        /**
         * @description gets all the registered clients from the rrServer and stores it into the clients property of the rrTCP
         * @returns boolean
         */
        clientGetList(): boolean;

        /**
         * @description Sends a command to rrClients. clientArray is a list with client IDs. If the list has only one element and the ID is -1, then the command is applied to all clients. param is an optional string parameter. It can be used to send commandlines to the client with the commandID _rrTCP._ClientCommand.cCommandLine If the function returns false, then please check errorMessage().
         * @param clientArray An array of client IDs which should receive the new command.
         * @param ID The ClientCommandID of the Command which should be send to the clients.
         * @param param Additional parameters which should be send with the new command.
         * @returns true if the operation succeeded.
         */
        clientSendCommand(clientArray: number[], ID: rrGlobal._EClientCommand, param?: string): boolean;

        // ----- USER -----
        /**
         * @description Gets all or only a specified user. The result of this request is filled into the .user parameter.
         * @param input IMPORTANT: Needs a non-zero String
         * @returns true if the operation succeeded - stores all Users in tcp.users
         */
        userGet(input: string): boolean;

        /**
         * @description After you retrieved a _rrTCPuser class and changed a few values, you have to send that user back to the rrServer/rrConfig. If the password is empty, then it will not be changed by the rrServer. Returns false if there was an error. Use userWasPartialFail() (NOT YET IMPLEMENTED IN NODE ADDON) to know if all settings have been applied. The rrServer sends the user class back with the current values.
         * @param user The modified user Object
         * @returns true if the operation succeeded
         */
        userModify(user: rrUserSettings): boolean;

        /**
         * @description After you got a new user via getNewUserPreset(), you have to send it to the rrServer/rrConfig. Returns false if there was an error. Use userWasPartialFail() (NOT YET IMPLEMENTED IN NODE ADDON) to know if all settings have been applied. The rrServer sends the user class back with the current values.
         * @param user The new user which should be added to the rrServer
         * @returns true if the operation succeeded
         */
        userNew(user: rrUserSettings): boolean;
    }

    interface _rrTCPuser {
        /**
         * @param userID ID of the user you want to get - int
         * @returns a user from the tcp.users list
         */
        at(userID: number): rrUserSettings;
    
        /**
         * @returns a new user Preset
         */
        getNewUserPreset(): rrUserSettings;
    
        /**
         * @returns a new anonymous user preset
         */
        getAnonymous(): rrUserSettings;
    
        /**
         * @returns the currently logged in user
         */
        getOurUser(): rrUserSettings;
    
        /**
         * @returns the number of users currently known in rrServer
         */
        count(): number;
    }

    interface rrUserSettings {
        name: string;
        emailAddress: string;
        userGroup: string;
        emailStatus: boolean;
        emailError: boolean;
        isAdmin: boolean;
        uniqueID: number;
        loginUser: string;
        mapUNC: string;
        mapLocal: string;
        userAdded: Date;
        lastUsed: Date;
    }

    interface _rrTCPjobList {
        /**
         * @description Tells you which data class is currently available for that job.
         * @param jobID The ID of the job you want to know the DataType of.
         * @returns one of the following _dataIDs enums as number values: jlNone  |   jlMinInfo   |   jlBasic   |   jlSend
         */
        getJobDataType(jobID: Utils.rrUint64): _EdataIDs;
    
        /**
         * @description Fetches the MinInfo of a job from the rrServer.
         * @param jobID ID of the job you want to get the min info from.
         * @returns The minimum information of a Job.
         */
        getJobMinInfo(jobID: Utils.rrUint64): Job._JobMinInfo;
    
        /**
         * @description If there is no _JobBasics for this job, then an empty job is returned. It has some fields like scene name set to ??..
         * @param jobID ID of the job you want to get the basic info from.
         * @returns The basic information of a Job.
         */
        getJobBasic(jobID: Utils.rrUint64): Job._JobBasics;
    
        /**
         * @description If there is no _JobSend for this job, then it returns getJobBasic().
         * @param jobID ID of the send job.
         * @returns The job which has been send.
         */
        getJobSend(jobID: Utils.rrUint64): Job._JobSend;
    
        /**
         * @description Returns the time this job object was updated by jobGetInfoBasic() or jobGetInfoSend(). The time is the rrServer time. Note: This is not the last time the job was changed. Use job.lastSettingsChanged or job.lastInfoChanged to get that information.
         * @param jobID ID of the job you want to get the updated Time for.
         * @returns the time this job object was updated by jobGetInfoBasic() or jobGetInfoSend().
         */
        getJobUpdatedTime(jobID: Utils.rrUint64): Date;
    
        /**
         * @returns Total number of jobs in RR.
         */
        getMaxJobs(): number;
    
        /**
         * @description for a loop with getMaxJobs().
         * @param ID the queueID
         * @returns NULL if queueID is invalid, else a _JobMinInfo Object
         */
        getJobMinInfo_queue(ID: number): Job._JobMinInfo;
    
        /**
         * @returns Total number of jobs in your filtered list
         */
        getMaxJobsFiltered(): number;
    
        /**
         * @description for a loop with getMaxJobsFiltered().
         * @param ID queueID
         * @returns a _JobMinInfo Object
         */
        getJobMinInfo_filterQueue(ID: number): Job._JobMinInfo;
    }

    interface _EdataIDs {
        readonly jlNone: number;
        readonly jlMinInfo: number;
        readonly jlBasic: number;
        readonly jlSend: number;
    }
    
    interface _EfilterIDs {
        readonly isIdle: number;
        readonly isRendering: number;
        readonly isDisabled: number;
        readonly isWaitFor: number;
        readonly isFinished: number;
        readonly isAll: number;
    }
    
    interface _EsortIDs {
        readonly sQueue: number;
        readonly sUser: number;
        readonly sDateSend: number;
        readonly sPriority: number;
        readonly sProject: number;
        readonly sCustomName: number;
        readonly sRenderApp: number;
        readonly sApproved: number;
        readonly sFramesLeft: number;
        readonly sFramesDone: number;
        readonly sTimeRemaining: number;
        readonly sStatus: number;
        readonly sScene: number;
        readonly sLayer: number;
        readonly sCamera: number;
        readonly sFrameTime: number;
    }

    interface _rrTCPclientList {
        /**
         * @description Retrieves a client by its ID from the rrServer
         * @param clientID the clientID of the client we want to investigate further
         */
        at(clientID: number): Client._ClientStatus;
        /**
         * @description Fetches the amount of registered clients which were returned by the clientGetList() function
         */
        count(): number;
        /**
         * @description Retrieves the current status of the specified client
         * @param clientID The clientID of the client we want to investigate further
         */
        clientStatus(clientID: number): string;
    }

    interface _rrGlobalInfo {
            readonly time: string;
            readonly infoClientSegment: _rrInfoClientSegment;
            readonly infoWOL: _rrInfoWOL;
    }

    interface _rrInfoClientSegment {
            readonly RenderSegmentsDone: number;
            readonly RenderSegmentsTime: number;
    }
    
    interface _rrInfoWOL {
            readonly WOlAble: number;
            readonly totalClientNeed: number;
            readonly LastWOLExecute: string;
    }
}

declare namespace libNodeRR2_datafiles {
    interface DataFiles {
    
        /**
         * @description Requires to call any jobGet..() function.
         */
        getRRModuleVersion(): string
    
        /**
         * @returns The path [RR]/sub/cfg_global. It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.
         */
        getRRFolder_cfgGlobal(): string
    
        /**
         * @returns The path [RR]/sub/cfg_user. It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.
         */
        getRRFolder_cfgUser(): string
    
        /**
         * @returns The path [RR]/sub/stats. It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.
         */
        getRRFolder_cfgStats(): string
    
        /**
         * @returns The path [RR]/bin/[OS] It has to be executed from a machine in an RR environment (System variable RR_ROOT is defined). Otherwise it returns an empty string.
         */
        getRRFolder_bin(): string
    
        /**
         * @description Job information for each project, user and render application that was used. Informations like Memory usage, CPU usage, Number of jobs rendering, idle, finished, .., Number of frames rendered and frames to be rendered.
         * @returns A new _DailyStats_Data instance.
         */
        _dailyStats_data(): _DailyStats_Data;
    
        /**
         * @description Same as you see in rrControl tab "Global Info".Clients enabled, disabled, rendering. Jobs rendering, waiting Frames rendered, waiting, Server CPU usage.
         * @returns A new _rrsStatsSaveData instance.
         */
        _rrsStatsSaveData(): _rrsStatsSaveData;
    
        /**
         * @description rrClient stats with CPU usage, memory usage, current job, ...
         * @returns A new _rrClientStats_Data instance.
         */
        _rrClientStats_data(): _rrClientStats_Data;
    
        /**
         * @description This class loads the file [RR]\sub\stats\server_stats.db This statistics file is used to create the server stats in rrControl, tab Global Info. There are three different stats: "day": A 24h statistic, saved every 90seconds. "month": A 20 day statistic, saved every 30 minutes. "year": A 160 days statistic, saved every 6 hours.
         * @returns A _rrsStatsSaveDataLS instance.
         */
        _rrsStatsSaveDataLS(): _rrsStatsSaveDataLS;
    
        /**
         * @description The client group list.
         * @returns A new _ClientGroupList instance.
         */
        _ClientGroupList(): _ClientGroupList;
    
        /**
         * @description Same data as the the "frames rendered" table in rrControl. Per frame information includes Render time, Memory (5 times per frame), CPU usage (5 times per frame)
         * @returns A _frameStatJob instance.
         */
        _frameStatJob(): _frameStatJob;
    
        /**
         * @description Every time a job is finished, it adds its average frame time to a list, separated by each layer of each project. It includes the last 100 finished jobs of each layer name of each project. (For example the the last 100 jobs of render layer "Ambient Occlusion" of project "FancyDrink-Commercial")
         * @returns A new _StatsRenderTime Instance.
         */
        _StatsRenderTime(): _StatsRenderTime;
    
        /**
         * @param idx The idx of the client group.
         * @returns A new _ClientGroup instance.
         */
        _ClientGroup(idx: number): _ClientGroup;
    }

    interface _rrStatsSharedFunctions {

        /**
         * @description Loads the stats from file FileName.
         * @param FileName Filename of the file which should be loaded.
         */
        loadFromFile(FileName: string): boolean
    
        /**
         * @returns The error message in case the loadFromFile() fails.
         */
        getError(): string;
    }

    interface _DailyStats_Data extends _rrStatsSharedFunctions {

        /**
         * @param id 0 -> User stats, 1 -> Project stats, 2 -> Render app stats
         * @returns A list of statistics.
         */
        singleStats(id: number): _singleStatDay[];
    
        /**
         * @returns The number of different stat lists. Which is 3.
         */
        singleStatsMax(): number;
    }
    
    interface _singleStatDay {
    
        /**
         * @description Name of the user, project or render app.
         */
        readonly name: string;
    
        /**
         * @description 0 -> User stats, 1 -> Project stats, 2 -> Render app stats
         */
        readonly type: number;
    
        /**
         * @description Each array item contains the stats for 15 minutes of that day: 0: 00:00- 00:15 1: 00:15- 00:30 2: 00:30- 00:45 ...
         * @param idx Array idx of the statistics data.
         */
        stats(idx: number): _singleStat;
    
        /**
         * @returns The maximum number of possible _singleStat values. It always returns 96 for this RR version. (24h/96 = 15 min)
         */
        statsMax(): number;
    }
    
    interface _singleStat {
        readonly avPSUsage: number;
        readonly maxPSUsage: number;
        readonly PSneeded: number;
        readonly renderLicNeeded: number;
        readonly jobsWaiting: number;
        readonly jobsDisabled: number;
        readonly jobsIdle: number;
        readonly jobsRendering: number;
        readonly jobsDone: number;
        readonly timesSended: number;
        readonly timesFinished: number;
        readonly avMemUsageMB: number;
        readonly maxMemUsageMB: number;
        readonly avFrameTime: number;
        readonly framesRendered: number;
        readonly framesLeft: number;
        readonly avGhzUsage: number;
        readonly maxGhzUsage: number;
        clear(): void
    }
    
    interface _rrsStatsSaveDataLS extends _rrsStatsSaveData, _rrStatsSharedFunctions {
 
        /**
         * @returns The current system time in the local time zone in seconds. The system time is based on the default unix timestamp (seconds since 00:00 hours, Jan 1, 1970). 
         */
        currentLocalTime(): number;
    }
    
    interface _rrsStatsSaveData {
    
        /**
         * @description The time the last index of the day array was saved. This value is the system time in the current time zone divided by 90. Use currentLocalTime() to get the current local time.
         */
        readonly lastSaveDay: number;
    
        /**
         * @description The time the last index of the day array was saved. This value is the system time in the current time zone divided by 1800 (=30 minutes). Use currentLocalTime() to get the current local time.
         */
        readonly lastSaveMonth: number;
    
        /**
         * @description The time the last index of the day array was saved. This value is the system time in the current time zone divided by 21600 (=6 hours). Use currentLocalTime() to get the current local time.
         */
        readonly lastSaveYear: number;
    
        /**
         * @description Get the day stats at index idx. Index 0 returns the first 90s of the day, the time from 00:00.00 to 00:01.30. 12:15 in seconds of the day is 12*60*60 + 15*60 = 44100. Divided by 90s  is 44100 / 90 =490. The stats are constantly overwritten with the stats right now, therefore an index larger than the current time returns stats of yesterday. E.g. it is 18:00 right now. If you get the stats from 17:00, then you have the stats from 1 hour ago. If you get the stats from 19:00, then you get the stats from 23h ago. Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveDay.
         */
        day(idx: number): _rrsStats_type;
    
        /**
         * @returns Max number of stat values in the array. It returns 960 for the current version.
         */
        dayMax(): number; 
    
        /**
         * @description The server adds the stats of the last 30 minutes to the last index (959) of the array and pushes all other stat values down in the array. Therefore an index of monthMax()-1=959 returns the stats of the last completed 30 minutes. E.g. if the current time is 18:15, then the last stats are from 17:30 - 18:00 Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveMonth.
         */
        month(): _rrsStats_type;
    
        /**
         * @returns Max number of stat values in the array. It returns 960 for the current version.
         */
        monthMax(): number;
    
        /**
         * @description The server adds the stats of the last 30 minutes to the last index (959) of the array and pushes all other stat values down in the array. Therefore an index of yearMax()-1=959 returns the stats of the last completed half day minutes. E.g. if the current time is 18:15, then the last stats are from 00:00 - 12:00 Note: This is only true as long as the rrServer is running and continues to save stats. Otherwise check lastSaveYear.
         */
        year(): _rrsStats_type;
    
        /**
         * @returns Max number of stat values in the array. It returns 960 for the current version.
         */
        yearMax(): number;
    }

    interface _rrsStats_type {

        /**
         * @description Is this data valid? If not, then this data is crap or from any other day/time.
         */
        readonly slot_used: boolean;
    
        /**
         * @description A estimate how many clients would be needed to start all unassigned frame segments.
         */
        readonly clients_needed: number;
    
        /**
         * @description Number of frames rendered during this time segment (90seconds, 30 minutes or 6hours depending on the stats type).
         */
        readonly framesPer90s: number;
    
        /**
         * @description Number of free clients.
         */
        readonly clients_free: number;
    
        /**
         * @description Number of clients rendering.
         */
        readonly client_rendering: number;
    
        /**
         * @description Number of disabled clients.
         */
        readonly clients_disabled: number;
    
        /**
         * @description CPU usage of the rrServer app (0-100%).
         */
        readonly cpuProcess: number;
    
        /**
         * @description CPU usage of the machine (0-100%).
         */
        readonly cpuMachine: number;
    
        /**
         * @description Temperature of the first HDD in the rrServer machine.
         */
        readonly serverTemperature: number;
    
        /**
         * @description Average temperature of the first HDD of all rrClients.
         */
        readonly avclientTemperature: number;
    
        /**
         * @description Number of unfinished jobs.
         */
        readonly jobs_unfinished: number;
    
        /**
         * @description Number of jobs rendering.
         */
        readonly jobs_rendering: number;
    
        /**
         * @description Total number of jobs.
         */
        readonly jobs_total: number;
    
        /**
         * @description Memory usage of the rrServer machine.
         */
        readonly memUsageMachine: number;
    
        /**
         * @description Memory usage of the rrServer application.
         */
        readonly memUsageProcess: number;
    
        /**
         * @description Memory usage of the 1st rrServers TCP socket buffer.
         */
        readonly tCPMemUsageSocket: number;
    
        /**
         * @description Memory usage of the 2nd rrServers TCP socket buffer.
         */
        readonly tCPMemUsageData: number;
    
        /**
         * @description Memory usage for all job data.
         */
        readonly jobBufferMemUsageJobs: number;
    
        /**
         * @description Max memory for a TCP socket buffer after compression.
         */
        readonly tCPMemUsageDataCompressed: number;
    
        /**
         * @description Average frame time of all jobs.
         */
        readonly av_frame_time: number;
    
        /**
         * @description Summed frames to be rendered from all jobs.
         */
        readonly frames_to_do: number;
    }

    interface _rrClientStats_Data extends _rrStatsSharedFunctions {

        /**
         * @description Should be the hex value A101.
         */
        readonly structureID: number;
    
        /**
         * @description Get the data per day. Index (daysMax() - 1) is the last day written into the stats file. If the client is currently running, then this is today. Index (daysMax() - 2) is the day before. Check days(...).daySet and days(...).day to verify that you got some data and that it is the right day.
         * @param idx The Index of the _rrClientStats_day instance you want to fetch.
         */
        days(idx: number): _rrClientStats_day;
    
        /**
         * @returns The maximum number of days in this array (180).
         */
        daysMax(): boolean;
    }
    
    interface _rrClientStats_day {

        /**
         * @description Contains this day any useful data? (e.g. if the client was not online that day, daySet is false).
         */
        readonly daySet: boolean;
    
        /**
         * @description The current day in the default unix timestamp (days since Jan 1, 1970). Note: Most time functions return the time in seconds since 1970, so divide that value with /60/60/24.
         */
        readonly day: number;
    
        /**
         * @description This data is collected every 20 seconds. Index 0 are the first 20 seconds of the day, Index 1 the 20-40 seconds of the day, ...
         */
        data(idx: number): _rrClientStats_day_data;
    
        /**
         * @returns The maximum number of values in the data array. (4320 for the current version, one data item every 20 seconds).
         */
        dataMax(): number;
    
        /**
         * @param idx 0 is the first hour of the day ( 00:00  - 01:00 ).
         */
        dataHourly(idx: number): _rrClientStats_day_data_hourly;
    
        /**
         * @description The maximum number of values in the hourly array (24).
         */
        dataHourlyMax(): number;
    }

    interface _rrClientStats_day_data {

        /**
         * @description Was a user logged in?
         */
        readonly userLoggedIn: boolean;

        /**
         * @description CPU usage as percentage of the system. The value is exported as float (1.0 = 100%).
         */
        readonly cpuTotal: number;

        /**
         * @description Total memory usage in MiB, divided by 10.
         */
        readonly memTotal10MB: number;

        /**
         * @return The data of a job thread.
         */
        jobThread(): _rrClientStats_day_data_jobthread

        /**
         * @returns The number of job threads the client was running in this time slot.
         */
        jobThreadMax(): number
    }

    interface _rrClientStats_day_data_jobthread {

        /**
         * @description Job status. See enumeration _Status.
         */
        readonly status: number;

        /**
         * @description CPU usage of this job. The value is exported as float (1.0 = 100%).
         */
        readonly cpuRender: number;

        /**
         * @description Memory usage of the render job in MB, divided by 10.
         */
        readonly memRender10MB: number;

        /**
         * @description The ID of the job in a shortened representation (The internal job ID in RR is usually a 64bit number. In this case truncated to 32bit only).
         */
        readonly jobIDShort: number;
        
        /**
         * @returns The jobIDShort as human readable string {ID}. 
         */
        jobIDShortStr(): string;
    }

    interface _rrClientStats_day_data_hourly {

        /**
         * @param idx Index of the job thread you want to fetch.
         * @returns The data for each job thread.
         */
        jobThread(idx: number): _rrClientStats_day_data_hourly_jobthread;

        /**
         * @returns The number of job threads the client was running in this hour.
         */
        jobThreadMax(): number;
    }

    interface _rrClientStats_day_data_hourly_jobthread {

        /**
         * @description Frames done in this hour.
         */
        readonly framesDone: number;

        /**
         * @description Number of times a job crashes.
         */
        readonly jobCrashed: number;

        /**
         * @description Number of times a job was aborted.
         */
        readonly jobAborted: number;

        /**
         * @description Number of times a job rendered successfully.
         */
        readonly jobSuccessful: number;
    }

    interface _frameStatJob extends _rrStatsSharedFunctions {

        /**
         * @param frame The Framenumber of the frame you want to fetch stats from.
         * @returns The stats of frame X. The first frame has index number 0. It is not the frame number in the scene file.
         */
        frame(frame: number): _frameStat;

        /**
         * @returns Max number of frames for this job.
         */
        frameMax(): number;
    }

    interface _frameStat {

        /**
         * @returns The time when the render logfile was started. It is the same time as in the filename. 
         */
        readonly logFileStart: Date;

        /**
         * @returns The first frame of the render log. It is the same frame number as in the filename.
         */
        readonly logFileStartFrame: number;

        /**
         * @returns The render time of the frame in seconds, divided by 5.
         */
        readonly renderTime5Sec: number;

        /**
         * @returns The frame number of the job.
         */
        readonly frameNrJob: number;

        /**
         * @returns Name of the client.
         */
        readonly client: string;

        /**
         * @description Sometimes the client is not able to get exact values per frames. In this case it collects the data of the whole frame segment and averages the values.
         * @returns The frame segment contains of averageValue frames.
         */
        readonly averageValue: number


        /**
         * @description Stats are collected multiple times while a frame is rendered. If a frame takes for example 10 minutes to render, then each of the 5 part represents 2 minute of the render.
         */
        part(): _frameStat_part;

        /**
         * @returns Max number of parts for each frame (5).
         */
        partMax(): number;
    }

    interface _frameStat_part {

        /**
         * @returns Memory usage of job.
         */
        readonly jobMemoryMB: number;

        /**
         * @returns CPU usage of the job.
         */
        readonly jobCPU: number;

        /**
         * @returns Other CPU usage of the machine.
         */
        readonly nonJobCPU: number;

        /**
         * @returns Number of job threads rendering on the client at this moment.
         */
        readonly renderThreads: number;
    }

    interface _ClientGroupList extends _rrStatsSharedFunctions {
        
        /**
         * @description Date/Time of the group settings file loaded/saved.
         */
        readonly settingsFileDate: Date;

        /**
         * @description Get/set the number of groups.
         */
        readonly count: number;

        /**
         * @param idx Index of the clientGroup you want to fetch.
         * @returns The client group at the specified idx.
         */
        clientGroup(idx: number): _ClientGroup;

        /**
         * 
         * @param idx The index of the client group which should be replaced.
         * @param group The client group which should replace the other client group, specified by the idx.
         */
        clientGroupSet(idx: number, group: _ClientGroup): void;

        /**
         * @returns The maximum number of possible groups in this RR version.
         */
        clientGroupsMax(): number;

        /**
         * @description Saves the stats into file FileName.
         * @param FileName The file name of the file where the stats should be saved to.
         */
        saveToFile(FileName: string): boolean;
    }

    interface _ClientGroup {

        /**
         * @description Remove all clients from the group.
         */
        clear(): void;

        /**
         * @returns The name of the group.
         */
        getName(): string;

        /**
         * @description Set the name of the group.
         * @param newName The new name of the group.
         */
        setName(newName: string): void;

        /**
         * @description Get client name at the list index.
         * @param idx The index of the clientName.
         */
        getClientName(idx: number): string;

        /**
         * @description Add a client with the specified name to the list.
         * @param name The name of the new Client.
         */
        addClient(name: string): void;

        /**
         * @description Remove client from the gorup with the specified name.
         * @param name The name of the client you want to remove.
         */
        removeClient(name: string): void;

        /**
         * @description Remove client at list index from the group.
         * @param idx The Index of the client you want to remove.
         */
        removeClientbyID(idx: number): void;

        /**
         * @returns Number of clients in group.
         */
        count():  number;
    }

    interface _StatsRenderTime {

        /**
         * @description Get the number of groups.
         */
        readonly prjCount: number;

        /**
         * @description Date/Time of the group settings file saved.
         */
        readonly lastSaved: Date;

        // can't inherit from _rrStatsSharedFunctions because loadFile != loadFromFile
        /**
         * @param idx The index of the project you want to fetch.
         * @returns The project of the specified index.
         */
        getProject(idx: number): _StatsRenderTime_project;

        /**
         * @description Loads the stats from file FileName.
         * @param FileName The name of the file you want to load the stats from.
         */
        loadFile(FileName: string): boolean;

        /**
         * @description Saves the stats into file FileName.
         * @param FileName The name of the file you want to save the stats to.
         */
        saveFile(FileName: string): boolean;

        /**
         * @returns The error message in case the loadFile() or saveFile() fails.
         */
        getError(): string;
    }

    interface _StatsRenderTime_project {

        /**
         * @returns The last time a job was added to this list. 
         */
        readonly lastUsed: Date;

        /**
         * @returns Name of the project.
         */
        readonly name: string;

        /**
         * @param idx The index of the Layer you want to fetch.
         */
        getLayer(idx: number): _StatsRenderTime_layer;

        /**
         * @returns The number of layers in this list.
         */
        layerCount(): number;
    }

    interface _StatsRenderTime_layer {

        /**
         * @description Number of jobs that have been added. This is NOT the number of jobs in this list.
         */
        readonly jobsAdded: number;

        /**
         * @description Name of the layer.
         */
        readonly name: string;

        /**
         * @returns The frame time at idx. The frame time is in PS*s.
         * @param idx The index of the Frame time.
         */
        getFrameTime(idx: number): number;

        /**
         * @returns The number of frame times in this list. The latest job is always at position 0.
         */
        timesCount(): number;
    }
}

declare namespace rrGlobal {
    interface rrGlobal {

        /**
         * @description You can use a number instead of the enumeration. The IDs will not change with any RR update.
         */
        readonly ClientCommand: _EClientCommand;
        readonly executeJobType: _EExecuteJobType;
    
        /**
         * @description You can use a number instead of the enumeration. The IDs will not change with any RR update.
         */
        readonly logLvL: _ELogLvL;
        readonly ClientStatusList: _EClientStatusList;
        readonly ClientStatusJob: _EClientStatusJob;
        readonly pluginReturn: _EPluginReturn;
    }

    interface _EClientCommand {
        readonly cAbortUNKNOWN: number;
        readonly cEnable: number;
        readonly cDisable: number;
        readonly cAllowLittle: number;
        readonly cForbitLittle: number;
        readonly cUseWorking: number;
        readonly cIgnoreWorking: number;
        readonly cRestartClientExe: number;
        readonly cWOL: number;
        readonly cRestartMachine: number;
        readonly cRestartMachineForce: number;
        readonly cShutdownMachine: number;
        readonly cShutdownMachineForce: number;
        readonly cAbortDisable: number;
        readonly cIgnoreCPU: number;
        readonly cReserveCPUInteractive: number;
        readonly cUseCPUInteractive: number;
        readonly cShutdownClientAndService: number;
        readonly cReloadClientConfig: number;
        readonly cReloadUserConfig: number;
        readonly cReloadGlobalConfig: number;
        readonly cReloadAllConfig: number;
        readonly cUpdateServiceCfg: number;
        readonly cConfigSearchForApplications: number;
        readonly cConfigSearchForApplicationsDeleteOld: number;
        readonly cShutdownClient: number;
        readonly cTimeSync: number;
        readonly cShowProcessTree: number;
        readonly cAbortAfterFrame: number;
        readonly cAbortAfterFrameDisable: number;
        readonly cDoSpeedTest: number;
        /**
         * @description Requires to set the param string of the clientSendCommand function. The client will create a batch file RR_LocalData/_command.bat. It executes the command and writes the output into RR_LocalData/_command.txt. If you want to keep your log output, you should redirect it into a file via your commandline. For example: myCommand 1>/fileserver/share/MyCommand_<LocalHost>.txt   2>/fileserver/share/MyCommand_<LocalHost>_error.txt myCommand 1>/fileserver/share/MyCommand_<LocalHost>.txt   2>&1 You can use all variables (like <LocalHost>) from  render configs, as long as they are not job specific. The command buffer can only take up to 500 letters.
         */
        readonly cCommandLine: number;
        readonly cResetIdleTime: number;
        readonly cDevDebug: number;
    }
    
    interface _EExecuteJobType {
    
        /**
         * @description default job.
         */
        readonly none: number;
    
        /**
         * @description Execute this job once.
         */
        readonly once: number;
    
        /**
         * @description Execute this job on each client.
         */
        readonly eachClient: number;
    
        /**
         * @description Execute this job once per frame.
         */
        readonly perFrame: number;
    }
    
    interface _ELogLvL {
    
        /**
         * @description Critical messages will force the RR application to restart or terminate themselves.
         */
        readonly critical: number;
    
        /**
         * @description Error messages are important for the execution of RR and should never fail. All RR error messages are collected in a seperate error log RR/sub/log/_ERROR.txt for the rrAdmin and/or rrSupport to fix issues.
         */
        readonly error: number;
    
        /**
         * @description Warning messages will have a "WRN - " in front to identify them faster in logfiles.
         */
        readonly warning: number;
    
        /**
         * @description default messages (At the moment there is no difference to "progress" besides for the message box).
         */
        readonly info: number;
    
        /**
         * @description default messages (At the moment there is no difference to "info" besides for the message box).
         */
        readonly progress: number;
    
        /**
         * @description Debug messages are ignored by default. They are shown if you have called debugEnable() or the RR application is not running in debug mode.
         */
        readonly debug: number;
    }

    interface _EClientStatusList {
        readonly sOff: number;
        readonly sFree: number;
        readonly sDisabled: number;
        readonly sRendering: number;
        readonly sRenderingSuccessful: number;
        readonly sAborted: number;
        readonly sCrashed: number;
        readonly sDisabledAllowLittle: number;
        readonly sRenderingStarting: number;
        readonly sNoLicense: number;
        readonly sPermanentCrashed: number;
        readonly sClientFreeze: number;
        readonly sAbortedDisable: number;
        readonly sAbortedLowMemory: number;
        readonly sAbortedFrozen: number;
        readonly sAbortedHighUserCPU: number;
        readonly sAbortedFrameTime: number;
        readonly sAbortedWorkinghours: number;
        readonly sAbortedReservedClient: number;
        readonly sAbortedHighPriority: number;
        readonly sAbortedrrControl: number;
        readonly sAbortedAverage: number;
        readonly sAbortedLicenseBlock: number;
        readonly sAbortedLocalMachine: number;
        readonly sAbortedProcessFound: number;
        readonly sRenderingSuccessfulNoNewJob: number;
        readonly sDisabledWorkinghours: number;
        readonly sDisabledWorkinghoursAllowLittle: number;
        readonly sDisabledKeepDisabled: number;
        readonly sCrashedKSOLogError: number;
    }

    interface _EClientStatusJob {
        readonly sjNone: number;
        readonly sjHighCpuUsage: number;
        readonly sjWorkingHours: number;
        readonly sjSatelliteRendering: number;
        readonly sjWait: number;
        readonly sjLowMemory: number;
        readonly sjInWOL: number;
        readonly sjUserLoggedOff: number;
        readonly sjShutdown: number;
        readonly sjInWOLBroken: number;
        readonly sjAbortProcess: number;
        readonly sjClientOff: number;
        readonly sjClientLost: number;
        readonly sjUITakeOver: number;
        readonly sjDeferMode: number;
        readonly sjVmBooting: number;
        readonly sjVmCreating: number;
        readonly sjMacRestart: number;
        readonly sjMacShutdown: number;
        readonly sjAppRestart: number;
        readonly sjAppShutdown: number;
    }

    interface _EPluginReturn {
        
        /**
         * @description The default value if nothing was set.
         */
        readonly rUnknownError: number;

        /**
         * @description Successful execution.
         */
        readonly rSuccessful: number;

        /**
         * @description File to read was not found.
         */
        readonly rFileNotFound: number;

        /**
         * @description Failed to open the file.
         */
        readonly rFileFailedToOpen: number;

        /**
         * @description This plugin does not support this file format. In such a case the next plugin that can open this file extension is executed.
         */
        readonly rUnsupportedFormat: number;
        readonly rRRDataVersionConflict: number;
        readonly rCError: number;
        readonly rMemError: number;
        readonly rPluginFileMissing: number;
        readonly rPluginLoadError: number;

        /**
         * @description The execution was successful, but the plugin has not created a job. And this should not be seen as an error.
         */
        readonly rSuccessfulIgnoreNoJobs: number;

        /**
         * @description Any other error.
         */
        readonly rOtherError: number;
        readonly rWrongFileSize: number;
        readonly rNoImageDimensions: number;

        /**
         * @description The data of the file seems to be broken.
         */
        readonly rDataError: number;
        readonly rImageDimensionsToLarge: number;
        readonly rRequireFullLoad: number;
        readonly rNoPluginforFileType: number;
        readonly rPythonError: number;

        /**
         * @description The file size is smaller than it should be. Indicates that the file was not completely written.
         */
        readonly rFileSizeToSmall: number;
        readonly rDebugCompile: number;
        readonly rIsPlaceHolderFile: number;
        readonly rFileFailedToSave: number;

        /**
         * @description The execution was not an error. But the main app should execute this plugin again.
         */
        readonly rSuccessfulRetryLoad: number;
        readonly rFileBuffertoSmall: number;

        /**
         * @description No image output set in scene file.
         */
        readonly rNoImageOutput: number;

        /**
         * @description The scene parser was not able to create a job as some scene settings do not use an absolute path. And this plugin was not able to resolve the relative path OR it will not be possible to render the scene with relative paths.
         */
        readonly rAbsolutePathsRequired: number;
        readonly rLoadEndOfFileOnly: number;
    }
}

declare namespace Job {
    interface rrJob {

        /**
         * @description _LogMessage is used for all job log messages and for commands send to a job.
         * @example
         * var rrJob = rrbinding.createRRJob();
         * tcp.jobSendCommand(jobIDs, rrJob._logMessage.lEnable, 0)
         */
        readonly _logMessage: _LogMessage;
    
        /**
         * @example
         * var rrJob = rrbinding.createRRJob();
         * rrJob.rrOption(rrJob._rrOptions.rroKeepSceneOpen);
         */
        readonly _rrOptions: _RROptions;
    
        /**
         * @example
         * var rrJob = rrbinding.createRRJob();
         * rrJob.rrParam(rrJob._rrParam.rrpRequiredMemoryGB);
         */
        readonly _rrParam: _RRParams;
        readonly _Status: _Status;
    
        // ----- FUNCTIONS -----
    
        /**
         * @returns A basic _JobBasics object with default values.
         */
        getClass_JobBasics(): _JobBasics;
    
        /**
         * @description If you want to change job settings, then you have to use this class and send the rrServer a command with the new values.
         * @returns a basic _SettingsOnly object with default values.
         */
        getClass_SettingsOnly(): _SettingsOnly;
    }

    interface _JobMinInfo {
        /**
         * @description The job ID
         */
        readonly ID: Utils.rrUint64;
    
        /**
         * @description The user who has send the job
         */
        readonly userName: string;
    
        /**
         * @description The company project of the job
         */
        readonly companyProjectName: string;
    
        /**
         * @description The name of the render application (Softimage, Nuke, ...)
         */
        readonly rendererName: string;
    
        /**
         * @description All jobs have a queue ID which starts at 0. Deleting/Moving jobs changes the queueID.
         */
        readonly queueIDAtServer: number;
    
        /**
         * @description A bit mask for different job states: 1 -> Not Rendering, 2 -> Rendering, 4 -> Disabled, 8 -> Wait for..., 16 -> Finished - See _filterIDs for equivalent data.
         */
        readonly filterMask: number;
    
        /**
         * @returns ID of the job as human readable/remember-able string E.g. {D5Ca}.
         */
        IDstr(): string;
    }
    
    interface _JobBasics {
        /**
         * @description MagicID/Version of the class.
         */
        readonly structureIDBasics: number;
    
        /**
         * @description MagicID/Version of the class.
         */
        readonly variablesIDBasics: number;
    
        /**
         * @description MagicID/Version of the class.
         */
        readonly structureIDSend: number;
    
        /**
         * @description MagicID/Version of the class.
         */
        readonly variablesIDSend: number;
    
        /**
         * @description OS of the texture paths inside this rrJob class. 1: Windows, 2: Linux, 3: OSX.
         */
        readonly rrJobOS: number;
    
        /**
         * @description OS the scene was created on (Texture paths inside the file). 1: Windows, 2: Linux, 3: OSX.
         */
        readonly sceneOS: number;
        
        /**
         * @description Render application and Renderer information.
         */
        readonly renderApp: _RenderAppBasic;
        readonly sceneName: string;
    
        /**
         * @description The Scene Database Directory of the current Job.
         */
        readonly sceneDatabaseDir: string;
        readonly camera: string;
        readonly layer: string;
        readonly channel: string;
        
        /**
         * @description The requiredLicenses for the current Job (e.g.: ;/Arnold, ...).
         */
        readonly requiredLicenses: string;
        
        /**
         * @description The Image Directory of the current Job.
         */
        readonly imageDir: string;
        readonly imageFileName: string;
    
        /**
         * @description Some render jobs render multiple layers/passes at once. The render application requires these parts of the file name as variables. E.g. <layer>.
         */
        readonly imageFileNameVariables: string;
        
        /**
         * @description The Output Render Extension Setting for the current Job (e.g.: .exr, ...).
         */
        readonly imageExtension: string;
        readonly imagePreNumberLetter: string;
        readonly imageFramePadding: number;
        readonly imageWidth: number;
        readonly imageHeight: number;
        readonly imageSingleOutputFile: boolean;
        
        /**
         * @description Number of tiles for a frame.
         */
        readonly imageMulti: number;
        
        /**
         * @description If used, then the image format is not the same as set in the scene. RR should override the image format at render time.
         */
        readonly imageFormatOverride: string;
        readonly imageStereoL: string;
        readonly imageStereoR: string;
        readonly localTexturesFile: string;
        
        /**
         * @description ID of the _JobBasics object.
         */
        readonly ID: Utils.rrUint64;
        
        /**
         * @description This variable is used for jobs before submission only! Please see function IDpre() (NOT IMPLEMENTED IN NODE ADDON) if you want to get the variable once the job was send. A value between 0 and 255. Each job gets the Pre ID attached as small letter to the main ID. It is the the small letter at the end of the ID.
         */
        readonly preID: number;
        
        /**
         * @description maximum number of waitForPreIDs. See functions of _JobBasics.
         */
        readonly maxWaitForPreID: number;
        readonly uiIsChecked: boolean;
        
        /**
         * @description ShotgunID of the Scene/Sequence. Usually retrieved at submission by an onsubmission script.
         */
        readonly shotgunID: string;
        readonly seqStart: number;
        readonly seqEnd: number;
        readonly seqStep: number;
        readonly seqFileOffset: number;
        
        /**
         * @description - not used -
         */
        readonly seqFrameSet: string;
        
        /**
         * @description - not used -
         */
        readonly seqIsFloatFrames: boolean;
        readonly additionalCommandlineParam: string;
    
        // ----- FUNCTIONS -----
    
        /**
         * @description This is only used for jobs at submission. Get the waitForPreID of this job. A job has up to 20 waitforIDs. When the job is received by the server, the server checks for other jobs send from the machine in the last 15 minutes. The server then gets the latest job with the same PreID as a WaitForPreID of this job, then this jobs waits for the other job. Index ranges from 0 to maxWaitForPreID. Maximum is 20.
         * @param index ranges from 0 to maxWaitForPreID. Maximum is 20.
         */
        waitForPreID(index: number): number;
    
        /**
         * @description Set the waitForPreID of this job. A job has up to 20 waitforIDs. You have to update maxWaitForPreID as well.
         * @param index The index of the waitforID. ranges from 0 to maxWaitForPreID. Maximum is 20.
         * @param value The value for the waitforID respectively.
         */
        waitForPreID_set(index: number, value: number): string;
    
        /**
         * @param index The index of the channel which should be fetched. Ranges from 0-100.
         * @returns The filename of the render Channel.
         */
        channelFileName(index: number): string;
    
        /**
         * @param index The index of the render channel you want to retrieve. Ranges from 0-100.
         * @returns The extension of the render channel.
         */
        channelExtension(index: number): string;
    
        /**
         * @description Set the filename of the render channel.
         * @param index The index of the render channel of which you want to change the filename. Ranges from 0-100.
         * @param value The new filename of the render channel.
         */
        channelFileName_set(index: number, value: string): void;
    
        /**
         * @description Set the extension of the render channel.
         * @param index The index of the render channel of which you want to change the extension. Ranges from 0-100.
         * @param value The new render channel Extension.
         */
        channelExtension_set(index: number, value: string): void;
    
        /**
         * @returns Short ID of the job as human readable/rememberable string E.g. {D5Ca}. The ID string is a short version of the job ID. It could happen that two jobs have the same short ID. IDstrFull() does not have this issue.
         */
        IDstr(): string;
    
        /**
         * @description IDstr() only delivers a short version of the jobID. This can lead to repeating IDs. IDstrFull() delivers the full version of this ID, which will not lead to ID repetition.
         * @returns the full short ID.
         */
        IDstrFull(): string;
    
        /**
         * @description Removes all extensions and variables from the scene file name and keeps only a few folders in front of the file name.
         */
        sceneDisplayName(): string;
    
        /**
         * @description You can save up to 5000 letters. If unicode letters are found in value, then the string takes twice its length in bytes. Reserved names are "UserInfo" and "EnvFile".
         * @param name Name of the data item of the job you want to retrieve.
         * @returns A custom data item of the job.
         */
        custom_Str(name: string): string;
    
        /**
         * @description Set custom data item. An empty value is not saved.
         * @param name Name of the data item you want to save. If this name already exists, the item in the server will be overwritten or deleted (if value is empty).
         * @param value Value of the data item you want to save.
         */
        customSet_Str(name: string, value: string): void;
    
        /**
         * @description Same as custom_Str("UserInfo"). UserInfo is displayed in rrControl.
         */
        custom_UserInfo(): string;
    
        /**
         * @description Same as customSet_Str("UserInfo"). UserInfo is displayed in rrControl.
         * @param info The new UserInfo.
         */
        customSet_UserInfo(info: string): void;
    
        /**
         * @returns The number of custom data items.
         */
        customGet_MaxIDs(): number;
    
        /**
         * @param id The data item id.
         * @returns Custom data item via its id.
         */
        custom_StrByID(id: number): string;
    
        /**
         * @description Set custom data item via its id.
         * @param id The data item id.
         * @param value The new value for the respective data item.
         */
        customSet_StrByID(id: number, value: string): void;
    
        /**
         * @param id The data item id.
         * @returns Name of the data item via id.
         */
        custom_NameByID(id: number): string;
    
        /**
         * @returns A string with all custom data items set.
         */
        custom_AllAsString(): string;
    
        /**
         * @description Deletes all custom data items.
         */
        custom_clearAll(): void;
    
        /**
         * @description Splits the imageFileName into imageDir and imageExtension if those two are empty. If ImageDir or imageExtension have a value, then this variable is not changed. The same applies for splitting channelFileNames  into file and extension. If imageSingleOutputFile is set, then no imageExtension will be set as there is no frame number in between. If an image padding is recognized, then imageFramePadding is set as well. Supported frame number formats are: %04d (only if percentPadding is set) #### [####] .125. If the file extension indicates a video or audio file, then imageSingleOutputFile is set to True. Note: This function is always executed in rrSubmitter. But you can call it yourself to check the values afterwards.
         */
        splitImageFileInto_DirFileExt(percentPadding: boolean): void;
    
    }
    
    interface _JobSend extends _JobBasics, _SettingsOnly {
    
        // _SettingsOnly with overridden properties -> now readonly
        //other properties and functions are extended by _JobBasics and _SettingsOnly
        readonly seqStart: number;
        readonly seqEnd: number;
        readonly seqStep: number;
        readonly seqFileOffset: number;
    
        /**
         * @description - not used -
         */
        readonly seqFrameSet: string;
    
        /**
         * @description - not used -
         */
        readonly seqIsFloatFrames: boolean;
        readonly additionalCommandlineParam: string;
    
        /**
         * @description User that submitted the job.
         */
        readonly userName: string;
        readonly customSeqName: string;
        readonly customShotName: string;
        readonly customVersionName: string;
        readonly companyProjectName: string;
        readonly notifyFinish: string;
        readonly notifyFinishClientName: string;
        readonly notifyFinishParam: number;
        readonly notifyFinishWhen: number;
    
        /**
         * @description The priority of the job.
         */
        readonly priority: number;
    
        /**
         * @description Sequence Divide Min value.
         */
        readonly seqDivMin: number;
    
        /**
         * @description Sequence Divide Max value.
         */
        readonly seqDivMax: number;
    
        /**
         * @description The job is deactivated until this time.
         */
        readonly timeToEnable: Date;
    
        /**
         * @description Number of pre/preview/post/finished commands for the job.
         */
        readonly prePostCommandCount: number;
    
        /**
         * @description Number of custom options for the job  (custom options are set in the render config of the job).
         */
        readonly customOptionsCount: number;
    
    
        // ----- _JobSend specific properties -----
    
        /**
         * @description Machine that submitted the job.
         */
        readonly submitMachine: string;
        readonly seqDivideEnabled: boolean;
        readonly disabled: boolean;
        readonly jobFilesFolderName: string;
        readonly localTexturesCount: number;
        readonly localTexturesSizeMB: number;
        readonly errorCountServer: number;
        readonly errorCount: number;
        readonly logCount: number;
        readonly infoTotalSend: number;
        readonly infoTotalCrashed: number;
        readonly infoTotalAborted: number;
        readonly infoAverageClients: number;
        readonly infoAverageClientPS: number;
        readonly infoAverageFrameTime: number;
    
        /**
         * @description Sequence check has processed the rendered image sequence.
         */
        readonly infoAnalyse_done: boolean;
    
        /**
         * @description Number of frames with potential issues found.
         */
        readonly infoAnalyse_error: number;
    
        /**
         * @description Number of frames with potential issues found.
         */
        readonly infoAnalyse_warning: number;
    
        /**
         * @description Number of frames with potential issues found.
         */
        readonly infoAnalyse_info: number;
        readonly infoTotalLimitsReached: number;
        readonly lastSettingsChanged: Date;
        readonly lastInfoChanged: Date;
        readonly lastErrorEmail: Date;
    
        /**
         * @description Total time the job was rendering. It does not take the number of clients into account. Therefore do not use this to calculate potential total times of the job. EDIT: else you should use renderTimeSum_seconds (NOT IMPLEMENTED IN NODEJS ADDON) where each client adds its own PS to the job.
         */
        readonly rendertime_seconds: number;
        //readonly rendertimeSum_seconds: number;
    
        /**
         * @description Collected PS spend on the job.
         */
        readonly renderTime_PS: number;
    
        /**
         * @description Collected Ghz spend on the job.
         */
        readonly renderTime_Ghz_h: number;
        readonly rendertime_remaining_seconds: number;
        readonly renderTime_remaining_PS: number;
        readonly framesDone: number;
    
        /**
         * @description Status of the job. See enumeration _Status for details.
         */
        readonly status: number;
        readonly timeFinished: Date;
    
        /**
         * @description Has the user approved the job (that small check mark in the rrControl job table).
         */
        readonly userApproved: boolean;
        readonly scriptPreviewExecuted: boolean;
        readonly previewStart: number;
        readonly FOICreated: number;
        readonly FOIFileName: string;
        readonly framesLeft: number;
        readonly framesTotal: number;
    
        /**
         * @description Different to framesTotal if the frames are tiled. This is the number of frames if they would not be tiled.
         */
        readonly framesTotalNonMulti: number;
    
        /**
         * @description 1kb placeholder frames that are created when the render of that frame starts.
         */
        readonly framesPlaceholderFound: number;
        readonly framesUnAssignedFoundNr: number;
        readonly lastFrameDone: number;
        readonly clientsRenderingCount: number;
        readonly averageMemoryUsage: number;
        readonly fileserverTimeDifference: number;
        readonly fileserverTimeDifferenceOffset: number;
        readonly check_interval: number;
        readonly check_lastExecution: Date;
        readonly check_next_seconds: number;
    
        /**
         * @description Number of clients needed to render all frames now.
         */
        readonly clientNeed: number;
        readonly isRendering: boolean;
        readonly queueIDAtServer: number;
    
        /**
         * @description Time the rrServer took to check the output folder for frames.
         */
        readonly foldersearchtime: number;
    
        // ----- FUNCTIONS -----
    
        /**
         * @param client_number The number of the client you want to get.
         * @returns true if the client is assigned for the job.
         */
        clientAssigned(client_number: number): boolean;
    
        /**
         * @description set the client assignment.
         * @param client_number The number of the client you want to modify.
         * @param assigned The new assigned value for the specified client.
         */
        clientAssigned_Set(client_number: number, assigned: boolean): void;
    
        /**
         * @description Gets some information about the client regarding the job.
         * @param client_number  The number of the client you want to get.
         * @param valueID 0 -> Number times the client got a segment of this job for rendering. 1 -> Number times the client was aborted. 2 -> Number of times the client crashed. 3 -> total frames rendered. 4 -> total time the client spend on this job.
         * @returns some information about the client regarding the job, based on the valueID parameter.
         */
        clientValue_Get(client_number: number, valueID: number): number;
    
        /**
         * @description A job counts frames internally 0,1,2,3,.... no matter which frame start or frame step the job has. This function converts a frame number into the internal job number.
         * @param filenumber The Framenumber to convert into the internal job number.
         * @param MultiFrameID If you use tile frame, then you need to set MultiFrameID to the tile you want to access. Otherwise use MultiFrameID=0.
         */
        fileNumber2jobNumber(filenumber: number, MultiFrameID: number): number;
    
        /**
         * @description A job counts frames internally 0,1,2,3,.... no matter which frame start or frame step the job has. This function converts the internal job number into a frame number.
         * @param jobNumber The internal job number you want to convert into a frame number.
         */
        jobNumber2fileNumber(jobNumber: number): number;
    
        /**
         * @description A job counts frames internally 0,1,2,3,.... no matter which frame start or frame step the job has. If you use tile frame, this function converts the internal job number into the tile ID. Otherwise it always returns 0.
         * @param jobNumber The job number you want to convert into a tile ID.
         * @returns Tile ID based on jobNumber input if tile frame is used. Returns 0 Otherwise.
         */
        jobNumber2multiID(jobNumber: number): number;
    
        /**
         * @param id The id of the preview frame you want to get the frame number of. There are maximal previewNumberOfFrames.
         * @returns The frame number of preview frame with id.
         */
        previewID2FrameNr(id: number): number;
    
        /**
         * @param id The id of the preview frame you want to get the file name of.
         * @returns The file name of the preview - thumbnail version.
         */
        previewFilenameThumbnail(id: number): string;
    
        /**
         * @param id The id of the preview Frame you want to get the file name of.
         * @returns The file name of the preview - full size RGB version.
         */
        previewFilenameRGB(id: number): string;
    
        /**
         * @param id The id of the preview Frame you want to get the file name of.
         * @returns The file name of the preview - full size Alpha version.
         */
        previewFilenameA(id: number): string;
    }

    interface _LogMessage {
        readonly lUnknown: number;
        readonly lAbortedReservedClients: number;
        readonly lEnable: number;
        readonly lDisable: number;
        readonly lDisableAbort: number;
        readonly lApprove: number;
        readonly lDisApprove: number;
        readonly lDelete: number;
        readonly lAbort: number;
        readonly lCheck: number;
        readonly lReset: number;
        readonly lResetNDelete: number;
        readonly lChangeClientAssignment: number;
        readonly lClientRenderSuccessful: number;
        readonly lClientRenderAborted: number;
        // readonly lClientRenderCrashed: number;
        readonly lAutoDeleteAfterDays: number;
        readonly lFramesDeleted: number;
        readonly lAllFramesAssigned: number;
        readonly lSeqDivAdjusted: number;
        readonly lReceiveJob: number;
        readonly lChangeSettings: number;
        readonly lDeleteFinished: number;
        readonly lDeleteDisabled: number;
        readonly lClearErrormessages: number;
        readonly lsetSoftX32: number;
        readonly lsetSoftX64: number;
        readonly lsetSoftXAll: number;
        readonly lmoveJobs: number;
        readonly lmarkFinished: number;
        readonly lDeassignClients: number;
        readonly lEmitChange: number;
        readonly lExportDebug: number;
        readonly lClientRenderAbortedLowMem: number;
        readonly lClientRenderAbortedFrozen: number;
        readonly lClientRenderError: number;
        readonly lClientWait: number;
        readonly lClientRenderAbortedHighCpu: number;
        readonly lAbortedFrameTime: number;
        readonly lAbortLowPriority: number;
        readonly lClientSegmentLessThanXs: number;
        readonly lClearErrormessagesEnable: number;
        readonly lFirstCheck: number;
        readonly lClientRenderAbortedWorkinghours: number;
        readonly lClientRenderAbortedProcessFound: number;
        readonly lClientRenderAbortedReservedClient: number;
        readonly lClientRenderAbortedHighPriorityJob: number;
        readonly lClientRenderAbortedrrControl: number;
        readonly lClientRenderAbortedAveraging: number;
        readonly lClientRenderAbortedLicenseBlock: number;
        readonly lClientRenderAbortedLocalMachine: number;
        readonly lDisableManyCrashes: number;
        readonly lDisableNoFrames: number;
        readonly lDisableNoOutputDir: number;
        readonly lDisableUNCFailed: number;
        readonly lDisableNoDriveSpace: number;
        readonly lClientAssignmentLost: number;
        readonly lClientAssignmentWrong: number;
        readonly lViewJobInfo: number;
        readonly lClientKSOClose: number;
        readonly lClientRenderAbortedDisabled: number;
    }
    
    interface _RROptions {
        readonly rroAbortLowJobs: number;
        readonly rroIgnoreCrashes: number;
        readonly rroAutoApprove: number;
        readonly rroSendSMS: number;
        readonly rroPreviewRendering: number;
        readonly rroNoWebsiteJpegs: number;
        readonly rroNoFrameChecking: number;
        readonly rroLittleJob: number;
        readonly rroMultipleInstances: number;
        readonly rroKeepSceneOpen: number;
        readonly rroAllowToDeleteCrashedFrame: number;
        readonly rroLocalSceneCopy: number;
        readonly rroTextureReplacements: number;
        readonly rroLocalRenderOut: number;
        readonly rroPreviewGamma22: number;
        readonly rroCropEXR: number;
        readonly rroMultiOSScene: number;
        readonly rroNoProcessTreeCheck: number;
        readonly rroOverwriteExisting: number;
        readonly rroNoFreezeDetection: number;
        readonly rroIsGPURender: number;
        readonly rroDisStartToEnd: number;
        readonly rroTotalrrOptions: number;
    }
    
    interface _RRParams {
        readonly rrpPreviewNumberOfFrames: number;
        readonly rrpMaxClientsAtATime: number;
        readonly rrpRequiredMemoryGB: number;
        readonly rrpMaxFrameTime: number;
        readonly rrpMinFileSizeKb: number;
        readonly rrpMaxCrashes: number;
        readonly rrpMaxLimitsReached: number;
        readonly rrpVerboseLevel: number;
        readonly rrpRenderQuality: number;
        readonly rrpColor: number;
    
        /**
         * @description Possible values: 0: No Approval Wait, 1: Wait before main render (after preview), 2: Wait after frames done (before finished-scripts), 3: Both (1+2).
         */
        readonly rrApproveJob: number;
    
        /**
         * @description No matter if there will be new options, this is always the total number of rrParams. Note for loop functions: This is not the ID of the last item!
         */
        readonly rrpTotalrrParameter: number;
    }
    
    interface _Status {
    
        readonly sNone: number;
    
        /**
         * @description Job was received, next server task is "first check" to find output dir and existing files.
         */
        readonly sFirstCheck: number;
    
        /**
         * @description Disabled while waiting for other jobs.
         */
        readonly sWaitForJobs: number;
    
        /**
         * @description About to execute pre-render scripts.
         */
        readonly sScriptPreRender: number;
    
        /**
         * @description Job is rendering the preview frames.
         */
        readonly sPreviewRender: number;
    
        /**
         * @description About to execute after-preview scripts.
         */
        readonly sScriptAfterPreview: number;
    
        /**
         * @description Waiting for user approval.
         */
        readonly sWaitForApprovalMain: number;
    
        /**
         * @description Disabled while waiting for other jobs.
         */
        readonly sWaitForJobsAfterPreview: number;
    
        /**
         * @description Main render of all frames.
         */
        readonly sMainRender: number;
    
        /**
         * @description About to execute post-render scripts.
         */
        readonly sScriptPostRender: number;
    
        /**
         * @description Waiting for user approval.
         */
        readonly sWaitForApprovalDone: number;
    
        /**
         * @description About to execute finished scripts.
         */
        readonly sScriptFinished: number;
    
        /**
         * @description Job is done.
         */
        readonly sFinished: number;
    }

    interface _SettingsOnly {
        seqStart: number;
        seqEnd: number;
        seqStep: number;
        seqFileOffset: number;
    
        /**
         * @description - not used -
         */
        seqFrameSet: string;
    
        /**
         * @description - not used -
         */
        seqIsFloatFrames: boolean;
        additionalCommandlineParam: string;
        userName: string;
        customSeqName: string;
        customShotName: string;
        customVersionName: string;
        companyProjectName: string;
        notifyFinish: string;
        notifyFinishClientName: string;
        notifyFinishParam: number;
        notifyFinishWhen: number;
    
        /**
         * @description The priority of the job.
         */
        priority: number;
    
        /**
         * @description Sequence Divide Min value.
         */
        seqDivMin: number;
    
        /**
         * @description Sequence Divide Max value.
         */
        seqDivMax: number;
    
        /**
         * @description The job is deactivated until this time.
         */
        timeToEnable: Date;
    
        /**
         * @description Number of pre/preview/post/finished commands for the job.
         */
        prePostCommandCount: number;
    
        /**
         * @description Number of custom options for the job  (custom options are set in the render config of the job).
         */
        customOptionsCount: number;
    
        // ----- FUNCTIONS -----
    
        /**
         * @description Use the enumeration _rrOption for ids. Example: rrbinding.createRRjob().rrOption(rrbinding.createRRjob().rroAbortLowJobs).
         * @param id The rrJob._rrOption id / enum value of the rrOption you want.
         * @returns The value of the specified rrOption of the job.
         */
        rrOption(id: number): boolean
    
        /**
         * @description Sets the rrOption of a job.
         * @param idx The index of the rrOption you want to set.
         * @param newValue The new value of the rrOption which should be changed.
         */
        rrOption_Set(idx: number, newValue: boolean): void;
    
        /**
         * @description Use the enumeration _rrParam for ids. Example: rrbinding.createRRjob().rrParam(rrbinding.createRRjob().rrpRequiredMemoryGB).
         * @param id The rrJob._rrParam id / enum value of the rrParam you want.
         * @returns The value of the specified rrParam of the job.
         */
        rrParam(id: number): number;
    
        /**
         * @description Sets the rrParam of a job.
         * @param idx The index of the rrParam you want to set.
         * @param newValue The new Value of the rrParam which should be changed.
         */
        rrParam_Set(idx: number, newValue: number): void;  
    }

    interface _RenderAppBasic {
        /**
         * @description Name of the render application (Maya, Nuke)
         */
        readonly name: string;
    
        /**
         * @description Name of the renderer (Vray, Arnold)
         */
        readonly rendererName: string;
    
        /**
         * @description Comp, 3D, Archive or Execute
         */
        readonly type: string;
    
        /**
         * @description Version of the renderer
         */
        readonly rendererVersion: string;
    
        /**
         * @description Version of the render application 
         */
        readonly version: number;
    
        /**
         * @description ID of the render config file.
         */
        readonly rendererConfigListID: number;
    
        /**
         * @description Sets if this is an execute job and if, which type of execute job
         * @see {@link http://www.royalrender.de/help8/index.html?modulerrGlobal.html}
         */
        readonly executeType: number;
    
        /**
         * @returns The minor version of the render app
         */
        versionMinorDisplay(): string
    
        /**
         * @description Set the minor and major version via a string. E.g. "2016.51"
         * @param ver new Version
         */
        setVersionBoth(ver: string): void
    
        /**
         * @description Set the minor version via a string. E.g. "031"
         * @param ver new Version
         */
        setVersionMinor(ver: string): void
    
        /**
         * @description Clears all settings
         */
        clearBasic(): void
    }
}

declare namespace Client {
    interface _ClientStatus {
        readonly name: string;
        readonly StructureID: number;
        readonly VariablesID: number;
        readonly localTextureSpaceUsed: number;
        readonly maxJobThreads: number;
        readonly CPU_Usage: number;
        readonly GPU_Usage: number;
        readonly gpuTemperature: number;
        readonly isRunningAsService: boolean;
        readonly availMemoryMB: number;
        readonly loggedUser: string;
        readonly maxCoresSetForJob: number;
    
        /**
         * @description Minutes since last user interaction.
         */
        readonly noUserInteraction: number;
        readonly version: string;
        readonly tempHDD: number;
    
        /**
         * @description The render thread by ID. The maximum threadID is maxJobThreads.
         * @param threadID ThreadID of the client status thread you want to fetch.
         */
        jobThread(threadID: number): _ClientStatusThread;
    }
    
    interface _ClientStatusThread {
        readonly jobID: Utils.rrUint64;
    
        /**
         * @description Start frame of the current segment as frame number and internal job number.
         */
        readonly jobSeqStart: number;
    
        /**
         * @description Start frame of the current segment as frame number and internal job number.
         */
        readonly jobSeqStartJobNr: number;
    
        /**
         * @description End frame of the current segment as frame number and internal job number.
         */
        readonly jobSeqEnd: number;
    
        /**
         * @description End frame of the current segment as frame number and internal job number.
         */
        readonly jobSeqEndJobNr: number;
    
        /**
         * @description Frame step of the current segment as frame number and internal job number.
         */
        readonly jobSeqStep: number;
    
        /**
         * @description Frame step of the current segment as frame number and internal job number.
         */
        readonly jobSeqStepJobNr: number;
    
        /**
         * @description Tile id.
         */
        readonly jobMultiFrameID: number;
        readonly jobIsPreview: boolean;
        readonly jobStatus: number;
        readonly clientStatus: number;
        readonly jobCPU_Usage: number;
        readonly jobMemoryUsageMB: number;
    
        /**
         * @returns True if the thread is keeping a scene in memory.
         */
        hasKSOLoaded(): boolean;
    
        /**
         * @returns True if the thread is rendering.
         */
        isRendering(): boolean
    
        /**
         * @returns The clientStatus+jobstatus of the thread as string.
         */
        clientStatusAsStringSingle(): string;
    }
}

declare namespace Utils {
    interface rrUint64 {
        readonly lower: number;
        readonly upper: number;
        toUint64Str(): string;
    }
}
