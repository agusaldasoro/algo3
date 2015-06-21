for i in 10 25 50 75 100; do
	directory="time_"$i"_v1_alpha"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat board | ../../../../mainV1_a $i 1>$directory/board.$i.out 2>$directory/board.$i.time;
	done;
done;
for i in 10 25 50 75 100; do
	directory="time_"$i"_v2_alpha"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat board | ../../../../mainV2_a $i 1>$directory/board.$i.out 2>$directory/board.$i.time;
	done;
done;
for i in 3 5 7 10 12; do
	directory="time_"$i"_v1_beta"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat board | ../../../../mainV1_b $i 1>$directory/board.$i.out 2>$directory/board.$i.time;
	done;
done;
for i in 3 5 7 10 12; do
	directory="time_"$i"_v2_beta"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat board | ../../../../mainV2_b $i 1>$directory/board.$i.out 2>$directory/board.$i.time;
	done;
done;

