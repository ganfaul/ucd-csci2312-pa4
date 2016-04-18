//
// Created by Gannon Faul on 3/31/16.
//

#include "Strategic.h"
#include <sstream>
#include <iomanip>

namespace Gaming {

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p,
                         double energy, Strategy *s
    ) : Agent(g, p, energy){
        __strategy = s;
    }

    Strategic::~Strategic() {
        delete __strategy;
    }

    void Strategic::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Strategic::STRATEGIC_ID;
        ss << __id;
        std::string id = std::to_string(__id);
        std::getline(ss, id);
        for (int i = 0; i < id.length(); i++) {
            os << id[i];
        }
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        return (*__strategy)(s);
    }
}
