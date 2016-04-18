//
// Created by Gannon Faul on 3/31/16.
//

#include "Agent.h"
#include "Food.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {
        __energy = energy;
    }

    Agent::~Agent() { }

    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {
        Piece *p = &other;
        Resource *r = dynamic_cast<Resource*>(p);
        if (r) {
            interact(r);
        }
        Agent *a = dynamic_cast<Agent*>(p);
        if (a) {
            interact(a);
        }
        if (!isFinished()) {
            Position pos;
            pos = other.getPosition();
            Position prev;
            prev = getPosition();
            setPosition(pos);
            other.setPosition(prev);
        }
        return *this;
    }

    Piece &Agent::interact(Agent *agent) {
        if (__energy != agent->__energy) {
            if (__energy <= agent->__energy) {
                agent->__energy -= __energy;
                finish();
            } else {
                __energy -= agent->__energy;
                agent->finish();
            }
        } else {
            finish();
            agent->finish();
        }
    }

    Piece &Agent::interact(Resource *agent) {
        __energy += agent->consume();
        return *this;
    }
}