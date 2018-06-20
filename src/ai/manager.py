#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import commands
import ai

class IAManager(ai.ai):

    def __init__(self, port, ip):
        self.cmdManager = commands.commands(port, ip)
        welcome = self.cmdManager.getWelcome()
        self.team = welcome[1]
        self.nbClients = welcome[2]
        ai.ai.__init__(self, *list(map(int, welcome[3].split())))

        # play firsts moves optimized
        self.firstStep()
        # play the rest of the game
        self.play()

    def firstStep(self):
        self.castCmd("Look")
        self.takeAllItem()
        self.castCmd("Left")
        self.castCmd("Forward")
        self.castCmd("Look")
        self.takeAllItem()
        self.castCmd("Left")
        self.castCmd("Forward")
        self.castCmd("Look")
        self.takeAllItem()
        self.castCmd("Left")
        self.castCmd("Forward")
        self.castCmd("Look")
        self.takeAllItem()

    def play(self):
        while self.level < 8:




    def interpreteMsg(self, message):
        # modifier les variables de l'ia en fonction du message

    def interpreteCmd(self, cmdResponse):
        # modifier les variables de l'ia en fonction du message

    def takeAllItem(self):
        actualSquare = self.map[self.y][self.x]
        if actualSquare:
            for item, number in actualSquare.items():
                for i in range(number):
                    self.castCmd("Take" + item)

    def castCmd(self, cmd):
        self.cmdManager.sendCmd(cmd)

        # delete this while if you want to make the IA taking decision without waiting server validation
        while len(self.cmdManager.cmdBuffer) > 0:
            responses = self.cmdManager.getResponse()
            for r in responses:
                if r['type'] == 'message':
                    self.interpreteMsg(r['message'])
                else:
                    self.interpreteCmd(r)
