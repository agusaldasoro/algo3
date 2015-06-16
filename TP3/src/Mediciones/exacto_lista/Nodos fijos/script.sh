for i in {0..185..5}
do
	cat Instance-20-$i.txt | ../../.././main >> Instance-20-$i.res.out
	echo "Instance-20-$i done!"
done