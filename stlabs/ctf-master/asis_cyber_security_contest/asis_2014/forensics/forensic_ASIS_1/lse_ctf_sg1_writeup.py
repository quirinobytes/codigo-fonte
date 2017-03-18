#!/usr/bin/python

#Script so para conectar no serviço do shellter, encontrado dentro do arquivo
PCAP


import socket
import string
import operator
import time

url = 'lse.epita.fr'
port = 52109

def is_digit(mystr):
    if mystr.isdigit() or (mystr[0] == '-' and mystr[1:].isdigit()):
        return True
    else:
        return False

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect((url, port))
data = sock.recv(4096)

while True:
    ind_nb = data.index('Begin')
    if 'End' in data:
        ind_ne = data.index('End')
    else:
        print 'No END'
        break    
    expr = data[ind_nb + 7:ind_ne - 3].strip('\n').replace('\n', ' ').replace('
', ' ')
    print expr
    arr = expr.split(' ')
    while len(arr) >= 3:
        for i in range(len(arr) -1, 0, -1):
            if is_digit(arr[i]) and is_digit(arr[i-1]) and not
is_digit(arr[i-2]):
                myeval = arr[i-1] + arr[i-2] + arr[i]
                arr[i-2] = str(eval(myeval))
                if i == len(arr):
                    arr = [ arr[k] for k in range(0, i - 1) ]
                else:
                    arr = [ arr[k] for k in range(0, i - 1) ] + [ arr[k] for k
in range(i + 1, len(arr))]
                break

    sock.send(arr[0] + '\n')
    time.sleep(3)
    data = sock.recv(128000) # why large buffer?
    time.sleep(3)
    print data

sock.close()
