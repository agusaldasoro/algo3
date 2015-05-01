import sys
import random as r

def generate_instance(numb):
	n = input("Enter n: ")
	m = input("Enter m: ")
	s = input("Enter s: ")

	for i in range(0,int(numb)):

		filename = "test"+str(i)
		inicioH = 1#r.randint(1,n+1)
		inicioV = 1#r.randint(1,m+1)
		bunkerH = m#r.randint(1,n+1)
		bunkerV = n#r.randint(1,m+1)
	
		f = open(filename,'w')
		f.write(str(n)+' ')
		f.write(str(m)+' ')
		f.write(str(s)+'\n')
	
		f.write(str(inicioH)+' ')
		f.write(str(inicioV)+' ')
		f.write(str(bunkerH)+' ')
		f.write(str(bunkerV)+'\n')
	
		for i in range(1,m):
			for h in range(1,n-1):
				f.write(str(r.randint(0,s+1))+' ')
			f.write(str(r.randint(0,s+1))+'\n')
			for v in range(1,n):
				f.write(str(r.randint(0,s+1))+' ')
			f.write(str(r.randint(0,s+1))+'\n')
		for h in range(1,n-1):
			f.write(str(r.randint(0,s+1))+' ')
		f.write(str(r.randint(0,s+1))+'\n')
	
		f.close()

generate_instance(sys.argv[1])