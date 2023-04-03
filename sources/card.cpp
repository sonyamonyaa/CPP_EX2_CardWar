#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "card.hpp"

using namespace std;

using namespace ariel;

string ariel::Card::CardToStr()
{
    string str = "";
    switch (ariel::Card::getRank())
    {
    case Ranks::Ace:
        str += "Ace";
        break;
    case Ranks::Jack:
        str += "Jack";
        break;
    case Ranks::Queen:
        str += "Queen";
        break;
    case Ranks::King:
        str += "King";
        break;
    default: // ranks 2-10
        str += to_string(ariel::Card::getRank());
        break;
    }
    str += " of ";

    switch (ariel::Card::getSuit())
    {
    case Suits::Hearts:
        str += "Hearts";
        break;
    case Suits::Spades:
        str += "Spades";
        break;
    case Suits::Diamonds:
        str += "Diamonds";
        break;
    case Suits::Clubs:
        str += "Clubs";
        break;

    default:
        break;
    }
    return str;
}

vector<Card> createStack()
{
    vector<Card> cardStack;
    int suits_len = 4;
    int rank_len = 13;

    for (int r = 1; r <= rank_len; r++)
    {
        for (int s = 0; s < suits_len; s++)
        {
            cardStack.push_back(Card(s, r));
        }
    }

    return cardStack;
}

void shuffleStack(vector<Card> cardStack)
{
    // used the code in here - https://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/
    srand(time(0)); //  Initialize seed randomly

    for (int i = 0; i < STACK_SIZE; i++)
    {
        // Random for remaining positions.
        int r = i + (rand() % (STACK_SIZE - i));

        swap(cardStack[i], cardStack[r]);
    }
}

vector<Card> ariel::Card::getNewStack(){
    vector<Card> cardStack = createStack();
    shuffleStack(cardStack);
    return cardStack;
}