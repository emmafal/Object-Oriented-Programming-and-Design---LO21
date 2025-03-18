#include "Joueur.h"
#include <fstream>
#include <stdexcept>
#include <sstream>


std::ostream& operator<<(std::ostream& os, const Joueur& joueur)
{
	os << joueur.nom << ", " << joueur.couleur;
	return os;
}

void Joueur::selectionnerPieceDeck(TypePiece type)
{
	selectionnee = deck.prendrePiece(type);
}

void Joueur::annulerSelection()
{
	if (selectionnee == nullptr) return;
	deck.reposerPiece(selectionnee->getType()); 
	selectionnee = nullptr;
}

void Joueur::save(std::ofstream& outFile) const {
    if (!outFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour la sauvegarde.");
    }

    // Save player details
    outFile << static_cast<std::string>(nom) << "\n";
    outFile << static_cast<int>(type) << "\n";
    outFile << static_cast<int>(couleur) << "\n";

    
    deck.save(outFile);

    /*
    if (selectionnee) {
        outFile << static_cast<int>(selectionnee->getType()) << "\n";
    } else {
        outFile << "-1\n";
    }*/

    outFile << "END_J\n";
}

void Joueur::load(std::ifstream& inFile, const Plateau& plateau) {
    if (!inFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour le chargement.");
    }

    try {
        std::getline(inFile, nom);
        if (inFile.fail() || nom.empty()) {
            throw std::runtime_error("Erreur : Nom du joueur invalide ou vide.");
        }
        //std::cout << "nom : "<< nom << "\n";

        int typeInt, couleurInt;
        inFile >> typeInt >> couleurInt;
        if (inFile.fail()) {
            throw std::runtime_error("Erreur : Type ou couleur du joueur invalide.");
        }
        type = static_cast<TypeJoueur>(typeInt);
        couleur = static_cast<Couleur>(couleurInt);
        //std::cout << "type : " << typeInt << " couleur : " << couleurInt << "\n";

        deck.load(inFile);
        
        selectionnee = nullptr;
        
        while (true) {
            std::string line;
            std::getline(inFile, line);  // Lire la ligne entière
            if (line.empty()) continue;  // Ignorer les lignes vides
            if (line == "END_J") break;  // Vérifier si on atteint "END_J"
        }
        
    } catch (const std::exception& e) {
        throw std::runtime_error("Erreur lors du chargement du joueur : " + std::string(e.what()));
    }
}



/*
void Joueur::load(std::ifstream& inFile, const Plateau& plateau) {
    if (!inFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour le chargement.");
    }

    int typeInt, couleurInt;
    std::string nomstr;
    inFile >> nomstr >> typeInt >> couleurInt;
    if (inFile.fail()) {
        throw std::runtime_error("Erreur : Type ou couleur du joueur invalide.");
    }
    nom = static_cast<std::string>(nomstr);
    type = static_cast<TypeJoueur>(typeInt);
    couleur = static_cast<Couleur>(couleurInt);
    std::cout << "Nom : " << nom << ", Type : " << typeInt << ", Couleur : " << couleurInt << "\n";

    deck.load(inFile);

    int selectedType;
    inFile >> selectedType;
    if (selectedType != -1) {
        selectionnee = deck.prendrePiece(static_cast<TypePiece>(selectedType));
    } else {
        selectionnee = nullptr;
    }
    std::cout << "type selectionne : " << selectedType << "\n";
    
    std::string endMarker;
    inFile >> endMarker;
    if (endMarker != "END_J") {
        throw std::runtime_error("Erreur : Fin de section END_J attendue.");
    }
    
}
*/