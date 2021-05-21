from tkinter import *
import serial

#Connexion au port COM
ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM2'
ser.open()
print("Le port est pris : " + str(ser.is_open))

#Fonction qui défini le seuil
def Click():
    read = Box.get()
    ser.write(read.encode())
    Seuil.config(text='Vous avez défini le seuil à : '+read)
    return read


#Fonction qui ferme la liason avec le port COM
def fermeture():
    ser.close()
    print("Le port est pris : " + str(ser.is_open))
    root.destroy()

#Fonction qui permet d'espacer dans l'interface graphique
def invisible():
    Invisible = Label(root, text='').pack()
    return Invisible

#Partie graphique
root = Tk()
root.geometry("400x300")

Title = Label(root, text='Simulation du projet en éléctronique digitale')
Title.pack()

invisible()

Box = Entry(root, width=20)
Box.pack()

invisible()

Btn = Button(root, text='Entrez', command=Click)
Btn.pack()

invisible()

Seuil = Label(root, text='')
Seuil.pack()

root.protocol("WM_DELETE_WINDOW", fermeture)
root.mainloop()
