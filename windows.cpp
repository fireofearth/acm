#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

/*
screen res 10^6 X 10^6
(0,0) upper-left; (999999,999999) lower-right

each input:
ln 1: pos int n rep nbr of windows opened
lns n: r c w h
  each window
  (r, c) coords of upper-left 0 <= r,c <= 999999
  (w, h) size of window 1 <= w,h
  all windows lie entirely on desktop (no cropping)
ln 2: pos int m rep nbr of queries
lns m: cr cc
  (cr, cc) coords of clicking on desktop

output:
ln 1: the desktop case
ln m: the response of each query
  background if nothing clicked
  window nbr for window clicked

*/

struct I {

};

struct Query : I {
  int id;
  int row;
  int col;
};

struct Window : I {
  int id;
  int urow;
  int lrow;
  int rcol;
  int lcol;
};

struct TestCase {
  int desktop;
  list<Window*> windows;
  vector<Query*> queries;
};

bool inCoords(Window* w, Query* q);
void setCoords(Window* w, int row, int col, int wid, int hgt);

int main() {
  //
  int row, col, wid, hgt;
  int nbrQueries; int nbrWindows = 1;
  Window* window;
  Query* query;
  int desktop = 1;
  TestCase testCase;
  vector<TestCase> testCases;
  vector<I*> dynamic;

  while(true) {
    cin >> nbrWindows;
    if(nbrWindows < 1) break;

    testCase = TestCase();
    testCase.desktop = desktop;

    for(int windowNbr = 1; windowNbr <= nbrWindows; windowNbr++) {
      cin >> row >> col >> wid >> hgt;
      window = new Window();
      window->id = windowNbr;
      setCoords(window, row, col, wid, hgt);

      dynamic.push_back(window);
      testCase.windows.push_front(window);
    }

    cin >> nbrQueries;
    for(int queryNbr = 1; queryNbr <= nbrQueries; queryNbr++) {
      cin >> row >> col;
      query = new Query();
      query->id = queryNbr;
      query->row = row;
      query->col = col;

      dynamic.push_back(query);
      testCase.queries.push_back(query);
    }

    testCases.push_back(testCase);
    desktop++;
  }
  
  bool hitWindow;
  for(TestCase& t: testCases) {
    cout << "Desktop " << t.desktop << ":\n";
    
    for(Query* q: t.queries) {
      /*cout << "TRACE: query " << q->id 
        << "(r,c)=(" << q->row << ","<< q->col << ")\n";*/
      hitWindow = false;

      for(Window* w: t.windows) {
        // cout << "TRACE: querying window " << w->id <<endl;
        if(inCoords(w, q)) {
          cout << "window " << w->id << endl;
          hitWindow = true;
          break;
        }
      }

      if(!hitWindow)
        cout << "background\n";
    }
  }


  return 0;
}

bool inCoords(Window* w, Query* q) {
  bool below_urow  = q->row >= w->urow;
  bool above_lrow  = q->row <  w->lrow;
  bool after_lcol  = q->col >= w->lcol;
  bool before_rcol = q->col <  w->rcol;

  /*cout << "TRACE: row" 
    << q->row << " >= " << w->urow
    << " " << (below_urow? "true" : "false") << "; "
    << q->row << " < " << w->lrow
    << " " << (above_lrow? "true" : "false") << endl;*/

  return below_urow && above_lrow && after_lcol && before_rcol;
}

void setCoords(Window* w, int row, int col, int wid, int hgt) {
  w->urow = row;
  w->lrow = row + hgt;
  w->rcol = col + wid;
  w->lcol = col;
}