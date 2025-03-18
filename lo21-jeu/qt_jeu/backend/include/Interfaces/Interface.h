#pragma once

#include <vector>

#include "Mouvement.h"
#include "Plateau.h"
#include "Piece.h"
#include "Partie.h"

#include "TypeInterface.h"



class Interface {
private:
public:
	virtual Partie configurerPartie() = 0;
	virtual void afficherPlateau(const Plateau& p) const = 0;
	virtual void choisirDeplacement(Partie& partie, Joueur& joueur) const = 0;
	virtual void choisirAction(Partie& partie, Joueur& joueur) const = 0;
	virtual void lancerPartie(Partie& partie) const = 0;
	virtual void finirPartie(Partie& partie, Joueur& gagnant) const = 0;
};
