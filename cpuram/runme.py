#!/usr/bin/python

"""
   Author : Spyridakis Christos   
   Created Date : 10/4/2019
   Last Updated : 10/4/2019
   Email : spyridakischristos@gmail.com
	
   Description: This script just reads cpu and virtual memory load 
   				(using psutil), creates packets containing the above 
				information and transmits these data to an arduino 
				using Serial port. Every 500 milliseconds a new 
				packet is transmitted. 

   Dependencies: Python2.7 and Latest version of pip2 NEEDED!!!
                
"""

#Import Libraries
import time
import os
import platform
import sys
import importlib
import signal

#----------------------------------------------
#               Check dependencies
#            and Install needed packages
packagesInstall = []

#psutil 
try:
	import psutil
except ImportError, e:
	packagesInstall.append("psutil")

#serial
try:
	import serial
	from serial import Serial
except ImportError, e:
	packagesInstall.append("serial")
	packagesInstall.append("pyserial")

#Check Platform    
myPlatform=''
if platform.system() == 'Windows':
	myPlatform="Windows" 
elif platform.system() == 'Linux':
	myPlatform="Linux"
print("My platform: " + myPlatform)

for pac in packagesInstall:
	print("\tInstalling " + str(pac))
	os.system('pip install ' + str(pac))
	try:
		importlib.import_module(pac)
	except:
		print("Python2.7 and latest version of pip2 needed")
		sys.exit()

#----------------------------------------------


#------------------------------------------------------------------------------------------------
#										Needed Classes START
"""
	\brief 	Use this class in order to compute
			cpu and virtual mem load 

	\see psutil
"""
class PCLoad(object):
	def cpuUsageReadPerCore(self):
		return psutil.cpu_percent(interval=1, percpu=True)

	def cpuUsagePercentage(self):
		cpusLoad=self.cpuUsageReadPerCore()
		percentage=0.0
		for i in cpusLoad:
			percentage+=i
		return percentage/len(cpusLoad)

	def ramUsagePercentage(self):
		return psutil.virtual_memory().percent

"""
	\brief  Use this class in order to send
			packets through serial port

	\see pyserial, serial
"""
class mySerial(object):
	def __init__(self, port, baud, timeout):
		self.port=port
		self.baud=baud
		self.timeout=timeout
		while 1:
			try:
				self.ser = serial.Serial(str(self.port), self.baud, timeout=self.timeout)
				self.ser.close()
				self.ser.open()
				break
			except:
				print("USB is not connected") 
					
			if handler.SIGINT:
				print("Exit")
				sys.exit()
			time.sleep(1)

	def send(self, cpu, ram):
		print ("Cpu: " + str(cpu) + " ram: " + str(ram))
		self.ser.write(str(cpu)+"|"+str(ram))
		time.sleep(0.1)

	def exit(self):
		self.ser.close()

"""
	\brief  Use this class in order to 
			properly exit the execution 
			of the program using Ctrl+C 

	\see signal
"""
class SIGINT_handler():
    def __init__(self):
        self.SIGINT = False

    def signal_handler(self, signal, frame):
        self.SIGINT = True
handler = SIGINT_handler()
signal.signal(signal.SIGINT, handler.signal_handler)

#											END
#------------------------------------------------------------------------------------------------

def main():
	#Create PC instance
	load=PCLoad()
	#Create Serial interface
	if(sys.argv[1]=="-h"):
		print("Usage: " + str(sys.argv[0]) + " [OPTION] [PORT_NUMBER]")
		print("Usage: " + str(sys.argv[0]) + " [PORT]")
		print("\n[Options]:")
		print("-p\t  /dev/ttyUSBX on linux | COMX on Windows")
		print("-pA\t  /dev/ttyACMX on linux | COMX on Windows")
		sys.exit()
	elif(sys.argv[1]=="-p"):
		if(myPlatform=="Linux"):
			port="/dev/ttyUSB"+sys.argv[2]
		elif(myPlatform=="Windows"):
			port="COM"+sys.argv[2]
	elif(sys.argv[1]=="-pA"):
		if(myPlatform=="Linux"):
			port="/dev/ttyACM"+sys.argv[2]
		elif(myPlatform=="Windows"):
			port="COM"+sys.argv[2]
	else:
		port=sys.argv[1]

	print("Connecting to: " + str(port))
	toUSB = mySerial(str(port),9600,0.5)


	#Send packages FOREVER!
	while(1):
		#Read cpu and ram load
		cpu = int(round(load.cpuUsagePercentage()))
		ram = int(round(load.ramUsagePercentage()))
		
		#Send Data
		try:
			toUSB.send(cpu, ram)
		except:
			print("USB is not connected")
		
		#Ctrl + C 
		if handler.SIGINT:
			toUSB.exit()
			print("Exit")
			break
		time.sleep(0.4)

  
if __name__== "__main__":
  main()