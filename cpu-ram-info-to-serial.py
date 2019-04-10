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
        for pac in packagesInstall:
                os.system('start cmd /k pip install ' + str(pac))
                print("Installing " + str(pac))
                importlib.import_module(pac)
elif platform.system() == 'Linux':
        myPlatform="Linux"
        for pac in packagesInstall:
                print("Installing " + str(pac))
                os.system('pip install ' + str(pac))
                importlib.import_module(pac)
print("My platform: " + myPlatform)
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

        def send(self, cpu, ram):
                ser = serial.Serial(self.port, self.baud, timeout=self.timeout)
                ser.close()
                ser.open()
                print ("Cpu: " + str(cpu) + " ram: " + str(ram))
                ser.write(str(cpu)+"|"+str(ram))
                time.sleep(0.1)
                ser.close()

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
        time.sleep(0.4)