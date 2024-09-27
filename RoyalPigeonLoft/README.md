### Installation ###

**Dependencies**

First install:

- Main RR config
  Open rrConfig, Menu Server, tab rrLogin.
  In "Authorization Options", add the IP range(s) of your companies network.
  Although this website automatically enables the remote access option, some other script might not.


- COPY FILES
	Copy the contents of RoyalPigeonLoft into some local folder.
	e.g. /home/$USER/RoyalPigeonLoft


- PYTHON
  RR provides python libraries for python 2.7, 3.7 and 3.9
  
  Note: If you use Python 2.7, then the version with 2 bytes UTF encoding must be installed.
  To check if your version suits run:
  python2.7 -c "import sys;print(sys.maxunicode)"
  It should be 65535. 

  LINUX: To get and compile 2.7.10 use:
    sudo apt update
	sudo apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev wget libbz2-dev
    cd /usr/src
    wget https://www.python.org/ftp/python/2.7.10/Python-2.7.10.tgz
    tar xzf Python-2.7.10.tgz
    cd Python-2.7.10
    ./configure --enable-optimizations
    make altinstall
	
  LINUX: To get and compile 3.9.7 use:
    Ubuntu:
		sudo apt update
		sudo apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev wget libbz2-dev
		sudo mkdir /usr/src/compile
		sudo chmod 777 /usr/src/compile
		wget https://www.python.org/ftp/python/3.9.7/Python-3.9.7.tgz
		tar -xf Python-3.9.7.tgz
		cd Python-3.9.7
		./configure --enable-optimizations
		make -j 8
		sudo make altinstall	
		python3.9 --version

	Centos:
	    You need to install these packages before compiling:
		sudo yum install gcc openssl-devel bzip2-devel	

	
    
- PIP

	To Install Pip for the default python version, please use
		sudo apt-get install python3-pip
		sudo apt-get install python3-distutils
		sudo apt-get install python3-apt
	
	To install pip on an alternate (not bundled) python version try:
		python2.7 -m ensurepip --default-pip
		python2.7 -m pip install --upgrade pip

    OR
	    sudo apt-get install python3.9-venv
		sudo apt-get install python3.9-distutils
		python3.9 -m ensurepip --default-pip
		python3.9 -m pip install --upgrade pip

	

- Virtualenv is recommended:
    python3.9 -m pip install virtualenv
    python3.9 -m virtualenv  /home/$USER/RoyalPigeonLoft/venv

- Flask is the only dependency:
    cd /home/$USER/RoyalPigeonLoft
    venv/bin/python3.9 -m pip install flask
    


- RR PYTHON MODULES
  There are two options for RoyalPigeonLoft to find the RR python libs.
  A) If your webserver is in your company network, then you have to use the RR_ROOT env variable to point to the RR folder
	 Add environment var:
		RR_ROOT=/mnt/RoyalRender
		export RR_ROOT
  B) Copy the python modules from RR into the subfolder  /home/$USER/RoyalPigeonLoft/modules
     Please see the readme in RoyalPigeonLoft/modules for the list of required files.
	 Add environment var:
		RR_PYTHON_FOLDER=/home/$USER/RoyalPigeonLoft/modules
		export RR_PYTHON_FOLDER
- TEST RUN
  Edit the file /home/$USER/RoyalPigeonLoft/config/default.py 
  and change the line TMP_RR_IP = '127.0.0.1' to match the IP of your rrServer
  
  Then execute:
	cd /home/$USER/RoyalPigeonLoft
	venv/bin/python3.9 -m app
	
  Open any webbrowser and open http://localhost::5000
  (Note: If you are running any firewall on your webserver, you need to allow the port)
	

### DataBase ###
RoyalPigeonLoft supports a sqlite3 database in bundle. The main purpose of the database is to store sessions and data to be
shared between workers (eg user settings and connection stats).
The database is managed by the SqLiteManager class. This manager creates the following tree inside the database folder:

    +--init
    |    +--sqlite
    +--update
    |    +--sqlite
    +--rr_data.sql
    
If you want to extend the database for your purposes you should place your .sql scripts inside the update/sqlite folder.
Scripts are executed in alphabetical order. We enforce the use of following file naming convention:

YYMMDD-PROG-DESCRIPTOR.sql

Where PROG is a progressive number in case multiple scripts are created/executed the same day

### Cloud Server ###
Secure your server and install ufw (ref. Linode/DigitalOcean guide)

    $ sudo apt-get install -y ufw
    $ sudo ufw allow ssh
    $ sudo ufw allow http
    $ sudo ufw allow 443/tcp
    $ sudo ufw --force enable
    $ sudo ufw status

Install GIT, Nginx, Supervisor

    $ sudo apt-get -y install supervisor nginx git

Install requirements in the virtual environment

    $ source venv/bin/activate
    (venv) $ pip install -r requirements.txt
    (venv) $ pip install gunicorn
    
Use supervisor to run server (.conf file can be any name)

    (venv) $ sudo nano /etc/supervisor/conf.d/rr-webapp.conf
    
rr-webapp.conf file content:

    [program:app]
    command=/home/user/rr-webapp/venv/bin/gunicorn -b localhost:8000 -w 4 app:app
    directory=/home/user/app
    user=PUT_USERNAME_HERE
    autostart=true
    autorestart=true
    stopasgroup=true
    killasgroup=true
    environment=RR_ROOT="/mnt/programmierung/RoyalRenderGit_75"

stop rr-webapp:
    
    $ sudo supervisorctl stop rr-webapp
      
restart rr-webapp:
    
    $ sudo supervisorctl start rr-webapp

restart supervisor_

    (venv) $ sudo supervisorctl reload
    
**NOTES ON SUPERVISOR**

Main *supervisor* config is in:

    /etc/supervisor/supervisord.conf

*Logging*

Supervisor service logging file is set in supervisord.conf:
    
    [supervisord]
    logfile=/var/log/supervisor/supervisord.log
    
This is the log file of *supervisor* application, in the same folder you can find stderr and stdout logs of the managed applications. **stderr and stdout are important for debugging unexpected errors that make the application crash**

    
**NGINX SETUP**

    $ mkdir certs
    $ openssl req -new -newkey rsa:4096 -days 365 -nodes -x509 \
      -keyout certs/key.pem -out certs/cert.pem
    $ sudo rm /etc/nginx/sites-enabled/default
    
    $ sudo nano /etc/nginx/sites-enabled/rr-webapp
    
Example /etc/nginx/sites-enabled/rr-webapp content:
    
    server {
        # listen on port 80 (http)
        listen 80;
        server_name _;
        location / {
            # redirect any requests to the same URL but on https
            return 301 https://$host$request_uri;
        }
    }
    server {
        # listen on port 443 (https)
        listen 443 ssl;
        server_name _;
    
        # location of the self-signed SSL certificate
        ssl_certificate /home/lucio/rr-webapp/certs/cert.pem;
        ssl_certificate_key /home/lucio/rr-webapp/certs/key.pem;
    
        # write access and error logs to /var/log
        access_log /var/log/rr-webapp_access.log;
        error_log /var/log/rr-webapp_error.log;
    
        location / {
            # forward application requests to the gunicorn server
            proxy_pass http://localhost:8000;
            proxy_redirect off;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        }
    
        location /static {
            # handle static files directly, without forwarding to the application
            alias /home/lucio/rr-webapp/static;
            expires 30d;
        }
    }