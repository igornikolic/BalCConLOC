#!/usr/bin/env python
import socket
import time
import random
if __name__ == '__main__':
  UDP_IP = "192.168.1.255"
  UDP_PORT = 6454
  MESSAGE = "KEEP ALIVE"
  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
  data = [0] * 300
  green = [255, 0, 0]
  black = [0, 0, 0]
  while True:
    bit = random.randint(0,3)
    data = ( green if bit == 3 else black ) +black + black + data[:-9]
    sock.sendto("Art-Net\x00\x00\x50\x00\x0e\xff\x00\x01\x00"+chr(01)+("".join(chr(x) for x in data)), (UDP_IP, UDP_PORT))
    time.sleep(0.1)
