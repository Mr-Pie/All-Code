#!/usr/bin/env python

import socket
import tkinter
from tkinter import *
from time import sleep
import threading

TCP_IP = '192.168.0.11'
#TCP_IP = '127.0.0.1'
TCP_PORT = 29200
BUFFER_SIZE = 4096
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

print('Initialising')

top = tkinter.Tk()
# Code to add widgets will go here...

def Listener():
    global s
    data = s.recv(BUFFER_SIZE)
    Text.insert(END,data)
    #print(data)
    print('repeating thread')
    Listener()
    
def MagicButton():
    #Text.insert(INSERT, "Hi Tomo\n")
    print('Sending Hello')
    MESSSAGE = b'HELLO\n'
    global s
    s.send(MESSSAGE)

MagicButton()

TCPListen = threading.Thread(target = Listener)
TCPListen.start()

Text = tkinter.Text(top, height = 10, width = 30)
BtnTest = tkinter.Button(top, text ="Button1Off", command = MagicButton)
Text.grid(column = 1, row = 1)
BtnTest.grid(column = 1,row = 4, columnspan = 2, rowspan = 2)
top.mainloop()



