//
// Created by Alex Szymanski on 4/24/18.
//

#include "CardsToValueConverter.h"
#include <iostream>

/**
 * Sorts order by rank (lowest first)
 * @param cardsToConvert - the vector to sort
 */
void CardsToValueConverter::SortByRank(std::vector<Card*>& cardsToConvert) {
    for (int i = 0; i < cardsToConvert.size(); i++) {
        for (int j = 0; j < cardsToConvert.size() - i - 1; j++) {
            if (cardsToConvert[j]->getRank() > cardsToConvert[j + 1]->getRank()) {
                std::swap(cardsToConvert[j], cardsToConvert[j+1]);
            }
        }
    }
}
/**
 * Sorts order by rank (basically just groups suits together)
 * @param cardsToConvert
 */
void CardsToValueConverter::SortBySuit(std::vector<Card*>& cardsToConvert) {
    for (int i = 0; i < cardsToConvert.size(); i++) {
        for (int j = 0; j < cardsToConvert.size() - i - 1; j++) {
            if (cardsToConvert[j]->getSuit() > cardsToConvert[j + 1]->getSuit()) {
                std::swap(cardsToConvert[j], cardsToConvert[j+1]);
            }
        }
    }
}
/**
 * Probably will clean this up (Function too long)
 * @param cardsToConvert cards to convert to values
 * @return the value of the vector of cards
 */
int CardsToValueConverter::ConvertCardsToValue(std::vector<Card*> cardsToConvert) { // 2 -> 7
    if (IsStraightFlush(cardsToConvert)) {
        SortByRank(cardsToConvert);
        SortBySuit(cardsToConvert);
        for (int i = 0; i < cardsToConvert.size() - 4; ++i) {
            if (cardsToConvert[i]->getSuit() == cardsToConvert[i + 1]->getSuit()
                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 2]->getSuit()
                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 3]->getSuit()
                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 4]->getSuit()
                && cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank() - 1
                && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank() - 2
                && cardsToConvert[i]->getRank() == cardsToConvert[i + 3]->getRank() - 3
                && cardsToConvert[i]->getRank() == cardsToConvert[i + 4]->getRank() - 4) {
                return 90000 + cardsToConvert[i + 4]->getRank();
            }
        }
        return 90000;
    } else if (IsFourOfAKind(cardsToConvert)) {
        SortByRank(cardsToConvert);
        int fourOfAKindRank = -1;
        int kicker = 0;
        for (int i = 0; i < cardsToConvert.size() - 3; ++i) {
            if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()
                                                    && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank()
                                                    && cardsToConvert[i]->getRank() == cardsToConvert[i + 3]->getRank()
                                                    ) {
                fourOfAKindRank = cardsToConvert[i]->getRank();
            }
        }
        for (int j = 0; j < cardsToConvert.size(); ++j) {
            if (cardsToConvert[j]->getRank() != kicker && cardsToConvert[j]->getRank() > kicker) {
                kicker = cardsToConvert[j]->getRank();
            }
        }
        std::cout << fourOfAKindRank << std::endl;
        std::cout << kicker << std::endl;

        return 80000+ ((fourOfAKindRank + 1) * 13) + kicker;
    } else if (IsFullHouse(cardsToConvert)) {
        SortByRank(cardsToConvert);
        int highestTriple = -1;
        int highestPair = -1;
        for (int i = 0; i < cardsToConvert.size() - 2; ++i) {
            if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()
                && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank()
                && cardsToConvert[i]->getRank() > highestTriple) {
                highestTriple = cardsToConvert[i]->getRank();
            }
        }
        for (int j = 0; j < cardsToConvert.size() - 1; ++j) {
            if (cardsToConvert[j]->getRank() == cardsToConvert[j+ 1]->getRank() && cardsToConvert[j]->getRank() != highestTriple
                                                                                && cardsToConvert[j]->getRank() > highestPair) {
                highestPair = cardsToConvert[j]->getRank();
            }
        }
        return 70000 + (highestTriple + 1) * 13 + highestPair;
    } else if (IsFlush(cardsToConvert)) {
        SortByRank(cardsToConvert);
        SortBySuit(cardsToConvert);
        int highestCardRank = 0;
        for (int i = 0; i < cardsToConvert.size() - 4; ++i) {
            if (cardsToConvert[i]->getSuit() == cardsToConvert[i + 1]->getSuit()
                                                    && cardsToConvert[i]->getSuit() == cardsToConvert[i + 2]->getSuit()
                                                    && cardsToConvert[i]->getSuit() == cardsToConvert[i + 3]->getSuit()
                                                    && cardsToConvert[i]->getSuit() == cardsToConvert[i + 4]->getSuit()) {
                highestCardRank = cardsToConvert[i + 4]->getRank();
            }
        }
        return 60000 + highestCardRank;
    } else if (IsStraight(cardsToConvert)) {
        SortByRank(cardsToConvert);
        int stepper = 0;
        int highestCardRank = 0;
        for (int j = 0; j < cardsToConvert.size() - 1; ++j) {
            if (cardsToConvert[j]->getRank() == cardsToConvert[j + 1]->getRank()) {
                int x = j;
                while (x > 0) {
                    std::swap(cardsToConvert[x] , cardsToConvert[x-1]);
                    x--;
                }
                stepper++;
            }
        }
            for (int i = stepper; i < cardsToConvert.size() - 4; ++i) {
            if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank() - 1
                                                    && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank() - 2
                                                    && cardsToConvert[i]->getRank() == cardsToConvert[i + 3]->getRank() - 3
                                                    && cardsToConvert[i]->getRank() == cardsToConvert[i + 4]->getRank() - 4) {
                highestCardRank = cardsToConvert[i + 4]->getRank();
            }
        }
        return 50000 + highestCardRank;
    } else if (IsThreeOfAKind(cardsToConvert)) {
        SortByRank(cardsToConvert);
        int highestTriple = -1;
        int kickerOne = 0;
        int kickerTwo = 0;
        for (int i = 0; i < cardsToConvert.size() - 2; ++i) {
            if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()
                                                    && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank()
                                                    && cardsToConvert[i]->getRank() > highestTriple) {
                highestTriple = cardsToConvert[i]->getRank();
            }
        }
        for (int i = 0; i < cardsToConvert.size() ; ++i) {
            if (cardsToConvert[i]->getRank() > kickerOne && cardsToConvert[i]->getRank() != highestTriple) {
                kickerTwo = kickerOne;
                kickerOne = cardsToConvert[i]->getRank();
            } else if (cardsToConvert[i]->getRank() > kickerOne && cardsToConvert[i]->getRank() != highestTriple
                       && cardsToConvert[i]->getRank() != kickerOne) {
                kickerTwo = cardsToConvert[i]->getRank();
            }
        }
        return (40000 + (highestTriple + 1) * 13*13) + (kickerOne + 1) * 13 + kickerTwo;
    } else if (IsTwoPair(cardsToConvert)) {
        SortByRank(cardsToConvert);
        int firstHighestPairRank = -1;
        int secondHighestPairRank = -1;
        int possibleThirdPair = -1;
        int kicker = 0;
        for (int i = 0; i < cardsToConvert.size() - 1; ++i) {
            if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()) {
                if (cardsToConvert[i]->getRank() > firstHighestPairRank) {
                    possibleThirdPair = secondHighestPairRank;
                    secondHighestPairRank = firstHighestPairRank;
                    firstHighestPairRank = cardsToConvert[i]->getRank();
                } else if (cardsToConvert[i]->getRank() > secondHighestPairRank) {
                    possibleThirdPair = secondHighestPairRank;
                    secondHighestPairRank = cardsToConvert[i]->getRank();
                } else {
                    possibleThirdPair = cardsToConvert[i]->getRank();
                }
            }
        }
        for (int j = 0; j < cardsToConvert.size(); j++) {
            if ((cardsToConvert[j]->getRank() != firstHighestPairRank
                && cardsToConvert[j]->getRank() != secondHighestPairRank
                && cardsToConvert[j]->getRank() != possibleThirdPair) && cardsToConvert[j]->getRank() > kicker) {
                kicker = cardsToConvert[j]->getRank();
            }
        }
        return (30000 + (firstHighestPairRank + 1) * 169) + (secondHighestPairRank + 1) * 13 + kicker; //2363 -> MAX 353 -> MIN
    } else if (IsPair(cardsToConvert)) {
        SortByRank(cardsToConvert);
        int highestPairRank = -1;
        int kickerOne = 0;
        int kickerTwo = 0;
        int kickerThree = 0;
        for (int i = 0; i < cardsToConvert.size() - 1; ++i) {
            if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank() && cardsToConvert[i]->getRank() > highestPairRank) {
                highestPairRank = cardsToConvert[i]->getRank();
            }
        }

        for (int i = 0; i < cardsToConvert.size(); ++i) {
            if (cardsToConvert[i]->getRank() > kickerOne && cardsToConvert[i]->getRank() != highestPairRank) {
                kickerThree = kickerTwo;
                kickerTwo = kickerOne;
                kickerOne = cardsToConvert[i]->getRank();
            } else if (cardsToConvert[i]->getRank() > kickerOne && cardsToConvert[i]->getRank() != highestPairRank
                                                                                && cardsToConvert[i]->getRank() != kickerOne) {
                kickerThree = kickerTwo;
                kickerTwo = cardsToConvert[i]->getRank();
            } else if (cardsToConvert[i]->getRank() > kickerOne && cardsToConvert[i]->getRank() != highestPairRank
                                                                                && cardsToConvert[i]->getRank() != kickerOne
                                                                                && cardsToConvert[i]->getRank() != kickerTwo) {
                kickerThree = cardsToConvert[i]->getRank();
            }
        }
        return (highestPairRank + 1) * 13*13*13 + (kickerOne + 1) * 13*13 + (kickerTwo + 1) * 13 + kickerThree;
    } else {
        SortByRank(cardsToConvert);
        int highestCardsRank = 0; // High Card MAX -> 12 MIN -> 0)
        for (int i = 2; i < cardsToConvert.size(); i++) {
            highestCardsRank += cardsToConvert[i]->getRank();
        }
        return highestCardsRank;
    }
}

std::string CardsToValueConverter::HandStrength(int num) {
    if (num <= 50) {
        return "high card";
    } else if (num < 30000) {
        return "pair";
    } else if (num < 40000) {
        return "two pair";
    } else if (num < 50000) {
        return "three of a kind";
    } else if (num < 60000) {
        return "straight";
    } else if (num < 70000) {
        return "flush";
    } else if (num < 80000) {
        return "full house";
    } else if (num < 90000) {
        return "four of a kind";
    } else if (num < 100000) {
        return "straight flush";
    } else {
        return "...";
    }
}

/**
 * WORKS ASSUMING SORTED VECTOR BY RANK AND SUIT
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsStraightFlush(std::vector<Card *> cardsToConvert) {
    SortByRank(cardsToConvert);
    SortBySuit(cardsToConvert);
    for (int i = 0; i < cardsToConvert.size() - 4; ++i) {
        if (cardsToConvert[i]->getSuit() == cardsToConvert[i + 1]->getSuit()
                                                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 2]->getSuit()
                                                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 3]->getSuit()
                                                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 4]->getSuit()
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank() - 1
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank() - 2
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 3]->getRank() - 3
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 4]->getRank() - 4) {
            return true;
        }
    }
    return false;
}
/**
 * WORKS ASSUMING SORTED VECTOR BY RANK
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsFourOfAKind(std::vector<Card*> cardsToConvert) {
    SortByRank(cardsToConvert);
    for (int i = 0; i < cardsToConvert.size() - 3; ++i) {
        if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank()
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 3]->getRank()) {
            return true;
        }
    }
    return false;
}
/**
 * WORKS ASSUMING SORTED VECTOR BY RANK
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsFullHouse(std::vector<Card*> cardsToConvert) {
    return (IsThreeOfAKind(cardsToConvert) && IsTwoPair(cardsToConvert));
}
/**
 * WORKS ASSUMING SORTED VECTOR BY SUIT
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsFlush(std::vector<Card*> cardsToConvert) {
    SortBySuit(cardsToConvert);
    for (int i = 0; i < cardsToConvert.size() - 4; i++) {
        if (cardsToConvert[i]->getSuit() == cardsToConvert[i + 1]->getSuit()
                                                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 2]->getSuit()
                                                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 3]->getSuit()
                                                && cardsToConvert[i]->getSuit() == cardsToConvert[i + 4]->getSuit()) {
            return true;
        }
    }
    return false;
}
/**
 * WORKS ASSUMING SORTED VECTOR BY RANK
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsStraight(std::vector<Card*> cardsToConvert) {
    SortByRank(cardsToConvert);
    int stepper = 0;
    for (int j = 0; j < cardsToConvert.size() - 1; ++j) {
        if (cardsToConvert[j]->getRank() == cardsToConvert[j + 1]->getRank()) {
            int x = j;
            while (x > 0) {
                std::swap(cardsToConvert[x] , cardsToConvert[x-1]);
                x--;
            }
            stepper++;
        }
    }
    for (int i = stepper; i < cardsToConvert.size() - 4; ++i) {
        if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank() - 1
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank() - 2
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 3]->getRank() - 3
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 4]->getRank() - 4) {
            return true;
        }
    }
    return false;
}
/**
 * ASSUMING SORTED BY RANK
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsThreeOfAKind(std::vector<Card*> cardsToConvert) {
    SortByRank(cardsToConvert);
    for (int i = 0; i < cardsToConvert.size() - 2; ++i) {
        if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()
                                                && cardsToConvert[i]->getRank() == cardsToConvert[i + 2]->getRank()) {
            return true;
        }
    }
    return false;
}
/**
 * ASSUMING SORTED VECTOR BY RANK
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsTwoPair(std::vector<Card*> cardsToConvert) {
    SortByRank(cardsToConvert);
    int numberOfPairs = 0;
    for (int i = 0; i < cardsToConvert.size() - 1; ++i) {
        if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()) {
            numberOfPairs++;
            i++;
        }
    }
    return (numberOfPairs > 1);
}
/**
 * WORKS ASSUMING SORTED VECTOR BY RANK
 * @param cardsToConvert vector to turn into a single value
 * @return said value
 */
bool CardsToValueConverter::IsPair(std::vector<Card*> cardsToConvert) {
    SortByRank(cardsToConvert);
    for (int i = 0; i < cardsToConvert.size() - 1; ++i) {
        if (cardsToConvert[i]->getRank() == cardsToConvert[i + 1]->getRank()) {
            return true;
        }
    }
    return false;
}
