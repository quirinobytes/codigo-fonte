#!/usr/bin/python
# -*- coding: utf-8 -*-

from passlib.hash import cisco_pix as pix
import sys
import base64
user = ''
xx = ''
if len(sys.argv) > 1:
    x = sys.argv[1]
#    x = [89, 86, 69, 121, 100, 82,69, 103, 98, 47, 48, 103, 80, 71, 77, 121]
    hashus = pix.encrypt('RTFM-CTF-IS', user=x)
    z = [89, 86, 69, 121, 100, 82,69, 103, 98, 47, 48, 103, 80, 71, 77, 121]
    for zz in z:
#        xx += chr(zz + 275 * 100001 - 275 * 1000 - 27225274)
        xx += chr(zz +1 )
    print xx
    print  base64.decodestring(xx)
    hashgen = pix.encrypt('RTFM-CTF-IS', user=base64.decodestring(xx))
    if hashgen == hashus:
        print 'Voce ta bixao mesmo, hein?! Poreemm :( ===>    ' + str(base64.encodestring(base64.decodestring(xx)))
        print 'Voce ta bixao mesmo, hein?! Poreemm :( ===>    ' + str(base64.decodestring(base64.encodestring(xx)))
    else:
        print 'Naaoooooo !! Leia o codigo com atencao!!!'
else:
    print 'Password !!'
