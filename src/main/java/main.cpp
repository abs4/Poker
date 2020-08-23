#include <iostream>
#include "Card.h"
#include "Deck.h"
#include <stack>
#include <tuple>
#include "GameEngine.h"
#include "CardsToValueConverter.h"
int main() {
    GameEngine g = GameEngine();
    std::cout << "How many other users do you want to play with?" << std::endl;
    int num;
    std::cin >> num;
    std::cout << "What's your name?" << std::endl;
    std::string str;
    std::cin >> str;
    g.GameSetUp(num + 1, str);
    while (g.GetNumOfPlayers() > 1) {
        g.PlayRound();
        g.ResetRound();
    }
}
