#!/usr/bin/env python3
#-*- coding: utf-8 -*-

class test:

    def __init__(self):
        self.a = 0
        self.b = 0
        self.c = 1

    def __str__(self):
        return "a = %d, b = %d, c = %d" % (self.a, self.b, self.c)

    def update(self, list_infos):
        for key, value in list_infos.items():
            setattr(self, key, value)



#toto = test()
#nbs = { 'a': 3, 'b': 5, 'c': 6 }
#toto.update(nbs)
#print (toto)

a = range(10)

print (a[:4])
print (a[4:])
print (a[-4:])
print (a[:-4])

print ()
#print ([[None] * 50] * 10)

s = " topas topas topas , food food, roche roche, cailloux"

# Separate on comma.
cities = s.split(",")
square = dict()
for city in cities:
    item = city.split()
    square[item[0]] = len(item)
print (square)
