from src.server_api import ServerApi
from flask import Config
import os
import json


class RRManager:

    def __init__(self):
        pass

    def get_royal_api(self, user, passHash, config):
        """
        Returns an api obj for user
        :param user: user name
        :type user: basestring
        :param: config: flask config obj
        :type config: Config
        :return:
        :rtype: ServerApi
        """

        api = ServerApi(host=config.get('TMP_RR_IP'), port=config.get('RR_PORT'), verbose=config.get('RRLIB_VERBOSE'))
        #api.set_login_no_pass(user)
        api.set_login_passHash(user, passHash)

        return api

    def check_credentials(self, username, password, config):
        """
        Login credentials check
        :param username:
        :type username: basestring
        :param password:
        :type password: basestring
        :param config:
        :type config: Config
        :return:
        """

        api = ServerApi(host=config.get('TMP_RR_IP'), port=config.get('RR_PORT'), verbose=config.get('RRLIB_VERBOSE'))

        return api.set_login(username, password)

    def save_statistics(self, api):
        """
        Save connection statistics log file
        :param api: the RR api object
        :type api: ServerApi
        :return:
        """

        logs_folder = os.getcwd() + os.path.sep + "logs"

        if not os.path.isdir(logs_folder):
            os.makedirs(logs_folder)
        else:
            appendable = api.get_stats()['connectionStatsJSON']
            stats = self.read_statistics()
            stats.update(appendable)
            try:
                with open(logs_folder + os.path.sep + "stats.log", 'w') as logfile:
                    logfile.write(str(stats))
            except Exception as e:
                return

    def read_statistics(self):
        """
        Returns a list of connection stats
        :return:
        :rtype: dict
        """

        logs_folder = os.getcwd() + os.path.sep + "logs"

        stats = {}
        if not os.path.isdir(logs_folder):
            os.makedirs(logs_folder)
        else:
            try:
                with open(logs_folder + os.path.sep + "stats.log", 'r') as logfile:
                    lines = logfile.readlines()
                    for line in lines:
                        stats.update(json.loads(line))
            except Exception as e:
                return stats
        return stats
