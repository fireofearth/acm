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

each input:
ln 1: number of cards laid out
ln 2: n chars corr U faced up or D faced down
ln 3: n-1 chars corr to R right flip L left flip
ln 4: has form "<m> <q1> <q2> ... <qm>"
  where each qi is a query on a position of a card in pile
0 for end of output

5
UUUDD
RRLL
5 1 2 3 4 5
10
UUDDUUDDUU
LLLRRRLRL
4 3 7 6 1
0
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
  vector<Flip> ops;
  vector<int> queries;
};

void runTests(TestCase& testCase);
void printTable(const deque< deque<Card*> >& table);
void printPile(const deque<Card*>& pile);
bool makeTable(TestCase& testCase, const string& corrFaces, vector<Card*>& dynamic);
bool makeOperations(TestCase& testCase, const string& operations);

int main(/*int argc, char* argv[]*/) {
  int numCards = 1; string corrFaces; string operations;
  vector<Card*> dynamic;
  int testCaseNbr = 1;
  int queryNbr;
  // vector<int> queries;
  TestCase testCase;
  vector<TestCase> testCases;

  while(true) {

    cin >> numCards;

    if(numCards < 1) break;

    cin >> corrFaces;
    cin >> operations;
    cin >> queryNbr;

    testCase.queries.resize(queryNbr);

    for(int i = 0; i < queryNbr; i++)
      cin >> testCase.queries[i];

    testCase.caseNbr = testCaseNbr;
    testCase.numCards = numCards;
    testCase.table = deque< deque<Card*> >();

    if(makeTable(testCase, corrFaces, dynamic)) { /* continue */ }
    else return 0;

    if(makeOperations(testCase, operations)) { /* continue */ }
    else return 0;

    testCases.push_back(testCase);
    testCase = TestCase();
    testCaseNbr++;
  }

  for(TestCase& t: testCases)
    runTests(t);

  for(Card* c: dynamic)
    delete c;

  return 0;
}

void runTests(TestCase& testCase) {
  Card* card; deque<Card*> pile; int ctr = 0;

  cout << "TRACE: " << testCase.ops.size() << " ";
  for(Flip op: testCase.ops)
    cout << (op? "right" : "left") << " ";
  cout << endl;

  for(Flip& op: testCase.ops) {
    cout << "TRACE: " << ctr << " "; 
    printTable(testCase.table); cout << endl;

    if(op == LEFT) {
      // pop leftmost to pile
      pile = testCase.table.front();
      testCase.table.pop_front();

      // for each in pile push to front of next leftmost pile
      for(auto it = pile.begin(); it < pile.end(); it++) {
        card = *it;
        if(card->face == UP) card->face = DOWN;
        else                 card->face = UP;

        testCase.table.front().push_front(card);
      }
    } else {
      // pop rightmost to pile
      pile = testCase.table.back();
      testCase.table.pop_back();

      // for each in pile push to front of next rightmost pile
      for(auto it = pile.begin(); it < pile.end(); it++) {
        card = *it;
        if(card->face == UP) card->face = DOWN;
        else                 card->face = UP;

        testCase.table.back().push_front(card);
      }
    }

    ctr++;
  }

  testCase.pile = testCase.table[0];
  testCase.table.pop_back();

  cout << "TRACE: "; printPile(testCase.pile); cout << endl;

  cout << "Pile " << testCase.caseNbr << endl;
  for(int& q: testCase.queries)
    cout << "Card " << q << " is a face " 
      << (testCase.pile[q - 1]->face ? "up" : "down") 
      << " " << testCase.pile[q - 1]->num << endl;
}

void printTable(const deque< deque<Card*> >& table) {
  cout << "[";
  for(auto it = table.begin(); it < table.end(); it++) {
    cout << " "; printPile(*it);
  }
  cout << " ]";
}

void printPile(const deque<Card*>& pile) {
  Card* card;

  cout << "< ";
  for(auto it = pile.begin(); it < pile.end(); it++) {
    card = *it;
    cout << card->num << (card->face == UP ? "up" : "dn") << " ";
  }
  cout << ">";
}

bool makeTable(TestCase& testCase, const string& corrFaces, vector<Card*>& dynamic) {
   int cardNum = 1; deque<Card*> pile; Card* card;

  if(corrFaces.length() != (unsigned long) testCase.numCards) {
    cout << "ERROR: faces don't match cards!\n"; return false;
  }

  for(auto it = corrFaces.begin(); it < corrFaces.end(); it++) {
    card = new Card();
    card->num = cardNum;

    if       (*it == 'U') {
      card->face = UP; 
    } else if(*it == 'D') {
      card->face = DOWN;
    } else {
      cout << "ERROR: incorrect face!\n"; return false;
    }

    pile = deque<Card*>();
    pile.push_back(card);
    dynamic.push_back(card);
    testCase.table.push_back(pile);

    cardNum++;
  }

  return true;
}

bool makeOperations(TestCase& testCase, const string& operations) {

  if(operations.length() != (unsigned long) (testCase.numCards - 1)) {
    cout << "ERROR: not the righ amt of ops!\n"; return false;
  }

  for(auto it = operations.begin(); it < operations.end(); it++) {
    if       (*it == 'L') {
      testCase.ops.push_back(LEFT);
    } else if(*it == 'R') {
      testCase.ops.push_back(RIGHT);
    } else {
      cout << "ERROR: incorrect operations!\n"; return false;
    }
  }

  return true;
}