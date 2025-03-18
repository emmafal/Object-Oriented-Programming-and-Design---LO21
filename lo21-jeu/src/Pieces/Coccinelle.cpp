#include "Coccinelle.h"
#include <functional>

std::set<Deplacement> Coccinelle::getDeplacements(Position origine, const Plateau& p) const
{
    if (!p.peutBouger(origine)) return std::set<Deplacement>();
    
    std::set<Deplacement> moves;
    const auto& cases = p.getCases();
    std::set<Position> visited;  // Ensemble pour suivre les positions déjà visitées

    
    // Fonction récursive interne
    std::function<void(const Position&, int, std::vector<Position>)> explore = [&](const Position& current, int depth, std::vector<Position> path) {
        if (depth == 3) {
            if ((cases.find(current) == cases.end() || !cases.at(current).estOccupee()) &&
                !path.empty() &&
                (cases.find(path[0]) != cases.end() && cases.at(path[0]).estOccupee())) {
                moves.insert(Deplacement(origine,current));
            }
            return;
        }
        
        visited.insert(current);
        path.push_back(current);
        
        std::vector<Position> adjacents = cases.at(current).getVoisins();
        for (const Position& neighbor : adjacents) {
            if (visited.find(neighbor) == visited.end()) {
                bool isValid = false;
                if (depth < 2) {
                    // Les deux premiers mouvements doivent être sur des cases occupées
                    isValid = (cases.find(neighbor) != cases.end() && cases.at(neighbor).estOccupee());
                } else if (depth == 2) {
                    // Le dernier mouvement doit être sur une case vide
                    isValid = (cases.find(neighbor) == cases.end() || !cases.at(neighbor).estOccupee());
                }
                
                if (isValid) {
                    explore(neighbor, depth + 1, path);
                }
            }
        }
        visited.erase(current);
    };
    
    // Lancer la recherche depuis la position actuelle
    explore(origine, 0, {});
    return moves;
}
