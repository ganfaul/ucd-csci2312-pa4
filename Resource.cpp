//
// Created by Gannon Faul on 3/31/16.
//

#include "Resource.h"

namespace Gaming {

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p){
        __capacity = capacity;
    }

    Resource::~Resource() { }

    double Resource::consume() {
        double resource = __capacity;
        __capacity = -1;
        finish();
        return resource;
    }

    void Resource::age() {
        __capacity = Resource::RESOURCE_SPOIL_FACTOR;
        if (__capacity <= 0) {
            finish();
        }
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return ActionType::STAY;
    }

    // note: these won't be called while resources don't move
    Piece &Resource::operator*(Piece &other) { }

    Piece &Resource::interact(Agent *) {
        return *this;
    }

    Piece &Resource::interact(Resource *) {
        return *this;
    } // note: no interaction between resources
}