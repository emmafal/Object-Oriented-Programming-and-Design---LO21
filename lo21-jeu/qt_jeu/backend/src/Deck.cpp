#include "Deck.h"
#include "PieceFactory.h"

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
