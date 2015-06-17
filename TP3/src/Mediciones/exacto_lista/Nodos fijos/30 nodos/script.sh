for i in {50..0..5}
do
	cat Instance-30-$i.txt | ../../../.././main >> Instance-30-$i.res.out
	echo "Instance-20-$i done!"
done