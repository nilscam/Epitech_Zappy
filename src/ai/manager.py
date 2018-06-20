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
        self.castCmd("Look\n")
        self.takeAllItem()
        self.castCmd("Left\n")
        self.castCmd("Forward\n")
        self.castCmd("Look\n")
        self.takeAllItem()
        self.castCmd("Left\n")
        self.castCmd("Forward\n")
        self.castCmd("Look\n")
        self.takeAllItem()
        self.castCmd("Left\n")
        self.castCmd("Forward\n")
        self.castCmd("Look\n")
        self.takeAllItem()

    def exploreStep(self):
        #Broadcast
        #Look
        #takeAllItem
        #Oriente
        #Move

    def play(self):
        while self.level < 8:
            if self.canIncante():
                self.reGroup()
            else:
                self.exploreStep()

    def broadcastInfos(self):
        # on envoie le nom de team + son id + son level + son inventaire
        message = "Broadcast " + self.team + " " + str(self.randomNumber) + " " + str(self.level) + " " + str(self.inventory) + "\n"
        self.castCmd(message)

    def interpreteMsg(self, message):
        splitted = message.split(',', 1)

        dir = int(splitted[0].split()[1])
        recv = splitted[1].split()

        #si il est de ma clic
        if recv[0] == self.team:
            info = {'direction': dir, 'id': int(recv[2]), 'level': int(recv[1]), 'inventory': eval(recv[3])}
            if self.level == info['level']:
                #rajouter ou update à la liste
                # del then add
            elif self.level < info['level']:
                # le supprimer de la liste

    def interpreteCmd(self, cmdResponse):
        # modifier les variables de l'ia en fonction du message

    def takeAllItem(self):
        actualSquare = self.map.getSquare(self.x, self.y)
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
