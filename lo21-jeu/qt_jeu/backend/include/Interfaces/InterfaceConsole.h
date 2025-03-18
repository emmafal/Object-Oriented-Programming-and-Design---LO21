#pragma once

#include "Interface.h"
#include "Deck.h"


class InterfaceConsole : public Interface {
private:
public:
	Partie configurerPartie() override;
	void afficherPlateau(const Plateau& p) const override;
	void choisirDeplacement(Partie& partie, Joueur& joueur) const override;
	void choisirPlacement(Partie& partie, Joueur& joueur) const;
	void choisirAction(Partie& partie, Joueur& joueur) const override;
	void lancerPartie(Partie& partie) const override;
	void finirPartie(Partie& partie, Joueur& gagnant) const override;
};