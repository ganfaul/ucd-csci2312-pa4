//
// Created by Gannon Faul on 3/31/16.
//

#include "DefaultAgentStrategy.h"

namespace Gaming {

    DefaultAgentStrategy::DefaultAgentStrategy() { }

    DefaultAgentStrategy::~DefaultAgentStrategy() { }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> board;
        std::default_random_engine gen;
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == PieceType::ADVANTAGE) {
                board.push_back(i);
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
        if (board.size() == 0) {
            for (int  i = 0; i < 9; i++) {
                if (s.array[i] == PieceType::SIMPLE) {
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