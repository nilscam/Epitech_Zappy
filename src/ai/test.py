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


test = inventory()

test.test({'life': 3, 'linemate': 200})

print(test)
