for i in {2..24..2}
do
	cat Instance-$i-0.txt | ../../.././main >> Instance-$i-0.out
	echo "Instance-$i-0 done!"
done