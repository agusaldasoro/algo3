def comparator():
	while(True):
		try:
			files = input("Please, enter a list of file ID's to compare (Eg: [1,4,5]): ")
			test = raw_input("Please, select the type of test (Greedy): ")
			if(test.lower() == "greedy"):
				break
			else:
				raise NameError()
			break
		except NameError:
			print "Invalid syntaxs"

	resultados = []
	for fid in files:
		exacto = open('comparaciones/exacto'+str(fid)+'.txt','r')
		exactNums = exacto.read().split()
		exactCant = exactNums[0]
		exacto.close()
		testfile = open('comparaciones/'+test.lower()+str(fid)+'.txt','r')
		testNums = testfile.read().split()
		testCant = testNums[0]
		testfile.close()
		resultados.append(float(exactCant)/float(testCant))
	f = open('comparaciones/resultado.txt','w')
	for perc in resultados:
		f.write(str(perc)+"\n")
	f.close()

comparator()