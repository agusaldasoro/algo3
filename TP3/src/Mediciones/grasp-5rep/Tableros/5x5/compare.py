import os

listaDirs = [o for o in os.listdir('.') if os.path.isdir(o)]

for directory in listaDirs:
	if directory != "backup":
		diferencia = 0
		suma = 0
		cant = 0
		f = open(directory+"/porcentaje.diff", 'w')
		for archivo in os.listdir(directory):
			if archivo.endswith("res.prom"):
				exacto = archivo[:-10]
				if exacto.endswith("10"):
					exacto = exacto[:-2]
				elif exacto.endswith("1") or exacto.endswith("2") or exacto.endswith("5") or exacto.endswith("7"):
					exacto = exacto[:-1]
				exacto += "res.out"
				g = open(directory+'/'+archivo, 'r')
				h = open("backup/"+exacto, 'r')
				leerDeG = ""
				leerDeH = ""
				for line in g:
					leerDeG = line
				for line in h:
					leerDeH = line
				diferencia = float(leerDeG)/float(leerDeH)
				diferencia -= 1
				cant += 1
				suma += diferencia
				g.close()
				h.close()
		suma /= cant
		f.write(str(suma))
		f.write('\n')
		f.close()
