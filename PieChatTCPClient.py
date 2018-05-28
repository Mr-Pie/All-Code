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
Text = tkinter.Text(top, height = 10, width = 30)
Text.grid(column = 1, row = 1)
TextInput = tkinter.Entry(top, bd =1, width = 35)
TextInput.grid(column = 1, row = 2)
               
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
    print('Sending message')
    LineFeed = '\n'
    MESSSAGE = bytes(TextInput.get()+LineFeed, 'utf-8')
    #MESSSAGE = b'HELLO\n'
    global s
    s.send(MESSSAGE)
    TextInput.delete(0,END)

def PressedEnter(junk):
    print('Enter Pressed')
    MagicButton()

MagicButton()

TCPListen = threading.Thread(target = Listener)
TCPListen.start()

top.bind('<Return>', PressedEnter)
BtnTest = tkinter.Button(top, text ="Send Message", command = MagicButton)
BtnTest.grid(column = 1,row = 4, columnspan = 2, rowspan = 2)
top.mainloop()


