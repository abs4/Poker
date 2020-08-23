//
// Created by Alex Szymanski on 4/25/18.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Card.h"
#include "Player.h"
#include "GameEngine.h"
#include "Deck.h"

TEST_CASE( "Tests for Game Set Up" ) {
   GameEngine g = GameEngine();
    g.GameSetUp(4, "ljf");
    REQUIRE(4 == g.GetNumOfPlayers());
    REQUIRE(0 == g.GetPot());
    REQUIRE(52 == g.GetDeck().size());
    REQUIRE(4 == g.GetPlayersInGame().size());
}
TEST_CASE( "Tests for Deal Cards" ) {
    GameEngine g = GameEngine();
    g.GameSetUp(4, "fff");
    REQUIRE(g.GetPlayersInGame()[0].GetPairOfCardsInHand().first == nullptr);
    REQUIRE(g.GetDeck().size() == 52);
    g.DealCards();
    REQUIRE(g.GetPlayersInGame()[0].GetPairOfCardsInHand().first != nullptr);
    REQUIRE(g.GetDeck().size() < 52);
}
TEST_CASE( "Tests for Set Blinds" ) {
    GameEngine g = GameEngine();
    g.GameSetUp(4, "fff");
    g.DealCards();
    REQUIRE(g.GetPot() == 0);
    g.SetBlindsAndAddBlindsToPot();
    REQUIRE(g.GetPot() == 150);
    REQUIRE(g.GetPlayersInGame()[0].GetAmountPaid() == 0);
    REQUIRE(g.GetPlayersInGame()[1].GetAmountPaid() == 50);
    REQUIRE(g.GetPlayersInGame()[2].GetAmountPaid() == 100);
}
TEST_CASE( "Tests for Turn" ) {
    GameEngine g = GameEngine();
    g.GameSetUp(4, "Fff");
    g.DealCards();
    g.SetBlindsAndAddBlindsToPot();
    g.PlayRound();
    REQUIRE(g.GetPlayersInGame()[2].GetAmountPaid() == 318);
}
TEST_CASE( "Tests for Cards on Table" ) {
    GameEngine g = GameEngine();
    g.GameSetUp(4, "Gg");
    g.DealCards();
    g.SetBlindsAndAddBlindsToPot();
    REQUIRE(g.GetTable().size() == 0);
    g.CardFlop();
    REQUIRE(g.GetTable().size() == 3);
    g.CardTurn();
    REQUIRE(g.GetTable().size() == 4);
    g.CardRiver();
    REQUIRE(g.GetTable().size() == 5);
}

TEST_CASE( "Tests for Game - Correct Pot and money" ) {
    GameEngine g = GameEngine();
    g.GameSetUp(3, "ff");
    g.DealCards();
    g.SetBlindsAndAddBlindsToPot();
    REQUIRE(g.GetPot() == 1000);
}
