import random as r
from numpy.random import random_integers as rand

def instancegen():
	while True:
		try:
			execution = raw_input("Please enter the type of execution (Once/Several): ")
			if(execution.lower() == "once"):
				try:
					nodes = input("Please enter the amount of nodes: ")
					if(not(type(nodes) is int)):
						raise NameError()
					while True:
						try:
							maxNodes = (nodes*(nodes-1)/2)
							edges = input("Please enter the amount of edges (MAX: "+str(maxNodes)+"): ")
							if(edges > maxNodes):
								raise NameError()
							break
						except NameError:
							print "Too many edges. There must be less than "+str(maxNodes)
					break
	 			except NameError:
	 				print "Invalid syntax. An integer must be provided"	
	 		elif(execution.lower() == "several"):
	 			try:
	 				tests = input("Please enter the amount of tests: ")
	 				if(not(type(tests) is int)):
						raise NameError()
					nodeRange = input("Enter the maximum amount of nodes: ")
					if(not(type(nodeRange) is int)):
						raise NameError()
	 				break
	 			except NameError:
	 				print "Invalid syntax. An integer must be provided"
	 		else:
	 			raise NameError()
	 	except NameError:
	 		print "Select one of the two: Once or Several"


	if(execution.lower() == "once"):
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
	else:
		for test in range(0, tests):
			nodes = r.randint(0,nodeRange)
			edges = r.randint(0,(nodes*(nodes-1))/2)
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