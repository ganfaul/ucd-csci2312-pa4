//
// Created by Gannon Faul on 3/31/16.
//

#include "Food.h"
#include <sstream>

namespace Gaming {

    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity){ }

    Food::~Food() { }

    void Food::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Food::FOOD_ID;
        ss << __id;
        std::string id = std::to_string(__id);
        std::getline(ss, id);
        for (int i = 0; i < id.length(); i++) {
            os << id[i];
        }
    }
}