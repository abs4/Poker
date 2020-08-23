//
// Created by Alex Szymanski on 4/17/18.
//

#ifndef UNTITLED_GAMEENGINE_H
#define UNTITLED_GAMEENGINE_H

#include "Deck.h"
#include "Player.h"
#include <vector>
class GameEngine {
    
public:
    void GameSetUp(unsigned num_of_players, std::string name); // Only to be used once
    void PlayRound();

    // Functions that make up a round of poker
    void DealCards();
    void SetBlindsAndAddBlindsToPot();
    void PlayerTurn(int choice); // called four times in round
    void CardFlop();
    void CardTurn();
    void CardRiver();
    void DistributeWealth();  // Rewards the winners with the spoils
    int DistributeWealthCalculateHelper(int amountPaid);


    void ResetRound(); // Reset round

    // Getters
    std::vector<Player> GetPlayersInGame();
    int GetNumOfPlayers();
    Deck GetDeck();
    int GetPot();
    std::vector<Card*> GetTable();
    std::vector<int> GetWinnings();
    int GetAmountNotYetFolded();
    std::vector<int> GetWinningPlayers();
    std::vector<std::string> GetConsole();
    int GetCount();
    int GetPosition();
    bool GetSettled();
    int GetUserAmountToCall();

    // Setters
    void SetCount(int amount);
    void SetSettled(bool flag);

private:
    int SMALL_BLIND = 50;
    int BIG_BLIND = 100;
    int pot_;
    int blindLocation_ = 0;
    int count_ = 0; //makes sure that turn function is done at least as many times as there are players still in the game
    std::vector<Player> playersInGame_;
    Deck gameDeck_;
    int numberOfPlayersLeft_ = 0;
    int currentAmountToPay_;
    std::vector<Card*> table_;
    std::vector<int> winnings_;
    int amount_players_not_yet_folded_;
    std::vector<int> winningPlayers_;
    std::vector<std::string> console;
    bool settled = false;
    int players_whose_turn = (blindLocation_ + 2) % numberOfPlayersLeft_;
};

#endif //UNTITLED_GAMEENGINE_H
