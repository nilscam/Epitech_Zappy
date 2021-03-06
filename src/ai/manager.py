#!/usr/bin/env python3
#-*- coding: utf-8 -*-

try:
    import commands
    import ai
except:
    from src.ai.ai import ai
    from src.ai.commands import commands

import random

class IAManager(ai):

    def __init__(self, port, name, ip):
        self.cmdManager = commands(port, ip)
        print('command init')
        welcome = self.cmdManager.getWelcome(name)
        self.team = name
        self.nbClients = welcome[0]
        ai.__init__(self, *list(map(int, welcome[1].split())))

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

    def exploreStep(self, mode):
        self.broadcastInfos()
        self.castCmd("Connect_nbr\n")
        self.castCmd("Look\n")
        self.castCmd("Inventory\n")
        self.takeAllItem()

        if mode == 'explore':
            vectorTurn = random.choice([['Left'], ['Right'], [], ['Left', 'Left']])
            for dir in vectorTurn:
                self.castCmd(dir + "\n")
            self.castCmd("Forward\n")

        elif mode == 'group':
            vectorTurn = self.orienteRegroupIncantation()
            for dir in vectorTurn:
                self.castCmd(dir + "\n")
            if self.shouldIMove():
                self.castCmd("Forward\n")

    def reGroup(self):
        if self.canStartIncante():
            self.dropNecessary()
            self.castCmd("Incantation\n")
            # tant que j'ai pas fini d'incanter je fais rien
            while self.incanting:
                self.waitServerEvent()
        else:
            # remplacer ça par les règles de Paint
            self.exploreStep('group')

    def play(self):
        while self.level < 8:
            if self.canIncante():
                print ('regroup , id = %d' % self.randomNumber)
                self.reGroup()
            else:
                print ('explore')
                self.exploreStep('explore')

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
            info = {'direction': dir, 'id': int(recv[1]), 'level': int(recv[2]), 'inventory': eval(recv[3])}
            if self.level == info['level']:
                self.removeFromAlly(info['id'])
                self.addToAlly(info)
            elif self.level < info['level']:
                self.removeFromAlly(info['id'])

    def interpreteServerEvent(self, response):
        # eject, dead, (ko, currentLevel)
        splitted = response.split()

        print (response)
        if splitted[0] == 'Current':
            self.level = int(response.split()[2])
            self.listIncantationsDir[:] = []
            self.incanting = False
        elif response == 'Elevation underway':
            # si je suis déjà en incantation j'ignore le mongole qui veut incanter avec moi
            if self.incanting == False:
                self.incanting = True
                while self.incanting:
                    self.waitServerEvent()
        elif response == 'Elevation failed':
            self.incanting = False
        elif response == 'dead':
            print ('fuck im dead :(')
            exit(0)
        elif splitted[0] == 'eject:':
            print ('je me suis fait pousser')
            self.ejected(int(splitted[1]))

    def interpreteCmd(self, cmdResponse):
        # modifier les variables de l'ia en fonction du message
        command = cmdResponse['cmd'].split()[0]
        response = cmdResponse['response']
        if command == 'Connect_nbr' and self.Connect_nbr(response):
            self.castCmd("Fork\n")
        elif command in ['Forward', 'Left', 'Right', 'Eject', 'Fork']:
            getattr(self, command)()
        elif command in ['Look', 'Inventory', 'Incantation']:
            getattr(self, command)(response)
        elif command in ['Set', 'Take']:
            getattr(self, command)(response, cmdResponse['cmd'].split()[1])
        elif command == 'Broadcast':
            #print ('broadcast with success')
            pass

    # prend un exemplaire de chaque item dispo sur la case
    def takeAllItem(self):
        actualSquare = self.map.getSquare(self.x, self.y)
        if actualSquare:
            for item, number in actualSquare.items():
                if item == 'food':
                    self.castCmd("Take " + item + "\n")
                    self.castCmd("Take " + item + "\n")
                    self.castCmd("Take " + item + "\n")
                    self.castCmd("Take " + item + "\n")
                    self.castCmd("Take " + item + "\n")
                    self.castCmd("Take " + item + "\n")
                elif item == 'player':
                    pass
                else:
                    self.castCmd("Take " + item + "\n")

    def dropNumber(self, ressource, nb):
        i = 0
        while i < nb and i < getattr(self.inventory, ressource):
            self.castCmd("Set " + ressource + "\n")
            i += 1

    def dropNecessary(self):
        for ressource, nb in self.incantationsStats[self.level].items():
            if ressource != 'player':
                self.dropNumber(ressource, nb)

    def castCmd(self, cmd):
        self.cmdManager.sendCmd(cmd)

        # delete this while if you want to make the IA taking decision without waiting server validation
        while len(self.cmdManager.cmdBuffer) > 0:
            responses = self.cmdManager.getResponse()
            for r in responses:
                if r['type'] == 'message':
                    self.interpreteMsg(r['message'])
                elif r['type'] == 'server':
                    self.interpreteServerEvent(r['response'])
                else:
                    self.interpreteCmd(r)

    def waitServerEvent(self):
        responses = self.cmdManager.getResponse()
        for r in responses:
            if r['type'] == 'message':
                self.interpreteMsg(r['message'])
            elif r['type'] == 'server':
                self.interpreteServerEvent(r['response'])
            else:
                self.interpreteCmd(r)
