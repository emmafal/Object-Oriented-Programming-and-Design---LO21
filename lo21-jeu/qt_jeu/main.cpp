#include <QApplication>
#include "MainWindow.h"
#include "MainWindowJeu.h"
#include "Partie.h"
#include "Joueur.h"
#include "Deck.h"
#include "IAFacile.h"
#include "InterfaceGraphique.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    MainWindow mainWindow;
    MainWindowJeu windowJeu;

    mainWindow.resize(1200, 700);
    windowJeu.resize(1200, 700);

    // settings (valider) -> interface jeu
    QObject::connect(&mainWindow, &MainWindow::goToWindowJeuClicked, [&](){
        mainWindow.hide();
        //creation de la partie et assigner à l´interface
        std::string Joueur1 = mainWindow.getjoueur1Name();
        std::string Joueur2 = mainWindow.getjoueur2Name();
        Deck deckJoueur1 = Deck::deckStandard(Couleur::Blanc);
        Deck deckJoueur2 = Deck::deckStandard(Couleur::Noir);
        for (auto it=windowJeu.selectedInsectsStored->begin();it!=windowJeu.selectedInsectsStored->end();++it) {
            if (it.value() == true) {
                TypePiece type;
                if (it.key().toStdString() == "moustique") type = TypePiece::Moustique;
                if (it.key().toStdString() == "coccinelle") type = TypePiece::Coccinelle;
                deckJoueur1.ajouterExtension(type, 1);
                deckJoueur2.ajouterExtension(type, 1);
            }
        }
        Joueur joueur1=Joueur(Joueur1,TypeJoueur::Humain,Couleur::Blanc,deckJoueur1);
        Joueur *joueur2;
        if (Joueur2 == "Skynet") {
            joueur2= new Joueur(Joueur2,TypeJoueur::IA,Couleur::Noir,deckJoueur2);
        }
        else {
            joueur2= new Joueur(Joueur2,TypeJoueur::Humain,Couleur::Noir,deckJoueur2);
        }

        InterfaceGraphique* inter =  new InterfaceGraphique();
        IA* ia = new IAFacile();			// Une partie a toujours un attribut IA qui permet de générer un mouvement, même s'il n'y a pas de joueur IA
        Partie* partietopass = new Partie(joueur1, *joueur2, *inter, 0, *ia);
        partietopass->sauvegarderPartie();
        inter->choisirAction(*partietopass,partietopass->getJoueurActuel());
        qDebug() << "premier joueur" << Joueur1;
        qDebug() << "deuxieme joueur" << Joueur2;
        qDebug() << "from main" << *windowJeu.selectedInsectsStored;
        windowJeu.resetToInterfaceJeu();
        windowJeu.show();
        windowJeu.assignPartie(partietopass);
    });
    QObject::connect(&mainWindow, &MainWindow::joueursConfigured, &windowJeu, &MainWindowJeu::setupJoueurs);

    QObject::connect(&windowJeu, &MainWindowJeu::updateInsectSelection, [&](QMap<QString,bool> selectedInsects){
        qDebug() << "selected insects from main" << selectedInsects;

    });

    //victoire (menu) -> menu debut
    //menu Post sauvegarde -> menu debut
    QObject::connect(&windowJeu, &MainWindowJeu::goToMenuDebut, [&](){
        mainWindow.resetToMenuDebut();
        mainWindow.show();
        windowJeu.hide();
    });
    // Info sur les extensions
    QObject::connect(&mainWindow, &MainWindow::insectSelectionValidated, &windowJeu, &MainWindowJeu::onInsectSelectionValidated);

    mainWindow.show();

    return app.exec();
    
}
