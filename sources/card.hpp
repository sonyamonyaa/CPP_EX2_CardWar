#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

const int STACK_SIZE = 52;

using namespace std;
// enums for easier printing
enum Suits
{
    Hearts,
    Spades,
    Diamonds,
    Clubs
};
enum Ranks
{
    Ace = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    Jack,
    Queen,
    King
};
enum Moves
{
    lose = -1,
    draw,
    win
};

namespace ariel
{
    class Card
    {

    private:
        Suits _suit;
        Ranks _rank;

    public:
        // ~Card() {}
        Card(Suits suit, Ranks rank) : _suit(suit), _rank(rank) {}

        int getSuit() const{ return _suit; }
        int getRank() const{ return _rank; }
        int compare(Card card);
        string CardToStr();
        static vector<Card> getNewStack();
    };
}