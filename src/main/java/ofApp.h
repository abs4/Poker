#pragma once

#include "ofMain.h"
#include "GameEngine.h"

enum GameState {
    IN_PROGRESS = 0,
    OPENING_SCREEN,
    FINISHED,
    PAUSED,
    DECISION
};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void drawWords(std::string msg);
        void draw();

        void keyPressed(int key);
        void mouseMoved(int x, int y );
        void mousePressed(int x, int y, int button);
    
        // Draw methods that were added
        void drawGamePaused();
        void drawGameDecision();
        void drawGameOver();
        void drawTable();
        void drawConsole();
        void drawOpeningScreen();
        void drawButtons();
        void drawPokerChipLogo();
        void drawPot();
        void drawCards();
        void drawHand();
        void drawPlayers();
        void drawHelpScreen();
        void drawPrintScreen();
 
    private:
        GameState current_state_ = OPENING_SCREEN;

        // Object images
        ofImage table;
        ofImage gameBox;
        ofImage hat;
        ofImage fold;
        ofImage call;
        ofImage raise;
        ofImage poker_chip;
        ofImage card_one;
        ofImage card_two;
        ofImage card_three;
        ofImage card_four_empty;
        ofImage card_five_empty;
        ofImage card_front_one;
        ofImage card_front_two;
        ofImage card_front_three;
        ofImage card_front_four;
        ofImage card_front_five;
        ofImage card_hand_one;
        ofImage card_hand_two;
        ofImage fold_card_one;
        ofImage fold_card_two;
        ofImage red_x;
        ofImage dog_title;
        ofImage black_border;
        ofImage win_screen;
        ofImage lose_screen;
        ofImage help_screen;
        ofImage border_black_two;

        // Sounds (Outside library)
        ofSoundPlayer god_father_sound;
        ofSoundPlayer poker_chip_sound;

        GameEngine g;


        // game logic booleans
        bool deal_cards_and_blinds = false;
        bool should_play_round = false;
        bool should_flop = false;
        bool should_play_round_after_flop = false;
        bool should_turn = false;
        bool should_play_round_after_turn = false;
        bool should_river = false;
        bool should_play_round_after_river = false;
        bool should_distribute_wealth = false;
        bool should_reset = false;

        // should draw certain objects booleans
        bool draw_cards_down = false;
        bool draw_cards_flop = false;
        bool draw_cards_turn = false;
        bool draw_cards_river = false;
        bool should_play_background_music = true;
        bool should_print_help_screen = false;
        bool should_print_raise_screen = false;
        bool showConsole = true;

        std::vector<std::string> console_txt;  // vector of strings containing actions in game
        int decision = -2; // used to determine what the player does
        int raise_amount = 0; // amount the player wants to raise
};
