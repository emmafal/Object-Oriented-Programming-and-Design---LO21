INCLUDEPATH += qt_jeu
#INCLUDEPATH += /include
INCLUDEPATH += backend/include
INCLUDEPATH += backend/include/Pieces
INCLUDEPATH += backend/include/IA
INCLUDEPATH += backend/include/Interfaces
INCLUDEPATH += backend/include/UI
#INCLUDEPATH += ../include/Pieces

QT += widgets
QT += core gui widgets
CONFIG += c++20
CONFIG+=utf8_source


SOURCES += \
        backend/src/Partie.cpp \
        backend/src/Plateau.cpp \
        backend/src/Case.cpp \
        backend/src/Position.cpp \
        backend/src/Mouvement.cpp \
        backend/src/Direction.cpp \
        backend/src/Controleur.cpp \
        backend/src/Couleur.cpp \
        backend/src/Deck.cpp \
        backend/src/Joueur.cpp \
        backend/src/Memento.cpp \
        backend/src/Pieces/Piece.cpp \
        backend/src/Pieces/ReineAbeille.cpp \
        backend/src/Pieces/Moustique.cpp \
        backend/src/Pieces/Scarabee.cpp \
        backend/src/Pieces/Coccinelle.cpp \
        backend/src/Pieces/Sauterelle.cpp \
        backend/src/Pieces/Araignee.cpp \
        backend/src/Pieces/Fourmis.cpp \
        backend/src/Interfaces/InterfaceConsole.cpp \
        backend/src/Interfaces/InterfaceGraphique.cpp \
        backend/src/UI/UIConsole.cpp \
        backend/src/UI/AsciiBoard.cpp \
        backend/src/UI/CharGrid.cpp \
        backend/src/UI/HexPrinter.cpp \
        backend/src/IA/IAFacile.cpp \
        InterfaceJeu.cpp \
        MainWindow.cpp \
        MainWindowJeu.cpp \
        MenuConfigJoueur.cpp \
        MenuDePartie.cpp \
        MenuDebut.cpp \
        MenuPostSauvegarde.cpp \
        MenuSauvegardeJeu.cpp \
        SettingsPartie.cpp \
        Victoire.cpp \
        HexagoneItem.cpp\
        PositionQt.cpp\
        main.cpp

HEADERS += \
        backend/include/IA/IA.h \
        backend/include/IA/IAFacile.h \
        backend/include/Partie.h \
        backend/include/Deck.h \
        backend/include/Plateau.h \
        backend/include/Case.h \
        backend/include/Position.h \
        backend/include/Mouvement.h \
        backend/include/Direction.h \
        backend/include/Joueur.h \
        backend/include/Controleur.h \
        backend/include/Interfaces/Interface.h \
        backend/include/Interfaces/InterfaceConsole.h \
        backend/include/Interfaces/InterfaceGraphique.h \
        backend/include/Interfaces/TypeInterface.h \
        backend/include/Plateau.h \
        backend/include/Pieces/Araignee.h \
        backend/include/Pieces/Coccinelle.h \
        backend/include/Pieces/Fourmis.h \
        backend/include/Pieces/Moustique.h \
        backend/include/Pieces/PieceFactory.h \
        backend/include/Pieces/ReineAbeille.h \
        backend/include/Pieces/Sauterelle.h \
        backend/include/Pieces/Scarabee.h \
        backend/include/Pieces/TypeInsecte.h \
        backend/include/UI/UIConsole.h \
        backend/include/UI/AsciiBoard.h \
        backend/include/UI/CharGrid.h \
        backend/include/UI/HexPrinter.h \
        #qt_jeu/InterfaceGraphique.h \
        InterfaceJeu.h \
        MainWindow.h \
        MainWindowJeu.h \
        MenuConfigJoueur.h \
        MenuDePartie.h \
        MenuDebut.h \
        MenuPostSauvegarde.h \
        MenuSauvegardeJeu.h \
        SettingsPartie.h \
        Victoire.h \
        HexagoneItem.h\
        PositionQt.h

RESOURCES += \
    ressources.qrc


