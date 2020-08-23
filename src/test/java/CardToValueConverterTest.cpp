//
// Created by Alex Szymanski on 4/24/18.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Card.h"
#include "CardsToValueConverter.h"

TEST_CASE( "Tests for Sort By Rank" ) {
    CardsToValueConverter c;
    std::vector<Card*> v;
    v.push_back(new Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::TEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::ACE, Card::CardSuit::HEARTS));
    c.SortByRank(v);
    REQUIRE( v[0]->getRank() == 1);
    REQUIRE( v[1]->getRank() == 6);
    REQUIRE( v[2]->getRank() == 6);
    REQUIRE( v[3]->getRank() == 8);
    REQUIRE( v[4]->getRank() == 10);
    REQUIRE( v[5]->getRank() == 11);
    REQUIRE( v[6]->getRank() == 12);
}

TEST_CASE( "Tests for Sort By Suit" ) {
    CardsToValueConverter c;
    std::vector<Card*> v;
    v.push_back(new Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::TEN, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::ACE, Card::CardSuit::CLUBS));
    c.SortBySuit(v);
    REQUIRE( v[0]->getSuit() == 0);
    REQUIRE( v[1]->getSuit() == 1);
    REQUIRE( v[2]->getSuit() == 1);
    REQUIRE( v[3]->getSuit() == 2);
    REQUIRE( v[4]->getSuit() == 3);
    REQUIRE( v[5]->getSuit() == 3);
    REQUIRE( v[6]->getSuit() == 3);
}
TEST_CASE( "Tests for Pair" ) {
    CardsToValueConverter c;
    std::vector<Card*> v;
    v.push_back(new Card(Card::CardRank::KING, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    REQUIRE(c.IsPair(v) == true);
    while (v.size() != 0) {
        v.pop_back();

    }
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    REQUIRE(c.IsPair(v) == false);
}
TEST_CASE( "Tests for Two Pair" ) {
    CardsToValueConverter c;
    std::vector<Card*> l;
    l.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    l.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    l.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::HEARTS));
    l.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    l.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    REQUIRE(c.IsTwoPair(l) == true);
    while (l.size() != 0) {
        l.pop_back();

    }
    l.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    l.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    l.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    l.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    l.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::SPADES));
    REQUIRE(c.IsTwoPair(l) == false);
}
TEST_CASE( "Tests for Three of a kind" ) {
    CardsToValueConverter c;
    std::vector<Card*> v;
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    REQUIRE(c.IsThreeOfAKind(v) == false);
    while (v.size() != 0) {
        v.pop_back();

    }
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::SPADES));
    REQUIRE(c.IsThreeOfAKind(v) == true);
}
TEST_CASE( "Tests for Four of a kind" ) {
    CardsToValueConverter c;
    std::vector<Card*> v;
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    REQUIRE(c.IsFourOfAKind(v) == false);
    while (v.size() != 0) {
        v.pop_back();
    }
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    REQUIRE(c.IsFourOfAKind(v) == true);
}
TEST_CASE( "Tests for Straight" ) {
    CardsToValueConverter c;
    std::vector<Card *> v;
    v.push_back(new Card(Card::CardRank::TWO, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::TWO, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::TWO, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SIX, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    REQUIRE(c.IsStraight(v) == true);
    while (v.size() != 0) {
        v.pop_back();
    }
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    REQUIRE(c.IsStraight(v) == false);
}
TEST_CASE( "Tests for Flush" ) {
    CardsToValueConverter c;
    std::vector<Card *> v;
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SIX, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    REQUIRE(c.IsFlush(v) == true);
    while (v.size() != 0) {
        v.pop_back();
    }
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::QUEEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    REQUIRE(c.IsFlush(v) == false);
}
TEST_CASE( "Tests for Straight Flush" ) {
    CardsToValueConverter c;
    std::vector<Card *> v;
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SIX, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    REQUIRE(c.IsStraightFlush(v) == false);
    while (v.size() != 0) {
        v.pop_back();
    }
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SIX, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    REQUIRE(c.IsStraightFlush(v) == true);
}
TEST_CASE( "Tests for Point Converter" ) {
    CardsToValueConverter c;
    std::vector<Card *> v;
    v.push_back(new Card(Card::CardRank::FIVE, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::THREE, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SIX, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::SIX, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::DIAMONDS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::DIAMONDS));
    REQUIRE(c.ConvertCardsToValue(v) == 50005);
    while (v.size() != 0) {
        v.pop_back();
    }
    v.push_back(new Card(Card::CardRank::JACK, Card::CardSuit::CLUBS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::ACE, Card::CardSuit::CLUBS));
    v.push_back(new Card(Card::CardRank::TWO, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::KING, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::NINE, Card::CardSuit::SPADES));

    REQUIRE(c.ConvertCardsToValue(v) == 12);
    while (v.size() != 0) {
        v.pop_back();
    }
    v.push_back(new Card(Card::CardRank::JACK, Card::CardSuit::CLUBS));
    v.push_back(new Card(Card::CardRank::SEVEN, Card::CardSuit::HEARTS));
    v.push_back(new Card(Card::CardRank::ACE, Card::CardSuit::CLUBS));
    v.push_back(new Card(Card::CardRank::TWO, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::FOUR, Card::CardSuit::SPADES));
    v.push_back(new Card(Card::CardRank::EIGHT, Card::CardSuit::CLUBS));
    v.push_back(new Card(Card::CardRank::TEN, Card::CardSuit::HEARTS));
    REQUIRE(c.ConvertCardsToValue(v) == 12);
}
