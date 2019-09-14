#!/usr/bin/env python
import socket
import time
if __name__ == '__main__':
  UDP_IP = "192.168.1.255"
  UDP_PORT = 6454
  MESSAGE = "KEEP ALIVE"
  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
  while True:
    sock.sendto("Art-Net\x00\x00\x50\x00\x0e\xff\x00\x01\x00"+chr(01)+("\xff\x00\x00"*90), (UDP_IP, UDP_PORT))
    time.sleep(0.1)
    sock.sendto("Art-Net\x00\x00\x50\x00\x0e\xff\x00\x01\x00"+chr(01)+("\x00\xff\x00"*90), (UDP_IP, UDP_PORT))
    time.sleep(0.1)
