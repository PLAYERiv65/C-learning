import time

class timer:
    def __init__(self, h=0, m=0, s=0):
        self._h = h
        self._m = m
        self._s = s
    
    def update(self):
        self._s += 1
        if self._s == 60:
            self._s = 0
            self._m += 1
        if self._m == 60:
            self._m = 0
            self._h += 1
        if self._h == 24:
            self._h = 0

    def __str__(self):
        return f'{self._h:02d}:{self._m:02d}:{self._s:02d}'