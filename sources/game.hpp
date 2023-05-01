#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "player.hpp"
#include "card.hpp"

const int MAX_MOVE = 26;
using namespace std;

namespace ariel
{
    class Game
    {
    private:
        Player &p1;
        Player &p2;
        vector<Card> cardStack;
        string last_turn;
        string log;
        int draw_count;
        int win_count;
        int curr_turn;
        int moves;

    public:
        Game(Player &player1, Player &player2) : p1(player1), p2(player2), moves(0), win_count(0), draw_count(0), curr_turn(0)
        {
            /** the logic here is that each game has its own stack of cards
             *   instead of each player holding one, avoiding the need to split the cards
             *   each turn will be indexed 0+i, 26+i for p1 and p2 respectfully.
             */
            p1.setPlaying(true);
            p2.setPlaying(true);
            cardStack = ariel::Card::getNewStack();

            // split to decks - with index
            p1.setDeck(0);
            p2.setDeck(MAX_MOVE);

            p1.setStackSize(MAX_MOVE);
            p2.setStackSize(MAX_MOVE);
        }
        void setLog(string const &str)
        {
            last_turn = str;
            log += str;
        }
        Player getP1() const { return p1; }
        Player getP2() const { return p2; }
        vector<Card> getStack() { return cardStack; }
        int getCurrTurn() const { return curr_turn; }
        int getWinCount() const { return win_count; }
        int getDrawCount() const { return draw_count; }
        int getMoves() const { return moves; }
        string getLastTurn() const { return last_turn; }
        string getLog() const { return log; }

        void setDrawCount() { draw_count++; }
        void setWinCount() { win_count++; }
        void addMoves(int move) { moves += move; }
        void setTurn() { curr_turn++; }

        string getStats();                                 // assist func for stats
        int MakeMove(unsigned int turn, string &curr_log); // assist func for making a move in a turn
        bool isFinished() const { return p2.stacksize()==0 && p1.stacksize() == 0; }
        void printLastTurn();
        void playTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}