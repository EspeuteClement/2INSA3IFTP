# Nom du projet
cmake_minimum_required(VERSION 3.2)
project(TpHeritage)

#Lister les fichiers sources

file(
	GLOB SOURCES "src/*"
)

include_directories("${PROJECT_SOURCE_DIR}")

#Création du fichier executable
add_executable(

        CommandeTestHistorique ${SOURCES} src/TestCommandeHistorique/TestMain.cpp
)

#Configuration de l'édition de liens


#target_compile_features(CommandeTest PRIVATE cxx_range_for)