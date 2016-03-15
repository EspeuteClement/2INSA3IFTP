### COMPILATION
# Le compilateur a utiliser
CC = g++
# L'editeur de lien à utiliser
LINK = g++
# Argument pour changer le nom de la sortie du compilo
CC_OUTPUT_FLAG = -o
# Arguments pour le stade d'édition des liens
LINK_FLAG = -lncurses -ltcl -Llib -ltp
# Arguments pour le stade de compilation
CC_COMP_FLAG = -c -std=c++11 -Wall -g -O3


# Commande d'affichage
PRINT = @printf

### FICHIERS
# Nom du fichier de sortie
EXEC = bin/Parking
#Nom des fichers sources
SRC = Mere.cpp
# Nom du dossier sources
SRC_FOLDER = src/
# Le dossier où metre les fichiers objs
OBJS_FOLDER = build/
# Le dossier où metre l'exec
EXEC_FOLDER = bin/

### CLEAN
CLEAN = clean
# La commande pour clean
CLEAN_COMMAND = rm
# Les flags pour clean
CLEAN_FLAG = -f
# Les fichier à clean lors d'un clean
ADDITIONAL_CLEAN = core $(OBJS) $(EXEC)

### TARGET POUR LANCER LE PROGRAME APRES LE MAKE
RUN = run

### AFFICHER DU GRAS :
BOLD = \033[1m
RESET_BOLD = \033[21m



### VARIABLES ADDITIONELLES CREES AUTOMATIQUEMENT
OBJS = $(subst .cpp,.o,$(addprefix $(OBJS_FOLDER),$(SRC)))

##########################################################################
############################LES CIBLES : #################################
##########################################################################

# CIBLE ALL POUR TOUT BUILD
.PHONY : all
all : directories $(EXEC)

# CIBLE OPTIONNELE POUR LANCER LE PROGRAMME APRES LE BUILD
$(RUN) : all
	$(PRINT) "$(BOLD)EXECUTION DE $(EXEC)\n$(RESET_BOLD)------------------\n"
	@./$(EXEC)

# EDITION DES LIENS :
$(EXEC) : $(OBJS)
	$(PRINT) "$(BOLD)EDITION DES LIENS\n\t$(RESET_BOLD)"
	$(LINK) $(CC_OUTPUT_FLAG) $(EXEC) $(OBJS) $(LINK_FLAG)

# CREER LES DOSSIERS MANQUANTS
.PHONY : directories
directories : $(OBJS_FOLDER) $(EXEC_FOLDER)

$(OBJS_FOLDER) :
	$(PRINT) "$(BOLD)CREATION DU REPERTOIRE $@\n\t$(RESET_BOLD)"
	mkdir -p $(OBJS_FOLDER)

$(EXEC_FOLDER) :
	$(PRINT) "$(BOLD)CREATION DU REPERTOIRE $@\n\t$(RESET_BOLD)"
	mkdir -p $(EXEC_FOLDER)

# # CREER LES FICHERS OBJETS
$(OBJS_FOLDER)%.o : $(SRC_FOLDER)%.cpp
	$(PRINT) "$(BOLD)COMPILATION DE $<\n\t$(RESET_BOLD)"
	$(CC) $(CC_OUTPUT_FLAG) $@ $< $(CC_COMP_FLAG)

### CIBLES DE DEPENDANCES

$(SRC_FOLDER)Mere.cpp :