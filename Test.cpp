#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test 1 - Initialize Game")
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);

    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
}

TEST_CASE("Test 2 - Finish Game")
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);

    game.playAll();

    CHECK((p1.stacksize() == 0 || p2.stacksize() == 0));
    CHECK((p1.cardesTaken() == 52 || p2.cardesTaken() == 52));
    CHECK(((p1.stacksize() == 0 && p2.cardesTaken() == 52) || (p2.stacksize() == 0 && p1.cardesTaken() == 52)));

    // play in same game after it finished sould be impossible
    CHECK_THROWS(game.playTurn());
}

TEST_CASE("Test 3 - illegal games")
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);
    CHECK_THROWS(Game(p1, p2)); // parallel game forbidden
    CHECK_THROWS(Game(p1, p1)); // same player impossible

    // no one can play with Cody
    Player p3("Cody");
    CHECK_THROWS(Game(p1, p3));
    CHECK_THROWS(Game(p3, p2));
}

TEST_CASE("Test 4 - after turn")
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);
    game.playTurn();
    CHECK(p1.stacksize() <= 25);
    CHECK(p2.stacksize() <= 25);
    for (int i = 0; i < 4; i++)
    {
        game.playTurn();
    }
    CHECK(p1.stacksize() <= 21);
    CHECK(p2.stacksize() <= 21);
}

TEST_CASE("Test 5 - another game") //if a game ends, we should be able to make a new game
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);

    game.playAll();

    CHECK_NOTHROW(Game(p1, p2)); // new game should be possible

    Game new_game(p1, p2);
    //init should be the same
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);  
}
