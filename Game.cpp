//
// Created by Gannon Faul on 3/31/16.
//

#include <sstream>
#include <iomanip>
#include <set>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned int Game::MIN_WIDTH = 3;
    const unsigned int Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

    // NOT DONE
    void Game::populate() {
        int  dimensions = __width * __height;
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, dimensions);

        __numInitAgents = dimensions / Game::NUM_INIT_AGENT_FACTOR;
        __numInitResources = dimensions / Game::NUM_INIT_RESOURCE_FACTOR;
        unsigned int ads = __numInitResources / 4;
        unsigned int food = __numInitResources - ads;
        unsigned int strat = __numInitAgents / 2;
        unsigned int simple = __numInitAgents - strat;

        int x, y;
        while (strat != 0) {
            int i = d(gen);
            if (i != dimensions) {
                if (!(__grid[i])) {
                    x = i / __width;
                    y = i % __width;
                    Position pos(x, y);
                    __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                    strat--;
                }
            }
        }
        while (simple != 0) {
            int i = d(gen);
            if (i != dimensions) {
                if (!(__grid[i])) {
                    x = i / __width;
                    y = i % __width;
                    Position pos(x, y);
                    __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                    simple--;
                }
            }
        }
        while (food != 0) {
            int i = d(gen);
            if (i != dimensions) {
                if (!(__grid[i])) {
                    x = i / __width;
                    y = i % __width;
                    Position pos(x, y);
                    __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                    food--;
                }
            }
        }
        while (ads != 0) {
            int i = d(gen);
            if (i != dimensions) {
                if (!(__grid[i])) {
                    x = i / __width;
                    y = i % __width;
                    Position pos(x, y);
                    __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                    ads--;
                }
            }
        }
    }

    // NOT DONE
    Game::Game(){
        __width = Game::MIN_WIDTH;
        __height = Game::MIN_HEIGHT;
        __round = 0;
        __verbose = false;
        __status = NOT_STARTED;
        for (int i = 0; i < __width * __height; i++) {
            __grid.push_back(nullptr);
        }

    }

    // NOT DONE
    Game::Game(unsigned width, unsigned height, bool manual) {
        if (width < MIN_WIDTH || height < MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }
        __width = width;
        __height = height;
        __round = 0;
        __verbose = false;
        __status = NOT_STARTED;
        for (int i = 0; i < __width * __height; i++) {
            __grid.push_back(nullptr);
        }
        if(!manual) {
            populate();
        }

    } // note: manual population by default

    Game::~Game() {
        for (auto it = __grid.begin(); it != __grid.end(); it++) {
            if(*it) {
               delete *it;
            }
        }
    }

    // Getters
    unsigned int Game::getNumPieces() const {
        return (getNumAgents() + getNumResources());
    }


    unsigned int Game::getNumAgents() const {
        return (getNumSimple() + getNumStrategic());
    }


    unsigned int Game::getNumSimple() const {
        unsigned int numSimple = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numSimple++;
        }
        return numSimple;
    }


    unsigned int Game::getNumStrategic() const {
        unsigned int numStrat = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Strategic *strat = dynamic_cast<Strategic*>(*it);
            if (strat) numStrat ++;
        }
        return numStrat;
    }


    unsigned int Game::getNumResources() const {
        unsigned int numResources = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) numResources++;
        }
        return numResources;
    }


    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
        unsigned int pos = y + __width * x;
        if(!(__grid[pos])) {
            throw PositionEmptyEx(x, y);
        }
        return __grid[pos];
    }




    // Grid Population Methods

    void Game::addSimple(const Position &position) {
        unsigned int pos = position.y + __width * position.x;
        if (pos > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if(__grid[pos]) {
            throw PositionNonemptyEx(position.x, position.y);
        }
        __grid[pos] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }


    void Game::addSimple(const Position &position, double energy) {
        unsigned int pos = position.y + __width * position.x;
        if (pos > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if(__grid[pos]) {
            throw PositionNonemptyEx(position.x, position.y);
        }
        __grid[pos] = new Simple(*this, position, energy);
    } // used for testing only


    void Game::addSimple(unsigned x, unsigned y) {
        if (x * __width + y > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if(__grid[x * __width + y]) {
            throw PositionNonemptyEx(x, y);
        }
        Position pos(x, y);
        addSimple(pos);
    }


    void Game::addSimple(unsigned x, unsigned y, double energy) {
        if (x * __width + y > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if(__grid[x * __width + y]) {
            throw PositionNonemptyEx(x, y);
        }
        Position pos(x, y);
        addSimple(pos, energy);
    }


    void Game::addStrategic(const Position &position, Strategy *s) {
        unsigned int pos = position.y + __width * position.x;
        if (pos > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if(__grid[pos]) {
            throw PositionNonemptyEx(position.x, position.y);
        }
        __grid[pos] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }


    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        if (x * __width + y > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if(__grid[x * __width + y]) {
            throw PositionNonemptyEx(x, y);
        }
        Position pos(x, y);
        addStrategic(pos, s);
    }


    void Game::addFood(const Position &position) {
        unsigned int pos = position.y + __width * position.x;
        if (pos > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if(__grid[pos]) {
            throw PositionNonemptyEx(position.x, position.y);
        }
        __grid[pos] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }


    void Game::addFood(unsigned x, unsigned y) {
        if (x * __width + y > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if(__grid[x * __width + y]) {
            throw PositionNonemptyEx(x, y);
        }
        Position pos(x, y);
        addFood(pos);
    }


    void Game::addAdvantage(const Position &position) {
        unsigned int pos = position.y + __width * position.x;
        if (pos > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if(__grid[pos]) {
            throw PositionNonemptyEx(position.x, position.y);
        }
        __grid[pos] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }


    void Game::addAdvantage(unsigned x, unsigned y) {
        if (x * __width + y > __grid.size()) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if(__grid[x * __width + y]) {
            throw PositionNonemptyEx(x, y);
        }
        Position pos(x, y);
        addAdvantage(pos);
    }

    // NOT DONE
    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings board;
        for (int i = 0; i < 9; i++) {
            board.array[i] = EMPTY;
        }
        for (int i = 1; i >= -1; i--) {
            for (int j = 1; j >= -1; j--) {
                if (pos.x - i >= 0 && pos.x - i < __height) {
                    if (pos.y - j >= 0 && pos.y -j < __width) {
                        int spot = pos.y - j + (pos.x - i) * __width;
                        if (__grid[spot]) {
                            board.array[1 - j + (1 - i) * 3] = __grid[spot]->getType();
                        }
                    } else {
                        board.array[1 - j + (1 - i) * 3] = INACCESSIBLE;
                    }
                } else {
                    board.array[1 - j + (1 - i) * 3] = INACCESSIBLE;
                }
            }
        }
        board.array[4] = SELF;
        return board;
    }



    // Gameplay Methods

    // NOT DONE
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        int x = to.x - from.x;
        int y  = to.y - from.y;
        if (((x + 1) * 3 + (y + 1)) == 0) {
            return NW;
        } else if (((x + 1) * 3 + (y + 1)) == 1) {
            return N;
        } else if (((x + 1) * 3 + (y + 1)) == 2) {
            return NE;
        } else if (((x + 1) * 3 + (y + 1)) == 3) {
            return W;
        } else if (((x + 1) * 3 + (y + 1)) == 4) {
            return STAY;
        } else if (((x + 1) * 3 + (y + 1)) == 5) {
            return E;
        } else if (((x + 1) * 3 + (y + 1)) == 6) {
            return SW;
        } else if (((x + 1) * 3 + (y + 1)) == 7) {
            return S;
        } else if (((x + 1) * 3 + (y + 1)) == 8) {
            return SE;
        } else {
            return STAY;
        }
    } // note: STAY by default

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        int x = pos.x;
        int y = pos.y;

        if (ac == N) {
            x--;
        } else if (ac == NE) {
            x--;
            y++;
        } else if (ac == E) {
            y++;
        } else if (ac == SE) {
            x++;
            y++;
        } else if (ac == S) {
            x++;
        } else if (ac == SW) {
            x++;
            y--;
        } else if (ac == W) {
            y--;
        } else if (ac == NW) {
            x--;
            y--;
        }

        if (x < __height && y < __width) {
            return true;
        } else {
            return false;
        }
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
        unsigned int x = pos.x;
        unsigned int y = pos.y;
        if (isLegal(ac, pos)) {
            if (ac == N) {
                x--;
            } else if (ac == NE) {
                x--;
                y++;
            } else if (ac == E) {
                y++;
            } else if (ac == SE) {
                x++;
                y++;
            } else if (ac == S) {
                x++;
            } else if (ac == SW) {
                x++;
                y--;
            } else if (ac == W) {
                y--;
            } else if (ac == NW) {
                x--;
                y--;
            }
        }
        Position p(x, y);
        return p;
    } // note: assumes legal, use with isLegal()

    void Game::round() {
        std::set<Piece*> set;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            if (*it) {
                set.insert(set.end(), *it);
                //pieces.insert(*it);
                (*it)->setTurned(0);
            }
        }
        for (auto it = set.begin(); it != set.end(); ++it) {
            if (!(*it)->getTurned()) {
                (*it)->setTurned(1);
                (*it)->age();
                Position current = (*it)->getPosition();
                ActionType ac = (*it)->takeTurn(getSurroundings((*it)->getPosition()));
                Position target = move(current, ac);
                if (current.x != target.x || current.y != target.y) {
                    Piece *piece = __grid[target.x * __width + target.y];
                    if (piece) {
                        **it * *piece;
                        if ((*it)->getPosition().x != current.x || (*it)->getPosition().y != current.y) {
                            __grid[target.x * __width + target.y] = (*it);
                            __grid[current.x * __width + current.y] = piece;
                        }
                    } else {
                        (*it)->setPosition(target);
                        __grid[target.x * __width + target.y] = (*it);
                        __grid[current.x * __width + current.y] = nullptr;
                    }
                }
            }
        }

        for (int i = 0; i < __grid.size(); ++i) {
            if (__grid[i]){
                if(!(__grid[i]->isViable())) {
                    delete __grid[i];
                    __grid[i] = nullptr;
                }
            }
        }
        if (getNumResources() == 0) {
            __status = Game::Status::OVER;
        }
        __round++;
    }   // play a single round

    // NOT DONE
    void Game::play(bool verbose){
        __status = Game::Status::PLAYING;
        __verbose = verbose;
        while (__status != OVER) {
            round();
            if (verbose) {
                std::cout << *this;
            }
        }
        if (!verbose) {
            std::cout << *this;
        }
    }    // play game until over

    // const Agent &Game::winner() // what if no winner or multiple winners?


    // Printing

    // Print as follows the state of the game after the last round:
    //
    // Round 1:
    // [F0   ][     ][T1   ]
    // [W2   ][     ][F3   ]
    // [     ][S4   ][     ]
    // Status: Playing...
    //
    // Round 5:
    // [     ][     ][     ]
    // [     ][T1   ][     ]
    // [     ][     ][     ]
    // Status: Over!
    //

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Round " << game.__round << std::endl;
        int i = 0;
        for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it) {
            if (*it) {
                std::stringstream ss;
                ss << "[" << **it;
                std::string id;
                std::getline(ss, id);
                os << id << "]";
            } else {
                os << "[" << std::setw(6) << "]";
            }
            i++;
            if (i % game.__width == 0) {
                os << std::endl;
            }
        }

        os << "Status: ";
        if (game.getStatus() == Game::Status::OVER) {
            os << "Over!";
        } else if (game.getStatus() == Game::Status::PLAYING){
            os << "Playing...";
        } else {
            os << "Not Started...";
        }
        os << std::endl;

        return os;
    }

}
