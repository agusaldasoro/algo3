import os

listaDirs = [o for o in os.listdir('.') if os.path.isdir(o)]
listaDirs.sort()
for directory in listaDirs:
	if directory != "backup":
		for archivo in os.listdir(directory):
			if archivo.endswith(".out"):
				suma = 0
				salida = archivo[:-7]
				salida += "promR"
				f = open(directory+'/'+salida, 'w')
				g = open(directory+'/'+archivo, 'r')
				spliteado = []
				for line in g:
					spliteado = line.split(' ')
					spliteado.pop()
				for elem in spliteado:
					suma += int(elem)
				suma /= len(spliteado)
				f.write(str(suma))
				g.close()
				f.close()
