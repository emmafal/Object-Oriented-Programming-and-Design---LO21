#include "Memento.h"
#include "Partie.h"

Memento::Memento(const Partie& p)
    : plateau(p.plateau), joueur1(p.joueur1), joueur2(p.joueur2), nbTours(p.nbTours), tour(p.tour), fin(p.fin), nbRetoursArriere(p.nbRetoursArriere), historiqueMouvements(p.historiqueMouvements) {}


void Memento::restaurer(Partie& partie) const {
    partie.restaurerEtat(plateau, joueur1, joueur2, nbTours, tour, fin, historiqueMouvements);
}
