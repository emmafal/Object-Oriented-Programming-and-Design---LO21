#include "Araignee.h"
#include <functional>


bool Araignee::deplacementValide(const Plateau & p, const Deplacement & d) const {
    const std::map<Position, Case>& cases = p.getCases();
    const Case& caseDest = cases.at(d.getDest());
    const Case& caseOrigine = cases.at(d.getOrigine());

    for (const Position& voisin : caseDest.getVoisins()) {
        auto it = cases.find(voisin);
        if (it != cases.end() && (*it).second.estOccupee())
        {
            const Case& caseVoisine = (*it).second;
            if (caseVoisine.getPos() != caseOrigine.getPos()) return true;
            if (caseVoisine.getNbPieces() - 1 > 0) return true;
        }
    }
    return false;
}

std::set<Deplacement> Araignee::getDeplacements(Position origine, const Plateau& p) const {

    if (!p.peutBouger(origine)) return std::set<Deplacement>();

    std::set<Deplacement> moves;
    std::vector<Direction> dirs = Direction::getDirs();
    std::map<Position, Case> cases = p.getCases();

    std::set<Position>  voisins;
    std::set<Position>  voisins_2;


    int i = 0;
    for (auto it = dirs.begin(); it != dirs.end(); ++it, i++)
    {
        Position gauche = origine + dirs[(i - 1 + dirs.size()) % dirs.size()];      // La gauche du premier élément du vecteur est le dernier élément du vecteur, il faut donc qu'il soit circulaire
        Position droite = origine + dirs[(i + 1) % dirs.size()];
        Position dest = origine + *it;
        bool pos_valide = !(cases.at(gauche).estOccupee() and cases.at(droite).estOccupee()) and !cases.at(dest).estOccupee();

        Deplacement d(origine, dest);
        if (pos_valide && (cases.at(gauche).estOccupee() || cases.at(droite).estOccupee()) && deplacementValide(p, d)) voisins.insert(dest);
    }


    for (const Position& voisin : voisins) {
        i = 0;
        for (auto it2 = dirs.begin(); it2 != dirs.end(); ++it2, i++)
        {
            Position gauche2 = voisin + dirs[(i - 1 + dirs.size()) % dirs.size()];
            Position droite2 = voisin + dirs[(i + 1) % dirs.size()];
            Position dest2 = voisin + *it2;
            if (cases.find(dest2) != cases.end()) {
                bool pos_valide2 = false;
                Deplacement d2(voisin, dest2);
                if (cases.find(gauche2) == cases.end() && cases.find(droite2) != cases.end()) pos_valide2 = (cases.at(droite2).estOccupee() && droite2 != origine) && !cases.at(dest2).estOccupee();
                else if (cases.find(droite2) == cases.end() && cases.find(gauche2) != cases.end()) pos_valide2 = (cases.at(gauche2).estOccupee() && gauche2 != origine) && !cases.at(dest2).estOccupee();
                else pos_valide2 = (!(cases.at(gauche2).estOccupee() and cases.at(droite2).estOccupee()) || (gauche2 == origine || droite2 == origine)) and !cases.at(dest2).estOccupee();

                if (pos_valide2 && voisins.find(dest2) == voisins.end() && deplacementValide(p, d2)) voisins_2.insert(dest2);
            }
        }

    }

    for (const Position& voisin2 : voisins_2) {
        i = 0;
        for (auto it3 = dirs.begin(); it3 != dirs.end(); ++it3, i++)
        {
            Position gauche3 = voisin2 + dirs[(i - 1 + dirs.size()) % dirs.size()];
            Position droite3 = voisin2 + dirs[(i + 1) % dirs.size()];
            Position dest3 = voisin2 + *it3;
            if (cases.find(dest3) != cases.end()) {
                bool pos_valide3 = false;
                Deplacement d3(voisin2, dest3);
                if (cases.find(gauche3) == cases.end() && cases.find(droite3) != cases.end()) pos_valide3 = cases.at(droite3).estOccupee() && droite3 != origine && !cases.at(dest3).estOccupee();
                else if (cases.find(droite3) == cases.end() && cases.find(gauche3) != cases.end()) pos_valide3 = cases.at(gauche3).estOccupee() && gauche3 != origine && !cases.at(dest3).estOccupee();
                else if ((droite3 == origine && !cases.at(gauche3).estOccupee()) || (gauche3 == origine && !cases.at(droite3).estOccupee())) {
                    pos_valide3 = false;
                }
                else pos_valide3 = (!(cases.at(gauche3).estOccupee() and cases.at(droite3).estOccupee()) || (gauche3 == origine || droite3 == origine)) and !cases.at(dest3).estOccupee();

                if (pos_valide3 && voisins_2.find(dest3) == voisins_2.end() && voisins.find(dest3) == voisins.end() && deplacementValide(p, d3)) moves.insert(Deplacement(origine, dest3));
            }
        }
    }
    return moves;
}
