#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import network

class commands:

    def __init__(self, port, ip):
        self.cmdBuffer = []
        self.networkManager = network.network(port, ip)

    def getResponse(self):
        responses = self.networkManager.getServerMessages()
        cmdResponses = []
        for r in responses:
            cmdResponses.append(self.cmdBuffer[0], r)
            self.cmdBuffer.pop(0)
        return cmdResponses

    def sendCmd(self, command):
        if len(cmdBuffer) >= 10:
            print("too many commands are already in queue")
        else:
            self.cmdBuffer.append(command)
            self.networkManager.sendMsg(command)
