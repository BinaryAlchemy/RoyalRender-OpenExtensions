import os
import sys

mod_dir = os.path.dirname(__file__)
if mod_dir not in sys.path:
    sys.path.append(mod_dir)
mod_dir = os.path.dirname(__file__)+'/modules'
if mod_dir not in sys.path:
    sys.path.append(mod_dir)
    
    
# is_Running_OnPremise modes:
# - is_Running_OnPremise= True
#       This version was designed to run from within your on-premise RR environment (Env var RR_ROOT defined)
#       It copies all required modules and libs into the folder '/modules'
# - is_Running_OnPremise= False
#       All required RR modules and libs have to be provided in folder '/modules'
#       Please see ReadMe in folder '/modules'

is_Running_OnPremise= True
if (is_Running_OnPremise):
    os.environ["RR_PYTHON_CACHE_FOLDER"] = mod_dir
else:
    os.environ["RR_PYTHON_LIBS_FOLDER"] = mod_dir




from flask import Flask, render_template, flash, redirect, url_for, session, request, jsonify, \
    send_from_directory, abort
from flask.sessions import SecureCookieSession
import logging
from datetime import datetime
# from wtforms import Form, StringField, TextAreaField, PasswordField, validators
# from passlib.hash import sha256_crypt
from functools import wraps
from src.server_api import ServerApi
from src.rrUtils import JobFilter, UserSettings, setup_logs
from src.rrAppMemoryManager import RRAppMemoryManager
from src.rrManager import RRManager
from src.sqLiteManager import SqLiteManager
from src.rrScheduler import RRScheduler
from uuid import uuid4

if sys.version_info[0] >= 3:
    long = int

config_path = os.path.dirname(__file__)+'/instance'

app = Flask(__name__, instance_relative_config=True)
#app = Flask(__name__, instance_path=config_path,  instance_relative_config=True)
app.config.from_object('config.default')
app.config.from_pyfile('config.py')
app.config['WORKER_ID'] = uuid4()
setup_logs(app.config.get('PIGEONLOFT_DEBUG'))


manager = RRManager()
db_manager = SqLiteManager(app.config.get('DB_PATH'), app.config.get('DB_NAME'),
                           session_time=app.config.get('SESSION_TIMEOUT'))

rr_sched = RRScheduler(app.config.get('RR_SCHEDULER_INTERVAL'))
rr_sched.add_callback(db_manager.delete_expired_sessions)

if 'STATS_EXPIRATION_TIME' in app.config:
    rr_sched.add_callback(db_manager.delete_old_statistics, past=app.config.get('STATS_EXPIRATION_TIME'))

rr_sched.start()


# Check if user logged in
def is_logged_in(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'uid' in session:
            if db_manager.is_session_valid(session['uid']):
                return f(*args, **kwargs)
            else:
                session.clear()
                flash('Session expired, please login again', 'danger')
                return redirect(url_for('login'))
        else:
            return redirect(url_for('login'))
    return wrap


def is_logged_in_ajax(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'uid' in session and db_manager.is_session_valid(session['uid']):
            return f(*args, **kwargs)
        else:
            session.clear()
            flash('Session expired, please login again', 'danger')
            return abort(403)
    return wrap


# Logout
@app.route('/logout')
def logout():
    if 'uid' in session:
        db_manager.delete_session(session['uid'])
        session.clear()
        flash('You are now logged out', 'success')
    return redirect(url_for('login'))


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == 'POST':
        # Get Form Fields
        username = request.form['username']
        password_candidate = request.form['password']
        request.api = ServerApi(host=app.config.get('TMP_RR_IP'), port=app.config.get('RR_PORT'), verbose=app.config.get('RRLIB_VERBOSE'))
        success, errMsg = request.api.set_login(username, password_candidate)
        if success:
            # Passed
            session['username'] = username
            session['passHash'] = request.api.getPassHash()
            logging.debug("getPassHash "+session['passHash'] )
            session['uid'] = db_manager.store_session(SecureCookieSession(session))

            flash('You are now logged in', 'success')
            return redirect(url_for('get_jobs'))
        else:
            flash(str(errMsg), 'success')
            invalid_login_message = 'Invalid login attempt\\n'+str(errMsg)
            return render_template('login.html', navbar=False, invalid_login_message=invalid_login_message)

    return render_template("login.html", navbar=False)


@app.route("/")
@app.route("/home")
@is_logged_in
def index():
    return render_template("home.html", navbar=True)


@app.route("/dashboard", methods=["GET", "POST"])
@is_logged_in
def dashboard():
    """
    WARNING USE ONLY TEXT (STR) OR CHKBOXES (BOOL) IN THE DASHBOARD
    """
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    if request.method == 'POST':
        settings = db_manager.get_user_settings(session['username'])
        for option in settings['clients'].keys():
            if option in request.form.getlist("clients"):
                settings['clients'][option] = True
            elif not issubclass(settings['clients'][option].__class__, str):
                settings['clients'][option] = False
        for option in settings['jobs'].keys():
            if option in request.form.getlist("jobs"):
                settings['jobs'][option] = True
            elif not issubclass(settings['jobs'][option].__class__, str):
                settings['jobs'][option] = False

        db_manager.update_user_settings(session['username'], settings)
        return redirect(url_for('get_jobs'))
    else:
        settings = db_manager.get_user_settings(session['username'])
        return render_template("dashboard.html", navbar=True, settings=settings)


@app.route("/jobs", methods=["GET", "POST"])
@is_logged_in
def get_jobs():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    settings = db_manager.get_user_settings(session['username'])
    time_now = datetime.now().strftime("%H:%M")

    if request.method == 'POST' and ('save_filter' in request.form or 'filter_jobs' in request.form):

        checked_boxes = request.form.getlist("filterChkBox")

        if 'save_filter' in request.form:
            new_settings = UserSettings()
            new_settings["filter"] = UserSettings()

            for field in ["Not Rendering", "Rendering", "Disabled", "Waiting", "Finished"]:
                if field in checked_boxes:
                    new_settings["filter"][field] = True
                else:
                    new_settings["filter"][field] = False

            new_settings["filter"]["Project"] = request.form.get("projectSelect")
            new_settings["filter"]["User"] = request.form.get("userSelect")
            new_settings["filter"]["App"] = request.form.get("appSelect")
            new_settings["filter"]["Age"] = request.form.get("ageSelect")

            db_manager.update_user_settings(session['username'], new_settings)

        if 'filter_jobs' in request.form:
            checked_boxes = request.form.getlist("filterChkBox")

        current_filter = JobFilter()

        for field in ["Not Rendering", "Rendering", "Disabled", "Waiting", "Finished", "invert"]:
            if field in checked_boxes:
                current_filter[field] = True
            else:
                current_filter[field] = False

        current_filter["username"] = request.form.get("userSelect")
        current_filter["project"] = request.form.get("projectSelect")
        current_filter["render_app"] = request.form.get("appSelect")
        current_filter["age"] = request.form.get("ageSelect")
        current_filter["includes"] = request.form.get("includeText") or ""

        session['current_filter'] = current_filter

        snap = request.api.get_job_groups_snapshot(current_filter)

        return render_template("jobs.html", navbar=True, snapshot=snap, settings=settings["jobs"],
                               filter_settings=current_filter, show_filter=True, time_now=time_now)

    if 'current_filter' in session.keys():
        current_filter = JobFilter(**session['current_filter'])
    else:
        current_filter = JobFilter(**settings["filter"])
        session['current_filter'] = current_filter

    snap = request.api.get_job_groups_snapshot(current_filter)

    return render_template("jobs.html", navbar=True, snapshot=snap, settings=settings["jobs"],
                           filter_settings=current_filter, show_filter=False, time_now=time_now)


@app.route("/project", methods=["POST"])
@is_logged_in_ajax
def get_project():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    if 'current_filter' in session.keys():
        job_filter = JobFilter(**session['current_filter'])
        request.api.set_job_filter(job_filter)
    response = {}
    project = request.form["project"]
    id_ = request.form["id"]
    jobs = request.api.get_jobs_by_project(project, filtered=True)

    if len(jobs) > 0:
        settings = db_manager.get_user_settings(session['username'])
        response['htmlBody'] = render_template("job_group.html", jobs=jobs, id=id_, settings=settings["jobs"])
        response['htmlHead'] = render_template("job_head.html", job=jobs[0], settings=settings["jobs"])
        response['n_jobs'] = len(jobs)
    return jsonify(response)


@app.route("/jobs_detail", methods=["GET"])
@is_logged_in
def get_jobs_details():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    if 'current_filter' in session.keys():
        job_filter = JobFilter(**session['current_filter'])
        request.api.set_job_filter(job_filter)
        request.api.update()
    jobs = []
    if 'job_id' in request.args:
        ids = request.args['job_id'].split(",")
        for id_ in ids:
            id_long = long(id_)
            job = request.api.get_job_by_id(id_long)
            if not job:
                flash("Selected job is no longer available", "warning")
                return redirect(url_for("get_jobs"))
            jobs.append(job)
    if 'project_id' in request.args:
        # todo: this is problematic jobs to be shown should be those currently available
        jobs = request.api.get_jobs_by_project(request.args['project_id'], filtered=True)
    return render_template("jobs_detail.html", jobs=jobs, navbar=True)


@app.route("/clients_detail", methods=["GET"])
@is_logged_in
def get_clients_details():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    clients = []
    if 'client_id' in request.args:
        indexes = request.args['client_id'].split(",")
        for idx_str in indexes:
            idx = int(idx_str)
            client = request.api.get_client(idx)
            clients.append(client)
    if 'group_id' in request.args:
        clients = request.api.get_clients_by_group(request.args['group_id'])
    return render_template("clients_detail.html", clients=clients, navbar=True)


@app.route("/clients", methods=["GET", "POST"])
@is_logged_in
def get_clients():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    client_groups = request.api.get_client_groups(update=True)
    time_now = datetime.now().strftime("%H:%M")

    return render_template("clients.html", navbar=True, client_groups=client_groups, time_now=time_now)


@app.route("/client_group", methods=["POST"])
@is_logged_in_ajax
def get_client_group():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    response = {}
    group = request.form["group"]
    id_ = request.form["id"]
    clients = request.api.get_clients_by_group(group)
    if len(clients) > 0:
        settings = db_manager.get_user_settings(session['username'])
        response['htmlBody'] = render_template("client_group.html", clients=clients,
                                               id=id_, settings=settings["clients"])
        response['htmlHead'] = render_template("client_head.html", client=clients[0], settings=settings["clients"])
        response['n_clients'] = len(clients)
    return jsonify(response)


@app.route("/job_command", methods=["POST"])
@is_logged_in_ajax
def post_job_command():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    jobs_list = request.form["jobs_list"].split(",")
    command = request.form["command"]
    if "parameter" in request.form:
        parameter = request.form["parameter"]
    else:
        parameter = 0
    response = {}

    [ok, message] = request.api.send_jobs_command(jobs=jobs_list, command=command, parameter=parameter)
    if not ok:
        response["out"] = "fail"
        response['content'] = message
    else:
        response["out"] = "done"

    return jsonify(response)


@app.route("/client_command", methods=["POST"])
@is_logged_in_ajax
def post_client_command():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    clients_list = request.form["clients_list"].split(",")
    clients_list = [int(c) for c in clients_list]
    command = request.form["command"]
    if "parameter" in request.form:
        parameter = request.form["parameter"]
    else:
        parameter = ""
    response = {}

    [ok, message] = request.api.send_clients_command(clients=clients_list, command=command, parameter=parameter)
    if not ok:
        response["out"] = "fail"
        response['content'] = message
    else:
        response["out"] = "done"

    return jsonify(response)


@app.route("/logs", methods=["GET", "POST"])
@is_logged_in
def get_logs():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    log_files = request.api.get_log_files()
    syslog_files = request.api.get_syslog_files()
    if request.method == "POST":
        f_name = request.form.get("logs_select")
        if "show" in request.form and f_name:
            text = request.api.get_log_file_content(f_name)
            return render_template("logs.html", navbar=True, log_files=log_files, syslog_files=syslog_files,
                                   selected=f_name, content=text)

    return render_template("logs.html", navbar=True, log_files=log_files, syslog_files=syslog_files,
                           selected="", content="")


@app.route('/logs/<path:filename>', methods=['GET', 'POST'])
@is_logged_in
def download_log(filename):
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    path = request.api.get_log_path(filename)
    return send_from_directory(directory=path, filename=filename)


@app.route("/stats", methods=["GET", "POST"])
@is_logged_in
def get_stats():
    request.api = manager.get_royal_api(session['username'], session['passHash'], app.config)
    stats = request.api.get_stats()
    stats['connectionStatsJSON']['LastConnections'] = db_manager.get_statistics(n_max=10)
    stats['appMemory'] = db_manager.get_mem_statistics()
    return render_template("stats.html", navbar=True, stats=stats)


# TODO remove demo page
@app.route("/demo", methods=["GET"])
@is_logged_in
def demo():
    return render_template("demo.html", navbar=True)


@app.route("/dyndns", methods=["POST"])
def dyndns():
    if request.method == 'POST':
        try:
            auth_key = request.form['data']
            if auth_key == app.config.get('DDNS_KEY'):
                temp_ip = request.remote_addr
                if temp_ip != app.config.get('TMP_RR_IP'):
                    app.config.update(TMP_RR_IP=temp_ip)
                    logging.info("DynDNS service IP changed: " + temp_ip)
            return ""
        except Exception as e:
            logging.error("Wrong access to DynDNS route from: " + request.remote_addr)
            logging.error(str(e))


@app.teardown_request
def teardown_operations(exc):
    if hasattr(request, 'api'):
        stats_list = request.api.get_stats()['connectionStatsJSON']['LastConnections']
        mem_size = RRAppMemoryManager.get_api_size(request.api, set([]))
        db_manager.store_mem_statistics(app.config.get("WORKER_ID"), mem_size)
        db_manager.store_statistics(stats_list)

    if 'uid' in session and db_manager.is_session_valid(session['uid']):
        db_manager.refresh_session(session['uid'])


if __name__ == "__main__":
    logging.info("RoyalPigeonLoft started...")
    app.logger.info("started")
    app.run(host='0.0.0.0')
