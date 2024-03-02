#include <iostream>

using namespace std;

#define TENTH(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT(...) TENTH(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

int main() {
  //cout << COUNT(2) << endl;
  cout << COUNT(2,3) << endl;
  cout << COUNT(2,3,5) << endl;


}
