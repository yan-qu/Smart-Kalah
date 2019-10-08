#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north): my_board(b)
{
    m_South = south;
    m_North = north;
    currentSide = SOUTH;
}

//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
void Game::display() const
{
    int nOfHoles = my_board.holes();
    
    string space(5*((nOfHoles+1)/2), ' ');
    //first line: display the north player's name
    cout<<space<<m_North->name()<<endl;
    
    string space1(5, ' ');
    //second line: display the content of the north side's holes
    for (int i = 1; i<=nOfHoles; i++)
    {
        cout<<space1<<my_board.beans(NORTH, i);
    }
    cout<<endl;
    
    string space2(5*(nOfHoles+1), ' ');
    //third line: display the content of the two pots
    cout<<my_board.beans(NORTH, 0);
    cout<<space2;
    cout<<my_board.beans(SOUTH, 0)<<endl;
    
    //Forth Line: display the content of the north side's holes
    for (int i = 1; i<=nOfHoles; i++)
    {
        cout<<space1<<my_board.beans(SOUTH, i);
    }
    cout<<endl;
    
    //Fifth line: display the name of the South's player
    cout<<space<<m_South->name()<<endl;
}

//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    //Whenever a turn ends with all of the holes on one side of the board empty (no matter whose turn ended), the game is over; otherwise it's not
    //If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else.
    if (my_board.beansInPlay(NORTH)!=0 && my_board.beansInPlay(SOUTH)!=0)
    {
        over = false;
        return;
    }
    
    //set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
    else
    {
        over = true;
        
        int nOfHoles = my_board.holes();
        int northTotal = 0;
        int southTotal = 0;
        
        //count the total number of beans in south and north, respectively
        
        //REMEMBER TO WIPE OUT THE REMAINING BEANS
        for (int i = 0; i<=nOfHoles; i++)
        {
            northTotal += my_board.beans(NORTH, i);
        }
        
        for (int i = 0; i<=nOfHoles; i++)
        {
            southTotal += my_board.beans(SOUTH, i);
        }
        
        if (northTotal != southTotal)
        {
            hasWinner = true;
            if (northTotal>southTotal)
            {
                winner = NORTH;
            }
            else
            {
                winner = SOUTH;
            }
        }
        else
        {
            hasWinner = false;
        }
    }
}

//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
bool Game::move()
{
    //set up currentPlayer
    Player* currentPlayer;
    if (currentSide == SOUTH)
    {
        currentPlayer = m_South;
    }
    else
    {
        currentPlayer = m_North;
    }
    
    //If the game is over, return false.
    bool gameOver = false;
    bool hasAWinner = false;
    Side Winner = NORTH;
    int numberOfHoles = my_board.holes();
    
    status(gameOver, hasAWinner, Winner);
    
    if (gameOver)
    {
        return false;
    }
    
    
    //use a flag and while lloop to take any additional turns that is required
    bool AdditionalTurn = true;
    
    while (AdditionalTurn)
    {
        AdditionalTurn = false;
        
        Side endside;
        int endhole;
        
        //display to the viewers what's happening (what move is chosen)
        
        int chosenMove;
        
        if (currentPlayer->isInteractive())
        {
            cout<<currentPlayer->name()<<", ";
            chosenMove = currentPlayer->chooseMove(my_board, currentSide);
            cout<<endl;
        }
        else
        {
            cout<<currentPlayer->name()<<" chooses the move ";
            chosenMove = currentPlayer->chooseMove(my_board, currentSide);
            cout<<chosenMove<<endl;
        }
        
        my_board.sow(currentSide, chosenMove, endside, endhole);
        
        //if additional turn is needed
        if (endside==currentSide && endhole == 0)
        {
            AdditionalTurn = true;
            display();
            status(gameOver, hasAWinner, Winner);
            //check if game is over, if it is, complete the gameoverOperation(sweeping any remaining beans into that side's player's pot) and return true
            if (gameOver)
            {
                if (my_board.beansInPlay(SOUTH) == 0 && my_board.beansInPlay(NORTH) != 0)
                {
                    for (int i = 1; i<=numberOfHoles; i++)
                    {
                        my_board.moveToPot(NORTH, i, NORTH);
                    }
                    
                    cout<<"Sweeping remaining beans into "<<m_North->name()<<"'s Pot"<<endl;
                    display();
                }
                else if (my_board.beansInPlay(NORTH) == 0 && my_board.beansInPlay(SOUTH) != 0)
                {
                    for (int i = 1; i<=numberOfHoles; i++)
                    {
                        my_board.moveToPot(SOUTH, i, SOUTH);
                    }
                    
                    cout<<"Sweeping remaining beans into "<<m_South->name()<<"'s Pot"<<endl;
                    display();
                }
                currentSide = opponent(currentSide);
                return true;
            }
            //else, display to the player and ask for additional move
            if (currentPlayer->isInteractive())
            {
                cout<<"Please take an additional move."<<endl;
            }
            else
            {
                cout<<currentPlayer->name()<<" gets an additional move. ";
            }
        }
        //else if a capture occurs
        else if (endside==currentSide && my_board.beans(currentSide, endhole) == 1 && my_board.beans(opponent(currentSide), endhole)!=0)
        {
            //do capture operation and display the new board
            my_board.moveToPot(currentSide, endhole, currentSide);
            my_board.moveToPot(opponent(currentSide), endhole, currentSide);
            display();
            cout<<"Nice Capture, "<<currentPlayer->name()<<"!"<<endl;
        }
    }
    
    //check if the game has ended, if it does, do the gameoverOperation
    if (my_board.beansInPlay(SOUTH) == 0 && my_board.beansInPlay(NORTH) != 0)
    {
        for (int i = 1; i<=numberOfHoles; i++)
        {
            my_board.moveToPot(NORTH, i, NORTH);
        }
        cout<<"Sweeping remaining beans into "<<m_North->name()<<"'s Pot"<<endl;
        display();
    }
    else if (my_board.beansInPlay(NORTH) == 0 && my_board.beansInPlay(SOUTH) != 0)
    {
        for (int i = 1; i<=numberOfHoles; i++)
        {
            my_board.moveToPot(SOUTH, i, SOUTH);
        }
        
        cout<<"Sweeping remaining beans into "<<m_South->name()<<"'s Pot"<<endl;
        display();
    }
    //set the playingSide to the other side (the opponent)
    currentSide = opponent(currentSide);
    //return true
    return true;
}

//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
void Game::play()
{
    //If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over; Similarly, if North has no beans in play, sweep any beans on the South into South's pot
    
    display();
    //to ensure that play is only called when the game is not yet over
    //let the currentPlayer complete their turn
    if (move())
    {
        //If neither player is interactive, periodically prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed.
        if ((!m_South->isInteractive())&&(!m_North->isInteractive()))
        {
            display();
            cout<<"Press enter to continue.";
            cin.ignore(10000,'\n');
        }
        cout<<endl;
        play();
    }
    
    else
    {
        bool gameOver, hasWinner;
        Side winner;
        
        status(gameOver, hasWinner, winner);
        
        cout<<"The Game is Over!"<<endl;
        
        //Announce the winner at the end of the game.
        if (hasWinner)
        {
            string winnerName;
            if (winner == SOUTH)
            {
                winnerName = m_South->name();
            }
            else
            {
                winnerName = m_North->name();
            }
            cout<<"The Winner is "<<winnerName<<"!"<<endl;
        }
        else
        {
            cout<<"It was a tie!"<<endl;
        }
    }
    
    
}

//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
    int nOfHoles = my_board.holes();
    if (hole>nOfHoles || hole<0)
    {
        return -1;
    }
    return (my_board.beans(s, hole));
}
