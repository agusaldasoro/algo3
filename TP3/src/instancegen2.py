def instancegen():
	while(True):
		try:
			instance = raw_input("Enter the type of instance (Clique/Tree/Bipartite/Cicle): ")
			if(instance.lower() == "clique"):
				nodes = input("Enter the number of nodes: ")
				break
			elif(instance.lower() == "bipartite"):
				nodesv1 = input("Enter the number of nodes for first partition: ")
				nodesv2 = input("Enter the number of nodes for second partition: ")
				break
			elif(instance.lower() == "cicle"):
				nodes = input("Enter the number of nodes: ")
				break
			elif(instance.lower() == "tree"):
				depth = input("Enter the tree depth: ")
				break
			else:
				raise NameError()
		except NameError:
			print "Please, select a valid instance"

	if(instance.lower() == "clique"):
		f = open("clique-"+str(nodes)+".txt",'w')
		maxNodes = (nodes*(nodes-1)/2)
		f.write(str(nodes)+" "+str(maxNodes)+"\n")
		for node in range(0,nodes):
			for child in range(node+1,nodes):
				f.write(str(node)+" "+str(child)+"\n")
		f.close()
	elif(instance.lower() == "bipartite"):
		f = open("bipartite-"+str(nodesv1)+"-"+str(nodesv2)+".txt",'w')
		f.write(str(nodesv1+nodesv2)+" "+str(nodesv1*nodesv2)+"\n")
		for nodev1 in range(0, nodesv1):
			for nodev2 in range(nodesv1, nodesv2+nodesv1):
				f.write(str(nodev1)+" "+str(nodev2)+"\n")
		f.close()
	elif(instance.lower() == "cicle"):
		f = open("cicle-"+str(nodes)+".txt",'w')
		f.write(str(nodes)+" "+str(nodes)+"\n")
		for node in range(0,nodes):
			f.write(str(node)+" "+str((node+1) % nodes)+"\n")
		f.close()

instancegen()
