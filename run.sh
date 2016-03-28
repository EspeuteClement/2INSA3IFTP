#Lance le programme et vérifie qu'il n'y a pas de fuite de ressources
#Si il y en à, le programme est capable de supprimer uniquement
#les resources qui ont été crées entre le lancement de l'application
#et sa fermeture

#Todo : S'occuper des processus
ipcs > ipcsAvant.tmp
ipcs -m > ipcsMAvant.tmp
ipcs -q > ipcsQAvant.tmp
ipcs -s > ipcsSAvant.tmp
ps -A -U `whoami` > psAvant.tmp

$1 2> log.log

ipcs > ipcsApres.tmp
ipcs -m > ipcsMApres.tmp
ipcs -q > ipcsQApres.tmp
ipcs -s > ipcsSApres.tmp

ps -A -U `whoami` | grep "Parking"> psApres.tmp

# Récuperer la liste des ipcs et process qui sont apparus
diff -u psAvant.tmp psApres.tmp | grep -E "^\+0" > psDiff.tmp

diff -u ipcsAvant.tmp ipcsApres.tmp | grep -E "^\+0" > ipcsDiff.tmp
diff -u ipcsMAvant.tmp ipcsMApres.tmp | grep -E "^\+0" > ipcsMDiff.tmp
diff -u ipcsQAvant.tmp ipcsQApres.tmp | grep -E "^\+0" > ipcsQDiff.tmp
diff -u ipcsSAvant.tmp ipcsSApres.tmp | grep -E "^\+0" > ipcsSDiff.tmp

LEAK=false
if [ "`cat ipcsDiff.tmp | wc -l`" -eq "0" ]; then
	printf "Aucune fuite de ressource detectée\n------------------\n"
else
	printf "Attention, fuite de ressource detectée !\n------------------\n"
	printf "\n------------------\n"
	
	read -r -p "Voulez vous nettoyer automatiquement la mémoire ? [y/N] " response
	case $response in
	    [yY][eE][sS]|[yY])
			# Note : Le bash devenait vraiement trop compliqué pour moi
			# je suis donc passé au Lua, désolé
	        lua Nettoyer.lua ipcsMDiff.tmp m
			lua Nettoyer.lua ipcsQDiff.tmp q
			lua Nettoyer.lua ipcsSDiff.tmp s
			echo "Mémoire nettoyée"
	        ;;
	    *)
	        echo No
	        ;;
	esac
fi

if [ "`cat psApres.tmp | wc -l`" -eq "0" ]; then
	printf "Aucune fuite de processus detectée\n------------------\n"
else
	printf "Attention, fuite de processus detectée !\n------------------\n"
fi

rm *.tmp

#usage : ipcsRmFile fileName type
#			type is : 	m for memory segments
#						q for message queues
#						s for semaphores
#function ipcsRmFile {
#	while IFS='' read -r line || [[ -n "$line" ]]; do
#    	ipcrm -$2 $line
#	done < $1
#}

# Ancien script plus sommaire
#IPCSAVANT=`ipcs | wc -l`; #Compter le nombre de ressources utilisées avant l'execution du programme
#PROCAVANT=`ps -u| wc -l`;
#$1
#IPCSAPRES=`ipcs | wc -l`;
#PROCAPRES=`ps -u| wc -l`;
# if [ "$IPCSAVANT" -eq "$IPCSAPRES" ]; then
# 	printf "Aucune fuite de ressource detectée\n------------------\n"
# else
# 	printf "Attention, fuite de ressource detectée !\n------------------\n"
# fi

