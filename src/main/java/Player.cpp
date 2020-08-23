//
// Created by Alex Szymanski on 4/17/18.
//

#include "Player.h"

// Default Constructor
Player::Player() {
    tokens_ = 1000;
    pairOfCardsInHand_ = std::make_pair(nullptr , nullptr);
    amoundAlreadyPaid_ = 0;
    isReadyForNextCount_ = false;
    hasFolded_ = false;
    name_ = "AI" + std::to_string((rand() % 50) + 10000); // Technically two players can have same name but VERY unlikely
}

// Constructor with name
Player::Player(std::string name) {
    tokens_ = 1000;
    pairOfCardsInHand_ = std::make_pair(nullptr , nullptr);
    amoundAlreadyPaid_ = 0;
    isReadyForNextCount_ = false;
    hasFolded_ = false;
    name_ = name;
}

/**
 * random strategies for now
 * @param tokens poker chips
 * @param hand two cards in hand
 * @return the number corresponding with decision - for fold 0 for check/call
 */
int Player::MakeDecision(int tokens, std::pair<Card *, Card *> hand, int pot_amount, int amount_to_stay_in,
                         int amount_already_in, int amount_players_not_yet_folded) {
    int n = (rand() % 3) - 1;

    if (tokens == 0 || amount_players_not_yet_folded == 1 || amount_to_stay_in < 50) {
        return 0;
    }
    if (n==1) {
        n = n * 5 + 50;
    }
    return n;
}

/**
 * New Round, reset player
 */
void Player::Reset() {
    SetReadyForNextCount(false);
    SetAmountPaid(0);
    SetPairOfCardsInHand(nullptr, nullptr);
    SetFolded(false);
}

// Getters
int Player::GetTokens() const{
    if (this!=nullptr) {
        return Player::tokens_;
    }
    return -1;
}
std::pair<Card*, Card*> Player::GetPairOfCardsInHand() const{
    return Player::pairOfCardsInHand_;
}
int Player::GetAmountPaid() {
    return Player::amoundAlreadyPaid_;
}
bool Player::IsReadyForNextCount() const {
    return Player::isReadyForNextCount_;
}
bool Player::HasFolded() const {
    return Player::hasFolded_;
}
std::string Player::GetName() const {
    return Player::name_;
}

// Setters
void Player::SetTokens(int t) {
    Player::tokens_ = t;
}
void Player::SetPairOfCardsInHand(Card *card1, Card *card2) {
    Player::pairOfCardsInHand_ = std::make_pair(card1, card2);
}
void Player::SetAmountPaid(int pay) {
    Player::amoundAlreadyPaid_ = pay;
}
void Player::SetReadyForNextCount(bool d) {
    Player::isReadyForNextCount_ = d;
}
void Player::SetFolded(bool d) {
    Player::hasFolded_ = d;
}


