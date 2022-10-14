import sys
import logging
from .errors import RR_GenericError
from . import cache as rr_cache

rr_cache.cache_module_locally()

loaded_rrLib = False

if sys.version_info.major == 2:
    import libpyRR2 as libpyRR
    loaded_rrLib = True
elif sys.version_info.major == 3:
    if sys.version_info.minor == 7:
        import libpyRR37 as libpyRR
        logging.debug("libpyRR37 loaded")
        loaded_rrLib = True
    elif sys.version_info.minor == 9:
        import libpyRR39 as libpyRR
        loaded_rrLib = True
else:
    raise RR_GenericError("\n    Unable to load RR module for python version {}.{}.\n"
                          .format(sys.version_info.major, sys.version_info.minor))

rrLib = libpyRR

if loaded_rrLib:
    print("libpyRR loaded ({})".format(rrLib.__file__))

try:
    import rrJob as libpyRRjob
except ImportError as e:
    raise RR_GenericError("\n    Unable to load rrJob module.\n")

rrJob = libpyRRjob
