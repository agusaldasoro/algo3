for i in {38..48..2}
do
	cat Instance-$i-45.txt | ../../.././main >> Instance-$i-45.out
	echo "Instance-$i-45 done!"
done