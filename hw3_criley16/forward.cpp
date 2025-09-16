#include <time.h>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ifstream fin("casino.benchmark1.txt");
  if (!fin.good()) {
    perror("error");
    cout << "error opening casino.benchmark1.txt\n";
    exit(1);
  }
  string buffer = "";
  string dice_rolls;
  while (getline(fin, buffer)) {
    dice_rolls += buffer;
  }
  cout << dice_rolls << "\n";
  int num_rolls = dice_rolls.size();
  vector<pair<double, bool>> fair_sums;  // first val is sum, bool is if it was the greater value at index
  vector<pair<double, bool>> load_sums;  // first val is sum, bool is if it was the greater value at index
  fair_sums.resize(dice_rolls.size() + 1);
  load_sums.resize(dice_rolls.size() + 1);
  fair_sums[0] = make_pair(1, true);
  load_sums[0] = make_pair(0, false);
}