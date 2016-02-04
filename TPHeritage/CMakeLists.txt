# Nom du projet
cmake_minimum_required(VERSION 2.8)
project(TpHeritage)

#Lister les fichiers sources

file(
	GLOB SOURCES "src/*" "src/Commandes/*"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${PROJECT_SOURCE_DIR}")


add_executable(
	Dessinator ${SOURCES} src/main.cpp
)

#Configuration de l'édition de liens


target_compile_features(Dessinator PRIVATE cxx_range_for)



#add_definitions(-DDEBUG)