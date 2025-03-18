#pragma once

#include "Mouvement.h"
#include "Joueur.h"
#include "Plateau.h"		// L'IA peut potentiellement avoir besoin du nombre de tours, des pièces que l'autre joueur dispose etc. en plus plateau
#include <memory>

class IA {
public:
	virtual const Mouvement* choisirMouvement(Joueur& joueurIA, const Plateau& p, bool premierTour) const = 0;
};