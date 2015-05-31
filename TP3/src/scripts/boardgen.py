def boardgen():
	while True:
		try:
			size = input("Please enter the board size: ")
			break
	 	except NameError:
	 		print "Invalid syntax. An integer must be provided"

	nodes = size*size
	row = []
	matrix = []
	for node in range(0, nodes):
		row.append(node)
		if len(row) == size:
			matrix.append(row)
			row = []
	createOutput(matrix, nodes)

def createOutput(matrix, nodes):
	filename = "board"
	f = open(filename, 'w')
	outString = ""
	edges = 0
	for row in range(0,len(matrix)):
		for col in range(0,len(matrix[row])):
			if col+2 < len(matrix[row]) and row+1 < len(matrix):
				edges += 1
				outString += str(matrix[row][col])+' '+str(matrix[row+1][col+2])+'\n'
			if col+1 < len(matrix[row]) and row+2 < len(matrix):
				edges += 1
				outString += str(matrix[row][col])+' '+str(matrix[row+2][col+1])+'\n'
			if col-2 >= 0 and row+1 < len(matrix):
				edges += 1
				outString += str(matrix[row][col])+' '+str(matrix[row+1][col-2])+'\n'
			if col-1 >= 0 and row+2 < len(matrix):
				edges += 1
				outString += str(matrix[row][col])+' '+str(matrix[row+2][col-1])+'\n'
	f.write(str(nodes)+' '+str(edges)+'\n')
	f.write(outString)

boardgen()

