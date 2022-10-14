# Default RRWebApp parameters


# DO NOT MODIFY THIS FILE
# DO NOT MODIFY THIS FILE
# Overwrite params in your own ./RRWebApp/instance/config.py file

PIGEONLOFT_VERSION = "9.0.00_beta_1"
PIGEONLOFT_VERSION_DATE = "221014"


# DO NOT USE DEBUG MODE IN PRODUCTION
DEBUG = True #flask debug mode
PIGEONLOFT_DEBUG = True #pigeonloft logging.xxxx("") 
RRLIB_VERBOSE = False  #rrLib module


# Application secret
# Flask Module help states 'SECRET_KEY': 
# A secret key that will be used for securely signing the session cookie and can be used for any other 
# security related needs by extensions or your application. It should be a long random bytes or str.
SECRET_KEY = '234fddfgFFS213495mdgkdsfolsower234945asASDd'             


# You have two options to define the IP for your RR server
# 1) Hardcode the TMP_RR_IP to the IP where you can reach your RR server.
#    a) If you are running this website within your on-premise network
#    b) If your company has a fixed wwww IP and your router is setup to forward the rrServer port to the wwww
# 2) This website is running on the www. And your company uses some kind of dial-in internet connection that changes the www each time
#    In this case forward the RR port from your rrServer to the internet.
#    Then install the rrDynDNS service on some machine in your on-premise company network
#    The rrDynDNS service requires this DDNS_KEY as config options
#    It is used by this website to authorize the IP change
#
#    Security:
#    Note that if someone retrieves the DDNS_KEY by reading this config file or by listening to TCP traffic, 
#    he could relink this website to some other rrServer.
#    So far the worst that we think that can happen is that this website does not report your jobs any more as the other rrServer does not have your jobs
#    Perhaps the hacker is even able to dublicate the authorization check send to the other rrServer and send it to your rrServer.
#    BUT this does not mean that he can retrieve any jobs! Any data send from the rrServer is encoded with the users password. 

DDNS_KEY = 'key123456789'                  
TMP_RR_IP = '127.0.0.1'           # IP/URL of RR Server
RR_PORT = 7773                    # RR Server Port



# SESSION
SESSION_TIMEOUT = 300

# MAIN SCHEDULER CYCLE TIME (USED FOR DB OPS)
RR_SCHEDULER_INTERVAL = 3600

# STATISTICS
# How long statistics will be held in DB
STATS_EXPIRATION_TIME = 3600*24

# DATABASE
DB_PATH = './db'
DB_NAME = 'rr_data.db'
DB_USER = ''
DB_PASS = ''
