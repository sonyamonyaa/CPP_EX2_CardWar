#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;
//enums for easier printing
enum Suits  {"Hearts", "Spades", "Diamonds", "Clubs"};
enum Ranks {"Ace", 2, 3, 4, 5, 6, 7, 8, 9, 10, "Jack", "Queen", "King"};
namespace ariel
{
    Class Card {

        private:
            Suits suit;
            Ranks rank;
        public:
            Card (){}
    }
}