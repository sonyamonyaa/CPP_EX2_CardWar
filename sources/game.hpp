#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"

using namespace std;

namespace ariel {
    Class Game {
        private:
            Player p1;
            Player p2;
            string turn;
            string Log;
            int win_rate;
            int draw_rate;
            int draw_count;
            int cards_won;
            string winner;
        
        public:
            Game(Player &p1, Player &p2): this.p1(p1), this.p2(p2);
            
            playAll(); 
            printWiner(); 
            printLog(); 
            printStats();
    }
}