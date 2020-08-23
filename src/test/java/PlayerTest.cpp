//
// Created by Alex Szymanski on 4/25/18.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Card.h"
#include "Player.h"

TEST_CASE( "Tests for Constructor" ) {
    Player p = Player();
    REQUIRE(p.GetTokens() == 1000);
    REQUIRE(p.GetPairOfCardsInHand().first == nullptr);
    REQUIRE(p.GetPairOfCardsInHand().second == nullptr);
    REQUIRE(p.GetAmountPaid() == 0);
    REQUIRE(!p.HasFolded());
    REQUIRE(!p.IsReadyForNextCount());
    REQUIRE(p.GetName() == "AI26807");
}
TEST_CASE( "Tests for Reset Player" ) {
    Player p = Player();
    REQUIRE(p.GetAmountPaid() == 0);
    REQUIRE(!p.HasFolded());
    p.SetAmountPaid(2);
    p.SetFolded(true);
    REQUIRE(p.GetAmountPaid() == 2);
    REQUIRE(p.HasFolded());
    p.Reset();
    REQUIRE(p.GetAmountPaid() == 0);
    REQUIRE(!p.HasFolded());
}
TEST_CASE( "Tests for Make Decision" ) {
    Player p = Player();
    int i = p.MakeDecision(1000, std::make_pair<Card *, Card *>(nullptr, nullptr), 500, 500,
            0, 200);
    REQUIRE(i > -1);
}