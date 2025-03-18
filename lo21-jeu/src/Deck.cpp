#include "Deck.h"
#include "PieceFactory.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

Deck::Deck(std::map<TypePiece, size_t> effectif, Couleur c): effectifPieces(effectif), couleur(c) {}

Deck Deck::deckStandard(Couleur c)
{
	std::map<TypePiece, size_t> effectifs = {
		{TypePiece::ReineAbeille, 1},
		{TypePiece::Araignee, 2},
		{TypePiece::Scarabee, 2},
		{TypePiece::Sauterelle, 3},
		{TypePiece::Fourmis, 3}
	};
	return Deck(effectifs, c);
}

void Deck::ajouterExtension(TypePiece piece, size_t effectif)
{
	effectifPieces.insert(std::pair(piece, effectif));
}

size_t Deck::getNbPiecesRestantes() const
{
	size_t total = 0;
	for (auto it = effectifPieces.begin(); it != effectifPieces.end(); ++it) total += (*it).second;
	return total;
}

const Piece* Deck::prendrePiece(TypePiece type)
{
	auto it = effectifPieces.find(type);
	if (it != effectifPieces.end() && (*it).second > 0) {
		(*it).second--;
		const Piece * piece = PieceFactory::construire(type, couleur);
		return piece;
	}
	return nullptr;
}

void Deck::reposerPiece(TypePiece type)
{
	auto it = effectifPieces.find(type);
	if (it != effectifPieces.end()) (*it).second++;
}

std::ostream& operator<<(std::ostream& os, const Deck& deck)
{
	size_t i = 1;
	for (auto it = deck.effectifPieces.begin(); it != deck.effectifPieces.end(); ++it, i++) {
		auto paire = *it;
		TypePiece type = (*it).first;
		size_t effectif = (*it).second;
		std::cout << PieceFactory::getNomByType(type) << " : " << effectif << "\n";
	}
	return os;
}

void Deck::save(std::ofstream& outFile) const {
    if (!outFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour la sauvegarde du Deck.");
    }

    // Save the color of the deck
    outFile << static_cast<int>(couleur) << "\n";

    // Save the number of types of pieces
    outFile << effectifPieces.size() << "\n";

    // Save the count of each type of piece
    for (const auto& [type, count] : effectifPieces) {
        outFile << static_cast<int>(type) << " " << count << "\n";
    }
}


void Deck::load(std::ifstream& inFile) {
    if (!inFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour le chargement du Deck.");
    }
    //std::cout << " deck \n";

    // Load the color of the deck
    int couleurInt;
    inFile >> couleurInt;
    couleur = static_cast<Couleur>(couleurInt);
    //std::cout << "couleur : " << couleurInt << "\n";

    // Load the number of types of pieces
    size_t effectifCount;
    inFile >> effectifCount;
    //std::cout << " effectif : " << effectifCount << "\n";

    // Load the count of each type of piece
    effectifPieces.clear();
    for (size_t i = 0; i < effectifCount; ++i) {
        int typeInt;
        size_t count;
        inFile >> typeInt >> count;
        effectifPieces[static_cast<TypePiece>(typeInt)] = count;
        //std::cout << "piece : " << typeInt << "nb : " << count << "\n";
    }
}
