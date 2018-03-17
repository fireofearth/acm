/*
input:
4 4
1
1
1
1
1 0 1 2 3
2 0 1 2 3
3 0 1 2 3
3 0 1 2 3
4 4
4
4
4
4
1 0 1 2 3
2 0 1 2 3
3 0 1 2 3
3 0 1 2 3
0 0

output:
30
36

passed 26/27 tests

g++ -std=c++11 -o job-postings job-postings.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

// year : choice
int s_matx[4][5] = {
  // 0, c1, c2, c3, c4
  {  0,  0,  0,  0,  0 }, //
  {  0,  4,  3,  2,  1 }, // y1
  {  0,  8,  7,  6,  5 }, // y2
  {  0, 12, 11, 10,  9 }  // y3
};

struct Student {
  int y; // Year
  int c1; int c2; int c3; int c4;
};

struct TestCase {
  int n; int m; // n postings; m students
  int* jobs; // array index is job; val is # positions
  vector<Student*> students;
};

void getMaxSat(TestCase* test_case) {
  int sat = 0;
  vector<Student*> arr[4];
  arr[1] = vector<Student*>();
  arr[2] = vector<Student*>();
  arr[3] = vector<Student*>();

  for(Student* student : test_case->students) {
    arr[student->y].push_back(student);
  }

  for(int k = 3; k > 0; k--) {
    for(Student* student : arr[k]) {
      if       (test_case->jobs[student->c1] > 0) {
        test_case->jobs[student->c1]--;
        sat += s_matx[k][1];

      } else if(test_case->jobs[student->c2] > 0) {
        test_case->jobs[student->c2]--;
        sat += s_matx[k][2];

      } else if(test_case->jobs[student->c3] > 0) {
        test_case->jobs[student->c3]--;
        sat += s_matx[k][3];

      } else if(test_case->jobs[student->c4] > 0) {
        test_case->jobs[student->c4]--;
        sat += s_matx[k][4];

      } else {
        // cout << "ERROR: no room for choices" << endl;
      }
    }
  }

  cout << sat << endl;

  //test_case
}

int main() {
  int n; int m; // n postings; m students
  int cases = 0;
  vector<TestCase*> test_cases;
  TestCase* test_case;
  Student* student;

  
  while(true) {
    cin >> n >> m;
    if(n == 0 && m == 0) break;

    test_case = new TestCase();
    test_case->jobs = new int[n];

    for(int i = 0; i < n; i++) { // postings
      cin >> test_case->jobs[i];
    }

    for(int i = 0; i < m; i++) { // students
      student = new Student();
      cin >> student->y 
          >> student->c1
          >> student->c2
          >> student->c3
          >> student->c4;
      test_case->students.push_back(student);
    }

    test_cases.push_back(test_case);
    cases++;
  }

  for(int i = 0; i < cases; i++)
    getMaxSat(test_cases[i]);

  return 0;
}