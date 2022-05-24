#include <iostream>
#include <vector>
#include <string>
#include "storage/slotted_page.h"

using namespace db;
using namespace std;

int main() {
  Page pg;
  Page pg2;

  vector<string> vals;
  vals.push_back("hi");
  vals.push_back("hello");
  vals.push_back("hey");
  vector<int> pk;
  pk.push_back(1);
  pg.addTuple(vals, pk);

  vector<string> vals2;
  vals2.push_back("hello");
  vals2.push_back("hello");
  vals2.push_back("hello");
  vals2.push_back("hello");
  vals2.push_back("hello");
  vals2.push_back("hello");
  vector<int> pk2;
  pg.addTuple(vals2, pk2);

  vector<string> vals3;
  vector<int> pk3;
  pg.addTuple(vals3, pk3);
  vector<Tuple> vt = pg.getTuples();
  cout << pg.size() << "\n";

  pg.removeTuple({0, 2});
  cout << pg.size() << "\n";

  Tuple t = pg.getTuple({0, 1});
  pg.removeTuple(t);
  cout << pg.size() << "\n";

  pg.removeTuple(vt[0]);
  cout << pg.size() << "\n";

  return 0;
}