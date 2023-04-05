#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"

using namespace std;

using namespace ariel;

string ariel::Player::moveDesc(Card &card){
    string str = this->getName() + " takes out " + card.CardToStr();
    return str;
}
