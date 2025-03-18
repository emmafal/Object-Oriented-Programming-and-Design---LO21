#pragma once

#include "Partie.h"
#include "Interface.h"

class Controleur {
private:
	Partie partie;
	Interface& interface;
public:
	Controleur(Interface& inter): interface(inter), partie(inter.configurerPartie()) {}
	const Partie& getPartie() const { return partie; }
	void demarrerPartie();
};