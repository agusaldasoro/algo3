for i in {1..9}
do
	cat tests.tp1.ej1/00$i.in | ./main
done
for i in {10..36}
do
	cat tests.tp1.ej1/0$i.in | ./main
done

