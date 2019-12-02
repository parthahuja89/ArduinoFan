from __future__ import print_function
import psutil
import serial 
import time 
import boto3
from decimal import Decimal

import matplotlib.pyplot as plt
import numpy as np
from collections import Counter 
class arduinoFan:
    def __init__(self):
        self.TableName = 'EnvironmentData'
        self.dynamoDB =  boto3.resource('dynamodb', region_name='us-east-2')
        self.temp = '' 
        self.humid = '' 
        self.ram = ''
        self.table = self.dynamoDB.Table('EnvironmentData')
        self.sensor_id = 0 
        self.client = boto3.client('dynamodb', region_name='us-east-2')
    
    # Configure Boto3 to connect to services 
    def postAWS(self):
        # print(self.client.list_tables())
        self.sensor_id += 1 
        self.table.put_item(
            Item={
                'sensor_Id': str(self.sensor_id),
                'Temperature': self.temp,
                'Humidity' : self.humid,
                "RAM Usage": Decimal(str(self.ram))
            }
        )
    
    def plotAWS(self, temps):
        freq = Counter(temps)
        plt.bar(range(len(freq)), list(freq.values()), align='center')
        plt.xticks(range(len(freq)), list(freq.keys()))

        plt.show()

    def getAWS(self):
        res = self.table.scan()
        items = res["Items"]
        temps = []

        for item in items: 
            val = item["Temperature"]
            temps += [int(val)]
            print(val)
        print(temps)
        self.plotAWS(temps)
        
    # Get System stats 
    def readStats(self):
        ard = serial.Serial('/dev/cu.usbmodem14201', 9600)
        self.temp = ard.readline().decode()
        self.humid = ard.readline().decode()
        self.ram = psutil.virtual_memory()[2]
        print('RAM: ', str(self.ram))
        print("TEMP: " + str(self.temp)) 
        print("HUMD: " + str(self.humid)) 
        time.sleep(3)
        self.postAWS()
        self.readStats()

    # main 
    def arduinoSetup(self):
        print("CLASS STARTED")
        self.readStats()
        # msg = ard.read(ard.inWaiting()) # read everything in the input buffer
        # print ("Message from arduino: ")
        # print (msg)

obj = arduinoFan()
obj.getAWS()