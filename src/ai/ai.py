#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import commands

class inventory:
    def __init__(self):
        self.life = 1260
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0

    def update(self, list_infos):
        for key, value in list_infos.items():
            setattr(self, key, value)

class map:
    def __init__(self):
        self.map = []
        self.x = 0
        self.y = 0

class ai:

    dirChanges = {
    'LEFT': {'UP': 'LEFT', 'DOWN': 'RIGHT', 'LEFT': 'DOWN', 'RIGHT': 'UP'}
    'RIGHT': {'UP': 'RIGHT', 'DOWN': 'LEFT', 'LEFT': 'UP', 'RIGHT': 'DOWN'}
    }

    def __init__(self):
        self.x = 0
        self.y = 0
        self.orientation = 'DOWN'
        self.inventory = inventory()
        self.map = map()

    def start(self):
        self.firstPart()
        self.secondPart()

    def move(self):
        if self.orientation == 'UP':
            self.y -= 1
        elif self.orientation == 'DOWN':
            self.y += 1
        elif self.orientation == 'RIGHT':
            self.x += 1
        elif self.orientation == 'LEFT':
            self.x -= 1

        if self.x >= self.map.x:
            self.x -= self.map.x
        if self.y >= self.map.y:
            self.y -= self.map.y

    def turn(self, dirTurn):
        self.orientation = self.dirChanges[dirTurn][self.orientation]

    def drop(self, ressource, nb):
        setattr(self.inventory, ressource, getattr(self.inventory, ressource) - nb)

    def take(self, ressource, nb):
        setattr(self.inventory, ressource, getattr(self.inventory, ressource) + nb)

    def inventory(self, newInventory):
        self.inventory.update(newInventory)
