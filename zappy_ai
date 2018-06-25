#!/usr/bin/env python3
#-*- coding: utf-8 -*-

try:
    from manager import IAManager
except:
    from src.ai.manager import IAManager

import sys

def eprint(*args, **kwargs):
        print(*args, file=sys.stderr, **kwargs)

def usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport\t\tis the port number")
    print("\tname\t\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")

def main():

    help_flags = ['-help', '-h', '--help']

    if len(sys.argv) == 2 and sys.argv[2] in help_flags:
        usage()
        exit(0)
    elif len(sys.argv) >= 5 and sys.argv[1] == '-p' and sys.argv[3] == '-n':

        port = name = machine = None
        try:
            port = int(sys.argv[2])
            name = str(sys.argv[4])
            machine = "localhost"
            if len(sys.argv) == 7 and sys.argv[5] == '-h':
                machine = str(sys.argv[6])
        except:
            eprint("Error: parsing")
            exit(84)

        #try:
        ia = IAManager(port, name, machine)
        print ('a fini')
        exit(0)
        #except:
        eprint("Error: execution")
    exit(84)

if (__name__ == '__main__'):
    main()
