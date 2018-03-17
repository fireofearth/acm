#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
anthony A points; cora C points

each game anthony or cora lose one point, not both

anthony has p_i probability winning

find probability of anthony winning the game

g++ -std=c++11 -o anth-and-cora anth-and-cora.cpp

3 2
1.0
0.0
1.0
0.0
exp output: 1.000000

3 2 0.5 0.5 0.5 0.5
exp output: 0.687500

2 3 0.5 0.5 0.5 0.5
exp output: 0.312500

1 1
0.500000
exp output: 0.500000

Solution passes two tests but memory exceeded (1024 MB); I need to implement dynamic memory storage.

*/

struct GameTree {
  int level;
  float p_win;
  int A;
  int C;
  GameTree* win_t;
  GameTree* lose_t;
};

void makeGameTree(int curr_l, vector<float>& game_prob, GameTree* curr,
  int A, int C) {

  curr->A = A;
  curr->C = C;
  curr->level = curr_l;

  if(curr->A > 0 && curr->C > 0) {

    curr->p_win = game_prob[curr_l];

    curr->win_t  = new GameTree();
    curr->lose_t = new GameTree();

    // cout << "DEBUG: level=" << curr->level << " (A,C)=(" << curr->A << "," << curr->C << ") p_win=" << curr->p_win << endl;

    makeGameTree(curr_l+1, game_prob, curr->win_t, A, C-1);
    makeGameTree(curr_l+1, game_prob, curr->lose_t, A-1, C);
  } else {

    curr->win_t  = NULL;
    curr->lose_t = NULL;

  }
}

float getTotalProb(GameTree* curr, float p_win) {

  /*cout << "DEBUG: curr_l= " << curr->level 
    << " curr->p_win=" << fixed << curr->p_win << " p_win=" << p_win << endl;*/

  if(curr->A > 0 && curr-> C > 0) {
    return getTotalProb(curr->win_t, curr->p_win * p_win) // if win
      + getTotalProb(curr->lose_t, (1 - curr->p_win) * p_win );   // if lose
  }

  if(curr->A > 0) {
    return p_win;
  }

  return 0;

}

int main() {
  cout.precision(6);
  int A = 0;
  int C = 0;
  int total_games = 0;
  vector<float> game_prob;
  GameTree* root;

  cin >> A; 
  cin >> C;
  if(A < 1 || C < 1) return 0;

  total_games = A + C - 1;
  game_prob.reserve(total_games);

  for(int i = 0; i < total_games; i++) {
    cin >> game_prob[i];
  }

  // make tree
  root = new GameTree();
  makeGameTree(0, game_prob, root, A, C);

  // recurse tree; ret prob of winning
  float total_prob = getTotalProb(root, 1.00);

  cout << fixed << total_prob << endl;

  return 0;
}