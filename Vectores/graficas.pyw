
import sqlite3
import numpy as np
import matplotlib.pyplot as plt


conn = sqlite3.connect("puntos.db")
cursor = conn.cursor()
cursor.execute("SELECT p20y, p24y from puntosroi")

p20y = []
p24y = []
media = []
for punto in cursor:
	print(punto)
	media.append(((punto[0] - punto[1])/2))
	p20y.append(punto[0])
	p24y.append(punto[1])
	pass
plt.plot(media)
plt.plot(p20y)
plt.plot(p24y)
plt.show()

conn.close()