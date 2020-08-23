//
// Created by Alex Szymanski on 4/17/18.
//

#ifndef UNTITLED_DECK_H
#define UNTITLED_DECK_H

#include "Card.h"

class Deck {
    public:
        enum Brand {TRICYCLE, DEE, CAVIATOR};
        Deck();
        Deck(Brand brand);
        Brand getDeckBrand() const;
        std::stack<Card>* getDeckOfCards();
        std::stack<Card>* addCardsToDeck();
        bool clearCardsFromDeck();
        std::stack<Card>* shuffleDeck();
        Card* drawCard();
        int size();

    private:
        Brand brand;
        std::stack<Card> cardsInDeck;
};
#endif //UNTITLED_DECK_H
