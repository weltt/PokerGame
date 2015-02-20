//
//  main.cpp
//  PokerGame
//
//  Created by Tyson Welt on 2/18/15.
//  Copyright (c) 2015 Tyson Welt. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include "card_games.h"



int main() {
    card_games *game;
    char game_choice;
    game_choice = choose_game();
    if(game_choice == 's')
        game = new StudPoker();
    else if(game_choice == 'd') {
       game = new go_drawPoker;
    }
    game->play();
    return 0;
}
