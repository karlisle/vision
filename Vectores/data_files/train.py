import sys

import numpy as np
import  sqlite3
import  csv
import operator
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QMainWindow, QApplication, QDialog, QPushButton, QLabel, QMessageBox
from PyQt5 import uic


class Openclose(QMainWindow):
    '''Clase que nor permitira discriminar manualmente entre ojos abiertos y cerrados
        que posteriormente se usaran para crear un modelo de descriptores
    '''
    def __init__(self):
        # Iniciar el objeto QMainWindow
        QMainWindow.__init__(self)
        # Cargar el archivo de interfaz
        uic.loadUi("openclose.ui", self)
        self.cont = 0
        self.cargarImagen()
        self.abierto.clicked.connect(self.ojoAbierto)
        self.cerrado.clicked.connect(self.ojoCerrado)


        pass

    ''' Definicion para conectarse a la base de datos'''
    def dataBase(selfm, query):
        conect = sqlite3.connect("puntos.db")

        if not conect:
            print('ERR: No se ha podido abrir la base de datos!!')
            return
            pass
        else:
            cursor = conect.cursor()
            res = cursor.execute(query)
            conect.commit()
            print('OK!')
            return res
            pass
        pass

    def getData(self, query):

        # Obtenemos los datos de laq base de datos

        datos = self.dataBase(query)
        rows = []
        for row in zip(datos):
            for col in row:
                rows.append(col)
                pass
            pass
        return  rows
        pass

    def cargarImagen(self):
        # Cargar las imagenes

        if  self.cont < 10:
            der = '000' + str(self.cont) + 'r.bmp'
            izq = '000' + str(self.cont) + 'l.bmp'
            pass
        elif self.cont < 100:
            der = '00' + str(self.cont) + 'r.bmp'
            izq = '00' + str(self.cont) + 'l.bmp'
            pass
        elif self.cont < 1000:
            der = '0' + str(self.cont) + 'r.bmp'
            izq = '0' + str(self.cont) + 'l.bmp'
            pass
        self.contador.setText(str(self.cont))
        self.der.setPixmap(QPixmap("/home/kharl/Documents/vision/Vectores/muestras/%s" % (der)))
        self.izq.setPixmap(QPixmap("/home/kharl/Documents/vision/Vectores/muestras/%s" % (izq)))


        print("Cargando")
        pass

    def ojoAbierto(self):
        print("Abierto")
        query = 'SELECT * from puntosroi WHERE id = %d' %(self.cont + 1)

        datos = self.getData(query)

        id = datos[0][0]
        roll = datos[0][1]
        yaw = datos[0][2]
        pitch = datos[0][3]
        p19x = datos[0][4]
        p19y = datos[0][5]
        p20x = datos[0][6]
        p20y = datos[0][7]
        p21x = datos[0][8]
        p21y = datos[0][9]
        p22x = datos[0][10]
        p22y = datos[0][11]
        p23x = datos[0][12]
        p23y = datos[0][13]
        p24x = datos[0][14]
        p24y = datos[0][15]
        p25x = datos[0][16]
        p25y = datos[0][17]
        p26x = datos[0][18]
        p26y = datos[0][19]
        p27x = datos[0][20]
        p27y = datos[0][21]
        p28x = datos[0][22]
        p28y = datos[0][23]
        p29x = datos[0][24]
        p29y = datos[0][25]
        p30x = datos[0][26]
        p30y = datos[0][27]
        state = 1
        print(id)

        inser = 'INSERT INTO ojos(id,roll,yaw,pitch,p19x,p19y,p20x,p20y,p21x,p21y,p22x,p22y,p23x,p23y,p24x,p24y,p25x,p25y,p26x,p26y,p27x,p27y,p28x,p28y,p29x,p29y,p30x,p30y,state) VALUES(%d, %f, %f, %f, %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)' %(id,roll, yaw,pitch,p19x,p19y,p20x,p20y,p21x,p21y,p22x,p22y,p23x,p23y,p24x,p24y,p25x,p25y,p26x,p26y,p27x,p27y,p28x,p28y,p29x,p29y,p30x,p30y,state)
        print(inser)
        self.dataBase(inser)
        self.cont += 1
        self.cargarImagen()
        pass

    def ojoCerrado(self):
        print("Cerrado")
        query = 'SELECT * from puntosroi WHERE id = %d' % (self.cont + 1)

        datos = self.getData(query)

        id = datos[0][0]
        roll = datos[0][1]
        yaw = datos[0][2]
        pitch = datos[0][3]
        p19x = datos[0][4]
        p19y = datos[0][5]
        p20x = datos[0][6]
        p20y = datos[0][7]
        p21x = datos[0][8]
        p21y = datos[0][9]
        p22x = datos[0][10]
        p22y = datos[0][11]
        p23x = datos[0][12]
        p23y = datos[0][13]
        p24x = datos[0][14]
        p24y = datos[0][15]
        p25x = datos[0][16]
        p25y = datos[0][17]
        p26x = datos[0][18]
        p26y = datos[0][19]
        p27x = datos[0][20]
        p27y = datos[0][21]
        p28x = datos[0][22]
        p28y = datos[0][23]
        p29x = datos[0][24]
        p29y = datos[0][25]
        p30x = datos[0][26]
        p30y = datos[0][27]
        state = 0
        print(id)

        inser = 'INSERT INTO ojos(id,roll,yaw,pitch,p19x,p19y,p20x,p20y,p21x,p21y,p22x,p22y,p23x,p23y,p24x,p24y,p25x,p25y,p26x,p26y,p27x,p27y,p28x,p28y,p29x,p29y,p30x,p30y,state) VALUES(%d, %f, %f, %f, %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)' % (id, roll, yaw, pitch, p19x, p19y, p20x, p20y, p21x, p21y, p22x, p22y, p23x, p23y, p24x, p24y, p25x, p25y, p26x, p26y, p27x, p27y, p28x, p28y, p29x, p29y, p30x, p30y, state)
        print(inser)
        self.dataBase(inser)
        self.cont += 1
        self.cargarImagen()

        pass
    def csv(self):
        datos = self.getData("select * from ojos")
        with open('openClose.csv', 'w', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter=' ', quotechar='|', quoting=csv.QUOTE_MINIMAL)
            spamwriter.writerow(
                [id, roll, yaw, pitch, p19x, p19y, p20x, p20y, p21x, p21y, p22x, p22y, p23x, p23y, p24x, p24y, p25x,
                 p25y, p26x, p26y, p27x, p27y, p28x, p28y, p29x, p29y, p30x, p30y, state] + ['\n'])
            pass
        pass

    pass

App = QApplication(sys.argv)
_ojos = Openclose()
_ojos.show()
App.exec_()



















