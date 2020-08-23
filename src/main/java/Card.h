//
// Created by Alex Szymanski on 4/17/18.
//

#ifndef UNTITLED_CARD_H
#define UNTITLED_CARD_H

#include <stack>

class Card {
    public:
        enum CardRank {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
        enum CardSuit {SPADES, DIAMONDS, CLUBS, HEARTS};
        CardRank getRank() const;
        CardSuit getSuit() const;
        Card(CardRank cardRank, CardSuit cardSuit);
        std::string getInfo() const;
        bool operator==(const Card& other) const;
        bool operator!=(const Card& other) const;
        int compareTo(Card otherCard) const;

    private:
        CardRank rank;
        CardSuit suit;
};

#endif //UNTITLED_CARD_H
