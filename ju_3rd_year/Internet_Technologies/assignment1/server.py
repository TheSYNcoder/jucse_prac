import sys
import socket
import selectors
import threading
import traceback
from threading import Thread

import types
from queue import Queue, SimpleQueue
from memory import MemoryDatabase
from libserver import Worker
import concurrent.futures as cf




memory_db = MemoryDatabase()
lock =threading.Lock()

threads=[]


def on_connection(sock , addr):
    print ( f'{addr} just connected to this server')
    worker =Worker(sock)    
    data = worker.read().replace('"', '')
    with lock:
        message = memory_db.analyse_and_return(data, addr)
    worker.write(message)
    print(f'{addr} disconnected')
    sock.close()


if len(sys.argv) != 3:
    print("usage:", sys.argv[0], "<host> <port>")
    sys.exit(1)

host, port = sys.argv[1], int(sys.argv[2])
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
lsock.bind((host, port))
lsock.listen()
print("listening on", (host, port))



def run_thread():
    try:
        while True:
            client, addr = lsock.accept()
            t = Thread( target=on_connection , args=(client, addr))
            t.start()
            threads.append(t)
            # on_connection(client , addr)

            
                    
    except Exception as e:
        print(e)
        
    finally:
        for t in threads:
            t.join()
    
# with cf.ProcessPoolExecutor(None) as pool:
#     future=[]
#     try:
#         future.append(pool.submit(run_thread))
#     except KeyboardInterrupt:
#         print('Gracefully shutting down the server')
        # break

    # for fut in cf.as_completed(future):
    #     fut.result()
try:
    run_thread()
except Exception as e:
    print('Gracefully shutting down the server')
