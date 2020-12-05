import serial
import numpy as np
from vpython import *
import time

# Creating Arduino Serial Object
arduino = serial.Serial('COM3', 115200)

# Setting up the environment
scene.range  = 2
scene.width  = 1510
scene.height = 685
caps         = label(text = 'IMU Visualization', pos = vector(0.1, 1.75,0), height = 30, box = False)


# Creating objects in 3-D environment
xarrow = arrow(color = color.red,   axis = vector(1,0,0), length = 0.4, pos = vector(-4.2,-1.6,-0.2))
yarrow = arrow(color = color.green, axis = vector(0,0,-1), length = 0.4, pos = vector(-4.2,-1.6,-0.2))
zarrow = arrow(color = color.blue,  axis = vector(0,1,0), length = 0.4, pos = vector(-4.2,-1.6,-0.2))
mybox  = box(size = vector(1, 1, 1), pos = vector(0,0,0), axis = vector(1,0,0), color = color.yellow)

dx = 0
rad = np.pi/180

# Continuosly acquiring data from arduino via serial port
try:
    while (1==1):

        rate(10)

        while(arduino.inWaiting()  > 0):
                
            # Reading data
            serdata  = arduino.readline()

            # Removing unwanted charactetrs from the acquired data
            serdata  = str(serdata, 'utf-8')

            
            
            try:
                # Splitting the acquired data into respective quantities
                ds       = serdata.split(',')
                

                # Acceleration in X direction
                dx       = float(ds[0])

                # Euler angles
                pitch    = float(ds[1])*rad # Rotation about Y-axis
                yaw      = float(ds[2])*rad # Rotation about Z-axis
                roll     = float(ds[3])*rad # Rotation about X-axi
            

                # Rotation Matrix about X-axis
                R_x      = np.array([[1,    0     ,     0     ],
                                     [0, cos(roll), -sin(roll)],
                                     [0, sin(roll),  cos(roll)]])

                # Rotation Matrix about Y-axis
                R_y      = np.array([[ cos(pitch), 0, sin(pitch)],
                                     [    0      , 1,    0      ],
                                     [-sin(pitch), 0, cos(pitch)]])

                # Rotation Matrix about Z-axis
                R_z      = np.array([[cos(yaw), -sin(yaw), 0],
                                     [sin(yaw),  cos(yaw), 0],
                                     [   0    ,     0    , 1]])

                
                rotmat     = np.dot(np.dot(R_z,R_y),R_x)
                dummy1     = np.array([[1], [0], [0]])
                dummy2     = np.array([[0], [1], [0]])
                newvec1    = rotmat @ dummy1
                newvec2    = rotmat @ dummy2
                mybox.axis = vector(newvec1[0], newvec1[1], newvec1[2])
                mybox.up   = vector(newvec2[0], newvec2[1], newvec2[2])

                mybox.pos.x = dx
                
            except:
                break;
                           

finally:
    print("Hellloooooo")
    arduino.close()








