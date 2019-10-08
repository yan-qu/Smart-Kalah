
#ifndef Player_h
#define Player_h

#include <iostream>
#include <string>
#include "Board.h"
#include "Side.h"

class AlarmClock;
class Player
{
public:
    Player(std::string name)
    {
        m_name = name;
    }
    //Create a Player with the indicated name.
    
    std::string name() const
    {
        return m_name;
    }
    //Return the name of the player.
    
    virtual bool isInteractive() const
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    {
        return false;
    }
    
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    
    virtual ~Player(){};
        //Since this class is designed as a base class, it should have a virtual destructor.
        
private:
    std::string m_name;
};

class HumanPlayer : public Player
{
public:
    HumanPlayer (std::string name) : Player(name)
    {
    }
    
    ~HumanPlayer(){};
    
    virtual bool isInteractive() const
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    {
        return true;
    }
    
    virtual int chooseMove(const Board& b, Side s) const;
    
};

class BadPlayer : public Player
{
public:
    BadPlayer (std::string name) : Player(name)
    {
    }
    
    ~BadPlayer(){};
    
    virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player
{
public:
    SmartPlayer (std::string name) : Player(name)
    {
    }
    
    ~SmartPlayer(){};
    
    virtual int chooseMove(const Board& b, Side s) const;
    
//private helper class for smartplayer's choosemove
private:
    void chooseMoveHelper(AlarmClock& ac, Side s, Side startingSide, Board b, int& bestHole, int& value) const;
    bool GameOverOperation(Board b) const;
    int evaluation (const Board& b, Side s) const;
    
};

#endif /* Player_h */
