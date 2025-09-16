#include <time.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void forward(string dice_rolls);

int main() {
  forward("casino.benchmark1.txt");
  forward("casino.benchmark2.txt");
  return 0;
}

void forward(string file){
ifstream fin(file);
  if (!fin.good()) {
    perror("error");
    exit(1);
  }
  string buffer = "";
  string dice_rolls;
  while (getline(fin, buffer)) {
    dice_rolls += buffer;
  }
  fin.close();
  int num_rolls = dice_rolls.size();
  vector<double> fair;
  vector<double> load;
  fair.resize(1 + num_rolls);
  load.resize(1 + num_rolls);
  fair[0] = 1;
  load[0] = 0;
  double sixth = 1.0 / 6.0;
  vector<double> fair_chances = {sixth, sixth, sixth, sixth, sixth, sixth};
  vector<double> load_chances = {.1, .1, .1, .1, .1, .5};
  for (int i = 1; i <= num_rolls; i++) {
    int roll = dice_rolls[i - 1] - '0';
    double fair_roll_chance = fair_chances[roll-1];
    double load_roll_chance = load_chances[roll-1];

    fair[i] = (fair[i-1]*.95 + load[i-1]*.1) * fair_roll_chance;
    load[i] = (fair[i-1]*.05 + load[i-1]*.9) * load_roll_chance;
  }
  double probability = fair[num_rolls] + load[num_rolls];
  cout << "Probability of sequence: " << probability << "\n";
}