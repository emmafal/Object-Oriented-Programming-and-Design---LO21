#include "InterfaceGraphique.h"
#include <iostream>
#include <iomanip>
#include <format>
#include <random>
#include "InterfaceConsole.h"
#include "Partie.h"
#include "PieceFactory.h"
#include "AsciiBoard.h"
#include "HexPrinter.h"
#include "IAFacile.h"
#include <QDebug>
#include <QMessageBox>

Partie InterfaceGraphique::configurerPartie() {
    //dummy
    Deck deckJoueur1 = Deck::deckStandard(Couleur::Blanc);
    Deck deckJoueur2 = Deck::deckStandard(Couleur::Noir);
    Joueur joueur1("dummy",TypeJoueur::Humain,Couleur::Blanc,deckJoueur1);
    Joueur joueur2("dummy",TypeJoueur::Humain,Couleur::Blanc,deckJoueur2);
    IA* ia = new IAFacile();
    return Partie(joueur1,joueur2,*this,0,*ia);
};

void InterfaceGraphique::afficherPlateau(const Plateau& p) const {
    return;
};
void InterfaceGraphique::choisirDeplacement(Partie& partie, Joueur& joueur) const
{
    return;
};
void InterfaceGraphique::choisirPlacement(Partie& partie, Joueur& joueur) const
{ return;
};
void InterfaceGraphique::choisirAction(Partie& partie, Joueur& joueur) const {
    //std::cout << "Choisir action called";
    return;
};
void InterfaceGraphique::lancerPartie(Partie& partie) const {
    return;
};
QString couleurToString(Couleur couleur) {
    switch (couleur) {
    case Couleur::Blanc:
        return "Blanc";
    case Couleur::Noir:
        return "Noir";
    default:
        return "Inconnu";
    }
}

void InterfaceGraphique::finirPartie(Partie& partie, Joueur& gagnant) const {
    qDebug() << "Fin de la partie";

    if (partie.getFin() == TypeFin::Egalite) {
        qDebug() << "Egalité parfaite";
        QMessageBox::information(nullptr, "Fin de la partie", "La partie se termine par une égalité parfaite.");
    } else {
        // Conversion de std::string à QString si nécessaire
        QString message = "Victoire de " + QString::fromStdString(gagnant.getNom()) + " (" + couleurToString(gagnant.getCouleur()) + ")";
        qDebug() << message;
        QMessageBox::information(nullptr, "Fin de la partie", message);
    }
}
