#!/usr/bin/env python3
#-*- coding: utf-8 -*-

class inventory:
    def __init__(self):
        self.life = 1260
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0

    def __str__(self):
        str = "{'linemate':%d,'deraumere':%d,'sibur':%d,'mendiane':%d,'phiras':%d,'thystame':%d}"
        return str % (self.linemate, self.deraumere, self.sibur, self.mendiane, self.phiras, self.thystame)

    def update(self, list_infos):
        for key, value in list_infos.items():
            setattr(self, key, value)

    def test(self, list_infos):
        getattr(self, 'update')(list_infos)



buffer = "mes"
msg = "sage 8, red 170654137 2 {'linemate':10,'deraumere':12,'sibur':20,'mendiane':8,'phiras':4,'thystame':0}"

msg = buffer + msg
buffer = ""

lines = msg.splitlines(True)
endlast = lines[-1]
lines = msg.splitlines()

list_endlines = ['\n', '\r']

if not endlast[-1:] in list_endlines:
    buffer = endlast
    lines = lines[:-1]

print (lines)
print (buffer)
