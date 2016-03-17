A=`ipcs | wc -l`; #Compter le nombre de ressources utilisées avant l'execution du programme
$1
B=`ipcs | wc -l`;
if [ "$A" -eq "$B" ]; then
	printf "Aucune fuite de ressource detectée\n------------------\n"
else
	printf "Attention, fuite de ressource detectée !\n------------------\n"
fi