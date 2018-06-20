#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import utils
import random

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

class map:
    def __init__(self, x, y):
        # size x and y
        self.x = x
        self.y = y
        self.map = [[None] * x] * y

    def setSquare(self, x, y, infoStr):
        square = dict()
        for item in infoStr:
            if square[item]:
                square[item] += 1
            else:
                square[item] = 1
        if x < 0:
            x += self.x
        if y < 0:
            y += self.y
        if x > self.x:
            x -= self.x
        if y > self.y:
            y -= self.y
        map[y][x] = square

    def getSquare(self, x, y):
        if x < 0:
            x += self.x
        if y < 0:
            y += self.y
        if x > self.x:
            x -= self.x
        if y > self.y:
            y -= self.y
        return map[y][x]

    def setLook(self, lookResult, dirLook, x, y, level):

        cases = {
        'UP': [[-1], [-1, 1]],
        'DOWN': [[1], [1, -1]],
        'LEFT': [[1, -1], [-1]],
        'RIGHT': [[-1, 1], [1]],
        }

        i = 1
        infos = lookResult.split(",")
        self.setSquare(x, y, infos[0])
        actualCase = cases[dirLook]
        ymove = actualCase[0]
        xmove = actualCase[1]

        if len(ymove) == 1:
            while i <= level:
                range = range(i * 2 + 1) if xmove[0] == -1 else range(i * 2 + 1).reverse()
                for toto in range(i * 2 + 1):
                    self.setSquare(x - toto, y + (ymove[0] * i), infos[i])
                i += 1
        else:
            while i <= level:
                range = range(i * 2 + 1) if ymove[0] == -1 else range(i * 2 + 1).reverse()
                for toto in range(i * 2 + 1):
                    self.setSquare(x + (xmove[0] * i), y - toto, infos[i])
                i += 1

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

    incantationsStats = {
    1: { 'player': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0 },
    2: { 'player': 2, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0 },
    3: { 'player': 2, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0 },
    4: { 'player': 4, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0 },
    5: { 'player': 4, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0 },
    6: { 'player': 6, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0 },
    7: { 'player': 6, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1 },
    8: { 'player': 9999, 'linemate': 9999, 'deraumere': 9999, 'sibur': 9999, 'mendiane': 9999, 'phiras': 9999, 'thystame': 9999 },
    }

    def __init__(self, mapx, mapy):
        self.x = 0
        self.y = 0
        self.level = 1
        self.randomNumber = random.randint(0, 999999999)
        self.orientation = 'DOWN'
        self.listIncantationsDir = []
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
        # modify self.listIncantationsDir ( + 2 - 2 )
        self.orientation = self.dirChanges[dirTurn][self.orientation]
        for player in self.listIncantationsDir:
            if player['direction'] != 0:
                if dirTurn == 'LEFT':
                    player['direction'] += 2
                elif dirTurn == 'RIGHT':
                    player['direction'] -= 2
                if player['direction'] > 8:
                    player['direction'] -= 8
                elif player['direction'] < 0:
                    player['direction'] += 8


    def drop(self, ressource, nb):
        setattr(self.inventory, ressource, getattr(self.inventory, ressource) - nb)

    def take(self, ressource, nb):
        setattr(self.inventory, ressource, getattr(self.inventory, ressource) + nb)

    def inventory(self, newInventory):
        self.inventory.update(newInventory)

    def removeFromAlly(self, id):
        self.listIncantationsDir = [x for x in self.listIncantationsDir if x['id'] != id]

    def addToAlly(self, player):
        self.listIncantationsDir.append(player)

    def joinForIncantation(self, listDir):
        actualDir = [0, 0]
        for id, dir in listIncantationsDir.items():
            actualDir[0] += self.optimizeDir[dir][0]
            actualDir[1] += self.optimizeDir[dir][1]

        actualDir[0] = utils.smoothDir(actualDir[0])
        actualDir[1] = utils.smoothDir(actualDir[1])
        return actualDir

    # return True if i can incante with all others players of my lv, False otherwise
    def canIncante(self):
        full_inventory = { 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0 }

        for player in self.listIncantationsDir:
            for item, nb in player.inventory.items():
                    full_inventory[item] += nb

        for prerequisites, number in self.incantationsStats[self.level].items():
            if prerequisites == 'player':
                if len(self.listIncantationsDir) + 1 < number:
                    return False
            else:
                if full_inventory[prerequisites] < number:
                    return False
        return True
