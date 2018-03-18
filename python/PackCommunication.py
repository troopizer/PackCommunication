#!/usr/bin/env python

import serial
import time
import msvcrt
import sys

class PackCommunication:

	def __init__(self, path, baud_rate):
		self.SFLAG = b'0'
		self.EFLAG = b'1'
		self.EESC  = b'2'
		self.byteT = 1.0/baud_rate

		self.s     = serial.Serial()
		self.error = ""
		try:
			self.s.port     = path
			self.s.baudrate = baud_rate
			self.s.timeout  = 0

			self.s.open()
			time.sleep(2.000)			# arduino reset
		except serial.serialutil.SerialException:
			self.error = path + " not found"

	def opened(self):
		return self.s.is_open

	def send(self, string):
		self.s.write(self.SFLAG)
		
		for c in string:
			if c.encode() == self.EFLAG or c.encode() == self.SFLAG or c.encode() == self.EESC:
				self.s.write(self.EESC)
			self.s.write(c.encode())
		
		self.s.write(self.EFLAG)
		self.s.flush()

	def send_bytes(self, _bytes):
		self.s.write(self.SFLAG)
		
		for c in _bytes:
			c = bytes([c])
			if c == self.EFLAG or c == self.SFLAG or c == self.EESC:
				self.s.write(self.EESC)
			self.s.write(c)

		self.s.write(self.EFLAG)
		self.s.flush()

	def recv(self):
		buff = bytearray()
		if (self.s.in_waiting < 2):
			return buff
		
		byte = self.s.read()
		if (byte != self.SFLAG):
			return buff

		while True:
			byte = self.s.read()
			if len(byte) == 0:
				continue
			elif byte == self.EFLAG:
				break
			elif byte == self.EESC:
				byte = self.s.read()
				while len(byte) < 1:
					byte = self.s.read()
			
			buff.extend(byte)

		return buff

	def recv_wait(self):
		while (self.s.in_waiting < 2):
			time.sleep(self.byteT)
		return self.recv()

# Program

if __name__ == "__main__":
	print("Example 1")

	paco = PackCommunication("COM3", 115200)
	if not paco.opened():
		print("Error : ", paco.error)
		exit(1)

	while True:
		paco.send("Hello World")
		print(paco.recv_wait().decode("utf-8") )

	