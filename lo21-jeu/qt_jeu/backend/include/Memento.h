#pragma once

#include <stack>

#include "Joueur.h"
#include "Plateau.h"
#include "TypeFin.h"
#include "Couleur.h"


class Interface;
class Partie;

class Memento {
private:
    Plateau plateau;
    Joueur joueur1;
    Joueur joueur2;
    size_t nbTours;
    Couleur tour;
    
    TypeFin fin;

    size_t nbRetoursArriere;
    std::stack<const Mouvement*> historiqueMouvements;

public:
    // Constructeur avec initialisation explicite
    Memento(const Partie& p);
    void restaurer(Partie& partie) const;

    // Getters pour récupérer l'état sauvegardé
    const Joueur& getJoueur1() const { return joueur1; }
    const Joueur& getJoueur2() const { return joueur2; }
    size_t getNbTours() const { return nbTours; }
    Couleur getTour() const { return tour; }
};

