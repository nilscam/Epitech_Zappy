#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import socket
import select

class network:

    list_endlines = ['\n', '\r']

    def __init__(self, port, ip):
        self.port = port
        self.ip = ip
        self.buffer = ""
        self.socket = None
        self.connect(port, ip)

    def connect(self, port, ip):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((ip, port))
            print ("Connection on {}".format(port))
        except:
            print ('Could not connect to server @%d' % self.port)
            exit(84)

    def sendMsg(self, message):
        self.socket.send((message + "\n").encode('utf-8'))

    def readSocket(self):
        return self.socket.recv(4096).decode('utf-8')

    def close(self):
        self.socket.close()
        print ("Connection closed")

    # retourne une liste de message
    def getServerMessages(self):
        try:

            inputready, outputready, _ = select.select([self.socket], [], 0)

            for i in inputready:
                if i == self.socket:
                    data = self.readSocket()
                    if not data:
                         print ('Server shut down')
                         self.socket.close()
                         exit(0)

                    lines = data.splitlines(True)
                    endlast = lines[-1]
                    lines = data.splitlines()

                    if not endlast[-1:] in self.list_endlines:
                        # si on a qu'une seule ligne et pas de \n on l'ajoute au buffer
                        if len(lines) == 1:
                            self.buffer += endlast
                        # sinon on a plusieurs lignes et pas de \n à la dernière ligne donc on dit que le buffer vaut la dernièr ligne
                        else:
                            self.buffer = endlast
                        lines = lines[:-1]

                    return lines
