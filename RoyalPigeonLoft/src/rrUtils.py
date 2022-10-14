import os
import sys
import struct
import time
import json
import logging
from collections import OrderedDict
from logging.config import dictConfig


if sys.version_info[0] >= 3:
    basestring = str


# Logging
def setup_logs(debugMode):
    """
    Sets up logging
    :return:
    """

    if not os.path.isdir('logs'):
        os.mkdir('logs')
    if (debugMode):
        dictConfig({
            'version': 1,
            'formatters': {'default': {
                'format': '[%(asctime)s] %(levelname)s in %(module)s: %(message)s',
            }},
            'handlers': {'file': {
                'class': 'logging.handlers.TimedRotatingFileHandler',
                'filename': 'logs/royal.log',
                'formatter': 'default',
                'backupCount': 5,
                'when': 'midnight',
                'interval': 1
            }},
            'root': {
                'level': 'DEBUG',
                'handlers': ['file']
            }
        })
    else:
        dictConfig({
            'version': 1,
            'formatters': {'default': {
                'format': '[%(asctime)s] %(levelname)s in %(module)s: %(message)s',
            }},
            'handlers': {'file': {
                'class': 'logging.handlers.TimedRotatingFileHandler',
                'filename': 'logs/royal.log',
                'formatter': 'default',
                'backupCount': 5,
                'when': 'midnight',
                'interval': 1
            }},
            'root': {
                'level': 'INFO',
                'handlers': ['file']
            }
        })


# Installation utilities
def getRR_Root():
    # getRR_Root derived from findRR_Root returns the RR path as search path for the module
    # This function will only work if RR was installed on the machine
    # If you are using it from an external machine, you have to add the path to the rrPy module yourself
    # sys.path.append(MyModulePath)

    if 'RR_ROOT' not in os.environ:
        return ""
    modPath = os.environ['RR_ROOT']
    is64bit = (struct.calcsize("P") == 8)
    if sys.platform.lower() == "win32":
        if is64bit:
            modPath = modPath + '/bin/win64'
        else:
            modPath = modPath + '/bin/win'
        modPath = modPath.replace("\\", "/")
    elif sys.platform.lower() == "darwin":
        if is64bit:
            modPath = modPath + '/bin/mac64/lib/python/27'
        else:
            modPath = modPath + '/bin/mac/lib/python/27'
    else:
        modPath = modPath + '/bin/lx64/lib'
    modPath = modPath.replace("_debug", "_release")
    return modPath
    # sys.path.append(modPath)
    # print("added module path " + modPath)


# Timestamp utilities
def timeformat(seconds):
    """
    Returns a 'Xd Yh' if seconds > 24h else 'HH:mm:ss'
    :param seconds:
    :type seconds: int or str
    :return:
    :rtype: str
    """

    if seconds < 0:
        return ""

    seconds = float(seconds)

    if seconds > (3600 * 24):
        days, remainder = divmod(seconds, 3600*24)
        hours, remainder = divmod(remainder, 3600)
        return "%sd %sh" % (int(days), int(hours))
    else:
        return time.strftime("%H:%M:%S", time.gmtime(seconds))


def seconds_to_minutes(seconds):
    """
    Returns m,sec as string
    :param seconds:
    :type seconds: int
    :return:
    :rtype: str
    """

    mins, secs = divmod(seconds, 60)

    return ".".join([str(mins), time.strftime("%S", time.gmtime(secs))])


# Filter class
class JobFilter(dict):

    ALL_STRING = "-- all --"
    age_options = ["1 day", "2 days", "3 days", "1 week", "2 weeks"]
    bool_options = ["Finished", "Waiting", "Disabled", "Rendering", "Not Rendering"]
    keys_to_convert = {"App": "render_app", "Age": "age", "Project": "project", "User": "username"}

    def __init__(self, *args, **kwargs):
        dict.__init__(self)
        self["username"] = ""
        self["project"] = ""
        self["render_app"] = ""
        self["age"] = 0
        self["includes"] = ""
        self["invert"] = False

        for field in self.bool_options:
            self[field] = False
        self["filter_mask"] = 0

        for k in kwargs:
            k_ = k
            if k in self.keys_to_convert:
                k_ = self.keys_to_convert[k]
            self[k_] = kwargs[k]

    def __getitem__(self, k):
        if k == "filter_mask":
            mask = int("".join(str(int(self[field])) for field in self.bool_options), 2)
            return mask
        else:
            return super(JobFilter, self).__getitem__(k)

    def __setitem__(self, k, v):
        if v == self.ALL_STRING:
            v = ""
        if k == "age":
            self["ageString"] = v
            if v in self.age_options:
                v = self._age_to_days(v)
            else:
                v = 0

        super(JobFilter, self).__setitem__(k, v)

    def _age_to_days(self, age):
        """
        Transforms age string to num of days
        :param age:
        :type age: basestring
        :return: num of days
        :rtype: int
        """

        if age not in self.age_options:
            e = Exception()
            e.message = "JobFilter cannot convert invalid age: " + str(age)
            raise e

        if "day" in age:
            return int(age.split(" ")[0])
        elif "week" in age:
            return 7*int(age.split(" ")[0])


class JobGroupsSnapshot:

    def __init__(self):
        self.job_groups = OrderedDict()
        self.job_groups_filtered = OrderedDict()
        self.apps = []
        self.users = []


class UserSettings(OrderedDict):

    @classmethod
    def from_table_row(cls, columns, values):
        """
        Returns User Settings from DB table row
        :param columns: column names
        :type columns: list
        :param values: values in the row
        :type: list
        :return:
        :rtype: UserSettings
        """

        new = UserSettings()

        for col, val in zip(columns, values):

            key = str(col).split("_")[0].lower()

            if key == "name":
                new['name'] = val
                continue

            subkey = str(col).split("_")[1].lower().capitalize()

            # Special Cases
            subkey = "Not Rendering" if subkey == "Notrendering" else subkey
            subkey = "CPU%" if subkey == "Cpu" else subkey
            subkey = "GPU%" if subkey == "Gpu" else subkey

            if key not in new:
                new[key] = UserSettings()

            new[key][subkey] = val

        return new

    def deep_update(self, other=None, **kwargs):
        """
        Recursive deep update of UserSettings object
        :param other: The other UserSettings (its values overwrite)
        :type other: UserSettings
        :param kwargs:
        :return:
        """

        for k in other.keys():
            if issubclass(type(other[k]), UserSettings):
                if k not in self or not issubclass(type(self[k]), UserSettings):
                    self[k] = UserSettings()
                self[k].deep_update(other[k], **kwargs)
            else:
                self[k] = other[k]

        if 'off_booleans' in kwargs and kwargs['off_booleans']:
            for k in self.keys():
                if issubclass(type(self[k]), bool) and k not in other.keys():
                    self[k] = False

    def to_json(self, pretty=False):
        """
        Convert UserSettings object into a json string
        :param pretty: add newlines to json string
        :type pretty: bool
        :return:
        """

        out = ""
        for k in self:
            if not issubclass(type(self[k]), UserSettings):
                if issubclass(type(self[k]), bool):
                    out += '"' + k + '": ' + str(self[k]).lower() + ', '
                elif issubclass(type(self[k]), basestring):
                    out += '"' + k + '": "' + str(self[k]) + '", '
                else:
                    out += '"' + k + '": ' + str(self[k]) + ', '
            else:
                out += '"' + k + '": ' + self[k].to_json() + ', '

        out = '{' + out.rstrip(', ') + '}'

        if pretty:
            out = out.replace('{', '{\n')
            out = out.replace('}', '\n}')
            out = out.replace(', ', ',\n')

        return out

    def dump(self, fp, pretty=False):
        """
        dumps a json version of UserSettings
        :param fp: file pointer
        :type fp: BinaryIO
        :param pretty: add newlines to dump
        :type pretty: bool
        :return:
        """

        content = self.to_json(pretty=pretty)
        fp.write(content)


class SettingsManager:
    """
    json based user settings manager.
    Uses UserSettings class
    """

    def __init__(self, user):
        """
        :param user:
        :type user: str
        """

        self.username = user
        self.settings = UserSettings()

    @staticmethod
    def reset_user_options():
        """
        Resets the user_options.json file
        :return:
        """

        with open("./settings/user_options.json", "w") as settings_file:
            empty_settings = UserSettings()
            empty_settings.dump(settings_file)

    def _read_settings(self):
        """

        :return:
        :rtype: UserSettings
        """

        if not self.username:
            return UserSettings()

        try:
            with open("./settings/user_options.json") as settings_file:
                all_settings = json.load(settings_file, object_pairs_hook=UserSettings)
        except Exception as e:
            logging.debug("Can't find user_options.json... recreating" + str(e))
            self.reset_user_options()
            all_settings = UserSettings()

        if self.username in all_settings.keys():
            return all_settings[self.username]
        else:
            with open("./settings/default_user_options.json") as default_settings_file:
                default_settings = json.load(default_settings_file, object_pairs_hook=UserSettings)
                return default_settings["default"]

    def get_settings(self):
        return self.settings

    def update_settings(self, settings=None):
        """

        :param settings:
        :type settings: UserSettings
        :return:
        """

        if settings:
            for k in settings.keys():
                self.settings[k].deep_update(settings[k], off_booleans=True)

        try:
            with open("./settings/user_options.json", "r") as settings_file:
                all_settings = json.load(settings_file, object_pairs_hook=UserSettings)

                if self.username not in all_settings:
                    all_settings[self.username] = UserSettings()
        except Exception as e:
            all_settings = UserSettings()
            all_settings[self.username] = UserSettings()
            logging.error("update_settings, reading file user_options.json")
            logging.error(str(e))

        for k in self.settings.keys():
            if k not in all_settings[self.username]:
                all_settings[self.username][k] = UserSettings()
            all_settings[self.username][k].deep_update(self.settings[k], off_booleans=True)
        with open("./settings/user_options.json", "w") as settings_file:
            all_settings.dump(settings_file, pretty=True)


if __name__ == "__main__":

    us = UserSettings()
    us['filter'] = UserSettings()
    us['clients'] = UserSettings()
    us['filter']['NotRendering'] = True
    us['filter']['Disabled'] = True
    us['clients']['Debug'] = True
    us['clients']['max_num'] = 12.8
    us['clients']['comment'] = "no way"

    print(us.to_json(pretty=True))

    un = UserSettings()
    un['filter'] = UserSettings()
    un['clients'] = UserSettings()
    un['filter']['Disabled'] = True
    un['clients']['max_num'] = 12.8
    un['clients']['comment'] = "no way"

    us.deep_update(un)

    print(us.to_json(pretty=True))

    f = JobFilter()
    f["Finished"] = True
    f["age"] = "1 day"
    print(f["filter_mask"])
