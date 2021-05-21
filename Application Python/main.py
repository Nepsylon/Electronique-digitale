from tkinter import *
import serial

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM2'
ser.open()
print("Le port est pris : " + str(ser.is_open))

root = Tk()
root.geometry("400x300")

def Click():
    read = E.get()
    ser.write(read.encode())
    return read

Title = Label(root, text='Simulation du projet en éléctronique digitale')
Title.pack()

E = Entry(root, width=20)
E.pack()

Bt = Button(root, text='Entrez', command=Click)
Bt.pack()

def fermeture():
    ser.close()
    print("Le port est pris : " + str(ser.is_open))
    root.destroy()

root.protocol("WM_DELETE_WINDOW", fermeture)
root.mainloop()