#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "Side.h"
#include <cassert>

//int main()
//{
//    //=====================testing Board's Class=========================================
//
//    //Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole.
//    Board test(3, 4);
//
//    //test if holes() returns the number of holes on a side (not counting the pot).
//    assert(test.holes()==3 && test.beans(SOUTH, POT)==0);
//
//    //test if beans() return the number of beans in the indicated hole or pot,
//    //or −1 if the hole number is invalid.
//    assert(test.beans(NORTH, POT)==0);
//    assert(test.beans(NORTH, 1)==4);
//    assert(test.beans(NORTH, 2)==4);
//    assert(test.beans(NORTH, 3)==4);
//    assert(test.beans(SOUTH, 3)==4);
//    assert(test.beans(SOUTH, 2)==4);
//    assert(test.beans(SOUTH, 1)==4);
//    assert(test.beans(SOUTH, 5)==-1);
//    assert(test.beans(NORTH, -8)==-1);
//    //test if beansInPlay() returns the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
//    assert(test.beansInPlay(SOUTH)==12);
//    assert(test.beansInPlay(NORTH)==12);
//
//    //test if totalBeans() return the total number of beans in the game, including any in the pots.
//    assert(test.totalBeans()==24);
//
//    //test sow() If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything.
//    Side endside;
//    int endHole;
//    //pot
//    assert(!test.sow(SOUTH, POT, endside, endHole));
//    //invalid
//    assert(!test.sow(SOUTH, 7, endside, endHole));
//
//    //test setBeans() If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter.
//    assert(!test.setBeans(SOUTH, -3, 2));
//    assert(!test.setBeans(SOUTH, 3, -2));
//    assert(test.beans(SOUTH, POT)==0);
//    assert(test.beans(NORTH, POT)==0);
//    assert(test.beans(NORTH, 1)==4);
//    assert(test.beans(NORTH, 2)==4);
//    assert(test.beans(NORTH, 3)==4);
//    assert(test.beans(SOUTH, 3)==4);
//    assert(test.beans(SOUTH, 2)==4);
//    assert(test.beans(SOUTH, 1)==4);
//
//    assert(test.setBeans(SOUTH, 3, 0));
//    assert(test.beans(SOUTH, 3)==0);
//    //empty hole
//    assert(!test.sow(SOUTH, 3, endside, endHole));
//    assert(!test.setBeans(SOUTH, -3, 2));
//    assert(!test.setBeans(SOUTH, 3, -2));
//    assert(test.beans(SOUTH, POT)==0);
//    assert(test.beans(NORTH, POT)==0);
//    assert(test.beans(NORTH, 1)==4);
//    assert(test.beans(NORTH, 2)==4);
//    assert(test.beans(NORTH, 3)==4);
//    assert(test.beans(SOUTH, 3)==0);
//    assert(test.beans(SOUTH, 2)==4);
//    assert(test.beans(SOUTH, 1)==4);
//
//    //test sow(): it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed.
//    assert(test.sow(SOUTH, 2, endside, endHole));
//    assert(test.beans(SOUTH, POT)==1);
//    assert(test.beans(NORTH, POT)==0);
//    assert(test.beans(NORTH, 1)==4);
//    assert(test.beans(NORTH, 2)==5);
//    assert(test.beans(NORTH, 3)==5);
//    assert(test.beans(SOUTH, 3)==1);
//    assert(test.beans(SOUTH, 2)==0);
//    assert(test.beans(SOUTH, 1)==4);
//    assert(endside==NORTH);
//    assert(endHole==2);
//
//    assert(test.setBeans(NORTH, 2, 7));
//    assert(test.sow(NORTH, 2, endside, endHole));
//    assert(test.beans(SOUTH, POT)==1);
//    assert(test.beans(NORTH, POT)==1);
//    assert(test.beans(NORTH, 1)==5);
//    assert(test.beans(NORTH, 2)==1);
//    assert(test.beans(NORTH, 3)==6);
//    assert(test.beans(SOUTH, 3)==2);
//    assert(test.beans(SOUTH, 2)==1);
//    assert(test.beans(SOUTH, 1)==5);
//    assert(endside==NORTH);
//    assert(endHole==2);
//
//    //constructor test: If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
//    Board test1(0, -3);
//    assert(test1.beans(NORTH, POT)==0);
//    assert(test1.beans(SOUTH, POT)==0);
//    assert(test1.beans(NORTH, 1)==0);
//    assert(test1.beans(SOUTH, 1)==0);
//    assert(test1.beans(NORTH, 2)==-1);
//    assert(test1.beans(SOUTH, 2)==-1);
//
//    //test movetopot() If the indicated hole is invalid or a pot, return false without changing anything.
//    assert(!test.moveToPot(SOUTH, 0, SOUTH));
//    assert(!test.moveToPot(SOUTH, -3, SOUTH));
//    assert(test.beans(SOUTH, POT)==1);
//    assert(test.beans(NORTH, POT)==1);
//    assert(test.beans(NORTH, 1)==5);
//    assert(test.beans(NORTH, 2)==1);
//    assert(test.beans(NORTH, 3)==6);
//    assert(test.beans(SOUTH, 3)==2);
//    assert(test.beans(SOUTH, 2)==1);
//    assert(test.beans(SOUTH, 1)==5);
//
//    //MOVEtoPot() move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
//    assert(test.moveToPot(NORTH, 3, SOUTH));
//    assert(!test.moveToPot(SOUTH, 0, SOUTH));
//    assert(!test.moveToPot(SOUTH, -3, SOUTH));
//    assert(test.beans(SOUTH, POT)==7);
//    assert(test.beans(NORTH, POT)==1);
//    assert(test.beans(NORTH, 1)==5);
//    assert(test.beans(NORTH, 2)==1);
//    assert(test.beans(NORTH, 3)==0);
//    assert(test.beans(SOUTH, 3)==2);
//    assert(test.beans(SOUTH, 2)==1);
//    assert(test.beans(SOUTH, 1)==5);
//
//
//    //===============================test the Player's class===========================================
//    HumanPlayer hp1("hi");
//    assert(hp1.isInteractive());
//    assert(hp1.name()=="hi");
//    BadPlayer bp3("hi");
//    assert(!bp3.isInteractive());
//    assert(bp3.name()=="hi");
//    SmartPlayer sp1("hi");
//    assert(!sp1.isInteractive());
//    assert(sp1.name()=="hi");
//
//    //test chooseMove
//    HumanPlayer hp("Marge");
//    assert(hp.name() == "Marge"  &&  hp.isInteractive());
//    BadPlayer bp("Homer");
//    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
//    SmartPlayer sp("Lisa");
//    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
//    Board b2(3, 2);
//    b2.setBeans(SOUTH, 2, 0);
//    std::cout << "=========" << std::endl;
//    int n = hp.chooseMove(b2, SOUTH);
//    std::cout << "=========" << std::endl;
//    assert(n == 1  ||  n == 3);
//    n = bp.chooseMove(b2, SOUTH);
//    assert(n == 1  ||  n == 3);
//    n = sp.chooseMove(b2, SOUTH);
//    assert(n == 1  ||  n == 3);
//
//    //========================test the game() class by playing the game===========================
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b1(3, 0);
//    b1.setBeans(SOUTH, 1, 2);
//    b1.setBeans(NORTH, 2, 1);
//    b1.setBeans(NORTH, 3, 2);
//    Game g(b1, &bp1, &bp2);
//    bool over;
//    bool hasWinner;
//    Side winner;
//    //    Homer
//    //   0  1  2
//    // 0         0
//    //   2  0  0
//    //    Bart
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//           g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//    g.move();
//    //   0  1  0
//    // 0         3
//    //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    g.move();
//    //   1  0  0
//    // 0         3
//    //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    g.move();
//    //   1  0  0
//    // 0         3
//    //   0  0  1
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//    g.move();
//    //   0  0  0
//    // 1         4
//    //   0  0  0
//    g.status(over, hasWinner, winner);
//    assert(over);
//    assert(g.beans(NORTH, POT) == 1);
//    assert(g.beans(SOUTH, POT) == 4);
//    assert(g.beans(NORTH, 1) == 0);
//    assert(g.beans(NORTH, 2) == 0);
//    assert(g.beans(NORTH, 3) == 0);
//    assert(g.beans(SOUTH, 1) == 0);
//    assert(g.beans(SOUTH, 2) == 0);
//    assert(g.beans(SOUTH, 3) == 0);
//    assert(hasWinner && winner == SOUTH);
//
//    Board b(3, 2);
//    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
//           b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
//    b.setBeans(SOUTH, 1, 1);
//    b.moveToPot(SOUTH, 2, SOUTH);
//    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
//           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
//           b.beansInPlay(SOUTH) == 3);
//    Side es;
//    int eh;
//    b.sow(SOUTH, 3, es, eh);
//    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
//           b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
//           b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
//
//    std::cerr<<"all test passed!"<<std::endl;
//}


//int main()
//{
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 2);
//    Game g(b, &bp1, &bp2);
//    g.play();
//}

int main()
{
    HumanPlayer hp("Marge");
    SmartPlayer bp("Homer");
    Board b(6, 4);
    Game g(b, &hp, &bp);
    g.play();


}



//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//
//using namespace std;
//
//void doPlayerTests()
//{
//    HumanPlayer hp("Marge");
//    assert(hp.name() == "Marge"  &&  hp.isInteractive());
//    BadPlayer bp("Homer");
//    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
//    SmartPlayer sp("Lisa");
//    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
//    Board b(3, 2);
//    b.setBeans(SOUTH, 2, 0);
//    cout << "=========" << endl;
//    int n = hp.chooseMove(b, SOUTH);
//    cout << "=========" << endl;
//    assert(n == 1  ||  n == 3);
//    n = bp.chooseMove(b, SOUTH);
//    assert(n == 1  ||  n == 3);
//    n = sp.chooseMove(b, SOUTH);
//    assert(n == 1  ||  n == 3);
//}
//
//int main()
//{
//    doPlayerTests();
//    cout << "Passed all tests" << endl;
//    }

//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 0);
//    b.setBeans(SOUTH, 1, 2);
//    b.setBeans(NORTH, 2, 1);
//    b.setBeans(NORTH, 3, 2);
//    Game g(b, &bp1, &bp2);
//    bool over;
//    bool hasWinner;
//    Side winner;
//    //    Homer
//    //   0  1  2
//    // 0         0
//    //   2  0  0
//    //    Bart
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//           g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//    g.move();
//    //   0  1  0
//    // 0         3
//    //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    g.move();
//    //   1  0  0
//    // 0         3
//    //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    g.move();
//    //   1  0  0
//    // 0         3
//    //   0  0  1
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//    g.move();
//    //   0  0  0
//    // 1         4
//    //   0  0  0
//    g.status(over, hasWinner, winner);
//    assert(over);
//    assert(g.beans(NORTH, POT) == 1);
//    assert(g.beans(SOUTH, POT) == 4);
//    assert(g.beans(NORTH, 1) == 0);
//    assert(g.beans(NORTH, 2) == 0);
//    assert(g.beans(NORTH, 3) == 0);
//    assert(g.beans(SOUTH, 1) == 0);
//    assert(g.beans(SOUTH, 2) == 0);
//    assert(g.beans(SOUTH, 3) == 0);
//    assert(hasWinner && winner == SOUTH);
//}
//
//int main()
//{
//    doGameTests();
//    cout << "Passed all tests" << endl;
//}

//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doBoardTests()
//{
//    Board b(3, 2);
//    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
//           b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
//    b.setBeans(SOUTH, 1, 1);
//    b.moveToPot(SOUTH, 2, SOUTH);
//    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
//           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
//           b.beansInPlay(SOUTH) == 3);
//    Side es;
//    int eh;
//    b.sow(SOUTH, 3, es, eh);
//    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
//           b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
//           b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
//}
//
//int main()
//{
//    doBoardTests();
//    cout << "Passed all tests" << endl;
//}


//int main()
//{
//    HumanPlayer hp("Marge");
//    SmartPlayer bp("Homer");
//    Board b(4, 4);
//    Game g(b, &hp, &bp);
//    g.play();

//    HumanPlayer hp("Marge");
//    SmartPlayer bp("Homer");
//    Board b(3, 2);
//    b.setBeans(SOUTH, 0, 2);
//    b.setBeans(SOUTH, 1, 2);
//    b.setBeans(SOUTH, 2, 0);
//    b.setBeans(SOUTH, 3, 0);
//    b.setBeans(NORTH, 0, 1);
//    b.setBeans(NORTH, 1, 3);
//    b.setBeans(NORTH, 2, 4);
//    b.setBeans(NORTH, 3, 0);
//    bp.chooseMove(b, NORTH);
//}

