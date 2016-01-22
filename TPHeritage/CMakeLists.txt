# Nom du projet
cmake_minimum_required(VERSION 2.8)
project(TpHeritage)

#Lister les fichiers sources

file(
	GLOB SOURCES "src/*"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${PROJECT_SOURCE_DIR}")

#Création du fichier executable
add_executable(

        CommandeTestHistorique ${SOURCES} src/TestCommandeHistorique/TestMain.cpp
)

#Configuration de l'édition de liens


target_compile_features(CommandeTestHistorique PRIVATE cxx_range_for)