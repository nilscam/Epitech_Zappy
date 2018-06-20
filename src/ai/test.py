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


print ()
#print ([[None] * 50] * 10)

i = inventory()
print (i)
print (eval(str(i)))

message = "message 3 , " + "toto" + " 4 " + " 123 " + str(i)

splitted = message.split(',', 1)

dir = int(splitted[0].split()[1])
print ()
print ()
print ()
print (dir)
print ()
print ()
print ()
print (splitted)
print (splitted[0].split())
print (splitted[1].split())

print ()

recv = splitted[1].split()
info = {'player_id': int(recv[2]), 'level': int(recv[1]), 'inventory': eval(recv[3])}
print (info)

dict1 = {'one':1, 'two':2, 'three': {'three.1': 3.1, 'three.2': 3.2 }}
str1 = str(dict1)

dict2 = eval(str1)

print (dict2)
