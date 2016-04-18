//
// Created by Gannon Faul on 3/31/16.
//

#include "Agent.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() { }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> board;
        std::default_random_engine gen;
        if (__agentEnergy > AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD) {
            for (int  i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC) {
                    board.push_back(i);
                }
            }
        }
        if (board.size() == 0) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::ADVANTAGE) {
                    board.push_back(i);
                }
            }
        }
        if (board.size() == 0) {
            for (int  i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::FOOD) {
                    board.push_back(i);
                }
            }
        }
        if (board.size() == 0) {
            for (int  i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::EMPTY) {
                    board.push_back(i);
                }
            }
        }

        if (board.size() != 0) {
            int next = board[0];
            if(board.size() > 1) {
                next = board[gen() % board.size()];
            }
            ActionType ac;
            if (next == 0) {
                ac = NW;
            } else if (next == 1) {
                ac = N;
            } else if (next == 2) {
                ac = NE;
            } else if (next == 3) {
                ac = W;
            } else if (next == 4) {
                ac = STAY;
            } else if (next == 5) {
                ac = E;
            } else if (next == 6) {
                ac = SW;
            } else if (next == 7) {
                ac = S;
            } else if (next == 8) {
                ac = SE;
            } else {
                ac = STAY;
            }
            return ac;
        }
        return STAY;
    }
}
