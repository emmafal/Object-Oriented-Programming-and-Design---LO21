cmake_minimum_required(VERSION 3.13)

project(hive_console)
set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} 
	"src/main.cpp"
	"src/Partie.cpp"
	"src/Plateau.cpp"
	"src/Case.cpp" 
	"src/Position.cpp"
	"src/Mouvement.cpp"
	"src/Direction.cpp" 
	"src/Controleur.cpp"
	"src/Pieces/Piece.cpp"  
	"src/Pieces/ReineAbeille.cpp" 
	"src/Pieces/Moustique.cpp"
	"src/Pieces/Scarabee.cpp"
	"src/Pieces/Coccinelle.cpp"
	"src/Pieces/Sauterelle.cpp"
	"src/Pieces/Araignee.cpp" 
	"src/Pieces/Fourmis.cpp"
	"src/Interfaces/InterfaceConsole.cpp" 
	"src/Couleur.cpp"
	"src/UI/UIConsole.cpp"
	"src/Deck.cpp"
	"src/Joueur.cpp"
	"src/Memento.cpp"
	"src/UI/AsciiBoard.cpp"
	"src/UI/CharGrid.cpp"
	"src/UI/HexPrinter.cpp"
	"src/IA/IAFacile.cpp"
)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/Pieces")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/Interfaces")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/UI")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/IA")

