
import sqlite3
import numpy as np
import matplotlib.pyplot as plt


conn = sqlite3.connect("puntos.db")
cursor = conn.cursor()
cursor.execute("SELECT id, p20y from puntosroi")

a = []

for punto in cursor:
	print(punto)
	a.append(punto[1])
	pass

plt.plot(a)
plt.show()

conn.close()