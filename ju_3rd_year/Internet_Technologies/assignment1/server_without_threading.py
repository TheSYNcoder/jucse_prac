import sys
import socket

from memory import MemoryDatabase
from libserver import Worker


memory_db = MemoryDatabase()



def on_connection(sock, addr):
    print(f'{addr} just connected to this server')
    worker = Worker(sock)
    data = worker.read().replace('"', '')    
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
lsock.listen(5)
print("listening on", (host, port))

try:
    while True:
        client, addr = lsock.accept()
        # t = Thread(target=on_connection, args=(client, addr))
        # t.start()
        # threads.append(t)
        on_connection(client ,addr)


except KeyboardInterrupt:
    print("Gracefully shutting down the server")
finally:
    print('ok')
