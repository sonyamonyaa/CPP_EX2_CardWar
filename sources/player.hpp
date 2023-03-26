#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "card.hpp"

using namespace std;

namespace ariel
{
    Class Player {

        private:
            string name;
            int stack_size;
            int cards_taken;
            boolean playing
            //add stack?
        public:
            Player (const string& n): name(n), stack_size(0), cards_taken(0)

            int stacksize() const{
                return stack_size;
            }

            int cardesTaken() const{
                return cards_taken;
            }
    }