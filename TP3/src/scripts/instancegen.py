import random as r
from numpy.random import random_integers as rand

def instancegen():
	while True:
		try:
			nodes = input("Please enter the amount of nodes: ")
			while True:
				try:
					edges = input("Please enter the amount of edges: ")
					if(edges > (nodes*(nodes-1)/2)):
						raise NameError()
					break
				except NameError:
					print "Too many edges. There must be less than nodes*(nodes-1)/2"
			break
	 	except NameError:
	 		print "Invalid syntax. An integer must be provided"	

	filename = "Instance-"+str(nodes)+"-"+str(edges)+".txt"
	f = open(filename, 'w')
	f.write(str(nodes)+' '+str(edges)+'\n')
	nodeList = [node for node in range(0,nodes)]
	edgesUsed = []
	for edge in range(0, edges):
		fromNode = r.choice(nodeList)
		nodeList.remove(fromNode)
		toNode = r.choice(nodeList)
		nodeList.append(fromNode)
		choice1 = [fromNode, toNode]
		choice2 = [toNode, fromNode]
		while ((edgesUsed.count(choice1) > 0) or (edgesUsed.count(choice2) > 0)):
			fromNode = r.choice(nodeList)
			nodeList.remove(fromNode)
			toNode = r.choice(nodeList)
			nodeList.append(fromNode)
			choice1 = [fromNode, toNode]
			choice2 = [toNode, fromNode]
		edgesUsed.append(choice1)
		f.write(str(fromNode)+' '+str(toNode)+'\n')
	f.close()

instancegen()