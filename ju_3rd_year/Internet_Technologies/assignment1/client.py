import sys
import socket

import types
from libclient import Worker

def prompt():
    message = 'Usage : \n'
    message += 'client.py host <destport> <srcport> ?multiple ?password <pass> get <key> put <key> <value> ...  '
    return message

def validate_args(args):
    if len(args) > 0:
        start = 0 
        if args[0] == 'multiple':
            start+=1
        if args[start] == 'password':
            assert start + 1  < len(args) , prompt()
            start += 2
        i = start
        while i < len(args):
            # print(args[i].lower())
            if args[i].lower() == 'get':
                assert i+1 < len(args) , prompt()
                i+=1
            elif args[i].lower() == 'put':
                assert i +2 < len(args) , prompt()
                i+=2
            else:
                raise ValueError(prompt())
            i+=1
        
if len(sys.argv) < 4:
    print(prompt()) 
    sys.exit()


host, port, local_port = sys.argv[1], int(sys.argv[2]),  int(sys.argv[3])
server_addr = (host, port)

args = sys.argv[4:]
try:
    validate_args(args)
except Exception as e:
    print(e)
    sys.exit()

print(server_addr)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((host, local_port))
sock.connect(server_addr)


print('Arguments O.K.\n\n')

worker = Worker(sock)
worker.write( ' '.join(str(a) for a in args))
worker.read()


try:
    sock.close()
except OSError as e:
    print(
        "error: socket.close() exception for" + e,
    )
finally:
    # Delete reference to socket object for garbage collection
    sock = None

