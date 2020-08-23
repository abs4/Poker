//
// Created by Alex Szymanski on 4/17/18.
//

#include "Deck.h"
#include <vector>
#include <cmath>
/**
 * Default Constructor - Creates a empty Trycicle deck
 */
Deck::Deck() {
    this->brand = Deck::Brand::TRICYCLE;
}

/**
 *  Constructor - Creates a empty deck of user's choice
 */
Deck::Deck(Deck::Brand brand) {
    this->brand = brand;
}

/**
 * Getter for brand
 * @return the brand of the deck
 */
Deck::Brand Deck::getDeckBrand() const{
    return brand;
}

/**
 * Getter for deck of cards
 * @return the deck of cards
 */
std::stack<Card>* Deck::getDeckOfCards() {
    return &cardsInDeck;
}

/**
 * Adds full set of 52 cards to empty deck
 * @return a stack of 52 cards or NULL if deck was previously not empty
 */
std::stack<Card>* Deck::addCardsToDeck() {
    if (cardsInDeck.empty()) {
        bool placedAce = false;
        for (int cardSuit = Card::CardSuit::SPADES; cardSuit != Card::CardSuit::HEARTS + 1; cardSuit++) {
            for (int cardRank = Card::CardRank::TWO; cardRank != Card::CardRank::ACE; cardRank++) {
                if (placedAce) {
                    cardsInDeck.push(
                            Card(static_cast<Card::CardRank>(cardRank), static_cast<Card::CardSuit>(cardSuit)));
                } else {
                    cardsInDeck.push(Card(static_cast<Card::CardRank>(Card::CardRank::ACE),
                                          static_cast<Card::CardSuit>(cardSuit)));
                    placedAce = true;
                    cardRank--;
                }
            }
            placedAce = false;
        }
        return &cardsInDeck;
    }
    else {
        return nullptr;
    }
}

/**
 * empties playing deck
 * @return true if deck is emptied
 */
bool Deck::clearCardsFromDeck() {
    while (cardsInDeck.size() != 0) {
        cardsInDeck.pop();
    }
    if (cardsInDeck.empty()) {
        return true;
    }
    return false;
}

/**
 * Shuffles deck of cards
 * @return said shuffled deck of cards
 */
std::stack<Card>* Deck::shuffleDeck() {
    std::vector<Card> tempForShuffle;
    while (!cardsInDeck.empty()) {
        tempForShuffle.push_back(cardsInDeck.top());
        cardsInDeck.pop();
    }

    std::random_shuffle(tempForShuffle.begin(), tempForShuffle.end());

    while (!tempForShuffle.empty()) {
        cardsInDeck.push(tempForShuffle.back());
        tempForShuffle.pop_back();
    }
    return &cardsInDeck;
}

/**
 * draws one card from deck (removes top card from deck)
 * @return the card drawn
 */
Card* Deck::drawCard() {
    if (!cardsInDeck.empty()) {
        Card* cardToDraw = new Card(cardsInDeck.top().getRank(), cardsInDeck.top().getSuit());
        cardsInDeck.pop();
        return cardToDraw;
    }
    return nullptr;
}

/**
 * size of deck
 * @return the size
 */
int Deck::size() {
    return cardsInDeck.size();
}
