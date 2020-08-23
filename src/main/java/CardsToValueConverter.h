//
// Created by Alex Szymanski on 4/24/18.
//

#ifndef UNTITLED_CARDSTOPOINTSCONVERTER_H
#define UNTITLED_CARDSTOPOINTSCONVERTER_H

#include "Card.h"
#include <vector>

class CardsToValueConverter {
    public:
        int ConvertCardsToValue(std::vector<Card*> cardsToConvert);
        void SortByRank(std::vector<Card*>& cardsToConvert);
        void SortBySuit(std::vector<Card*>& cardsToConvert);
        bool IsStraightFlush(std::vector<Card *> cardsToConvert);
        bool IsFourOfAKind(std::vector<Card*> cardsToConvert);
        bool IsFullHouse(std::vector<Card*> cardsToConvert);
        bool IsFlush(std::vector<Card*> cardsToConvert);
        bool IsStraight(std::vector<Card*> cardsToConvert);
        bool IsThreeOfAKind(std::vector<Card*> cardsToConvert);
        bool IsTwoPair(std::vector<Card*> cardsToConvert);
        bool IsPair(std::vector<Card*> cardsToConvert);
        std::string HandStrength(int num);

private:
};
#endif //UNTITLED_CARDSTOPOINTSCONVERTER_H
