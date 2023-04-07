#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"


TEST_CASE("for each turn the number of cards in the stack decreases") {
    Player p1("A");
    Player p2("B");
    Game game(p1, p2);
    int temp = 26;
    for (int i = 0;  i < 7; i++) {
        if(0 < p1.stacksize()){
            game.playTurn();
            CHECK_LE(p1.stacksize(),temp-1);
            temp = p1.stacksize();}
        else
            CHECK_THROWS(game.playTurn());

    }
}

TEST_CASE("At the end of the game both stack will be empty and all the cards will be Taken"){
    Player p1("A");
    Player p2("B");
    Game game(p1,p2);
    game.playAll();
    CHECK_EQ(p1.stacksize(),0);
    CHECK_EQ(p2.stacksize(),0);
    CHECK_EQ(p2.cardesTaken()+p1.cardesTaken(),52);
}

TEST_CASE("the beginning of the game"){
    Player p1("A");
    Player p2("B");
    Game game(p1, p2);

    SUBCASE("Checks that the constructor has initialized well"){
        CHECK_EQ(p2.stacksize() , 26);
        CHECK_EQ(p1.stacksize() , 26);
        CHECK_EQ(p2.cardesTaken() , 0);
        CHECK_EQ(p1.cardesTaken() , 0);
    }
    SUBCASE("Functions that print TURN will throw an error if the game has not yet started"){
        CHECK_THROWS(game.printLog());
        CHECK_THROWS(game.printLastTurn());
    }
    SUBCASE("Functions that print status will not throw an error even if the game has not yet started"){
        CHECK_NOTHROW(game.printStats());
        CHECK_NOTHROW(game.printWiner());
    }
}

TEST_CASE("The number of cards in one player's stack is always equal to the number of cards in the other player's stack"){
    Player p1("a");
    Player p2("b");
    Game game(p1, p2);
    for (int i=0; 0<p1.stacksize() && i<7;i++){
        game.playTurn();
        CHECK_EQ(p1.stacksize(),p2.stacksize());
    }

}
TEST_CASE("At all times there are 52 cards in the game"){
    Player p1("a");
    Player p2("b");
    Game game(p1, p2);
    for (int i=0; 0<p1.stacksize() && i<7;i++){
        game.playTurn();
        CHECK_EQ(p1.stacksize()+p2.stacksize()+p2.cardesTaken()+p1.cardesTaken(),52);
    }
}
TEST_CASE("Multiplayer and multigames") {
    Player p1("a");
    Player p2("b");
    Player p3("c");
    Player p4("d");
    Player p5("e");
    Player p6("f");

    SUBCASE("A player can participate in a new game if the old one is over") {
        Game game3(p4, p5);
        game3.playAll();
        CHECK_NOTHROW(Game {p4, p5});

    }
    SUBCASE("A player cannot play two games at the same time") {
        CHECK_NOTHROW(Game {p1, p2});
        CHECK_THROWS(Game {p1, p3});

    }
    SUBCASE("A player cannot play against himself") {
        CHECK_THROWS(Game {p6, p6});
    }
}

TEST_CASE("You can't play after the cartridges are empty"){
    Player p1("A");
    Player p2("B");
    Game game(p1,p2);
    game.playAll();
    CHECK_THROWS(game.playTurn());
    CHECK_THROWS(game.playAll());
}



