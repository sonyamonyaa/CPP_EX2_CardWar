#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "card.hpp"

using namespace std;

namespace ariel
{
    class Player
    {

    private:
        string name;
        int stack_size;
        int cards_taken;
        bool playing;
        unsigned int deck; // place in deck
    public:
        Player(const string &n) : name(n), stack_size(0), cards_taken(0), playing(false), deck(0) {}

        string getName() { return name; }
        void setPlaying(bool plays) { playing = plays; }

        void setDeck(unsigned int place)
        {
            deck = place;
        }
        void setStackSize(int size){
            stack_size = size;
        }

        int stacksize() const
        {
            return stack_size;
        }

        int cardesTaken() const
        {
            return cards_taken;
        }

        void takeCards(int cards) { cards_taken += cards; }

        Card takeOutCard(vector<Card> &cardStack, unsigned int turn)
        {
            stack_size-=1;  
            size_t index = turn + deck;
            return cardStack.at(index);
        }
        string moveDesc(Card &card);
    };
}