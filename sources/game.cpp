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

void throwFinished()
{
    throw string{
        "Game finished"};
}

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
    if (this->isFinished())
        throwFinished();
    // check same player
    if (&this->p1 == &this->p2)
        throw string{"same player"};

    int turn = this->getCurrTurn();
    int move = 0;
    int win_deck = 0;
    string curr_log = "Turn " + to_string(turn + 1) + ": \n";
    // each player takes out a card
    int res = MakeMove((unsigned int)turn, curr_log);
    move++;
    while (res == Moves::draw && (move + this->getMoves()) < MAX_MOVE)
    {
        curr_log += "\nDraw, both players put down hidden card\n";
        // hide next card
        this->p1.updateStack();
        this->p2.updateStack();
        this->setDrawCount();
        move++;                                    // one card hidden
        if ((move + this->getMoves()) >= MAX_MOVE) // taking one hidden card could end the game
            break;
        
        // take out the next card
        if ((move + 1 + this->getMoves()) < MAX_MOVE) // the hidden card might be the last
        {
            move++;
            res = MakeMove((unsigned int)move, curr_log);
        }
    }

    win_deck += (2 * move); // each move adds 2 cards

    if (res == Moves::win)
    { // p1 wins

        curr_log += "\np1:" + this->p1.getName() + " wins in " + to_string(move) + " moves\n";
        this->p1.takeCards(win_deck);
        this->setWinCount(); // win count is for p1. p2 win count is win - draw counts
    }
    else if (res == Moves::lose)
    { // p2 wins
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
}

void ariel::Game::playAll()
{
    while (!this->isFinished())
        playTurn();
}

void ariel::Game::printLastTurn() { std::cout << "LAST TURN \t" + this->getLastTurn() << endl; }
void ariel::Game::printWiner()
{
    // TO DO: throw if game not finished
    // if (!(this->isFinished()))
    // {
    //     throw string{"Game hasn't finished"};
    // }
    string winner = "The winner is ";
    if (this->p1.cardesTaken() > this->p2.cardesTaken())
    {
        winner += "p1: " + this->p1.getName();
    }
    else if (this->p1.cardesTaken() < this->p2.cardesTaken())
    {
        winner += "p2: " + this->p2.getName();
    }
    else
    { // a tie
        winner = "It's a tie";
    }
    std::cout << winner << endl;
}
void ariel::Game::printLog()
{
    if (this->getLog().empty())
    {
        throw string{"Game hasn't started"};
    }
    std::cout << "GAME LOG:\n" + this->getLog() << endl;
}

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
    stats += "p1 wins:p2 wins:draws:turns\n";
    stats += to_string(p1_wins) + "\t" + to_string(p2_wins) + "\t" + to_string(draws) + "\t" + to_string(totalTurns);

    // win rates
    stats += "\nRATES:\n";
    stats += "p1 rate:p2 rate:draw rate\n";
    double p1_rate = (p1_wins + 0.0) / (totalTurns + 0.0);
    double p2_rate = (p2_wins + 0.0) / (totalTurns + 0.0);
    double draw_rate = (draws + 0.0) / (totalTurns + 0.0);
    stats += to_string(p1_rate) + "\t" + to_string(p2_rate) + "\t" + to_string(draw_rate);

    // stack size
    stats += "\nCARDS TAKEN:\n";
    stats += "p1 stack:p2 stack\n";
    stats += to_string(this->p1.cardesTaken()) + "\t" + to_string(this->p2.cardesTaken());

    return stats;
}

void ariel::Game::printStats()
{
    if (this->getLog().empty())
    {
        throw string{"Game hasn't started"};
    }
    // if (!(this->isFinished()))
    // {
    //     throw string{"Game hasn't finished"};
    // }
    std::cout << this->getStats() << endl;
}
