#!/usr/bin/python

import sys
import os
import socket
import pickle

#HOST = '127.0.0.1'
HOST = '128.2.13.134'
PORT = 15122

def printUsage():
  print "Usage: {} submit <string> [<alias>] \n".format(args[0]) + \
        "       {} top\n".format(args[0]) + \
        "Note that string and alias must be less than 64 characters long"

if __name__ == "__main__":
  args = sys.argv;
  if len(args) == 1:
    printUsage()
    sys.exit(1)
  elif len(args) == 2:
    if args[1] != "top":
      printUsage()
      sys.exit(1)
  elif 3 <= len(args) and len(args) <= 4:
    if args[1] != "submit" or len(args[2]) > 64 or \
        (len(args) == 4 and  len(args[3]) > 64):
            printUsage()
            sys.exit(1)
  else:
    printUsage()
    sys.exit(1)

  andrewid = os.getenv('USER')

  sock = socket.socket(
      socket.AF_INET, socket.SOCK_STREAM)

  try:
    sock.connect((HOST, PORT))
  except socket.error as msg:
    print 'Connect failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit(1)

  if args[1] == "top":
    message = ("top", andrewid) 
    sock.sendall(pickle.dumps(message));
  elif args[1] == "submit":
    message = ""
    if len(args) == 3:
      message = ("submit", andrewid, args[2])
    else:
      message = ("submit", andrewid, args[2], args[3])
    sock.sendall(pickle.dumps(message));
    
  rv = sock.recv(1024);
  print rv
  sock.close()
