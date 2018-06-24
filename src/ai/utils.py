#!/usr/bin/env python3
#-*- coding: utf-8 -*-

def smoothDir(x):
    if x < 0:
        return -1
    elif x > 0:
        return 1
    else:
        return 0
