//
// Created by Alex Szymanski on 4/17/18.
//

#include "Card.h"
#include <string>

/**
 * Constructor - Creates a Card of user's choice
 * @param cardRank - rank of card ex. KING
 * @param cardSuit - suit of card ex. SPADES
 */
Card::Card(CardRank cardRank, CardSuit cardSuit) {
    this->rank = cardRank;
    this->suit = cardSuit;
}

/**
 * Getter for rank
 * @return the rank of the card
 */
Card::CardRank Card::getRank() const{
        return this->rank;
}

/**
 * Getter for suit
 * @return the suit of the card
 */
Card::CardSuit Card::getSuit() const{
    return this->suit;
}

/**
 * get Suit and Rank of card as words (rather than values)
 * @return the info of a card
 */
std::string Card::getInfo() const{
    std::string rankArray[] = { "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE" };
    std::string suitArray[] = { "SPADES", "DIAMONDS", "CLUBS", "HEARTS" };

    std::string info = "";
    int c = rank;
    info.append(rankArray[(int)rank]);
    info.append(" of \n");
    info.append(suitArray[(int)suit]);
    return info;
}

/**
 * Checks to see if two cards are identical in suit and rank
 * @param other - the other card to compare to
 * @return true if the same and false if not
 */
bool Card::operator==(const Card &other) const {
    if (this->getSuit() == other.getSuit()
            && this->getRank() == other.getRank()) {
        return true;
    }
    return false;
}

/**
 * Checks to see if two cards are identical in suit and rank
 * @param other - the other card to compare to
 * @return false if not the same and true if so
 */
bool Card::operator!=(const Card &other) const {
    return !(*this==other);
}

/**
 * Checks to see what card is of higher value
 * @param otherCard - the other card to compare to
 * @return 1 if the cards compared to is less, -1 if cards compared to is more, 0 if same
 */
int Card::compareTo(Card otherCard) const{
    if (this->getRank() < otherCard.getRank()) {
        return -1;
    }

    if (this->getRank() > otherCard.getRank()) {
        return 1;
    }
    return 0;
}
