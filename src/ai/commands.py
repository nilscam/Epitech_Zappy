#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import network

class commands:

    def __init__(self, port, ip):
        self.cmdBuffer = []
        self.networkManager = network.network(port, ip)

    def getWelcome(self):
        welcome = self.networkManager.getServerMessages()
        while len(welcome) < 4:
            welcome += self.networkManager.getServerMessages()
        return welcome[:4]

    def getResponse(self):
        responses = self.networkManager.getServerMessages()
        cmdResponses = []
        for r in responses:
            # rajouter le fait que si c'est un message d'un joueur on ne l'associe pas à une commande
            if r.split()[0] != 'message':
                cmdResponses.append({ 'type': 'cmd', 'cmd': self.cmdBuffer[0], 'response': r })
                self.cmdBuffer.pop(0)
            else:
                cmdResponses.append({ 'type': 'message', 'response': r })
        return cmdResponses

    def sendCmd(self, command):
        if len(cmdBuffer) >= 10:
            print("too many commands are already in queue")
        else:
            self.cmdBuffer.append(command)
            self.networkManager.sendMsg(command)
