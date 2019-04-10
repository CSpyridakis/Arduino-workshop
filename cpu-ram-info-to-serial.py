#!/usr/bin/python

"""
   Author : Spyridakis Christos   
   Created Date : 10/4/2019
   Last Updated : 10/4/2019
   Email : spyridakischristos@gmail.com

   Description: This is a simple script that uses psutil
                and reads cpu and ram load and then sends
                these information in packets every 500 miliseconds
                in order to been read by an arduino through Serial
                
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
        os.system('pip install ' + str(pac))
        print("Installing " + str(pac))
        importlib.import_module(pac)

#----------------------------------------------

"""
        \brief Use this class in order to compute
        cpu load and ram load in persentage

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
        \brief Use this class in order to send
        packages through serial port

        \see pyserial
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

class SIGINT_handler():
    def __init__(self):
        self.SIGINT = False

    def signal_handler(self, signal, frame):
        self.SIGINT = True
handler = SIGINT_handler()
signal.signal(signal.SIGINT, handler.signal_handler)

#Create PC info interface
load=PCLoad()
#Create Serial interface
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
        
        if handler.SIGINT:
                toUSB.exit()
                print("Exit")
                break
        time.sleep(0.4)