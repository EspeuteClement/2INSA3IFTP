-- Petit script pour netoyer la machine entre 2 executions
-- Arguments : 
-- (1) Un fichier contenant un résultat de l'execution de ipcs (ou le diff de 2 executions de ipcs)
-- (2) Le type de ipcs que l'on doit supprimé (voir la doc de ipcrm)
-- Ex : lua Nettoyer fichier m --> supprime tout les memory segments dans le fichier fichier

S = io.open(arg[1])
S_str = S:read("*all")

for ipcs in S_str:gmatch("%+*0x%d* %d*") do -- Récuperer la partie "0xchépasquoi id"
	os.execute("ipcrm -"..arg[2].." "..ipcs:match("%d*$")) -- Récuperer que l'id et executer la fonction ipcrm
end