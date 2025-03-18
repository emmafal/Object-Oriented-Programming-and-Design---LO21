#pragma once
#include <string>
#include <stack>

#include "Plateau.h"
#include "Joueur.h"
#include "Couleur.h"
#include "Mouvement.h"
#include "TypeFin.h"
#include "Memento.h"
#include "IA.h"

class Interface;
class IA;

class Partie {
private:
    Plateau plateau;

    Joueur joueur1;
    Joueur joueur2;

    Couleur tour;

	size_t nbTours;

    TypeFin fin;

    size_t nbRetoursArriere;

	Interface& interface;

    IA& ia;

    friend class Memento;
public:
    std::stack<Memento> sauvegardes;
    std::stack<const Mouvement*> historiqueMouvements;
	Partie(Joueur joueur1, Joueur joueur2, Interface& interface, size_t nbRetoursArriere, IA& ia): tour(Couleur::Blanc), joueur1(joueur1), joueur2(joueur2), nbTours(0), fin(TypeFin::Aucune), interface(interface), nbRetoursArriere(nbRetoursArriere), ia(ia) {}
  //  Partie(Joueur joueur1, Joueur joueur2, size_t nbRetoursArriere, IA& ia);
    ~Partie() = default;
    Partie(const Partie&) = delete;
    const Partie& operator=(const Partie&) = delete;
    Joueur& getJoueurActuel();
    Joueur& getJoueur1();
    Joueur& getJoueur2();
    const Plateau& getPlateau() const { return plateau; }
    const IA& getIA() const { return ia; }
    bool actionPossible(const Joueur& joueur) const;

    const size_t getNbTours() const { return nbTours; }
    Couleur getTour() const { return tour; }
    TypeFin getFin() const { return fin; }

	void changerCote();

    void updateFin();

	void lancer();
    void finir();

	void jouerTour(const Mouvement* mouvement);
    void passerTour();
    void retourArriere();

    void sauvegarderPartie();
    void chargerPartie();

    friend std::ostream& operator<<(std::ostream& os, const Partie& p);
    Memento creerMemento() const;
    void restaurerEtat(const Plateau& p, const Joueur& j1, const Joueur& j2, size_t nbt, Couleur t, TypeFin f, std::stack<const Mouvement*> historique);
    friend std::ostream& operator<<(std::ostream& os, const Partie& p);
};
