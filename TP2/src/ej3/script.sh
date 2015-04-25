for i in {1..9}
do
	cat tests.tp2.ej3/00$i.in | ./main > tests.tp2.ej3/00$i.miSol
done
for i in {10..38}
do
	cat tests.tp2.ej3/0$i.in | ./main > tests.tp2.ej3/0$i.miSol
done

