testin () {
	FILES=tests/$1/*
	for f in $FILES
	do
		name=$(basename $f)
		for i in {1..1000}
		do
			(cat $f | ./main) >> timeof$name
		done
		mv timeof$name mediciones/$1/
	done
}

while true; do
    read -p "Which set of tests would you like to run? Allways/Random/Impossible/Maze: " tst
    case $tst in
        [Allways]* ) testin AllWays; break;;
        [Random]* ) testin Random; break;;
		[Impossible]* ) testin Impossible; break;;
		[Maze]* ) testin Maze; break;;
        * ) echo "Please answer one of the options.";;
    esac
done