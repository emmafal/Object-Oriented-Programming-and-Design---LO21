#include <iostream>

#include "Partie.h"
#include "Partie.h"
#include "Direction.h"
#include "ReineAbeille.h"
#include "Moustique.h"
#include "Mouvement.h"
#include "InterfaceConsole.h"
#include "PieceFactory.h"
#include "Deck.h"
#include "Controleur.h"

int main() {
	InterfaceConsole inter;
	Controleur controleur = Controleur(inter);
	controleur.demarrerPartie();
	return 0;
}