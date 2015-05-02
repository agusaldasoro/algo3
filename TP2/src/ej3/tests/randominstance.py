import sys
import random as r

def generate_instance(numb):
	s = input("Enter Costo Refineria: ")

	for i in range(0,int(numb)):

		n = input("Enter Cantidad pozos: ")
#		m = input("Enter Cantidad conexiones: ")
#		s = input("Enter Costo Refineria: ")

		filename = "test"+str(i)
	
		f = open(filename,'w')
		f.write(str(n)+' ')
		f.write(str((n-1)*(n))+' ')
		f.write(str(s)+'\n')
	
#		for i in range(0,m):
#			f.write(str(r.randint(1,n+1))+' ')#pozoA
#			f.write(str(r.randint(1,n+1))+' ')#pozoB
#			f.write(str(r.randint(0,2*s))+'\n')#costo tubo

		for i in range(0,n):
			for j in range(0,n):
				if(i!=j):
					f.write(str(i+1)+' ')#pozoA
					f.write(str(j+1)+' ')#pozoB
					f.write(str(r.randint(0,2*s))+'\n')#costo tubo
	
		f.close()

generate_instance(sys.argv[1])
