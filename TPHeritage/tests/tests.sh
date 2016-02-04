exe=../bin/CommandeTestDessin
nOk=0
nKo=0
nTotal=0

for i in Test*
do
	printf "\e[1m\e[93m$i\e[0m\n"
	$exe < $i/in > $i/exe.out
	diff -wB -I^# $i/exe.out $i/out >/dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[32mTest OK\e[0m\n"
		let "nOk=$nOk+1"
	else
		printf "\e[31m\e[31mTest ERR\e[0m\n"
		let "nKo=$nKo+1"
	fi
	let "nTotal=$nTotal+1"
	echo "------------"
done
echo "Reussi : $nOk/$nTotal"
