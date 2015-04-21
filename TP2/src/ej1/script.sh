for i in {1..9}
do
	cat tests.tp2.ej1.v1.1/00$i.in | ./main > tests.tp2.ej1.v1.1/00$i.miSol
done
for i in {10..29}
do
	cat tests.tp2.ej1.v1.1/0$i.in | ./main > tests.tp2.ej1.v1.1/0$i.miSol
done

