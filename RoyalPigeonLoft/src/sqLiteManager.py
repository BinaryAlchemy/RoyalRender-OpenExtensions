import sqlite3
from flask.sessions import SecureCookieSession
import os
import time
import json
import uuid
import logging
from uuid import UUID
from functools import wraps
from src.rrUtils import UserSettings
import traceback

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
    trc = 'Traceback:\n'
    stackstr = trc + ''.join(stack)
    #if exc is not None:
    #     stackstr += '  ' + traceback.format_exc().lstrip(trc)
    return stackstr

# DB WRITE Wrapper
def writes_db(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        try:
            return f(*args, **kwargs)
        except Exception as e:
            logging.error("Writing on DB: "+ str(e)+"\n"+str(traceback.format_exc(limit=6)))
            logging.error(str(full_stack(True)))
    return wrap


# DB READ Wrapper
def reads_db(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        try:
            return f(*args, **kwargs)
        except Exception as e:
            logging.error("Reading on DB "+str(e))
    return wrap


class SqLiteManager:

    def __init__(self, path, name, user='', password='', session_time=300):
        """

        :param path: path to db file
        :param name: name of db file
        :param user: db username
        :param password: db passw
        :param session_time: Session time in seconds
        """

        self.db_path = path
        self.db_name = name
        self.user = user
        self.password = password
        self.session_time = session_time

        self.initialize_db()
        self.update_db()

        self.cleanup_db()

    def _get_database(self):
        """
        Returns a db connection instance
        :return:
        :rtype: sqlite3.Connection
        """

        if not os.path.isdir(self.db_path):
            os.makedirs(self.db_path)

        complete_path = os.path.sep.join([self.db_path, self.db_name])

        try:
            return sqlite3.connect(complete_path)
        except Exception as e:
            logging.error("Unable to connect to DB")
            logging.error(str(e))

    def _get_cursor(self):
        """
        Returns a cursor to DB
        :return:
        :rtype: sqlite3.Cursor
        """

        conn = self._get_database()

        try:
            return conn.cursor()
        except Exception as e:
            logging.error("Unable to get cursor")
            logging.error(str(e))

    def _close(self, cursor):
        """
        Closes cursor and connection
        :param cursor:
        :type cursor: sqlite3.Cursor
        :return:
        """

        conn = cursor.connection
        cursor.close()
        conn.close()

    def _commit_and_close(self, cursor):
        """
        Commits and closes cursor and connection
        :param cursor:
        :type cursor: sqlite3.Cursor
        :return:
        """

        conn = cursor.connection
        conn.commit()
        cursor.close()
        conn.close()

    @writes_db
    def _execute_scripts(self, path, script_list, store=False):
        """
        Sequentially executes a list of scripts on the managed sqlite DB.
        The caller is responsible for the execution order
        :param path: where to
        :type path: str
        :param script_list: list of script file names
        :type script_list: list
        :param store: if True stores the script as executed in the executed_scripts table
        :type store: bool
        :return:
        """

        cur = self._get_cursor()

        for script in script_list:
            script_path = os.path.sep.join([path, script])
            if os.path.isfile(script_path) and script.endswith(".sql"):
                with open(script_path) as script_file:
                    statements = script_file.read().split(";")
                    for statement in statements:
                        cur.execute(statement)
                    if store:
                        now = int(time.time())
                        cur.execute("insert into EXECUTED_SCRIPTS (name, execution_time) values (?, ?)",
                                    (script, now))
                    logging.info("Updating DB... executed script: " + script)

        self._commit_and_close(cur)

    @writes_db
    def _ignore_scripts(self, path, script_list):
        """
        Flags scripts as executed in the DB
        :param path: scripts path
        :type path: str
        :param script_list: a list of scripts to ignore
        :type script_list: list
        :return:
        """

        cur = self._get_cursor()

        for script in script_list:
            script_path = os.path.sep.join([path, script])
            if os.path.isfile(script_path) and script.endswith(".sql"):
                now = int(time.time())
                cur.execute("insert into EXECUTED_SCRIPTS (name, execution_time) values (?, ?)",
                            (script, now))
                logging.debug("Deactivating script: " + script)

        self._commit_and_close(cur)

    @writes_db
    def _create_schema(self):
        """
        Sqlite DB basic initialization
        :return:
        """

        cur = self._get_cursor()

        # EXECUTED_SCRIPTS TABLE to manage DB updates
        cur.execute("create table EXECUTED_SCRIPTS (NAME varchar(255) primary key, EXECUTION_TIME integer)")

        logging.info("Created a new RoyalRender DB")

        self._commit_and_close(cur)

    def initialize_db(self):
        """
        Initializes DB with scripts found in /db/init/sqlite
        Scripts are executed in alphabetical order
        :return:
        """

        init_path = os.path.sep.join([self.db_path, 'init', 'sqlite'])
        if not os.path.exists(init_path):
            os.makedirs(init_path)

        update_path = os.path.sep.join([self.db_path, 'update', 'sqlite'])
        if not os.path.exists(update_path):
            os.makedirs(update_path)

        if not os.path.isfile(os.path.sep.join([self.db_path, self.db_name])):
            self._create_schema()
            script_list = os.listdir(init_path)
            script_list.sort()
            self._execute_scripts(path=init_path, script_list=script_list)

            # ignore update scripts. init scripts must take care of DB updates
            script_list = os.listdir(update_path)
            script_list.sort()
            self._ignore_scripts(update_path, script_list)

    @reads_db
    def update_db(self):
        """
        Updates the DB with scripts found in /db/update/sqlite
        Scripts are first checked for execution then executed in alphabetical order
        :return:
        """

        cur = self._get_cursor()
        cur.execute("SELECT name from EXECUTED_SCRIPTS")
        out = cur.fetchall()
        names = (row[0] for row in out)
        executed_set = set(names)

        update_path = os.path.sep.join([self.db_path, 'update', 'sqlite'])
        script_list = list(set(os.listdir(update_path)).difference(executed_set))
        script_list.sort()

        self._execute_scripts(path=update_path, script_list=script_list, store=True)

    def cleanup_db(self):
        """
        Performs cleanup ops befor DB startup.
        :return:
        """

        self.empty_memory_usage_stats()

    @writes_db
    def empty_memory_usage_stats(self):
        """
        Removes all rows from MEMORY_USAGE_STATS TABLE
        :return:
        """

        cur = self._get_cursor()

        cur.execute("DELETE from MEMORY_USAGE_STATS")

        self._commit_and_close(cur)

    @writes_db
    def store_session(self, session):
        """
        Stores session info
        :param session:
        :type session: SecureCookieSession
        :return:
        :rtype: UUID
        """
 
        expiration = int(time.time()) + self.session_time
        uuid_id = uuid.uuid4().hex
        #uuid_id= bytes(uuid_id, "ascii")
        logging.info("---DB----  store_session "+str(uuid_id)+"   "+str(session["passHash"]))

        cur = self._get_cursor()
        cur.execute("insert into sessions(id, user, expiration, passhash) values (?, ?, ?, ?)",                    
        (uuid_id, session["username"], expiration, session["passHash"]))
        self._commit_and_close(cur)

        return uuid_id

    @writes_db
    def delete_session(self, session_id):
        """
        Removes session from DB
        :param session_id: id
        :type session_id: UUID
        :return:
        """

        session_id = session_id

        cur = self._get_cursor()
        cur.execute("DELETE FROM sessions where id=?", (session_id,))

        self._commit_and_close(cur)

    @writes_db
    def delete_expired_sessions(self):
        """
        Removes all expired sessions from DB
        :return:
        """

        now = int(time.time())

        cur = self._get_cursor()
        cur.execute("DELETE FROM sessions where expiration<?", (now,))

        self._commit_and_close(cur)

    @writes_db
    def refresh_session(self, session_id):
        """
        Restores session as active
        :param session_id:
        :return:
        """

        expiration = int(time.time()) + self.session_time

        session_id = session_id

        cur = self._get_cursor()
        cur.execute("UPDATE sessions SET expiration=? where id=?", (expiration, session_id,))

        self._commit_and_close(cur)

    @reads_db
    def get_active_sessions(self):
        """
        Returns a sessions list
        :return:
        :rtype: list
        """

        now = int(time.time())

        cur = self._get_cursor()
        cur.execute("SELECT id from sessions where expiration>?", (now,))
        rows = cur.fetchall()

        return rows

    @reads_db
    def is_session_valid(self, session_id):
        """
        Returns true if session exists and it's not expired
        :param session_id: UUID
        :return:
        """
        now = int(time.time())

        session_id = session_id
        logging.info("---DB----  is_session_valid "+str(session_id)+"   "+str(type(session_id)))

        cur = self._get_cursor()
        cur.execute("SELECT expiration from sessions where id=?", (session_id,))
        expiration = cur.fetchone()

        if not expiration:
            return False

        return now < expiration[0]

    @reads_db
    def get_session(self, session_id):
        """
        Get specific session info
        :param session_id:
        :return:
        """

        session_id = session_id

        cur = self._get_cursor()
        cur.execute("SELECT id from sessions where id=?", (session_id,))
        row = cur.fetchone()

        return row

    @writes_db
    def store_statistics(self, statistics):
        """
        Stores last stats list
        :param statistics:
        :type statistics: list
        :return:
        """

        now = int(time.time())

        cur = self._get_cursor()

        for stat in statistics:

            cur.execute("insert into connection_statistics (json, timestamp) values (?, ?)", (json.dumps(stat), now,))

        self._commit_and_close(cur)

    @writes_db
    def store_mem_statistics(self, worker_id, mem_occupation):
        """
        Stores memory occupation on DB
        :param worker_id: ID of worker
        :type worker_id: uuid.UUID
        :param mem_occupation: Mem occupation
        :type mem_occupation: int
        :return:
        """
        now = int(time.time())

        cur = self._get_cursor()

        cur.execute("INSERT into MEMORY_USAGE_STATS (worker_id, memory_occupation, timestamp) values (?, ?, ?)",
                    (str(worker_id), mem_occupation, now,))

        self._commit_and_close(cur)

    @reads_db
    def get_mem_statistics(self, window=60):
        """
        Gets the memory statistics stored in the last 'window' minutes
        :param window:
        :return:
        """

        cur = self._get_cursor()
        now = int(time.time())
        before = now - window*60
        cur.execute("SELECT worker_id, memory_occupation, TIMESTAMP from MEMORY_USAGE_STATS where timestamp > ?",
                    (before,))
        rows = cur.fetchall()

        mem_stats = {'total': [], 'window_mins': window, 'timestamps': [], 'workers': {}}

        for r in rows:
            if r[0] not in mem_stats['workers']:
                mem_stats['workers'][r[0]] = []
            mem_stats['workers'][r[0]].append(r[1])
            mem_stats['total'].append(r[1])
            mem_stats['timestamps'].append(r[2])

        return mem_stats

    @reads_db
    def get_statistics(self, n_max):
        """
        Returns last 'max' statistics
        :return:
        """

        cur = self._get_cursor()
        cur.execute("SELECT json from connection_statistics order by timestamp desc ")
        rows = cur.fetchmany(n_max)

        d_list = [json.loads(r[0]) for r in rows]

        return d_list

    @writes_db
    def delete_old_statistics(self, past):
        """
        Removes all expired sessions from DB
        :param past: older than past secs
        :type past: int
        :return:
        """

        limit = int(time.time()) - past

        cur = self._get_cursor()
        cur.execute("DELETE FROM connection_statistics where timestamp<?", (limit,))

        self._commit_and_close(cur)

    @reads_db
    def get_user_settings(self, user):
        """
        Returns the user settings
        :param user:
        :type user: basestring
        :return:
        """

        cur = self._get_cursor()
        cur.execute("SELECT * from USER_SETTINGS where NAME=?", (user,))

        values = cur.fetchone()

        if not values:
            self.create_user_settings(user)
            cur.execute("SELECT * from USER_SETTINGS where NAME=?", (user,))
            values = cur.fetchone()

        columns = [description[0] for description in cur.description]

        user_settings = UserSettings.from_table_row(columns, values)

        return user_settings

    @writes_db
    def create_user_settings(self, user_name):
        """
        Creates a new user settings entry if it does not exist
        :param user_name:
        :type user_name: basestring
        :return:
        """

        cur = self._get_cursor()
        cur.execute("INSERT into USER_SETTINGS (NAME) VALUES (?)", (user_name,))
        self._commit_and_close(cur)

    @writes_db
    def update_user_settings(self, user_name, user_settings):
        """
        Saves new user settings
        :param user_name:
        :type user_name: basestring
        :param user_settings:
        :type user_settings: dict
        :return:
        """

        columns = []
        values = []

        for key in user_settings.keys():
            _key = key.replace("_", "").lower()
            if _key == "jobs":
                # JOBS
                for inkey in user_settings[key].keys():
                    val = user_settings[key][inkey]
                    val = int(val) if isinstance(val, bool) else val
                    values.append(val)
                    inkey = inkey.replace("_", "").replace(" ", "").lower()
                    columns.append(str("_".join(["jobs", inkey])))
            if _key == "clients":
                # CLIENTS
                for inkey in user_settings[key].keys():
                    val = user_settings[key][inkey]
                    val = int(val) if isinstance(val, bool) else val
                    values.append(val)
                    inkey = inkey.replace("_", "").replace(" ", "").replace("%", "").lower()
                    columns.append(str("_".join(["clients", inkey])))
            if _key == "filter":
                # FILTER
                for inkey in user_settings[key].keys():
                    val = user_settings[key][inkey]
                    val = int(val) if isinstance(val, bool) else val
                    values.append(val)
                    inkey = inkey.replace("_", "").replace(" ", "").lower()
                    columns.append(str("_".join(["filter", inkey])))

        values.append(user_name)

        cur = self._get_cursor()

        query_text = str.format("UPDATE USER_SETTINGS SET " + "=?, ".join(columns) + "=? WHERE NAME=?")

        cur.execute(query_text, tuple(values))

        self._commit_and_close(cur)


if __name__ == "__main__":
    man = SqLiteManager("../db", "test.sql", session_time=1)

    us_sett = {"Name": "renderfarm", "filter": {"Not Rendering": True, "Project": "--all--"}, "jobs": {"Basic": True}}

    curr_sett = man.get_user_settings(user=us_sett["Name"])

    curr_sett['filter']['Project'] = 'unforeseen'

    man.update_user_settings(curr_sett['name'], curr_sett)

    # man = SqLiteManager("../db", "rr_data.sql", session_time=1)

    # _cur = man._get_cursor()
    # _cur.execute("SELECT * from sessions")
    # rows = _cur.fetchall()

    _session = {'username': 'USER'}
    _session['uid'] = man.store_session(_session)
    _session_list = man.get_active_sessions()
    if man.is_session_valid(_session['uid']):
        print("active")
    else:
        print("updating")
        man.refresh_session(_session['uid'])

    # statz = [{'one': 1}, {'two': 2}]
    # man.store_statistics(statz)

    # _res = man.get_statistics(10)
    #
    # l = [x[1] for x in _res]
    # o = [json.loads(e.replace("\'", "\"")) for e in l]

    print("over")
