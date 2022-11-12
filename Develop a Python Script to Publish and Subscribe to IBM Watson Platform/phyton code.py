import wiotp.sdk.device
import time
import os
import datetime
import random
myConfig = {
     "identity": {
         "orgId":"hj5fmy",
         "typeId":"Device1",
         "deviceId":"12345"
      },
      "auth":{
             "token":"12345678"
          }
}
client=wiotp.sdk.device.DeviceClient(config=myconfig, logHandlers=None)
client.connect()
def myCommandCallback(cmd):
print("message receieved from IBM IoT Platform: %S" % cmd.data['command'])
m=cmd.data['command']
if(m=="motoron"):
print("Motor is Switched on")
elseif(m=="motoroff"):
print("Motor is Switched OFF")
print(" ")
while True:
soil=random.randint(0,100)
temp=random.randint(-20,125)
hum=random.randint(0,100)
myData={'soil_moisture':soil, 'temperature':temp, 'humidity':hum}
client.publishEvent(eventId="status",msgFormat="json", data=myData, qos=0, onPublish=None)
time.sleep(2)
client.commandCallback = myCommandcallback
client.disconnect()