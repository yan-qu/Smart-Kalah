#include "Player.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <future>
#include <atomic>
using namespace std;

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================


class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};

// A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number.
int HumanPlayer::chooseMove(const Board &b, Side s) const
{
    
    //if no move is possible, return -1;
    if (b.beansInPlay(s)==0)
    {
        return -1;
    }
    
    //first prompt the person to enter a choice
    cout<<"Please choose a move: ";
    int choice;
    cin>>choice;
    
    //reprompting if necessary until the person enters a valid hole number or that the hole is not empty
    int holeNumber = b.holes();
    while(choice < 1 || choice > holeNumber || b.beans(s, choice)==0)
    {
        if (choice < 1 || choice > holeNumber)
        {
            cout<<"Please enter a valid hole number. Between 1 and " << holeNumber<< "(inclusive): ";
            cin>>choice;
        }
        else
        {
            cout<<"There are no beans in the hole. Please re-enter: ";
            cin>>choice;
        }
    }
    
    //returning that choice
    return choice;
}

//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    //if no move is possible, return -1;
    if (b.beansInPlay(s)==0)
    {
        return -1;
    }
    
    //choosing an arbitrary valid move (a hole number between 1 and the total number of holes at one side) by looping a for-loop to take out empty bean holes
    int holeNumber = 0;
    for (int i = 1; i<= b.holes(); i++)
    {
        if (b.beans(s, i)!=0)
        {
            holeNumber = i;
            break;
        }
    }
    return holeNumber;
}

//the evaluation contains the heuristics I used to evaluate board position, returning the difference between the number of beans in my pot and the number in my opponent's.
int SmartPlayer::evaluation (const Board& b, Side s) const
{
    //heuristics: The greater the difference between the number of beans in my pot and the number in my opponent's, the better
    if (b.beansInPlay(SOUTH) + b.beansInPlay(NORTH) == 0)
    {
        if (s == SOUTH)
        {
            if (b.beans(SOUTH, 0)>b.beans(NORTH, 0))
            {
                return 1000000;
            }
            else if (b.beans(SOUTH, 0)==b.beans(NORTH, 0))
            {
                return 0;
            }
            else
            {
                return -1000000;
            }
        }
        else
        {
            if (b.beans(SOUTH, 0)<b.beans(NORTH, 0))
            {
                return 1000000;
            }
            else if (b.beans(SOUTH, 0)==b.beans(NORTH, 0))
            {
                return 0;
            }
            else
            {
                return -1000000;
            }
        }
    }
    else
    {
        if (s==SOUTH)
        {
            return (b.beans(SOUTH, 0)-b.beans(NORTH, 0));
        }
        else
        {
            return (b.beans(NORTH, 0)-b.beans(SOUTH, 0));
        }
    }
}

//this function is called whenever a move is made by the chooseMoveHelper to check if, after the move, the game has ended or not. If the game is now over, this function also moves any remaining beans in the holes to corresponding pots. It returns true if game is over and false if it is not.
bool SmartPlayer::GameOverOperation(Board b) const
{
    int numberOfHoles = b.holes();
    
    if (b.beansInPlay(SOUTH) == 0 && b.beansInPlay(NORTH) != 0)
    {
        for (int i = 1; i<=numberOfHoles; i++)
        {
            b.moveToPot(NORTH, i, NORTH);
        }
        return true;
    }
    else if (b.beansInPlay(NORTH) == 0 && b.beansInPlay(SOUTH) != 0)
    {
        for (int i = 1; i<=numberOfHoles; i++)
        {
            b.moveToPot(SOUTH, i, SOUTH);
        }
        return true;
    }
    else if (b.beansInPlay(NORTH) == 0 && b.beansInPlay(SOUTH) == 0)
    {
        return true;
    }
    return false;
}

//chooseMoveHelper takes in more arguments than the chooseMove and it does the actual work of what SmartPlayer::chooseMove is supposed to do, which is choosing a valid move and returns it as bestHole
void SmartPlayer::chooseMoveHelper(AlarmClock& ac, Side s, Side startingSide, Board b, int& bestHole, int& value) const
{
    //set initial worst value
    if (s==startingSide)
    {
        value = -1000000;
    }
    else
    {
        value = 1000000;
    }
    Board copy = b;
    //if no move for player exists (i.e., game is over)
    if (GameOverOperation(copy))
    {
        bestHole = -1;
        value = evaluation(copy, startingSide);
        return;
    }
    
    //if the criterion says we should not search below this node
    if (ac.timedOut())
    {
        bestHole = -1;
        value = evaluation(b, startingSide);
        return;
    }
    
    
    int numberOfHoles = b.holes();
    
    
    //for every hole h the player can choose
    for (int i = 1; i<=numberOfHoles; i++)
    {
        if (b.beans(s, i)!=0)
        {
            Board copied = b;
            Side endside;
            int endhole;
            copied.sow(s, i, endside, endhole);
            
            if (endside==s && endhole == 0)
            {
                if (!GameOverOperation(copied))
                {
                    int bestHole1, value1;
                    chooseMoveHelper(ac, s, startingSide, copied, bestHole1, value1);
                    if (s==startingSide)
                    {
                        if (value1>=value)
                        {
                            value = value1;
                            bestHole = i;
                        }
                    }
                    else
                    {
                        if (value1<=value)
                        {
                            value = value1;
                            bestHole = i;
                        }
                    }
                }
            }
            
            else if (endside==s && copied.beans(s, endhole) == 1 && copied.beans(opponent(s), endhole)!=0)
            {
                copied.moveToPot(s, endhole, s);
                copied.moveToPot(opponent(s), endhole, s);
            }
            
            GameOverOperation(copied);
            
            int currentValue, currentBestHole;
            chooseMoveHelper(ac, opponent(s), startingSide, copied, currentBestHole, currentValue);
            
            if (s==startingSide)
            {
                if (currentValue>=value)
                {
                    value = currentValue;
                    bestHole = i;
                }
            }
            else
            {
                if (currentValue<=value)
                {
                    value = currentValue;
                    bestHole = i;
                }
            }
            
        }
    }
    return;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    
    //if no move is possible, return -1;
    if (b.beansInPlay(s)==0)
    {
        return -1;
    }
    
    int bestMove;
    int val;
    AlarmClock ac(4900);
    //use helper function and thus creating a copy of the board so that the program can make moves
    chooseMoveHelper(ac, s, s, b, bestMove, val);
    
    //in case the smart player function fails
    if (bestMove < 1 || bestMove > b.holes() || b.beans(s, bestMove)==0)
    {
        for (int i = 1; i<= b.holes(); i++)
        {
            if (b.beans(s, i)!=0)
            {
                bestMove = i;
                break;
            }
        }
    }
    
    return bestMove;
}


