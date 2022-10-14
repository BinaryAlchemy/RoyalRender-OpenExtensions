from threading import Timer
import time


class RRScheduler:

    def __init__(self, interval):
        """
        threading based timed scheduler
        :param interval:
        :type interval: int
        """

        self.interval = interval
        self.callbacks = []
        self.args_l = []
        self.kwargs_l = []

    def start(self):

        for i, call in enumerate(self.callbacks):
            args = self.args_l[i]
            kwargs = self.kwargs_l[i]
            call(*args, **kwargs)

        t = Timer(self.interval, self.start)
        t.start()

    def add_callback(self, call, *args, **kwargs):
        """
        Adds a callback to the list
        :param call: a callable object
        :type call: callable
        :return:
        """

        self.callbacks.append(call)
        self.args_l.append(args)
        self.kwargs_l.append(kwargs)


def test_function():
    print("here: " + str(time.time()))


def test2_function():
    print("now: " + str(time.time()))


def test3_function(text, number=0):
    print(text + str(number) + "-" + str(time.time()))
