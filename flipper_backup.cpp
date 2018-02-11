#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

/*
Start with n cards 1 to n in row left (1st) to right (nth)
cards are either faced up or down
n - 1 flips either right flips or left flips

ex:
(left) 1up 2up 3up 4dn 5dn (right)
<(top) (bottom)>
2 right flips
then 2 left flips

0: 1up 2up 3up 4dn 5dn
1: 1up 2up 3up < 5up 4dn >
2: 1up 2up < 4up 5dn 3up >
3: < 1dn 2up > < 3up 5dn 4up >
4: < 2dn 1up 3up 5dn 4up >

< 2dn 1up 4up 5dn 3up >

each input:
ln 1: number of cards laid out
ln 2: n chars corr U faced up or D faced down
ln 3: n-1 chars corr to R right flip L left flip
ln 4: has form "<m> <q1> <q2> ... <qm>"
  where each qi is a query on a position of a card in pile
0 for end of output

TODO: finish the querying and multiple test cases
TODO: fix memory leak
*/

enum Face { UP   = 1, DOWN = 0 };

enum Flip {
  RIGHT = 1, // right to left
  LEFT  = 0  // left  to right
};

struct Card {
  int num;
  Face face;
};

struct TestCase {
  int caseNbr;
  int numCards; // number of cards laid out
  deque< deque<Card*> > table;
  deque<Card*> pile;
};

void printPile(deque<Card*> pile);

int main(/*int argc, char* argv[]*/) {
  int numCards; string corrFaces; string operations;
  Card* card;
  deque<Card*> pile;
  vector<Card*> dynamic;
  cin >> numCards;
  cin >> corrFaces;
  cin >> operations;

  if(numCards < 1) {
    cout << "ERROR: less than 1 card!\n"; return 0;
  }

  if(corrFaces.length() != (unsigned long) numCards) {
    cout << "ERROR: faces don't match cards!\n"; return 0;
  }

  if(operations.length() != (unsigned long) (numCards - 1)) {
    cout << "ERROR: not the righ amt of ops!\n"; return 0;
  }

  TestCase myTest;
  myTest.caseNbr = 1;
  myTest.numCards = numCards;
  myTest.table = deque< deque<Card*> >();
  int cardNum = 1;
  for(auto it = corrFaces.begin(); it < corrFaces.end(); it++) {
    card = new Card();
    card->num = cardNum;

    if(*it == 'U') {
      card->face = UP; 
    } else if(*it == 'D') {
      card->face = DOWN;
    } else {
      cout << "ERROR: incorrect face!\n";
      return 0;
    }

    pile = deque<Card*>();
    pile.push_back(card);
    dynamic.push_back(card);
    myTest.table.push_back(pile);

    cardNum++;
  }

  //cout << "TRACE: after loop\n";
  //cout << "TRACE: " << myTest.table.size() << endl;

  /*for(int i = 0; i < myTest.numCards; i++) {
    cout << "TRACE: " << myTest.table[i][0]->num << " "
      << myTest.table[i][0]->face << endl;
  }*/

  for(auto it = operations.begin(); it < operations.end(); it++) {
    char op = *it;
    if(op == 'L') {
      // pop leftmost to pile
      pile = myTest.table.front();
      myTest.table.pop_front();

      // deque<Card*>* toPile = myTest.table.front();

      // for each in pile push to front of next leftmost pile
      for(auto it = pile.begin(); it < pile.end(); it++) {
        card = *it;
        if(card->face == UP) card->face = DOWN;
        else                 card->face = UP;

        myTest.table.front().push_front(card);
      }

    } else if(op == 'R') {
      // pop rightmost to pile
      pile = myTest.table.back();
      myTest.table.pop_back();

      // for each in pile push to front of next rightmost pile
      for(auto it = pile.begin(); it < pile.end(); it++) {
        card = *it;
        if(card->face == UP) card->face = DOWN;
        else                 card->face = UP;

        myTest.table.back().push_front(card);
      }

    } else {
      cout << "ERROR: incorrect operation!\n";
      return 0;
    }
  }

  myTest.pile = myTest.table[0];
  myTest.table.pop_back();
  // printPile(myTest.pile);


  // cout << "TRACE: table size now " << myTest.table.size() << endl;
}

void printPile(deque<Card*> pile) {
  Card* card;
  cout << "< ";
  for(auto it = pile.begin(); it <pile.end(); it++) {
    card = *it;
    cout << card->num << (card->face == UP ? "up" : "dn") << " ";
  }
  cout << ">\n";
}