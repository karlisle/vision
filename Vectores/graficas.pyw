
import sqlite3
import numpy as np
import matplotlib.pyplot as plt



class Ojos:
	def __init__(self):
		pass
	# definicion encargada de conectar y ejecutar las consultas en labase de datos
	def getData(self, consulta):
		#print(consulta)
		conn = sqlite3.connect("puntos.db")
		cursor = conn.cursor()
		res = cursor.execute(consulta)
		return  res
		pass

	''' Obtener los valores correspondientes a los 4 puntos de interes [(p20y, p24y),(p21y, p23y)] del ojos derecho
	 	y [(p26y, p30y), (p27y, p29y)] del Izquierdo.
	'''
	def roiPoints(self):
		#Construimos una consulta pidiendo los puntos
		consultad = "SELECT  p20y, p24y, p21y, p23y FROM puntosroi"
		consultai = "SELECT  p26y, p30y, p27y, p29y FROM puntosroi"

		der = self.getData(consultad)
		izq = self.getData(consultai)

		p20 = []
		p24 = []
		p21 = []
		p23 = []

		p26 = []
		p30 = []
		p27 = []
		p29 = []
		for a, b in zip(der, izq):
			p20.append(a[0])
			p24.append(a[1])
			p21.append(a[2])
			p23.append(a[3])

			p26.append(b[0])
			p30.append(b[1])
			p27.append(b[2])
			p29.append(b[3])
			pass

		self.graficarY(p20, p24, p21,p23, p26, p30, p27, p29)
		pass
	def graficarY(self, p20, p24, p21,p23, p26, p30, p27, p29):

		print(p20)
		print(p24)
		plt.figure('Ojo derecho')
		plt.suptitle('Valores en Y ojo derecho')
		plt.rc('font', size= 8)
		plt.rc('lines', linewidth=1)

		plt.subplot(3, 1, 1)
		plt.plot((p20), color = 'red', label = 'p20y' )

		plt.title(u'Distribucion sobre Y')
		plt.xlabel("Consultas")
		plt.ylabel("Posición en Y")
		plt.legend(loc=1)
		#plt.subplot(2, 1, 1)
		#plt.plot((p24), label='p24y')
		plt.legend(loc=1)

		plt.subplot(3, 1, 2)
		plt.scatter(p20, p24)
		plt.xlabel('P20')
		plt.ylabel('P24')

		distanciaMedia = []
		for sup, inf in zip(p24, p20):
			distanciaMedia.append(sup - inf)
			pass

		sum = 0
		for val in distanciaMedia:
			sum = sum + val
			pass
		print('Media Derecha = ', sum / len(distanciaMedia))

		plt.show()
		pass
	def gt(self):

		pass
	pass


app = Ojos()
app.roiPoints()



