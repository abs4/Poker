//
// Created by Alex Szymanski on 4/24/18.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Card.h"

TEST_CASE( "Tests for Single Card INFO" ) {
    Card c = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    REQUIRE(c.getInfo() == "JACK of HEARTS.");
}
TEST_CASE( "Tests for Single Card Rank" ) {
    Card c = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    REQUIRE(c.getRank() == 9);
}
TEST_CASE( "Tests for Single Card Suit" ) {
    Card c = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    REQUIRE(c.getSuit() == 3);
}
TEST_CASE( "Tests for operator=" ) {
    Card c = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    Card c2 = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    Card c3 = Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS);
    REQUIRE(c==c2);
    REQUIRE(c!=c3);
}
TEST_CASE( "Tests for compare To" ) {
    Card c = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    Card c2 = Card(Card::CardRank::JACK, Card::CardSuit::HEARTS);
    Card c3 = Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS);
    Card c4 = Card(Card::CardRank::TWO, Card::CardSuit::HEARTS);
    REQUIRE(c.compareTo(c2) == 0);
    REQUIRE(c.compareTo(c3) < 0);
    REQUIRE(c.compareTo(c4) > 0);
}
