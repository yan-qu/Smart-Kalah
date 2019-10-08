#ifndef Game_h
#define Game_h

#include "Board.h"
#include "Side.h"
#include "Player.h"


class Game
{
public:
    //constructor
    Game(const Board& b, Player* south, Player* north);
    
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move();
    void play();
    int beans(Side s, int hole) const;
    
private:
    Board my_board;
    Player* m_South;
    Player* m_North;
    Side currentSide;
};

#endif /* Game_h */
