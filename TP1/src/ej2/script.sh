for i in {1..9}
do
	cat tests.tp1.ej2/00$i.in | ./main
done
for i in {10..26}
do
	cat tests.tp1.ej2/0$i.in | ./main
done

