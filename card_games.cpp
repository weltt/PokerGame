//
//  card_games.cpp
//  PokerGame
//
//  Created by Tyson Welt on 2/19/15.
//  Copyright (c) 2015 Tyson Welt. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "card_games.h"

using namespace std;

char choose_game() {
    char choice;
    cout << "What game would you like to play?" << endl;
    cout << "(s)tud or (d)raw" << endl;
    cin >> choice;
    return choice;
}

void poker::mkdeck() {
    deck.clear();
    const char suits[] = { 'C', 'D', 'H', 'S'};
    for(int i=0; i < 4; i++)
        for(int j=2; j < 15; j++)
            deck.push_back(card(j,suits[i]));
    
}

poker::poker() {
    mkdeck();
}


void poker::deal(int c) {
    for(int i=0; i < c; i++) {
        for(int j=0; j < getplayers(); j++) {
            card dealt=draw();
            cout << dealt.getsuit() << endl;
            playa[j].hand.push_back(dealt);
            cout << dealt.getvalue() << endl;
        }
    }
}

void player::addcard(const card addme) {
    hand.push_back(addme);
}

card poker::draw() {
    unsigned int randc = rand() % (deck.size());
    //cout << randc << " " << deck.begin()+randc << endl;
    cout << "randc" << randc << endl;
    card drawn(0, 'c');
    drawn.setvalue(deck[randc].getvalue());
    drawn.setsuit(deck[randc].getsuit());
    deck.erase(deck.begin()+randc);
   
    return drawn;
}


void poker::bets() {
    int chips;
    cout << "BETS!!!" << endl;
    for (int i=0; i < getplayers(); i++) {
        if(!playa[i].getfolded()) {
        cout << "Player " << i+1 << " Bet , 0 to fold" << endl;
        cin >> chips;
        if (chips == 0) {
            playa[i].setfolded();
            cout << "Player " << i+1 << " Folds!";
        }
            addpot(playa[i].betchips(chips));
        }
    }
    cout << "POT IS " << pot << endl;
}



void StudPoker::play() {
    int playas,won;
    int card=1;
    char choice;
    
    srand(static_cast<unsigned int>(time(NULL)));
    
    cout << "Two Player Stud Poker coming up.. " << endl;
    cout << "how many players?" << endl;
    cin >> playas;
    
    if (playas > 1 && playas < 7) {
        setplayers(playas);
        
    } else {
        cout << "wrong number of players" << endl;
    }
    
    cout << "Dealing the first card" << endl;
    
    for(int i=0; i<5; i++) {
        deal(card);
        print();
        bets();
    }
    rankem();
    won = winner();
    cout << " PLAYER " << won+1 << " IS THE WINNER OF " <<  playa[won].addchips(getpot()) << endl;
    
    printchips();
    
    cout << "play again? y/n" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        newgame();
    }
    
    
}

void go_drawPoker::play() {
    int playas,won;
    int card=5;
    char choice;
    
    srand(static_cast<unsigned int>(time(NULL)));
    
    cout << "Five Card Poker coming up.. " << endl;
    cout << "how many players?" << endl;
    cin >> playas;
    
    if (playas > 1 && playas < 7) {
        setplayers(playas);
        
    } else {
        cout << "wrong number of players" << endl;
    }
    
    cout << "Dealing the first round" << endl;
    
    deal(card);
    print();
    bets();
    drawcards();

    bets();
    rankem();
    
    //Check if tied
    if (!tied) {
        won = winner();
        cout << " PLAYER " << won+1 << " IS THE WINNER OF " <<  playa[won].addchips(getpot()) << endl;
    } else {
        tie();
        cout << "TIE!@$%" << endl;
    }
    
    
    printchips();
    
    cout << "play again? y/n" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        newgame();
    }
    
    
}

void poker::drawcards() {
    for (int i=0; i < getplayers(); i++) {
        cout << "Pick which ones to discard..." << endl;
        
        int newcards=0;
        char choice;
        cout << "Player " << i+1 << " ... " << endl;
        cout << "Discard #1 y/n" << endl;
        cin >> choice;
        if (choice== 'y') {
            newcards++;
            playa[i].hand[0]=draw();
        }
        cout << "Discard #2 y/n" << endl;
        cin >> choice;
        if (choice== 'y') {
            newcards++;
            playa[i].hand[1]=draw();
        }
        cout << "Discard #3 y/n" << endl;
        cin >> choice;
        if (choice== 'y') {
            newcards++;
            playa[i].hand[2]=draw();
        }
        cout << "Discard #4 y/n" << endl;
        cin >> choice;
        if (choice== 'y') {
            newcards++;
            playa[i].hand[3]=draw();
        }
        if (newcards == 4) {
            cout << "only four cards dude" << endl;
        }
        if (newcards < 4) {
            cout << "Discard #5 y/n" << endl;
            cin >> choice;
        }
        if (choice== 'y' && newcards < 4) {
            newcards++;
            playa[i].hand[4]=draw();
        }
        print();
    }
}

void poker::print() {
    cout << "players" << getplayers();
    for(int i=0; i < getplayers(); i++) {
        cout <<
        endl <<
        "player " << i+1 << " hand: ";
        
        // sort(playa[i].hand.begin(), playa[i].hand.end());
        
        for (int j=0; j < playa[i].hand.size(); j++) {
            if (playa[i].hand[j].getvalue() == 11)
                cout << "J";
            else if (playa[i].hand[j].getvalue() == 12)
                cout << "Q";
            else if (playa[i].hand[j].getvalue() == 13)
                cout << "K";
            else if (playa[i].hand[j].getvalue() == 14)
                cout << "A";
            else
                cout << playa[i].hand[j].getvalue();
            
            cout << playa[i].hand[j].getsuit() << " ";
        }
        cout << endl;
    }
}

void card_games::setplayers(int p) {
    players = p;
    playa.reserve(p);
}


void SortSuit(vector<card> &job) {
    int minj;
    for (int i=0; i<5; i++) {
        minj = i;
        for (int j=i+1; j<5; j++) {
            if (job[i].getsuit() < job[minj].getsuit()) {
                minj=j;
            }
        }
        card temp = job[i];
        job[i] = job[minj];
        job[minj] = temp;
    }
}

bool poker::isStraight(vector<card> &job) {
    int temp;
    if (job[4].getvalue() == 14) {
        //check if round the world straight
    } else {}
    temp = job[4].getvalue() + 1;
    for(int i=1; i < 5; i++) {
        if (job[i].getvalue() != temp)
            return false;
    }
    return true;
}

void poker::SortRank(vector<card> &job) {
    int minj;
    for (int i=0; i<5; i++) {
        minj = i;
        for (int j=i+1; j<5; j++) {
            if (job[i].getvalue() < job[minj].getvalue()) {
                minj=j;
            }
        }
        card temp = job[i];
        job[i] = job[minj];
        job[minj] = temp;
    }
}

bool poker::isFlush(vector<card> &job) {
    SortSuit(job);
    return(job[0].getsuit()==job[4].getsuit());
}

bool poker::is4(vector<card> &job) {
    bool t1, t2;
    SortRank(job);
    t1 =
    job[0].getvalue() == job[1].getvalue() &&
    job[1].getvalue() == job[2].getvalue() &&
    job[2].getvalue() == job[3].getvalue();
    t2 =
    job[1].getvalue() == job[2].getvalue() &&
    job[2].getvalue() == job[3].getvalue() &&
    job[3].getvalue() == job[4].getvalue();
    return (t1 || t2);
}

bool poker::isFull(vector<card> &job) {
    bool t1, t2;
    SortRank(job);
    t1 =
    job[0].getvalue() == job[1].getvalue() &&
    job[1].getvalue() == job[2].getvalue() &&
    job[3].getvalue() == job[4].getvalue();
    
    t2=
    job[1].getvalue() == job[2].getvalue() &&
    job[2].getvalue() == job[3].getvalue() &&
    job[0].getvalue() == job[1].getvalue();
    
    return (t1 || t2);
}

bool poker::is3(vector<card> &job) {
    bool t1,t2,t3;
    SortRank(job);
    
    t1 =
    job[0].getvalue() == job[1].getvalue() &&
    job[1].getvalue() == job[2].getvalue() &&
    job[3].getvalue() != job[0].getvalue() &&
    job[4].getvalue() != job[0].getvalue() &&
    job[3].getvalue() != job[4].getvalue();
    
    t2 =
    job[1].getvalue() == job[2].getvalue() &&
    job[2].getvalue() == job[3].getvalue() &&
    job[0].getvalue() != job[1].getvalue() &&
    job[4].getvalue() != job[1].getvalue() &&
    job[0].getvalue() != job[4].getvalue();
    
    t3 =
    job[2].getvalue() == job[3].getvalue() &&
    job[3].getvalue() == job[4].getvalue() &&
    job[0].getvalue() != job[2].getvalue() &&
    job[1].getvalue() != job[2].getvalue() &&
    job[0].getvalue() != job[1].getvalue();

    return (t1 || t2 || t3);
    
}

bool poker::is2pair(vector<card> &job) {
    bool t1,t2,t3;
    SortRank(job);
    t1 =
    job[0].getvalue() == job[1].getvalue() &&
    job[2].getvalue() == job[3].getvalue();
    t2 =
    job[0].getvalue() == job[1].getvalue() &&
    job[3].getvalue() == job[4].getvalue();
    t3 =
    job[1].getvalue() == job[2].getvalue() &&
    job[3].getvalue() == job[4].getvalue();
    
    return (t1 || t2 || t3);
    
}

bool poker::ispair(vector<card> &job) {
    bool t1, t2, t3, t4;
    SortRank(job);
    t1 = job[0].getvalue() == job[1].getvalue();
    t2 = job[2].getvalue() == job[3].getvalue();
    t3 = job[3].getvalue() == job[4].getvalue();
    t4 = job[2].getvalue() == job[1].getvalue();
    
    return (t1 || t2 || t3 || t4);
}

int poker::hcard(vector<card> &job) {
    SortRank(job);
    return job[4].getvalue();
}

void poker::rankem() {
    for(int i=0; i < getplayers(); i++) {
        int high=hcard(playa[i].hand);
        if(isFlush(playa[i].hand) && isStraight(playa[i].hand)) {
            playa[i].setrank(SFLUSH+high);
        } else if (is4(playa[i].hand)) {
            playa[i].setrank(KIND4+high);
        } else if (isFull(playa[i].hand)) {
            playa[i].setrank(FHOUSE+high);
        } else if (isFlush(playa[i].hand)) {
            playa[i].setrank(FLUSH+high);
        } else if (isStraight(playa[i].hand)) {
            playa[i].setrank(STR8+high);
        } else if (is3(playa[i].hand)) {
            playa[i].setrank(THREE+high*3);
        } else if (is2pair(playa[i].hand)) {
            playa[i].setrank(TWOPAIR+high);
        } else if (ispair(playa[i].hand)) {
            playa[i].setrank(PAIR+high);
        } else {
            playa[i].setrank(high+playa[i].hand[3].getvalue());
        }
    }
    
}

void poker::newgame() {
    mkdeck();
    for(int i=0; i<getplayers(); i++) {
        playa[i].hand.clear();
        cout << "Player " << i+1 << " has " << playa[i].getchips() << endl;
    }
    this->play();
}

void poker::printchips() {
    for(int i=0; i<getplayers(); i++) {
        cout << "Player " << i+1 << " has " << playa[i].getchips() << endl;
    }
}
int poker::winner() {
    int win = 0, max = playa[0].getrank(), tied = 0;
    for(int i=1; i<getplayers(); i++) {
        if(playa[i].getrank() > max && !playa[i].getfolded()) {
            max=playa[i].getrank();
            win=i;
        } else if (playa[i].getrank() == max) {
            if(tied<max)
                tied = max;
        }
    }
    if (tied == max)
        settied(true);
    return win;
}

void poker::tie() {
    int tie[5], tieway=0;
    int temp=getplayers();
    if(playa[temp-1].getrank() == playa[temp-2].getrank()) {
        tie[temp]=1;
        tie[temp-1]=1;
        if(temp-2 > 0) {
            if(playa[temp-2].getrank() == playa[temp-3].getrank())
                tie[temp-2]=1;
            if(temp-3>0){
                if(playa[temp-3].getrank() == playa[temp-4].getrank())
                    tie[temp-3]=1;
                if(temp-4) {
                    if(playa[temp-1].getrank() == playa[temp-2].getrank()) {
                        tie[temp-4]=1;
                    }
                }
            }
        }
    }
    if(temp-2 > 0) {
        if(playa[temp-2].getrank() == playa[temp-3].getrank())
            tie[temp-2]=1;
        if(temp-3>0){
            if(playa[temp-3].getrank() == playa[temp-4].getrank())
                tie[temp-3]=1;
            if(temp-4) {
                if(playa[temp-1].getrank() == playa[temp-2].getrank()) {
                    tie[temp-4]=1;
                }
            }
        }
    }
    if(temp-3>0){
        if(playa[temp-3].getrank() == playa[temp-4].getrank())
            tie[temp-3]=1;
        if(temp-4) {
            if(playa[temp-1].getrank() == playa[temp-2].getrank()) {
                tie[temp-4]=1;
            }
        }
    }
    if(temp-4) {
        if(playa[temp-1].getrank() == playa[temp-2].getrank()) {
            tie[temp-4]=1;
        }
    }
    for (int i=0; i<temp; i++)
        if(tie[i])
            tieway++;
    
    int newpot = getpot();
    newpot /= tieway;
    settied(false);
    for(int i=1; i<getplayers(); i++)
        if (tie[i])
            playa[i].addchips(ceil(newpot));
}