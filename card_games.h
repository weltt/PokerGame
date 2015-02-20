//
//  card_games.h
//  PokerGame
//
//  Created by Tyson Welt on 2/18/15.
//  Copyright (c) 2015 Tyson Welt. All rights reserved.
//

#ifndef PokerGame_card_games_h
#define PokerGame_card_games_h

#include <string>
#include <vector>



enum Suit {
    C, D, H, S,
    RankF=C, RankL=S
};

using namespace std;

char choose_game();

class card {
public:
    int getvalue() { return value; }
    void setvalue(int v) { value = v; }
    char getsuit() { return suit; }
    void setsuit(char c) { suit = c; }
    card(int value, char suit) : value(value), suit(suit) {}
protected:
    int value;
    char suit;
};


class chand : public card {
public:
    chand();
protected:
    vector<card> hand;
};

class player : public chand {
    int chips;
    int rank;
    bool folded, winner;
public:
    player() { folded = 0; winner = 0; }
    void setrank(int c) { rank = c; }
    bool getfolded() { return folded; }
    void setfolded() { folded = true; }
    bool getwinner() { return winner; }
    void setwinner() { winner = true; }
    int getrank() { return rank; }
    int betchips(int c) { chips -= c; return c; }
    int getchips() { return chips; }
    int addchips(int c) { chips += c; return c;}
    void addcard(const card);

    friend class poker;

};

class card_games {
    
    int players;
public:
    int getplayers() { return players; }
    void setplayers(int);
    
    virtual void play()=0;
protected:
    vector<player>playa;
};

class poker : public card_games {
    vector<card> deck;
    int pot;
    bool tied;

    
    // Values of hands
    static const int SFLUSH= 8000000;
    static const int KIND4=  7000000;
    static const int FHOUSE= 6000000;
    static const int FLUSH=  5000000;
    static const int STR8=   4000000;
    static const int TWOPAIR=2000000;
    static const int THREE=  3000000;
    static const int PAIR=   2000000;
    
    friend class go_drawPoker;
    
    
public:
    poker();
    void mkdeck();
    card draw();
    void deal(int);
    void settied(bool c) { tied = c; }
    void bets();
    void addpot(int chips) { pot += chips; };
    int getpot() {  int chips=pot;
                    pot=0;
                    return chips;
                    }
    void print();
    int winner();
    void printchips();
    void newgame();
    void drawcards();
    void tie();
    bool isStraight(vector<card> &job);
    void SortRank(vector<card> &job);
    bool is4(vector<card> &job);
    bool isFull(vector<card> &job);
    bool is3(vector<card> &job);
    bool is2pair(vector<card> &job);
    bool ispair(vector<card> &job);
    bool isFlush(vector<card> &job);
    int hcard(vector<card> &job);
    
    void givepot(int);
    void rankem();
};

class StudPoker : public poker {
public:
    void play();
};

class go_drawPoker : public poker {
public:
    void play();
    void dealtoplayer(int,player);
};

#endif
