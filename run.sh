IPCSAVANT=`ipcs | wc -l`; #Compter le nombre de ressources utilisées avant l'execution du programme
PROCAVANT=`ps -u| wc -l`;
$1
IPCSAPRES=`ipcs | wc -l`;
PROCAPRES=`ps -u| wc -l`;
if [ "$IPCSAVANT" -eq "$IPCSAPRES" ]; then
	printf "Aucune fuite de ressource detectée\n------------------\n"
else
	printf "Attention, fuite de ressource detectée !\n------------------\n"
fi

if [ "$PROCAVANT" -eq "$PROCAPRES" ]; then
	printf "Aucune fuite de processus detectée\n------------------\n"
else
	printf "Attention, fuite de processus detectée !\n------------------\n"
fi