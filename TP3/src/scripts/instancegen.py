import random as r
from numpy.random import random_integers as rand

def instancegen():
	while True:
		try:
			execution = raw_input("Please enter the type of execution (Once/Several): ")
			if(execution.lower() == "once"):
				try:
					nodes = input("Please enter the amount of nodes: ")
					while True:
						try:
							maxEdges = (nodes*(nodes-1)/2)
							edges = input("Please enter the amount of edges (MAX: "+str(maxEdges)+"): ")
							if(edges > maxEdges):
								raise NameError()
							break
						except NameError:
							print "Too many edges. There must be less than "+str(maxEdges)
					break
	 			except NameError:
	 				print "Invalid syntax. An integer must be provided"	
	 		elif(execution.lower() == "several"):
	 			try:
	 				tests = input("Please enter the amount of tests: ")
	 				fix = raw_input("What element would you have fixed? (Nodes/Edges): ")
	 				if(fix.lower() == "nodes"):
	 					nodes = input("Enter the amount of nodes: ")
	 					maxEdges = (nodes*(nodes-1)/2)
	 					edges = input("Enter the starting edges (MAX: "+str(maxEdges)+"): ")
	 					step = input("Enter the steps: ")
	 					break
	 				elif(fix.lower() == "edges"):
	 					nodes = input("Enter the starting nodes: ")
	 					maxEdges = (nodes*(nodes-1)/2)
	 					edges = input("Enter the amount of edges (MAX: "+str(maxEdges)+"): ")
	 					step = input("Enter the steps: ")
	 					break
	 				else:
	 					raise NameError()
	 			except NameError:
	 				print "Invalid syntax or value."
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
		test = 0
		if(fix.lower() == "nodes"):
			while(test < tests and edges < maxEdges):
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
				edges+=step
				test+=1
		else:
			while(test < tests):
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
				nodes+=step
				test+=1

instancegen()