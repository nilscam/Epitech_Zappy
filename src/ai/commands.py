#!/usr/bin/env python3
#-*- coding: utf-8 -*-

try:
    import network
except:
    from src.ai.network import network

class commands:

    def __init__(self, port, ip):
        self.cmdBuffer = []
        self.savecmdBuffer = []
        self.saveresponseBuffer = []
        self.networkManager = network(port, ip)

    def getWelcome(self, teamname):
        welcome = self.networkManager.getServerMessages()
        self.networkManager.sendMsg(teamname + "\n")
        while len(welcome) < 3:
            welcome += self.networkManager.getServerMessages()
        return welcome[1:3]

    def getResponse(self):
        responses = self.networkManager.getServerMessages()
        cmdResponses = []
        for r in responses:
            # rajouter le fait que si c'est un message d'un joueur on ne l'associe pas à une commande
            firstWord = r.split()[0]
            if firstWord != 'message':
                if len(self.cmdBuffer) == 0  or firstWord in ['Current', 'Elevation', 'dead', 'eject']:
                    #eject, incantation ...
                    cmdResponses.append({ 'type': 'server', 'response': r })
                else:
                    cmdResponses.append({ 'type': 'cmd', 'cmd': self.cmdBuffer[0], 'response': r })
                    self.saveresponseBuffer.append(r)
                    self.cmdBuffer.pop(0)
            else:
                cmdResponses.append({ 'type': 'message', 'message': r })
        return cmdResponses

    def sendCmd(self, command):
        if len(self.cmdBuffer) >= 10:
            print("too many commands are already in queue")
        else:
            self.cmdBuffer.append(command)
            self.savecmdBuffer.append(command)
            self.networkManager.sendMsg(command)
