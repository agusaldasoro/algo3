testin () {
	FILES=Greedy/$1/*
	for f in $FILES
	do
		name=$(basename $f)
		for i in {1..1000}
		do
			(cat $f | ./main) >> timeof$name
		done
		mv timeof$name Greedy/mediciones/$1/
	done
}

while true; do
    read -p "Which set of tests would you like to run? Fixnode/Fixedge/Worst: " tst
    echo $tst
    case $tst in
        Fixnode* ) testin Fixnode; break;;
        Fixedge* ) testin Fixedge; break;;
		Worst* ) testin Worst; break;;
        * ) echo "Please answer one of the options.";;
    esac
done