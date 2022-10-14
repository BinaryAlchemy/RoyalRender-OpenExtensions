from sys import getsizeof
from collections import Mapping, Container
from src.server_api import ServerApi

from src import rrLib


class RRAppMemoryManager:

    @classmethod
    def get_api_size(cls, o, ids):
        """
        Find the memory footprint of a RR api object

        This is a recursive function that drills down a RR api object graph

        The sys.getsizeof function does a shallow size of only. It counts each
        object inside a container as pointer only regardless of how big it
        really is.

        :param o:
        :param ids:
        :return:
        """

        d = cls.get_api_size
        if id(o) in ids:
            return 0

        r = getsizeof(o)
        ids.add(id(o))

        if isinstance(o, str):
            return r

        if isinstance(o, Mapping):
            return r + sum(d(k, ids) + d(v, ids) for k, v in o.items())

        if isinstance(o, Container):
            return r + sum(d(x, ids) for x in o)

        if isinstance(o, ServerApi):
            return r + d(o.tcp, ids) + d(o.job_groups, ids) + d(o.job_groups_filtered, ids) + getsizeof(o.jobs, ids) +\
                   d(o.clients, ids) + d(o.jobs, ids) + d(o.job_commands, ids)

        if isinstance(o, rrLib._rrTCP) or isinstance(o, rrLib._rrTCPclientList) or isinstance(o, rrLib._rrTCPjobList):
            return r + sum(d(getattr(o, x), ids) for x in dir(o))

        return r
