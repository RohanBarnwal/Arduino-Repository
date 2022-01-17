import serial
import pyautogui

ser = serial.Serial('COM7', baudrate = 9600, timeout=1)

while 1:

    arduinoData = ser.readline().decode('ascii')
    print(arduinoData)
    
    
