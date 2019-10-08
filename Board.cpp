#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    //Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
    
    //If nHoles is not positive, set it to 1;
    if (nHoles <= 0)
    {
        nHoles = 1;
    }
    //if nInitialBeansPerHole is negative, set it to 0.
    if (nInitialBeansPerHole < 0)
    {
        nInitialBeansPerHole = 0;
    }
    
    //record the number of holes per side, the initial number of beans per hole, and the total number of holes
    m_nHoles = nHoles;
    m_nInitialBeansPerHole = nInitialBeansPerHole;
    m_totalnOfHoles = 2*m_nHoles+2;
    
    //create the south's holes, fill each with initialBeansPerHole
    for (int i = 0; i<nHoles; i++)
    {
        m_board.push_back(m_nInitialBeansPerHole);
    }
    
    //create the south's pot, and set it to empty
    m_board.push_back(0);
    
    //create the north's holes, fill each with initialBeansPerHole
    for (int i = 0; i<nHoles; i++)
    {
        m_board.push_back(m_nInitialBeansPerHole);
    }
    //create the north's pot, and set it to empty
    m_board.push_back(0);
}

int Board::holes() const
{
    //Return the number of holes on a side (not counting the pot).
    return m_nHoles;
}

int Board::beans(Side s, int hole) const
{
    //Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
    if (hole > m_nHoles || hole < 0)
    {
        return -1;
    }
    
    //if the hole is a pot
    if (hole == 0)
    {
        //return the content of the North's pot
        if (s == NORTH)
        {
            return (m_board.back());
        }
        
        //return the content of the South's pot
        else
        {
            return (m_board.at(m_nHoles));
        }
    }
    
    //if the hole is a hole
    else
    {
        if (s == SOUTH)
        {
            //return the content of the South's holes
            return (m_board.at(hole-1));
        }
        else
        {
            //return the content of the North's holes
            return (m_board.at(m_totalnOfHoles-1-hole));
        }
    }
}

//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot
int Board::beansInPlay(Side s) const
{
    int total = 0;
    //return the total number of beans on South by traversing the vector and totaling the content on the South's side
    if (s == SOUTH)
    {
        for (int i = 0; i<m_nHoles; i++)
        {
            total += m_board.at(i);
        }
    }
    //return the total number of beans on North by traversing the North element and totaling the content on the North side
    else
    {
        for (int i = m_nHoles+1; i<m_totalnOfHoles-1; i++)
        {
            total += m_board.at(i);
        }
    }
    return total;
}

//Return the total number of beans in the game, including any in the pots.

int Board::totalBeans() const
{
    //record the sum of the number of beans in both NORTH side's holes and SOUTH side's holes
    int totalNumber = beansInPlay(NORTH) + beansInPlay(SOUTH);
    
    //add to the totalNumber the number of beans in the two pots
    
    //SOUTH POT
    totalNumber += m_board.at(m_nHoles);
    
    //NORTH POT
    totalNumber += m_board.at(m_totalnOfHoles-1);
    
    return totalNumber;
}

//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    //Return false if the hole number is invalid or is a pot(not between 1 and m_nHoles).
    if (hole > m_nHoles || hole < 1)
    {
        return false;
    }
    
    //If the hole indicated by (s,hole) is empty), return false;
    if (s == SOUTH)
    {
        if (m_board.at(hole-1)==0)
        {
            return false;
        }
    }
    else
    {
        if (m_board.at(m_totalnOfHoles-1-hole)==0)
        {
            return false;
        }
    }
    
    //declare a currentPos variable to record the current hole the sowing has reached
    int currentPos;
    if (s == SOUTH)
    {
        currentPos = hole-1;
    }
    else
    {
        currentPos = m_totalnOfHoles-1-hole;
    }
    //note down the position of the opponent's pot and assign it to skippedPos
    int skippedPos;
    if (opponent(s)==SOUTH)
    {
        skippedPos = m_nHoles;
    }
    else
    {
        skippedPos = m_totalnOfHoles-1;
    }
    
    //record down the total number of beans to be sown in the hole and clear the current hole (set remaining beans to be 0)
    int toBeSown = m_board.at(currentPos);
    m_board[currentPos] = 0;
    
    
    //move the currentPos to next position
    currentPos++;
    
    //Keep sowing if there are beans left to be sown.
    while (toBeSown > 0)
    {
        //check if the currentPos is invalid,
        //if it's the skippedPos, skip it;
        
        if (currentPos == skippedPos)
        {
            currentPos++;
        }
        //if it's the end of the vector (the North Pot), move the currentPos back to the beginning of the vector;
        
        else if (currentPos == m_totalnOfHoles)
        {
            currentPos = 0;
        }
        else
        {
        //otherwise, the currentPos is valid, increment the currentPos's hole and decrement the number of beans to be sown, and move the currentPos to next position
            m_board[currentPos] += 1;
            toBeSown--;
            currentPos++;
        }
    }
    //shift currentPos back to the endPosition
    currentPos--;
    
    //determine endSide
    if (currentPos<=m_nHoles)
    {
        endSide = SOUTH;
    }
    else
    {
        endSide = NORTH;
    }
    
    //determine endHole
    if(endSide == SOUTH)
    {
        if (currentPos == m_nHoles)
        {
            endHole = 0;
        }
        else
        {
            endHole = currentPos+1;
        }
    }
    else
    {
        if (currentPos == m_totalnOfHoles-1)
        {
            endHole = 0;
        }
        else
        {
            endHole = m_totalnOfHoles-1-currentPos;
        }
    }
    //return true after the sowing has been done
    return true;
}

//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    //Return false if the hole number is invalid or is a pot(not between 1 and m_nHoles).
    if (hole > m_nHoles || hole < 1)
    {
        return false;
    }
    
    //declare a currentPos variable to record the current hole's position
    int currentPos;
    if (s == SOUTH)
    {
        currentPos = hole-1;
    }
    else
    {
        currentPos = m_totalnOfHoles-1-hole;
    }
    
    //obtain the number of beans in the hole and move all of the beans in hole (s,hole)
    int toBeMoved = m_board.at(currentPos);
    m_board[currentPos] = 0;
    
    if(potOwner == SOUTH)
    {
        m_board[m_nHoles] += toBeMoved;
    }
    else
    {
        m_board[m_totalnOfHoles-1] += toBeMoved;
    }
    
    return true;
}

//If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)

bool Board::setBeans(Side s, int hole, int beans)
{
    //Return false if the hole number is invalid (not between 0 and m_nHoles).
    if (hole > m_nHoles || hole < 0)
    {
        return false;
    }
    //return false if beans is negative
    if (beans < 0)
    {
        return false;
    }
    
    //declare a currentPos variable to record the current hole's position
    int currentPos;
    if (s == SOUTH)
    {
        if (hole == 0)
        {
            currentPos = m_nHoles;
        }
        else
        {
            currentPos = hole-1;
        }
    }
    else
    {
        if (hole == 0)
        {
            currentPos = m_totalnOfHoles-1;
        }
        else
        {
            currentPos = m_totalnOfHoles-1-hole;
        }
    }
    //change the content at the current hole to beans
    m_board[currentPos] = beans;
    return true;
}
