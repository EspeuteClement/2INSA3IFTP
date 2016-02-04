rm results
exe=../../bin/CommandeTestDessin
for i in in*
do
	echo "-----------"
		echo "Test pour $i"
	for j in `seq 1 10`
	do

		echo -n "`/usr/bin/time -f %e $exe < $i >/dev/null`" >> results
	done
done