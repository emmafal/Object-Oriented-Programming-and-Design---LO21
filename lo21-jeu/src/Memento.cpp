#include "Memento.h"
#include "Partie.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>


Memento::Memento(const Partie& p)
    : plateau(p.plateau), joueur1(p.joueur1), joueur2(p.joueur2), nbTours(p.nbTours), tour(p.tour), fin(p.fin), nbRetoursArriere(p.nbRetoursArriere), historiqueMouvements(p.historiqueMouvements) {}


void Memento::restaurer(Partie& partie) const {
    partie.restaurerEtat(plateau, joueur1, joueur2, nbTours, tour, fin, historiqueMouvements);
}

void Memento::save(std::ofstream& outFile) const {
    if (!outFile) {
        throw std::runtime_error("Erreur lors de l'ouverture du fichier pour la sauvegarde du Memento.");
    }
    
    // Sauvegarde de l'état du plateau
    plateau.save(outFile);
    
    // Sauvegarde des deux joueurs
    joueur1.save(outFile);
    joueur2.save(outFile);

    // Sauvegarde des autres données
    outFile << nbTours << "\n";
    outFile << static_cast<int>(tour) << "\n";
    outFile << static_cast<int>(fin) << "\n";
    outFile << nbRetoursArriere << "\n";
}

void Memento::load(std::ifstream& inFile) {
    if (!inFile) {
        throw std::runtime_error("Erreur lors de l'ouverture du fichier pour le chargement du Memento.");
    }

    // Chargement de l'état du plateau
    plateau.load(inFile);

    // Chargement des deux joueurs
    joueur1.load(inFile, plateau);
    joueur2.load(inFile, plateau);

    // Chargement des autres données
    int tourInt, finInt;
    inFile >> nbTours >> tourInt >> finInt >> nbRetoursArriere;
    tour = static_cast<Couleur>(tourInt);
    fin = static_cast<TypeFin>(finInt);
}