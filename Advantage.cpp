//
// Created by Gannon Faul on 3/31/16.
//

#include "Advantage.h"
#include <sstream>

namespace Gaming {

    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) { }

    Advantage::~Advantage() { }

    void Advantage::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Advantage::ADVANTAGE_ID;
        ss << __id;
        std::string id = std::to_string(__id);
        std::getline(ss, id);
        for (int i = 0; i < id.length(); i++) {
            os << id[i];
        }
    }

    double Advantage::getCapacity() const {
        double cap = __capacity * Advantage::ADVANTAGE_MULT_FACTOR;
        return cap;
    }

    double Advantage::consume() {
        double eat = getCapacity();
        __capacity = -1;
        finish();
        return eat;
    }

}