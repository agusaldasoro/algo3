i = 50
g = open("Promgrasp",'w')
while(i <= 1000):
	f = open("Coliseo/Tiempos/Fixedge/300/Instance-"+str(i)+"-300.txt.tgreedy",'r')
	content = f.readlines()
	promedio = 0;
	for num in content:
		promedio += float(num)
	promedio = promedio/len(content)
	g.write(str(promedio)+"\n")
	f.close()
	i += 50
g.close()