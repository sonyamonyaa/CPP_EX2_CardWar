#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"
#include "card.hpp"
#include "game.hpp"

using namespace std;

using namespace ariel;

int ariel::Game::MakeMove(unsigned int turn, string &curr_log)
{
    ariel::Card card1 = this->p1.takeOutCard(this->cardStack, turn);
    ariel::Card card2 = this->p2.takeOutCard(this->cardStack, turn);
    curr_log += "p1:" + this->p1.moveDesc(card1) + "\tp2:" + this->p2.moveDesc(card2);
    int res = card1.compare(card2);
    return res;
}

void ariel::Game::playTurn()
{
    int turn = this->getCurrTurn();
    int move = 0;
    int win_deck = 0;
    string curr_log = "Turn " + to_string(turn + 1) + ": \n";
    // each player takes out a card
    int res = MakeMove((unsigned int)turn, curr_log);
    move++;
    while (res == Moves::draw && turn + this->getMoves() < MAX_MOVE)
    {
        curr_log += "Draw \n";
        win_deck += 2;
        res = MakeMove((unsigned int)move + 1, curr_log);
        this->setDrawCount();
    }
    if (res == Moves::win)
    { // p1 wins
        win_deck += 2;
        curr_log += "\np1:" + this->p1.getName() + " wins in " + to_string(move) + " moves\n";
        this->p1.takeCards(win_deck);
        this->setWinCount(); // win count is for p1. p2 win count is win - draw counts
    }
    else if (res == Moves::lose)
    { // p2 wins
        win_deck += 2;
        curr_log += "\np2:" + this->p2.getName() + " wins in " + to_string(move) + " moves\n";
        this->p2.takeCards(win_deck);
    }
    else // game ended draw
    {
        int half = (int)win_deck / 2;
        this->p1.takeCards(half);
        this->p2.takeCards(half);
    }
    this->addMoves(move);
    this->setTurn();

    this->setLog(curr_log);
    // printLastTurn();
}

void ariel::Game::playAll()
{
    while (this->getMoves() < 26)
        playTurn();
}

void ariel::Game::printLastTurn() { cout << "LAST TURN \t" + this->getLastTurn() << endl; }
void ariel::Game::printWiner()
{
    // TO DO: throw if game not finished
    string winner = "The winner is ";
    if (this->p1.cardesTaken() > this->p2.cardesTaken())
    {
        winner += "p1: " + this->p2.getName();
    }
    else if (this->p1.cardesTaken() < this->p2.cardesTaken())
    {
        winner += "p2: " + this->p2.getName();
    }
    else
    {                          // a tie
        winner = "It's a tie"; // throw error?
    }
    cout << winner << endl;
}
void ariel::Game::printLog() { cout << "GAME LOG:\n" + this->getLog() << endl; }

string ariel::Game::getStats()
{
    // TO DO: throw if game not finished
    string stats = "STATS\n";

    int totalTurns = this->getCurrTurn(); // after the last turn is set, it's saved as curr_turn
    int draws = this->getDrawCount();
    int p1_wins = this->getWinCount();
    int p2_wins = totalTurns - draws - p1_wins;
    // counts
    stats += "COUNTS\n";
    stats += "p1 wins:p2 wins:draws\n";
    stats += to_string(p1_wins) + "\t" + to_string(p2_wins) + "\t" + to_string(draws);

    // win rates
    stats += "\nWIN RATE:\n";
    stats += "p1:p2\n";
    stats += to_string((float)(p1_wins / totalTurns)) + "\t" + to_string((float)(p2_wins / totalTurns));

    // draw rates
    stats += "\nDRAW RATE: ";
    stats += to_string((float)(draws / totalTurns));

    return stats;
}

void ariel::Game::printStats() { cout << this->getStats() << endl; }
