

import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('127.0.0.1', 5500))
server_socket.listen(2)
print("Working...")
client_socket, address = server_socket.accept()
data = client_socket.recv(1024).decode('utf-8')
print(data)