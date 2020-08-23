//
// Created by Alex Szymanski on 4/17/18.
//

#include "GameEngine.h"
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "CardsToValueConverter.h"
#include <vector>
#include <iostream>


/**
 * Sets up a game of poker, only need to be called once
 * @param num_of_players the amount of players partaking
 */
void GameEngine::GameSetUp(unsigned num_of_players, std::string name) {
    //Create and set Deck
    std::string gameSetUpBorder = "-----------------------------";
    std::string gameSetUpHeader = "S E T T I N G   G A M E   U P";

    console.push_back(gameSetUpBorder);
    console.push_back(gameSetUpHeader);
    console.push_back(gameSetUpBorder);

    GameEngine::numberOfPlayersLeft_ = num_of_players;
    GameEngine::gameDeck_ = Deck();
    gameDeck_.addCardsToDeck();
    gameDeck_.shuffleDeck();

    // Create num of players and set those players to a vector of players
    GameEngine::numberOfPlayersLeft_ = num_of_players;
    GameEngine::playersInGame_ = std::vector<Player>();
    playersInGame_.push_back(Player(name));
    console.push_back(name + " joins the game.");
    for (int i = 0; i < num_of_players - 1; i++) {
        std::string temp = "AI46" + std::to_string(i+1);
        console.push_back(temp + " joins the game.");
        playersInGame_.push_back(Player("AI46" + std::to_string(i+2)));
    }

    // Set turn table
    blindLocation_ = rand() % num_of_players;
    pot_ = 0;
    currentAmountToPay_ = 0;
    count_ = 0;
    amount_players_not_yet_folded_ = num_of_players;
}

/**
 * deals the amount of cards to each of the num_of_players
 * @param num_of_players the number of players partaking
 * @return true if successful, false if not enough cards left in deck to deal
 */
void GameEngine::DealCards() {
    std::string dealingHeaderOne = "*Dealing Cards*";
    console.push_back(dealingHeaderOne);
    if (GameEngine::gameDeck_.size() < (numberOfPlayersLeft_ * 2) + 5 ) { // use a new deck if not enough cards (2 for each card in hand + 5 on table)
        gameDeck_.clearCardsFromDeck();
        gameDeck_.addCardsToDeck();
        gameDeck_.shuffleDeck();
    }
    for (int i = 0; i < GameEngine::playersInGame_.size(); i++) {
        playersInGame_[(i + blindLocation_) % numberOfPlayersLeft_].SetPairOfCardsInHand(gameDeck_.drawCard(),
                                                                                   gameDeck_.drawCard());
    }
}

/**
 * Determines order of turns and who is starting and who is a blind
 * @param num_of_players - number of players left
 */
void GameEngine::SetBlindsAndAddBlindsToPot() {
    std::string blindsHeaderOne = "*Setting Blinds";
    std::string blindsHeaderTwo = "(small = 50; big = 100)*";
    if (!playersInGame_.empty()) {
    console.push_back(blindsHeaderOne);
    console.push_back(blindsHeaderTwo);
    currentAmountToPay_ = BIG_BLIND; // set current amount to pay for each player to be big blind

    for (int i = 0; i < numberOfPlayersLeft_; i++) {
        playersInGame_[i].SetAmountPaid(0);
    }
    std::string smallBlindTxt = playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetName() + "($"
                + std::to_string(playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetTokens()) + ") is Small blind.";
    console.push_back(smallBlindTxt);
    
    std::string bigBlindTxt = playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetName() + "($"
        + std::to_string(playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetTokens()) + ") is Big blind.";
    console.push_back(bigBlindTxt);

    
    // Small blind
    if (playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetTokens() >= GameEngine::SMALL_BLIND) {
        pot_+= SMALL_BLIND;
        playersInGame_[(blindLocation_) % numberOfPlayersLeft_].SetAmountPaid(SMALL_BLIND);

        playersInGame_[(blindLocation_) % numberOfPlayersLeft_].SetTokens(
                playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetTokens() - SMALL_BLIND);
    } else {
        pot_+= playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetTokens();
        playersInGame_[(blindLocation_) % numberOfPlayersLeft_].SetAmountPaid(
                playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetTokens());
        playersInGame_[(blindLocation_) % numberOfPlayersLeft_].SetTokens(0);
        amount_players_not_yet_folded_--;
        playersInGame_[(blindLocation_) % numberOfPlayersLeft_].SetFolded(true);
    }
    // Big Blind
    if (playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetTokens() >= GameEngine::BIG_BLIND) {
        pot_+= BIG_BLIND;
        playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].SetAmountPaid(BIG_BLIND);
        playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].SetTokens(
                playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetTokens() - BIG_BLIND);
    } else {
        pot_+= playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetTokens();
        playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].SetAmountPaid(
                playersInGame_[(blindLocation_) + 1 % numberOfPlayersLeft_].GetTokens());
        playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].SetTokens(0);
        amount_players_not_yet_folded_--;
        playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].SetFolded(true);
    }
    std::string smallBlindTxtAfter = playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetName() + " now has $" + std::to_string(playersInGame_[(blindLocation_) % numberOfPlayersLeft_].GetTokens()) + ".";
    console.push_back(smallBlindTxtAfter);

    std::string bigBlindTxtAfter = playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetName() + " now has $" + std::to_string(playersInGame_[(blindLocation_ + 1) % numberOfPlayersLeft_].GetTokens()) + ".";
    console.push_back(bigBlindTxtAfter);
    }
}

void GameEngine::PlayerTurn(int choice) {
    if((numberOfPlayersLeft_ == 0 || amount_players_not_yet_folded_ <= 1)) {
        return;
    }
        if ((!settled || count_ <numberOfPlayersLeft_)) {
    
    
        int temp = -1;
        if (players_whose_turn == 0 && !playersInGame_[0].HasFolded()) {
            std::cout << "You have a " << playersInGame_[0].GetPairOfCardsInHand().first->getInfo() << " and a "
                      << playersInGame_[0].GetPairOfCardsInHand().second->getInfo()<< std::endl;
            std::cout << "The pot is " << pot_ << std::endl;
            std::cout << "The amount you would have to pay is " << currentAmountToPay_ - playersInGame_[0].GetAmountPaid() << std::endl;

            std::cout << "What do you want to do? - 1 for fold 0 for call + for raise" << std::endl;
            temp = choice;
        } else {
            temp = playersInGame_[players_whose_turn].MakeDecision(playersInGame_[players_whose_turn].GetTokens(),
                                                                   playersInGame_[players_whose_turn].GetPairOfCardsInHand(),
                                                                   pot_,
                                                                   currentAmountToPay_,
                                                                   playersInGame_[players_whose_turn].GetAmountPaid(),
                                                                   amount_players_not_yet_folded_);
        }
        if (playersInGame_[players_whose_turn].HasFolded()) {
            std::string alreadyFoldedTxt = playersInGame_[players_whose_turn].GetName() + "($"
            + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ") has already folded.";
            console.push_back(alreadyFoldedTxt);
            std::cout << alreadyFoldedTxt << std::endl;
        } else {
            if (temp < 0) {
                std::string foldsTxt = playersInGame_[players_whose_turn].GetName() + "($"
                + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ") Folds.";
                console.push_back(foldsTxt);
                std::cout << foldsTxt << std::endl;
                amount_players_not_yet_folded_--;
                playersInGame_[players_whose_turn].SetFolded(true);
            } else if (temp == 0) {
                std::string callTxt = playersInGame_[players_whose_turn].GetName() + "($"
                + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ") Calls/Checks.";
                console.push_back(callTxt);
                std::cout << callTxt << std::endl;
                playersInGame_[players_whose_turn].SetReadyForNextCount(true);
                if (playersInGame_[players_whose_turn].GetAmountPaid() <
                    currentAmountToPay_) { // need to pay in order to check
                    if (playersInGame_[players_whose_turn].GetTokens() >=
                        (currentAmountToPay_ - playersInGame_[players_whose_turn].GetAmountPaid())) {

                        pot_ += (currentAmountToPay_ - playersInGame_[players_whose_turn].GetAmountPaid());
                        playersInGame_[players_whose_turn].SetTokens(
                                playersInGame_[players_whose_turn].GetTokens() -
                                (currentAmountToPay_ -
                                 playersInGame_[players_whose_turn].GetAmountPaid()));
                        playersInGame_[players_whose_turn].SetAmountPaid(currentAmountToPay_);


                    } else {

                        pot_ += playersInGame_[players_whose_turn].GetTokens();
                        playersInGame_[players_whose_turn].SetAmountPaid(
                                playersInGame_[players_whose_turn].GetAmountPaid() +
                                playersInGame_[players_whose_turn].GetTokens());
                        playersInGame_[players_whose_turn].SetTokens(0);
                    }
                }
                std::string nowHasTxt = playersInGame_[players_whose_turn].GetName() + " now has $"
                + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ".";
                console.push_back(nowHasTxt);
                std::cout << nowHasTxt << std::endl;

            } else {
                std::string dotDotDotTxt = playersInGame_[players_whose_turn].GetName() + " ...";
                console.push_back(dotDotDotTxt);
                std::cout << dotDotDotTxt << std::endl;
                if (playersInGame_[players_whose_turn].GetTokens() != 0) {
                    if (temp + currentAmountToPay_ > playersInGame_[players_whose_turn].GetTokens()) {
                        std::string allInTxt = playersInGame_[players_whose_turn].GetName() + "($"
                        + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ") Goes ALL in with $"
                        + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ".";
                        console.push_back(allInTxt);
                        std::cout << allInTxt << std::endl;
                        if (playersInGame_[players_whose_turn].GetTokens() +
                                    playersInGame_[players_whose_turn].GetAmountPaid() > currentAmountToPay_) {
                            for (int j = 0; j < playersInGame_.size(); ++j) {
                                playersInGame_[j].SetReadyForNextCount(false);
                            }
                        }
                        pot_ += playersInGame_[players_whose_turn].GetTokens();
                        playersInGame_[players_whose_turn].SetAmountPaid(
                                playersInGame_[players_whose_turn].GetAmountPaid() +
                                playersInGame_[players_whose_turn].GetTokens());


                        currentAmountToPay_ = std::max(playersInGame_[players_whose_turn].GetAmountPaid(),
                                                      currentAmountToPay_);
                        playersInGame_[players_whose_turn].SetTokens(0);
                    } else {
                        for (int j = 0; j < playersInGame_.size(); ++j) {
                            playersInGame_[j].SetReadyForNextCount(false);
                        }
                        std::string raisesTxt = playersInGame_[players_whose_turn].GetName() + "($"
                        + std::to_string(playersInGame_[players_whose_turn].GetTokens()) + ") raises $" + std::to_string(temp) + ".";
                        console.push_back(raisesTxt);
                        std::cout << raisesTxt << std::endl;
                         pot_ += temp + (currentAmountToPay_ - playersInGame_[players_whose_turn].GetAmountPaid());
                        int t = currentAmountToPay_;
                        currentAmountToPay_ += (temp);


                        playersInGame_[players_whose_turn].SetTokens(
                                playersInGame_[players_whose_turn].GetTokens() -
                                (temp + (t -
                                         playersInGame_[players_whose_turn].GetAmountPaid())));

                        playersInGame_[players_whose_turn].SetAmountPaid(t + temp);
                    }
                }
            }
        }
    
        playersInGame_[players_whose_turn].SetReadyForNextCount(true);
        settled = true;
        for (int j = 0; j < playersInGame_.size(); ++j) {
            if (!playersInGame_[j].IsReadyForNextCount()) {
                settled = false;
                break;
            }
        }
        players_whose_turn = (players_whose_turn + 1) % numberOfPlayersLeft_;
        count_++;
        std::cout << std::endl;
    }
}


int GameEngine::DistributeWealthCalculateHelper(int amountPaid) {
    int amountEarned = 0;
    for (int i = 0; i < playersInGame_.size(); i++) {
        if (playersInGame_[i].GetAmountPaid() <= amountPaid) {
            amountEarned = amountEarned + playersInGame_[i].GetAmountPaid();
        } else if (playersInGame_[i].GetAmountPaid() > amountPaid && playersInGame_[i].GetAmountPaid() != INT_MAX) {
            amountEarned = amountEarned + amountPaid;
        }
    }
    return amountEarned;
}

/**
 * distributes wealth after round is over
 * @param num_of_players to consider when distributing wealth
 * @return the amount of players remaining
 */
void GameEngine::DistributeWealth() {
    std::string distWealthTxt = "*Rewarding the Spoils*";
    console.push_back(distWealthTxt);
    CardsToValueConverter cardsToValueConverter = CardsToValueConverter();

    for (int i = 0; i < playersInGame_.size(); i++) {
        std::vector<Card*> temp;
        temp.push_back(playersInGame_[i].GetPairOfCardsInHand().first);
        temp.push_back(playersInGame_[i].GetPairOfCardsInHand().second);
        for (int j = 0; j < table_.size(); j++) {
            temp.push_back(table_[j]);
        }
        winnings_.push_back(cardsToValueConverter.ConvertCardsToValue(temp)); // vector of values
        std::string handStrenghtTxt = "";
        if (!playersInGame_[i].HasFolded()) {
            handStrenghtTxt = cardsToValueConverter.HandStrength(winnings_[i]);
        } else {
            handStrenghtTxt = " is not in this round.";
        }
        console.push_back(playersInGame_[i].GetName() + " had a "+ handStrenghtTxt + ".");
    }
    int amountOfPeopleFullyPaid = 0;
    for (int q = 0; q < playersInGame_.size(); ++q) {
        if (playersInGame_[q].GetAmountPaid() >= currentAmountToPay_) {
            amountOfPeopleFullyPaid++;
        }
    }
    int WinningAmountValue = 0;
    while (1) {
        int max = 0;
        int maxIndex = 0;
        std::vector<int> winnersIndexPositions(1,0);
        int numberOfWinners = 1;
        for (int k = 0; k < playersInGame_.size(); ++k) {
            if (winnings_[k] > max && !playersInGame_[k].HasFolded()) {
                max = winnings_[k];
                maxIndex = k;
                winnersIndexPositions[0] = k;
            } else if (winnings_[k] == max && !playersInGame_[k].HasFolded()) {
                numberOfWinners++;
                winnersIndexPositions.push_back(k);
            }
        }
        int earned = DistributeWealthCalculateHelper(playersInGame_[maxIndex].GetAmountPaid());
        if ((currentAmountToPay_ <= playersInGame_[maxIndex].GetAmountPaid() && numberOfWinners == 1 ) || (amount_players_not_yet_folded_ == 1)) { // Case 1
            int temp = playersInGame_[winnersIndexPositions[maxIndex]].GetTokens();
            playersInGame_[maxIndex].SetTokens(
                    playersInGame_[maxIndex].GetTokens() + pot_);
            if (playersInGame_[maxIndex].GetTokens() - temp > 0) {
                console.push_back(playersInGame_[maxIndex].GetName() + " recieved " + std::to_string(playersInGame_[maxIndex].GetTokens() - temp) + " tokens.");
            }
            pot_ = 0;
            break;
        } else if (currentAmountToPay_ > playersInGame_[maxIndex].GetAmountPaid() && numberOfWinners == 1) { // CASE 2
            int temp = playersInGame_[winnersIndexPositions[maxIndex]].GetTokens();
            playersInGame_[maxIndex].SetTokens(earned);
                    console.push_back(playersInGame_[maxIndex].GetName() + " recieved " + std::to_string(playersInGame_[maxIndex].GetTokens() - temp) + " tokens.");
            pot_ -= earned;
            playersInGame_[maxIndex].SetAmountPaid(INT_MAX);
            playersInGame_[maxIndex].SetFolded(true);
            amount_players_not_yet_folded_--;
        } else if (currentAmountToPay_ <= playersInGame_[maxIndex].GetAmountPaid() && numberOfWinners > 1) { // CASE 3
            for (int r = 0; r < numberOfWinners; ++r) {
                int temp = playersInGame_[winnersIndexPositions[r]].GetTokens();
                playersInGame_[winnersIndexPositions[r]].SetTokens(playersInGame_[winnersIndexPositions[r]].GetTokens()
                                                                   + pot_ / numberOfWinners);
                console.push_back(playersInGame_[r].GetName() + " recieved " + std::to_string(playersInGame_[r].GetTokens() - temp) + " tokens.");
            }
            pot_ = 0;
            break;
        } else { // Muliple winners that didn't fully pay CASE 4
            for (int r = 0; r < numberOfWinners; ++r) {
                int temp = playersInGame_[winnersIndexPositions[r]].GetTokens();
                playersInGame_[winnersIndexPositions[r]].SetTokens(playersInGame_[winnersIndexPositions[r]].GetTokens() + (earned) / numberOfWinners);
                console.push_back(playersInGame_[r].GetName() + " recieved " + std::to_string(playersInGame_[r].GetTokens() - temp) + " tokens.");

                playersInGame_[winnersIndexPositions[r]].SetAmountPaid(INT_MAX);
                playersInGame_[winnersIndexPositions[r]].SetFolded(true);
                amount_players_not_yet_folded_--;
            }
            pot_ -= (earned);
        }
        if (!winnings_.empty()) {
            winnings_[maxIndex] = -1;
            
        }
        for (int i = 0; i < winnersIndexPositions.size() - 1; ++i) {
            winnersIndexPositions.pop_back();
            winnings_[winnersIndexPositions[i]] = -1;
        }
        if (max > WinningAmountValue) {
            WinningAmountValue = max;
        }
    }
    for (int k = 0; k < numberOfPlayersLeft_; k++) {
        
    }
}

/**
 * simple flip the first three cards to be faced up
 */
void GameEngine::CardFlop() {
    table_.push_back(gameDeck_.drawCard());
    table_.push_back(gameDeck_.drawCard());
    table_.push_back(gameDeck_.drawCard());
    if (amount_players_not_yet_folded_ <= 1) {
        return;
    }
    std::string potTxt = "The pot is now $" + std::to_string(pot_) + ".";
    console.push_back(potTxt);
    std::string flopBorder = "================";
    std::string flopHeader = "    F L O P     ";
    console.push_back(flopBorder);
    console.push_back(flopHeader);
    console.push_back(flopBorder);
    
    std::string infoTxt = "STATE OF TABLE :" + table_[0]->getInfo() + " : " + table_[1]->getInfo() + " : "
    + table_[2]->getInfo();
   // console.push_back(infoTxt);
    std::cout << flopBorder << std::endl;
    std::cout << flopHeader<<  std::endl;
    std::cout << flopBorder << std::endl;
    std::cout << "The pot is currently $" << pot_ << "." << std::endl;
    std::cout << "STATE OF TABLE :" << table_[0]->getInfo() << " : " << table_[1]->getInfo() << " : "
                                                            << table_[2]->getInfo() << std::endl;
    std::cout << std::endl;

}
/**
 * simple flip 4th card up
 */
void GameEngine::CardTurn() {
    table_.push_back(gameDeck_.drawCard());
    if (amount_players_not_yet_folded_ <= 1) {
        return;
    }
    std::string potTxt = "The pot is now $" + std::to_string(pot_) + ".";
    console.push_back(potTxt);
    std::string turnBorder = "================";
    std::string turnHeader = "    T U R N     ";
    console.push_back(turnBorder);
    console.push_back(turnHeader);
    console.push_back(turnBorder);
    std::cout << turnBorder<< std::endl;
    std::cout << turnHeader <<  std::endl;
    std::cout << turnBorder << std::endl;
    std::cout << "The pot is currently $" << pot_ << "." << std::endl;
    std::cout << "STATE OF TABLE: " << table_[0]->getInfo() << " : " << table_[1]->getInfo() << " : "
              << table_[2]->getInfo() << " : " << table_[3]->getInfo() << std::endl;
    std::cout << std::endl;
}
/**
 * simple flip 5th card up
 */
void GameEngine::CardRiver() {
    table_.push_back(gameDeck_.drawCard());
    if (amount_players_not_yet_folded_ <= 1) {
        return;
    }
    std::string potTxt = "The pot is now $" + std::to_string(pot_) + ".";
    console.push_back(potTxt);
    std::string riverBorder = "================";
    std::string riverHeader = "   R I V E R    ";
    console.push_back(riverBorder);
    console.push_back(riverHeader);
    console.push_back(riverBorder);
    std::cout << riverBorder<< std::endl;
    std::cout << riverHeader <<  std::endl;
    std::cout << riverBorder << std::endl;
    std::cout << "The pot is currently $" << pot_ << "." << std::endl;
    std::cout << "STATE OF TABLE: " << table_[0]->getInfo() << " : " << table_[1]->getInfo() << " : "
              << table_[2]->getInfo() << " : " << table_[3]->getInfo() << " : " << table_[4]->getInfo() << std::endl;
    std::cout << std::endl;
}

/**
 * Function made of many helper functions
 * @param num_of_players left before starting the function
 * @return number of players remaining after function call
 */
void GameEngine::PlayRound() {

    DealCards();
    SetBlindsAndAddBlindsToPot();
    std::cout << "===============" << std::endl;
    std::cout << "  R O U N D " << std::endl;
    std::cout << "===============" << std::endl;
    std::cout << "The pot is currently $" << pot_ << "." << std::endl;
    PlayerTurn(-1);
    CardFlop();
    PlayerTurn(-1);
    CardTurn();
    PlayerTurn(-1);
    CardRiver();
    PlayerTurn(-1);
    DistributeWealth();
}

/**
 * function that makes it possible for the next round to begin
 */
void GameEngine::ResetRound() {
    std::string resetBorderTxt = "===============";
    std::string resetHeaderTxt = "   R E S E T   ";
    console.push_back(resetBorderTxt);
    console.push_back(resetHeaderTxt);
    console.push_back(resetBorderTxt);
    pot_ = 0;
    for (int i = 0; i < numberOfPlayersLeft_; i++) {
        if (playersInGame_[i].GetTokens() <= 0) {
            numberOfPlayersLeft_--;
            std::string playerOutTxt = "Player " + playersInGame_[i].GetName() + " is out.";
            std::string playerRemainTxt = std::to_string(numberOfPlayersLeft_) + " Players remain!";
            console.push_back(playerOutTxt);
            console.push_back(playerRemainTxt);
            playersInGame_.erase(playersInGame_.begin() + i);
            i--;
        }
    }
    for (int j = 0; j < numberOfPlayersLeft_; j++) {
        playersInGame_[j].Reset();
    }
    blindLocation_++;
    while (!table_.empty()) {
        table_.pop_back();
    }
    while (!winnings_.empty()) {
        winnings_.pop_back();
    }
    amount_players_not_yet_folded_ = numberOfPlayersLeft_;
    int total = 0;
    for (int k = 0; k < playersInGame_.size(); ++k) {
        total += playersInGame_[k].GetTokens();
    }
}

// Getters
std::vector<Player> GameEngine::GetPlayersInGame() {
    return GameEngine::playersInGame_;
}
int GameEngine::GetNumOfPlayers() {
    return GameEngine::numberOfPlayersLeft_;
}
Deck GameEngine::GetDeck() {
    return GameEngine::gameDeck_;
}
int GameEngine::GetPot() { // Not that kind of pot
    return pot_;
}
std::vector<Card*> GameEngine::GetTable() {
    return table_;
}
std::vector<int> GameEngine::GetWinnings() {
    return winnings_;
}
int GameEngine::GetAmountNotYetFolded() {
    return amount_players_not_yet_folded_;
}
std::vector<int> GameEngine::GetWinningPlayers() {
    return winningPlayers_;
}
std::vector<std::string> GameEngine::GetConsole() {
    return console;
}
int GameEngine::GetCount() {
    return count_;
}
bool GameEngine::GetSettled() {
    return settled;
}
int GameEngine::GetPosition() {
    return players_whose_turn;
}
int GameEngine::GetUserAmountToCall() {
    return currentAmountToPay_ - playersInGame_[0].GetAmountPaid();
}

// Setters
void GameEngine::SetCount(int amount) {
    count_ = amount;
}
void GameEngine::SetSettled(bool flag) {
    settled = flag;
}
