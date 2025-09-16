#include <iostream>
#include <random>
#include <vector>
#include <time.h>
using namespace std;

int main() {
  srand(time(0));
  double sixth = 1 / 6;
  vector<char> dice_numbers = {'1', '2', '3', '4', '5', '6'};
  vector<double> fair_dice = {sixth, sixth, sixth, sixth, sixth, sixth};
  vector<double> loaded_dice = {.1, .1, .1, .1, .1, .5};
  int rand_fair_dice_roll = rand() % 6;   // get numbers 0 through 5
  int rand_load_dice_roll = rand() % 10;  // get numbers 0 through 9, 5-9 are a 6-roll
  int swap_roll = rand() % 100;
  bool is_on_fair_dice = true;
  string dice_choice = "";
  string dice_out = "";
  for (int i = 0; i < 300; i++) {
    if (is_on_fair_dice) {
      rand_fair_dice_roll = rand() % 6;
      dice_choice += 'F';
      dice_out += dice_numbers[rand_fair_dice_roll];
    } else {
      rand_load_dice_roll = rand() % 10;
      if(rand_load_dice_roll > 4){
        rand_load_dice_roll = 5;
      }
      dice_choice += 'L';
      dice_out += dice_numbers[rand_load_dice_roll];
    }
    swap_roll = rand() % 100;
    if(swap_roll < 5){
      is_on_fair_dice = !is_on_fair_dice;
    }
    if((i % 100 == 0 && i != 0) || i == 299){
      cout << dice_choice << "\n";
      cout << dice_out << "\n";
      cout << "\n";
      dice_choice = "";
      dice_out = "";
    }
  }
}