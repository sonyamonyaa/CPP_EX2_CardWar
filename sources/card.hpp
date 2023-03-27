#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;
//enums for easier printing
enum Suits {Hearts, Spades, Diamonds, Clubs};
enum Ranks {Ace=1, two=2, three=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10, Jack=11, Queen=12, King=13};
namespace ariel
{
    class Card {

        private:
            const Suits _suit;
            const Ranks _rank;
        public:
            Card(Suits suit, Ranks rank): _suit(suit), _rank(rank){}
    };
}