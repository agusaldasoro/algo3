import sys
import random as r
import numpy
from numpy.random import random_integers as rand
import matplotlib.pyplot as pyplot

def generate_instance():
	while True:
	 	try:
			sizes = input("Please enter a list of sizes: ")
			test = raw_input("Which kind of test? Allways/Random/Impossible/Maze: ")
	 		break
	 	except NameError:
	 		print "Invalid syntax. A list of integers must be provided. Example: [100,20]"
	 	except:
	 		print "Stop being an asshole and write it right!"
	
	for size in sizes:
		m = size
		n = size
		s = 20
		filename = "test"+str(m)+'x'+str(n)
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

		if test == "Allways":
			for i in range(1,m):
				for h in range(1,n-1):
					f.write(str(0)+' ')
				f.write(str(0)+'\n')
				for v in range(1,n):
					f.write(str(0)+' ')
				f.write(str(0)+'\n')
			for h in range(1,n-1):
				f.write(str(0)+' ')
			f.write(str(0)+'\n')
		elif test == "Impossible":
			for i in range(1,m):
				for h in range(1,n-1):
					f.write(str(s*2+1)+' ')
				f.write(str(s*2+1)+'\n')
				for v in range(1,n):
					f.write(str(s*2+1)+' ')
				f.write(str(s*2+1)+'\n')
			for h in range(1,n-1):
				f.write(str(s*2+1)+' ')
			f.write(str(s*2+1)+'\n')
		elif test == "Random":
			for i in range(1,m):
			 	for h in range(1,n-1):
			 		f.write(str(r.randint(0,s+(s/2)))+' ')
			 	f.write(str(r.randint(0,s+(s/2)))+'\n')
			 	for v in range(1,n):
			 		f.write(str(r.randint(0,s*2))+' ')
			 	f.write(str(r.randint(0,s*2))+'\n')
			for h in range(1,n-1):
			 	f.write(str(r.randint(0,s+(s/2)))+' ')
			f.write(str(r.randint(0,s+(s/2)))+'\n')
		else:
			mazegen(m,n,s,f)


	f.close()

def maze(width=81, height=51, complexity=.75, density=.75):
    # Only odd shapes
    shape = ((height // 2) * 2 + 1, (width // 2) * 2 + 1)
    # Adjust complexity and density relative to maze size
    complexity = int(complexity * (5 * (shape[0] + shape[1])))
    density    = int(density * (shape[0] // 2 * shape[1] // 2))
    # Build actual maze
    Z = numpy.zeros(shape, dtype=bool)
    # Fill borders
    Z[0, :] = Z[-1, :] = 1
    Z[:, 0] = Z[:, -1] = 1
    # Make aisles
    for i in range(density):
        x, y = rand(0, shape[1] // 2) * 2, rand(0, shape[0] // 2) * 2
        Z[y, x] = 1
        for j in range(complexity):
            neighbours = []
            if x > 1:             neighbours.append((y, x - 2))
            if x < shape[1] - 2:  neighbours.append((y, x + 2))
            if y > 1:             neighbours.append((y - 2, x))
            if y < shape[0] - 2:  neighbours.append((y + 2, x))
            if len(neighbours):
                y_,x_ = neighbours[rand(0, len(neighbours) - 1)]
                if Z[y_, x_] == 0:
                    Z[y_, x_] = 1
                    Z[y_ + (y - y_) // 2, x_ + (x - x_) // 2] = 1
                    x, y = x_, y_
    #print Z
    return Z

def mazegen(m,n,s,f):
	inicioH = 1#r.randint(1,n+1)
	inicioV = 1#r.randint(1,m+1)
	bunkerH = m#r.randint(1,n+1)
	bunkerV = n#r.randint(1,m+1)

	Z = maze(m*2+1,n*2+1)

	width = len(Z[0])
	if m % 2 == 0:
		width -= 1
	height = len(Z)
	if n % 2 == 0:
		height -= 1

	for i in range(1,height):
		for h in range(1,width):
			if(h % 2 == 0 and i % 2 == 0):
				f.write(' ')
			elif(h % 2 == 1 and i % 2 == 1):
				f.write(' ')
			else:
				if(not Z[i][h]):
					f.write(str(r.randint(0,s+s/2)))
				else:
					f.write(str(s+s/4))
		f.write('\n')

	# pyplot.figure(figsize=(10, 5))
	# pyplot.imshow(Z, cmap=pyplot.cm.binary, interpolation='nearest')
	# pyplot.xticks([]), pyplot.yticks([])
	# pyplot.show()

generate_instance()