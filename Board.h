#ifndef Board_h
#define Board_h

#include "Side.h"
#include <vector>

class Board
{
public:
    //constructor
    Board(int nHoles, int nInitialBeansPerHole);
    
    //public member functions
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
    
private:
    std::vector<int> m_board;
    int m_nHoles;
    int m_nInitialBeansPerHole;
    int m_totalnOfHoles;
};

#endif /* Board_h */
