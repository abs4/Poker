//
// Created by Alex Szymanski on 4/17/18.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include <tuple>
#include "Card.h"
#include <string>

class Player {
    public:

        Player(); // Default constructor (random Name)
        Player(std::string name); // 1 par Constructor with chosen name
        // Check  0
        // Call 0
        // Fold 1
        // Raise 2
        // Function that incorporates all of the info to create a decision based off of position in
        int MakeDecision(int tokens, std::pair<Card *, Card *> hand, int pot_amount, int amount_to_stay_in,
                         int amount_already_in, int amount_players_not_yet_folded);

        void Reset(); // restart player for next round

        // Getters
        int GetTokens() const;
        std::pair<Card*, Card*> GetPairOfCardsInHand() const;
        int GetAmountPaid();
        bool IsReadyForNextCount() const;
        bool HasFolded() const;
        std::string GetName() const;

        // Setters
        void SetTokens(int t);
        void SetPairOfCardsInHand(Card *card1, Card *card2);
        void SetAmountPaid(int price);
        void SetReadyForNextCount(bool d);
        void SetFolded(bool d);

    private:
        std::pair<Card*, Card*> pairOfCardsInHand_;
        int tokens_ = 1000;
        int amoundAlreadyPaid_ = 0;
        bool isReadyForNextCount_ = false;
        bool hasFolded_ = false;
        std::string name_;
};
#endif //UNTITLED_PLAYER_H
