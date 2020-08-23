#include "ofApp.h"
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
    g = GameEngine();
       table.load("/Users/alexanderszymanski/Desktop/126P/table.png");
       gameBox.load("/Users/alexanderszymanski/Desktop/126P/gameBox.png");
       fold.load("/Users/alexanderszymanski/Desktop/126P/Fold.png");
       call.load("/Users/alexanderszymanski/Desktop/126P/Call.png");
       raise.load("/Users/alexanderszymanski/Desktop/126P/Raise.png");
       poker_chip.load("/Users/alexanderszymanski/Desktop/126P/PokerLogo.png");
       help_screen.load("/Users/alexanderszymanski/Desktop/126P/helpScreen.png");
       poker_chip_sound.load("/Users/alexanderszymanski/Desktop/126P/pokerChipSound.wav");
       god_father_sound.load("/Users/alexanderszymanski/Desktop/126P/godFather.mp3");
       god_father_sound.setLoop(true);
       god_father_sound.setVolume(1);
       god_father_sound.play();
       
       ofSetFullscreen(true);
       ofSetBackgroundColor(135,205,250);
}
//--------------------------------------------------------------
void ofApp::update(){
      if (current_state_ == OPENING_SCREEN || (g.GetNumOfPlayers() > 1 && g.GetPlayersInGame()[0].GetName() == "USER")) {
            if (deal_cards_and_blinds) {
                g.DealCards();
                g.SetBlindsAndAddBlindsToPot();
                deal_cards_and_blinds = false;
                should_play_round = true;
                draw_cards_down = true;
                draw();
            }
            else if (should_play_round) {
                    if (!(g.GetNumOfPlayers() == 0 || g.GetAmountNotYetFolded() <= 1) && (!g.GetSettled() || g.GetCount() < g.GetNumOfPlayers())) {
                        if (g.GetPosition() == 0 && !g.GetPlayersInGame()[0].HasFolded()) {
                            if (decision < - 1) {
                                current_state_ = DECISION;
                                 return;
                            } else {
                                g.PlayerTurn(decision);
                                decision = -2;
                            }
                        } else if (!g.GetPlayersInGame()[g.GetPosition()].HasFolded()){
                            g.PlayerTurn(-1);
                        } else {
                            g.PlayerTurn(-1);
                        }
                    } else {
                        should_play_round = false;
                        g.SetCount(0);
                        g.SetSettled(false);
                        should_flop = true;
                    }
                if (g.GetPlayersInGame()[0].GetTokens() == 0) {
                    decision = 0;
                    
                }
            }
            else if (should_flop) {
                g.CardFlop();
                draw_cards_down = false;
                draw_cards_flop = true;
                should_flop = false;
                should_play_round_after_flop = true;
            }
            else if (should_play_round_after_flop) {
                    if (!(g.GetNumOfPlayers() == 0 || g.GetAmountNotYetFolded() <= 1) && (!g.GetSettled() || g.GetCount() < g.GetNumOfPlayers())) {
                        if (g.GetPosition() == 0 && !g.GetPlayersInGame()[0].HasFolded()) {
                            if (decision < - 1) {
                                current_state_ = DECISION;
                                return;
                            } else {
                                g.PlayerTurn(decision);
                                decision = -2;
                            }
                        } else if (!g.GetPlayersInGame()[g.GetPosition()].HasFolded()){
                            g.PlayerTurn(-1);
                        } else {
                            g.PlayerTurn(-1);
                        }
                    } else {
                        should_play_round_after_flop = false;
                        g.SetCount(0);
                        g.SetSettled(false);
                        should_turn = true;
                    }
                if (g.GetPlayersInGame()[0].GetTokens() == 0) {
                    decision = 0;
                }
            }
            else if (should_turn) {
                g.CardTurn();
                draw_cards_flop = false;
                draw_cards_turn = true;
                should_turn = false;
                should_play_round_after_turn = true;
            }
            else if (should_play_round_after_turn) {
                if (!(g.GetNumOfPlayers() == 0 || g.GetAmountNotYetFolded() <= 1) && (!g.GetSettled() || g.GetCount() < g.GetNumOfPlayers())) {
                    if (g.GetPosition() == 0 && !g.GetPlayersInGame()[0].HasFolded()) {
                        if (decision < - 1) {
                            current_state_ = DECISION;
                            return;
                        } else {
                            g.PlayerTurn(decision);
                            decision = -2;
                        }
                    } else if (!g.GetPlayersInGame()[g.GetPosition()].HasFolded()){
                        g.PlayerTurn(-1);
                    } else {
                        g.PlayerTurn(-1);
                    }
                } else {
                    should_play_round_after_turn = false;
                    g.SetCount(0);
                    g.SetSettled(false);
                    should_river = true;
                }
                if (g.GetPlayersInGame()[0].GetTokens() == 0) {
                    decision = 0;
                }
            }
            else if (should_river) {
                g.CardRiver();
                draw_cards_turn = false;
                draw_cards_river = true;
                should_river = false;
                should_play_round_after_river = true;
            }
            else if (should_play_round_after_river) {
                if (!(g.GetNumOfPlayers() == 0 || g.GetAmountNotYetFolded() <= 1) && (!g.GetSettled() || g.GetCount() < g.GetNumOfPlayers())) {
                    if (g.GetPosition() == 0 && !g.GetPlayersInGame()[0].HasFolded()) {
                        if (decision < - 1) {
                            current_state_ = DECISION;
                            return;
                        } else {
                            g.PlayerTurn(decision);
                            decision = -2;
                        }
                    } else if (!g.GetPlayersInGame()[g.GetPosition()].HasFolded()){
                        g.PlayerTurn(-1);
                    } else {
                        g.PlayerTurn(0);
                    }
                } else {
                    should_play_round_after_river = false;
                    should_distribute_wealth = true;
                    g.SetCount(0);
                    g.SetSettled(false);
                }
            } else if (should_distribute_wealth) {
                g.DistributeWealth();
                poker_chip_sound.play();
                draw_cards_turn = false;
                draw_cards_river = true;
                should_distribute_wealth = false;
                should_reset = true;
            }
            else if (should_reset) {
                g.ResetRound();
                draw_cards_river = false;
                should_reset = false;
                deal_cards_and_blinds = true;
            }
        } else {
            current_state_ = FINISHED;
        }
        draw();
    }

//--------------------------------------------------------------
void ofApp::drawWords(std::string msg) {
    ofDrawBitmapString(msg ,ofGetWidth() - ofGetWidth() / 2.5 ,ofGetHeight() - ofGetHeight() / 2.7);
}

// checks states to see what to draw
void ofApp::draw(){
    if (current_state_ == OPENING_SCREEN) {
        drawOpeningScreen();
    }
    else if(current_state_ == IN_PROGRESS) {
        drawTable();
        drawCards();
        if (g.GetPlayersInGame()[0].GetPairOfCardsInHand().first != nullptr) {
            drawHand();
        }
        drawPlayers();
        drawConsole();
        drawPokerChipLogo();
        drawPot();
    }
    else if(current_state_ == FINISHED) {
        drawGameOver();
    }
    else if(current_state_ == DECISION) {
        drawGameDecision();
        drawCards();
        if (g.GetPlayersInGame()[0].GetPairOfCardsInHand().first != nullptr) {
            drawHand();
        }
        drawPot();
        drawPrintScreen();
    }
    if (should_print_help_screen) {
        drawHelpScreen();
    }
}

// Draws opening screen
void ofApp::drawOpeningScreen() {
    dog_title.load("/Users/alexanderszymanski/Desktop/126P/dogTitle.jpg");
    dog_title.draw(-100, 0);
    black_border.load("/Users/alexanderszymanski/Desktop/126P/borderBlack.png");
    black_border.draw(ofGetWindowWidth() / 3.4 + 41, ofGetWindowHeight() / 2.3 + 15);
    string opening_message = "ENTER HOW MANY OTHER PLAYERS YOU WANT TO PLAY WITH... (1 to 7)";
    ofDrawBitmapString(opening_message, ofGetWindowWidth() / 3.4 + 45, ofGetWindowHeight() / 2.3 + 35);
}

// Draws ending screen
void ofApp::drawGameOver() {
    if (g.GetPlayersInGame()[0].GetName() == "USER") {
        win_screen.load("/Users/alexanderszymanski/Desktop/126P/win.png");
        win_screen.draw(-100, -100);
    } else {
        lose_screen.load("/Users/alexanderszymanski/Desktop/126P/lose.jpg");
        lose_screen.draw(-100, -100);
    }
}

// Draws Game Decision screen
void ofApp::drawGameDecision() {
    table.draw(100, 110);
    drawPlayers();
    drawButtons();
    drawConsole();
    drawPokerChipLogo();
    string decision = "Make a decision";
    ofDrawBitmapString(decision, ofGetWindowWidth() / 3.3 + 30, ofGetWindowHeight() / 2.8 - 178);
    string amountToPayForCallTxt = "Amount to Call: $" + std::to_string(g.GetUserAmountToCall());
    ofDrawBitmapString(amountToPayForCallTxt, ofGetWindowWidth() / 3.3 + 15, ofGetWindowHeight() / 2.8 - 150);
}
// Draws playing table
void ofApp::drawTable() {
    table.draw(100, 110);
}

// Draws screen that shows quality of hand rank
void ofApp::drawHelpScreen() {
    help_screen.draw(300, 50);
}

// Draws raise screen
void ofApp::drawPrintScreen() {
    if (should_print_raise_screen) {
        border_black_two.load("/Users/alexanderszymanski/Desktop/126P/borderBlack2.png");
        border_black_two.draw(489, 249);
        ofDrawBitmapString("$" + std::to_string(raise_amount), 489, 269);
    }
}

// Draws Console
void ofApp::drawConsole() {
    gameBox.draw(ofGetWidth() - ofGetWidth() / 2.5 - 40,ofGetHeight() - ofGetHeight() / 2.7);
    ofDrawBitmapString("CONSOLE: ", ofGetWidth() - ofGetWidth() / 5 - 80,ofGetHeight() - ofGetHeight() / 2.7 + 25);
    if (g.GetConsole().size() <= 42) {
        for (int i = 0; i < g.GetConsole().size(); i++) {
            if (i < 21) {
                string temp = g.GetConsole()[i];
                ofDrawBitmapString(temp, ofGetWidth() - ofGetWidth() / 2.5 - 30,ofGetHeight() - ofGetHeight() / 2.7 + ((i + 1) * 13) + 35);
            } else {
                string temp = g.GetConsole()[i];
                ofDrawBitmapString(temp, ofGetWidth() - ofGetWidth() / 2.5 + 270,ofGetHeight() - ofGetHeight() / 2.7 + (((i - 21) + 1) * 13) + 35);
            }
        }
    } else {
        for (int i = g.GetConsole().size() - 42; i < g.GetConsole().size(); i++) {
            if (i < g.GetConsole().size() - 21) {
                string temp = g.GetConsole()[i];
                ofDrawBitmapString(temp, ofGetWidth() - ofGetWidth() / 2.5 - 30,ofGetHeight()
                                   - ofGetHeight() / 2.7 + ((i - (g.GetConsole().size() - 42)) + 1) * 13 + 35);
            } else {
                string temp = g.GetConsole()[i];
                ofDrawBitmapString(temp, ofGetWidth() - ofGetWidth() / 2.5 + 270,ofGetHeight()
                                   - ofGetHeight() / 2.7 + (((i - (g.GetConsole().size() - 42)) - 21) + 1) * 13 + 35);
            }
        }
    }
}


// Draws decision buttons
void ofApp::drawButtons() {
    fold.draw(ofGetWindowWidth() / 3.3 - 160, ofGetWindowHeight() / 2.8 + 30);
    call.draw(ofGetWindowWidth() / 3.3 + 20, ofGetWindowHeight() / 2.8 + 30);
    raise.draw(ofGetWindowWidth() / 3.3 + 200, ofGetWindowHeight() / 2.8 + 30);
}

// Draws poker logo cs126
void ofApp::drawPokerChipLogo() {
    poker_chip.draw(ofGetWindowWidth() - (ofGetWindowWidth() / 3.5), ofGetWindowHeight() / 4.5 - 30);
}
// Draws pot text
void ofApp::drawPot() {
    ofDrawBitmapString("Pot: " + std::to_string(g.GetPot()), ofGetWindowWidth() / 3.3 + 60, ofGetWindowHeight() / 2.8 - 130);
}
// Draws user hand
void ofApp::drawHand() {
    if (g.GetPlayersInGame()[0].HasFolded()) {
        fold_card_one.load("/Users/alexanderszymanski/Desktop/126P/foldCard.png");
        fold_card_two.load("/Users/alexanderszymanski/Desktop/126P/foldCard.png");
        fold_card_one.draw((ofGetWidth() * 2) / (ofGetWidth() * 8) + 50, (ofGetHeight() - 200));
        fold_card_two.draw((ofGetWidth() * 2) / (ofGetWidth() * 8) + 350, (ofGetHeight() - 200));
        ofDrawBitmapString("  Folded.", ofGetWidth() * 2 / (ofGetWidth() * 8) + 302, ofGetHeight() - 225);
    } else {
        if ((int)(g.GetPlayersInGame()[0].GetPairOfCardsInHand().first->getSuit() % 2 == 1)) {
            card_hand_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRedHand.png");
        } else {
            card_hand_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlackHand.png");
        }
        if ((int)(g.GetPlayersInGame()[0].GetPairOfCardsInHand().second->getSuit() % 2 == 1)) {
            card_hand_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRedHand.png");
        } else {
            card_hand_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlackHand.png");
        }
        card_hand_one.draw((ofGetWidth() * 2) / (ofGetWidth() * 8) + 50, (ofGetHeight() - 200));
        card_hand_two.draw((ofGetWidth() * 2) / (ofGetWidth() * 8) + 350, (ofGetHeight() - 200));

        ofDrawBitmapString("Your Hand.", ofGetWidth() * 2 / (ofGetWidth() * 8) + 302, ofGetHeight() - 225);
        ofDrawBitmapString(g.GetPlayersInGame()[0].GetPairOfCardsInHand().first->getInfo(), ofGetWidth() * 2 / (ofGetWidth() * 8) + 100, ofGetHeight() - 160);
        ofDrawBitmapString(g.GetPlayersInGame()[0].GetPairOfCardsInHand().second->getInfo(),(ofGetWidth() * 2) / (ofGetWidth() * 8) + 400, ofGetHeight() - 160);
    }
}

// Draws cards on table
void ofApp::drawCards() {
    if (draw_cards_down) {
        card_one.load("/Users/alexanderszymanski/Desktop/126P/cardBack.png");
        card_two.load("/Users/alexanderszymanski/Desktop/126P/cardBack.png");
        card_three.load("/Users/alexanderszymanski/Desktop/126P/cardBack.png");
        card_four_empty.load("/Users/alexanderszymanski/Desktop/126P/cardBackEmpty.png");
        card_five_empty.load("/Users/alexanderszymanski/Desktop/126P/cardBackEmpty.png");
        card_one.draw(ofGetWidth() / 5 ,ofGetHeight() / 4 - 20);
        card_two.draw(ofGetWidth() / 5 + 100,ofGetHeight() / 4 - 20);
        card_three.draw(ofGetWidth() / 5 + 200,ofGetHeight() / 4 - 20);
        card_four_empty.draw(ofGetWidth() / 5 + 300,ofGetHeight() / 4 - 20);
        card_five_empty.draw(ofGetWidth() / 5 + 400,ofGetHeight() / 4 - 20);
    } else if (draw_cards_flop) {
        if ((int)(g.GetTable()[0]->getSuit()) % 2 == 1) {
            card_front_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[1]->getSuit()) % 2 == 1) {
            card_front_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[2]->getSuit()) % 2 == 1) {
            card_front_three.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_three.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        card_four_empty.load("/Users/alexanderszymanski/Desktop/126P/cardBackEmpty.png");
        card_five_empty.load("/Users/alexanderszymanski/Desktop/126P/cardBackEmpty.png");
        card_front_one.draw(ofGetWidth() / 5,ofGetHeight() / 4 - 20);
        card_front_two.draw(ofGetWidth() / 5 + 100,ofGetHeight() / 4 - 20);
        card_front_three.draw(ofGetWidth() / 5 + 200,ofGetHeight() / 4 - 20);
        card_four_empty.draw(ofGetWidth() / 5 + 300,ofGetHeight() / 4 - 20);
        card_five_empty.draw(ofGetWidth() / 5 + 400,ofGetHeight() / 4 - 20);
        ofDrawBitmapString(g.GetTable()[0]->getInfo(), ofGetWidth() / 5 + 10,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[1]->getInfo(), ofGetWidth() / 5 + 110,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[2]->getInfo(), ofGetWidth() / 5 + 210,ofGetHeight() / 4);

    } else if (draw_cards_turn) {
        if ((int)(g.GetTable()[0]->getSuit()) % 2 == 1) {
            card_front_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[1]->getSuit()) % 2 == 1) {
            card_front_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[2]->getSuit()) % 2 == 1) {
            card_front_three.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_three.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[3]->getSuit()) % 2 == 1) {
            card_front_four.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_four.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        card_five_empty.load("/Users/alexanderszymanski/Desktop/126P/cardBackEmpty.png");
        card_front_one.draw(ofGetWidth() / 5,ofGetHeight() / 4 - 20);
        card_front_two.draw(ofGetWidth() / 5 + 100,ofGetHeight() / 4 - 20);
        card_front_three.draw(ofGetWidth() / 5 + 200,ofGetHeight() / 4 - 20);
        card_front_four.draw(ofGetWidth() / 5 + 300,ofGetHeight() / 4 - 20);
        card_five_empty.draw(ofGetWidth() / 5 + 400,ofGetHeight() / 4 - 20);
        ofDrawBitmapString(g.GetTable()[0]->getInfo(), ofGetWidth() / 5 + 10, ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[1]->getInfo(), ofGetWidth() / 5 + 110,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[2]->getInfo(), ofGetWidth() / 5 + 210,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[3]->getInfo(), ofGetWidth() / 5 + 310,ofGetHeight() / 4);

    } else if (draw_cards_river) {
        if ((int)(g.GetTable()[0]->getSuit()) % 2 == 1) {
            card_front_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_one.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[1]->getSuit()) % 2 == 1) {
            card_front_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_two.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[2]->getSuit()) % 2 == 1) {
            card_front_three.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_three.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[3]->getSuit()) % 2 == 1) {
            card_front_four.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_four.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        if ((int)(g.GetTable()[4]->getSuit()) % 2 == 1) {
            card_front_five.load("/Users/alexanderszymanski/Desktop/126P/cardFrontRed.png");
        } else {
            card_front_five.load("/Users/alexanderszymanski/Desktop/126P/cardFrontBlack.png");
        }
        card_five_empty.load("/Users/alexanderszymanski/Desktop/126P/cardBackEmpty.png");
        card_front_one.draw(ofGetWidth() / 5,ofGetHeight() / 4 - 20);
        card_front_two.draw(ofGetWidth() / 5 + 100,ofGetHeight() / 4 - 20);
        card_front_three.draw(ofGetWidth() / 5 + 200,ofGetHeight() / 4 - 20);
        card_front_four.draw(ofGetWidth() / 5 + 300,ofGetHeight() / 4 - 20);
        card_front_five.draw(ofGetWidth() / 5 + 400,ofGetHeight() / 4 - 20);
        ofDrawBitmapString(g.GetTable()[0]->getInfo(), ofGetWidth() / 5 + 10,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[1]->getInfo(), ofGetWidth() / 5 + 110,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[2]->getInfo(), ofGetWidth() / 5 + 210,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[3]->getInfo(), ofGetWidth() / 5 + 310,ofGetHeight() / 4);
        ofDrawBitmapString(g.GetTable()[4]->getInfo(), ofGetWidth() / 5 + 410,ofGetHeight() / 4);
    }
}


// Draws all the players
void ofApp::drawPlayers() {
    red_x.load("/Users/alexanderszymanski/Desktop/126P/redX.png");

    hat.draw(ofGetWidth() / 2 - 45, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7));
    if (g.GetPlayersInGame()[0].HasFolded()) {
        red_x.draw(ofGetWidth() / 2 - 45, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7));
    }
    ofDrawBitmapString(g.GetPlayersInGame()[0].GetName(),
                       ofGetWidth() / 2 - 11, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7) + 30);
    ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[0].GetTokens()), ofGetWidth() / 2 - 50, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7) + 45);
    
    for (int i = 1; i < g.GetNumOfPlayers(); i++) {
        ofImage temp;
        temp.load("/Users/alexanderszymanski/Desktop/126P/HAT.png");
        if (i == 1) {
            temp.draw(ofGetWidth() / 5 - 5, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7));
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() / 5 - 5, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7));
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                               ofGetWidth() / 5 + 18, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7) + 30);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                               ofGetWidth() / 5  - 5, 100 + ofGetHeight() / 5 - (ofGetHeight() / 3.7) + 45);

        }
        else if (i == 2) {
            temp.draw(ofGetWidth() / 5 - (ofGetWidth() / 9) - 45, 30 + ofGetHeight() / 9 - 20);
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() / 5 - (ofGetWidth() / 9) - 45, 30 + ofGetHeight() / 9 - 20);
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                               ofGetWidth() / 5 - (ofGetWidth() / 9) - 22, 30 + ofGetHeight() / 9 + 10);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                               ofGetWidth() / 5 - (ofGetWidth() / 9) - 45, 30 + ofGetHeight() / 9 + 25);
        }
        else if (i == 3) {
            temp.draw(ofGetWidth() / 5 - (ofGetWidth() / 9) - 45 , 30 + ofGetHeight() / 2 - 5);
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() / 5 - (ofGetWidth() / 9) - 45 , 30 + ofGetHeight() / 2 - 5);
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                               ofGetWidth() / 5 - (ofGetWidth() / 9) - 22, 30 + ofGetHeight() / 2 + 25);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                               ofGetWidth() / 5 - (ofGetWidth() / 9) - 45, 30 + ofGetHeight() / 2 + 40);
        }
        else if (i == 4) {
            temp.draw(ofGetWidth() / 5 , 100 + ofGetHeight() / 2 - 30);
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() / 5 , 100 + ofGetHeight() / 2 - 30);
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                                ofGetWidth() / 5 + 23, 100 + ofGetHeight() / 2);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                                ofGetWidth() / 5 , 100 + ofGetHeight() / 2 + 15);
        }
        else if (i == 5) {
            temp.draw(ofGetWidth() / 2 - 45, 100 + ofGetHeight() / 2 - 30);
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() / 2 - 45, 100 + ofGetHeight() / 2 - 30);
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                                ofGetWidth() / 2 - 23, 100 + ofGetHeight() / 2);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                                ofGetWidth() / 2  - 45, 100 + ofGetHeight() / 2 + 15);
        }
        else if (i == 6) {
            temp.draw(ofGetWidth() - (ofGetWidth() / 2.5) + 15, 30 + ofGetHeight() / 2 - 5);
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() - (ofGetWidth() / 2.5) + 15, 30 + ofGetHeight() / 2 - 5);
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                               ofGetWidth() - (ofGetWidth() / 2.5) + 38, 30 + ofGetHeight() / 2 + 25);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                               ofGetWidth() - (ofGetWidth() / 2.5) + 15, 30 + ofGetHeight() / 2 + 40);
            
        }
        else if (i == 7) {
            temp.draw(ofGetWidth() - (ofGetWidth() / 2.5) + 20, 30 + ofGetHeight() / 9 - 20);
            if (g.GetPlayersInGame()[i].HasFolded()) {
                red_x.draw(ofGetWidth() - (ofGetWidth() / 2.5) + 20, 30 + ofGetHeight() / 9 - 20);
            }
            ofDrawBitmapString(g.GetPlayersInGame()[i].GetName(),
                               ofGetWidth() - (ofGetWidth() / 2.5) + 43, 30 + ofGetHeight() / 9 + 10);
            ofDrawBitmapString("CHIPS: $" + std::to_string(g.GetPlayersInGame()[i].GetTokens()),
                               ofGetWidth() - (ofGetWidth() / 2.5) + 20, 30 + ofGetHeight() / 9 + 25);
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int upper_key = toupper(key); // Standardize on upper case

    if (key >= '1' && key <= '7' && current_state_ == OPENING_SCREEN) {
        g.GameSetUp((key - '0') + 1, "USER");
        g.ResetRound();
        hat.load("/Users/alexanderszymanski/Desktop/126P/PLAYERHAT.png");
        current_state_ = IN_PROGRESS;
        deal_cards_and_blinds = true;
        return;
    }
    else if (upper_key == 'H' && current_state_ != FINISHED  && current_state_ != OPENING_SCREEN) {
        should_print_help_screen = !should_print_help_screen;
    }
    else if (upper_key == 'M' && current_state_ != FINISHED  && current_state_ != OPENING_SCREEN) {
        should_play_background_music = !should_play_background_music;
        if (should_play_background_music) {
            god_father_sound.setVolume(1);
        } else {
            god_father_sound.setVolume(0);
        }
    }
    else if (key >= '0' && key <= '9' && current_state_ == DECISION && should_print_raise_screen) {
        if (std::to_string(raise_amount).length() < 9) {
            std::string temp = std::to_string(raise_amount) + std::to_string(key - '0');
            istringstream ( temp ) >> raise_amount;
        }
    }
    else if (key == 127 && current_state_ == DECISION && should_print_raise_screen) {
        if (std::to_string(raise_amount).length() > 1) {
            std::string temp = std::to_string(raise_amount).substr(0, std::to_string(raise_amount).length() - 1);
            istringstream ( temp ) >> raise_amount;
        } else {
            raise_amount = 0;
        }
    }
    else if ((key == 28 || key == 10 || key == 13) && current_state_ == DECISION && should_print_raise_screen) {
        decision = raise_amount;
        should_print_raise_screen = false;
        current_state_ = IN_PROGRESS;
    }
    else if ((upper_key == 'Q') && current_state_ == DECISION && should_print_raise_screen) {
        raise_amount = 0;
        should_print_raise_screen = false;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if ((x > ofGetWindowWidth() / 3.3 - 158) && (y > ofGetWindowHeight() / 2.8 + 33) && (x < ofGetWindowWidth() / 3.3 - 15)
        && (y < ofGetWindowHeight() / 2.8 + 117) && current_state_ == DECISION && !should_print_help_screen) {
        decision = -1;
        current_state_ = IN_PROGRESS;
    }
    else if ((x > ofGetWindowWidth() / 3.3 + 22) && (y > ofGetWindowHeight() / 2.8 + 33) && (x < ofGetWindowWidth() / 3.3 + 165)
        && (y < ofGetWindowHeight() / 2.8 + 117) && current_state_ == DECISION && !should_print_help_screen) {
        current_state_ = IN_PROGRESS;
        decision = 0;
    }
    else if ((x > ofGetWindowWidth() / 3.3 + 202) && (y > ofGetWindowHeight() / 2.8 + 33) && (x < ofGetWindowWidth() / 3.3 + 345)
             && (y < ofGetWindowHeight() / 2.8 + 117) && current_state_ == DECISION && !should_print_help_screen) {
        should_print_raise_screen = true;
    }
}
