//
// Created by Alex Szymanski on 4/24/18.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Card.h"
#include "Deck.h"

TEST_CASE( "Tests for Deck Size" ) {
    Deck d = Deck();
    REQUIRE(d.size() == 0);
    d.addCardsToDeck();
    REQUIRE(d.size() == 52);
}
TEST_CASE( "Tests for Deck Draw Card" ) {
    Deck d = Deck();
    d.addCardsToDeck();
    REQUIRE(d.getDeckOfCards()->top() == Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
    REQUIRE(*d.drawCard() == Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
}
TEST_CASE( "Tests for Deck Brand" ) {
    Deck d = Deck();
    REQUIRE(std::to_string(d.getDeckBrand()) == "0");
}
TEST_CASE( "Tests for Deck Clear" ) {
    Deck d = Deck();;
    d.addCardsToDeck();
    REQUIRE(d.size() == 52);
    d.clearCardsFromDeck();
    REQUIRE(d.size() == 0);
}
TEST_CASE( "Tests for Deck Shuffle" ) {
    Deck d = Deck();
    d.addCardsToDeck();
    d.shuffleDeck();
    REQUIRE(d.getDeckOfCards()->top() != Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
    REQUIRE(*d.drawCard() != Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
}
