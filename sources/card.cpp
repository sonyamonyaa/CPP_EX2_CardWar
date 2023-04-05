#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

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

int ariel::Card::compare(Card card)
{
    int thisRank = this->getRank();
    int otherRank = card.getRank();

    if (thisRank == otherRank)
    {
        return Moves::draw;
    }

    bool loss = ((otherRank == Ranks::Ace)                              // Ace wins all
                 || (thisRank == Ranks::Ace && otherRank == Ranks::two) // except 2
                 || (thisRank < otherRank && thisRank != Ranks::Ace));  // rest of ranks are by who's bigger

    if (loss)
        return Moves::lose;
    else
        return Moves::win;
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
            cardStack.push_back(Card((Suits)s, (Ranks)r));
        }
    }

    return cardStack;
}

void shuffleStack(vector<Card> cardStack)
{
    // reference - https://cplusplus.com/reference/algorithm/random_shuffle//
    srand(time(0)); //  Initialize seed randomly
    random_shuffle(cardStack.begin(), cardStack.end());
}

vector<Card> ariel::Card::getNewStack()
{
    vector<Card> cardStack = createStack();
    shuffleStack(cardStack);
    return cardStack;
}