#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

#define STACK_SIZE 52

using namespace std;
//enums for easier printing
enum Suits {Hearts, Spades, Diamonds, Clubs};
enum Ranks {Ace=1, two=2, three=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10, Jack=11, Queen=12, King=13};
namespace ariel
{
    class Card {

        private:
            Suits _suit;
            Ranks _rank;

        public:
            Card(){}
            ~Card(){}
            Card(int suit, int rank): _suit((Suits)suit), _rank((Ranks)rank){}
            
            int getSuit() {return _suit;}
            int getRank() {return _rank;}
            string CardToStr();
            vector<Card> getNewStack();
    };
}