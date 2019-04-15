#!/usr/bin/python

"""
   Author: Spyridakis Christos   
   Created Date: 10/4/2019
   Last Updated: 15/4/2019
   Email: spyridakischristos@gmail.com
	
   Description: 
	This script just reads cpu and virtual memory load 
   	using psutil, creates packets containing the above 
	information and transmits these data to an arduino 
	using Serial port. Every 500 milliseconds a new 
	packet is generated. 

   Dependencies: 
   	- Python2.7 
	- pip2 version 8.1.1 and later
	- pyserial 3.4 and later
	- psutil 5.6.1 and later
"""

#Import Libraries
import time, os, platform, sys, signal

#Check Platform    
myPlatform=''
if platform.system() == 'Windows':
	myPlatform = "Windows" 
elif platform.system() == 'Linux':
	myPlatform = "Linux"

#----------------------------------------------
#               Check dependencies
#            and Install needed packages

#psutil 
try:
	import psutil
except ImportError:
	os.system('pip2 install psutil')

#pyserial
try:
	from serial import Serial
except ImportError:
	os.system('pip2 install pyserial')

#Import them if the just installed
try:
	import psutil
        from serial import Serial
except ImportError:
	print("Please try to install psutil and pyserial manually")
	sys.exit()
#----------------------------------------------

#------------------------------------------------------------------------------------------------
#					Needed Classes START

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
	def __init__(self, port, baud, timeout, debug):
		self.port=port
		self.baud=baud
		self.timeout=timeout
                self.debug=debug
		while 1:
			try:
				self.ser = Serial(str(self.port), self.baud, timeout=self.timeout)
				self.ser.close()
				self.ser.open()
				break
			except NameError:
				print("Class name Error")
                                sys.exit()
			except:
				print("USB is not connected") 
					
			if handler.SIGINT:
				print("Exit")
				sys.exit()
			time.sleep(1)

	def send(self, cpu, ram):
		mess = "[" + str(cpu) + "|" + str(ram) + "] "
		self.ser.write(mess)
		if self.debug:
			print (mess)
		else:
			print ("Cpu: " + str(cpu) + " ram: " + str(ram))
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
#						END
#------------------------------------------------------------------------------------------------

def readArgs():
        DEBUG = 0
       	if(sys.argv[1]=="-h"):
                print("Usage: " + str(sys.argv[0]) + " [OPTION] [PORT_NUMBER] [DEBUG]")
                print("Usage: " + str(sys.argv[0]) + " [PORT] [DEBUG]")
		print("\n[Options]:")
		print("-p\t  /dev/ttyUSBX on linux | COMX on Windows")
		print("-pA\t  /dev/ttyACMX on linux | COMX on Windows")
                print("\n[DEBUG]:")
		print("-D\t  print payload")
                print("\nExamples:")
                print("Usage 1 - Do not print DEBUB messages: \t\t\t\t$ " + str(sys.argv[0]) + " -p 2")
                print("Usage 2 - Print DEBUG messages and connect to /dev/ttyACM0:\t$ " + str(sys.argv[0]) + " -pA 0 -D")
                print("Usage 3 - Print DEBUG messages and connect to /dev/ttyUSB1:\t$ " + str(sys.argv[0]) + " /dev/ttyUSB1 -D")
                print("Usage 4 - Do not print DEBUG messages and connect to COM2:\t$ " + str(sys.argv[0]) + " COM2")
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
        
        #Debug
        try: 
		if (sys.argv[2]=="-D" or sys.argv[3]=="-D"):
			DEBUG = 1
	except:
		pass
        return port, DEBUG

def main():
        #Read input args
        port, debug = readArgs()
        print("My platform: " + myPlatform)
	#Create PC instance
	load=PCLoad()
	#Create Serial interface
        print("Connecting to: " + str(port))
	toUSB = mySerial(str(port),9600,0.5,debug)

        #Send packages FOREVER!
	while(1):
		#Read cpu and ram load
		cpu = int(round(load.cpuUsagePercentage()))
		ram = int(round(load.ramUsagePercentage()))

		#Send Data
		try:
			toUSB.send(cpu, ram)
		except:
			print("Connection failed. Reconnect...")
		
		#Ctrl + C 
		if handler.SIGINT:
			toUSB.exit()
			print("Exit")
			break
		time.sleep(0.4)

if __name__== "__main__":
  main()
