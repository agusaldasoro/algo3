for i in 10 25 50 75 100; do
	directory="time_"$i"_v1_alpha"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat $f | ../../../../mainV1_a $i 1>$directory/$f.$i.out 2>$directory/$f.$i.time;
	done;
done;
for i in 10 25 50 75 100; do
	directory="time_"$i"_v2_alpha"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat $f | ../../../../mainV2_a $i 1>$directory/$f.$i.out 2>$directory/$f.$i.time;
	done;
done;
for i in 3 5 7 10 12; do
	directory="time_"$i"_v1_beta"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat $f | ../../../../mainV1_b $i 1>$directory/$f.$i.out 2>$directory/$f.$i.time;
	done;
done;
for i in 3 5 7 10 12; do
	directory="time_"$i"_v2_beta"
	if [ ! -d $directory ]; then
		mkdir $directory;
	fi
	for f in *.txt; do
		cat $f | ../../../../mainV2_b $i 1>$directory/$f.$i.out 2>$directory/$f.$i.time;
	done;
done;

