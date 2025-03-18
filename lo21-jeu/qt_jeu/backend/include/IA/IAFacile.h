#pragma once

#include "IA.h"

class IAFacile : public IA {
public:
	virtual const Mouvement* choisirMouvement(Joueur& joueurIA, const Plateau& p, bool premierTour) const override;
};