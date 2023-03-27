#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"

using namespace std;

namespace ariel {
    class Game {
        private:
            Player p1;
            Player p2;
            string turn;
            string Log;
            int win_rate;
            int draw_rate;
            int draw_count;
            int cards_won;
        
        public:
            Game(Player &player1, Player &player2): p1(player1), p2(player2), win_rate(0), draw_rate(0), draw_count(0), cards_won(0) {};
            
            void printLastTurn();
            void playTurn();
            void playAll(); 
            void printWiner(); 
            void printLog(); 
            void printStats();
    };
}