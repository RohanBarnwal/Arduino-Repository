import pyautogui
import serial
data=serial.Serial('com5',9600)

pyautogui.write(data)
    