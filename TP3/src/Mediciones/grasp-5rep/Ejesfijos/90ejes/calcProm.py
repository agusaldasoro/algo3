import os

listaDirs = [o for o in os.listdir('.') if os.path.isdir(o)]

for directory in listaDirs:
	if directory != "backup":
		for archivo in os.listdir(directory):
			if archivo.endswith(".time"):
				cant = 0
				suma = 0
				salida = archivo[:-4]
				salida += "prom"
				f = open(directory+'/'+salida, 'w')
				g = open(directory+'/'+archivo, 'r')
				for line in g:
					cant += 1
					suma += float(line)
				suma /= cant
				f.write(str(suma))
				g.close()
				f.close()
