#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import utils

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
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.map = []

class ai:

    dirChanges = {
    'LEFT': {'UP': 'LEFT', 'DOWN': 'RIGHT', 'LEFT': 'DOWN', 'RIGHT': 'UP'}
    'RIGHT': {'UP': 'RIGHT', 'DOWN': 'LEFT', 'LEFT': 'UP', 'RIGHT': 'DOWN'}
    }

    optimizeDir = {
    0: (0, 0)
    1: (-1, 0)
    2: (-1, 1)
    3: (0, 1)
    4: (1, 1)
    5: (1, 0)
    6: (1, -1)
    7: (0, -1)
    8: (-1, -1)
    }

    def __init__(self, mapx, mapy):
        self.x = 0
        self.y = 0
        self.level = 1
        self.orientation = 'DOWN'
        self.listIncantationsDir = {}
        self.inventory = inventory()
        self.map = map(mapx, mapy)

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

    def joinForIncantation(self, listDir):
        actualDir = [0, 0]
        for id, dir in listIncantationsDir.items():
            actualDir[0] += self.optimizeDir[dir][0]
            actualDir[1] += self.optimizeDir[dir][1]

        actualDir[0] = utils.smoothDir(actualDir[0])
        actualDir[1] = utils.smoothDir(actualDir[1])
        return actualDir



    #core function of the ia
    # return a string defining the decision to take depending on the situation
    def takeDecision(self):
