#include <iostream>
#include <fstream>
#include <math.h>
#include <array>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{

  ifstream fin("human_mito.fasta");
  if (!fin.good())
  {
    perror("Error can not open file\n");
    return -1;
  }
  string line;
  string sequence = "";
  bool skip = true;
  while (getline(fin, line))
  {
    if (skip)
    {
      skip = false;
      continue;
    }
    sequence += line;
  }
  // cout << sequence;
  fin.close();

  // begin multinomial model calculations
  array<double, 256> nucleotides;
  nucleotides['A'] = 0;
  nucleotides['T'] = 0;
  nucleotides['C'] = 0;
  nucleotides['G'] = 0;
  nucleotides['N'] = 0;

  for (int i = 0; i < sequence.length(); i++)
  {
    nucleotides[sequence[i]] += 1;
  }

  nucleotides['A'] += nucleotides['N']; // convert any N's to A's
  int nuc_sum = nucleotides['A'] + nucleotides['T'] + nucleotides['C'] + nucleotides['G'];
  double a_prob = nucleotides['A'] / nuc_sum;
  double t_prob = nucleotides['T'] / nuc_sum;
  double c_prob = nucleotides['C'] / nuc_sum;
  double g_prob = nucleotides['G'] / nuc_sum;

  // cout << a_prob << "\n";
  // cout << c_prob << "\n";
  // cout << g_prob << "\n";
  // cout << t_prob << "\n";

  fin.open("neander_sample.fasta");
  if (!fin.good())
  {
    perror("Error can not open neander_sample.fasta\n");
    return -1;
  }
  line = "";
  string neander_sequence = "";
  skip = true;
  while (getline(fin, line))
  {
    if (skip)
    {
      skip = false;
      continue;
    }
    neander_sequence += line;
  }
  fin.close();
  // cout << neander_sequence << "\n";
  double prob = 0;
  for (int i = 0; i < neander_sequence.length(); i++)
  {
    switch (neander_sequence[i])
    {
    case 'A':
      prob += log(a_prob);
      break;
    case 'C':
      prob += log(c_prob);
      break;
    case 'G':
      prob += log(g_prob);
      break;
    case 'T':
      prob += log(t_prob);
      break;
    default:
      prob += log(a_prob); // if nucletide is N then add A's probability
      break;
    }
  }
  cout << "Neanderthal Multinomial Model log-probability:        "<< prob << "\n"; // expected is -452.662
  // end multinomial model
  // begin 3rd order markov model
  int first = 0;
  int second = 1;
  int third = 2;
  int curr = 3;
  double markov_array[4][4][4][4] = {0};
  string markov_sequence = "";
  for (int i = 0; i < sequence.length(); i++)
  {
    switch (sequence[i])
    {
    case 'A':
      markov_sequence += 'A';
      break;
    case 'C':
      markov_sequence += 'B';
      break;
    case 'G':
      markov_sequence += 'C';
      break;
    case 'T':
      markov_sequence += 'D';
      break;
    default:
      markov_sequence += 'A';
      break;
    }
  }
//  cout << markov_sequence << "\n";
  while(curr < markov_sequence.length()){
    markov_array[markov_sequence[first] - 'A'][markov_sequence[second] - 'A'][markov_sequence[third] - 'A'][markov_sequence[curr]-'A'] += 1;
    first = second;
    second = third;
    third = curr;
    curr+=1;
  }
  
  //int mar_sum = 0;
  double markov_prob_array[4][4][4][4] = {0};
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      for(int k = 0; k < 4; k++){
        for(int m = 0; m < 4; m++){
          int order_sum = markov_array[i][j][k][0] + markov_array[i][j][k][1] + markov_array[i][j][k][2] + markov_array[i][j][k][3];
          if( order_sum == 0)break;
          //cout << "order_sum: " << order_sum << "\n";
          //cout << "markov_array: " << markov_array[i][j][k][m] << "\n";
          markov_prob_array[i][j][k][m] = markov_array[i][j][k][m] / order_sum;
          //cout <<  "markov_prob_array: "<<markov_prob_array[i][j][k][m] << "\n";

          //mar_sum += markov_array[i][j][k][m];
        }
      }
    }
  }
  string markov_neander_seq = "";
  for(int i = 0; i < neander_sequence.length(); i++){
    switch (neander_sequence[i])
    {
      case 'A':
      markov_neander_seq += 'A';
      break;
      case 'C':
      markov_neander_seq += 'B';
      break;
      case 'G':
      markov_neander_seq += 'C';
      break;
      case 'T':
      markov_neander_seq += 'D';
      break;
      default:
      markov_neander_seq += 'A';
      break;
    }
  }
  double markov_prob = 0;
  first = 0;
  second = 1;
  third = 2;
  curr = 3;
  for(int i = 0; i < 3; i++){
    switch (neander_sequence[i])
    {
    case 'A':
      markov_prob += log(a_prob);
      break;
    case 'C':
      markov_prob += log(c_prob);
      break;
    case 'G':
      markov_prob += log(g_prob);
      break;
    case 'T':
      markov_prob += log(t_prob);
      break;
    default:
      markov_prob += log(a_prob);
      break;
    }
  }
  while(curr < markov_neander_seq.length()){
    markov_prob += log(markov_prob_array[markov_neander_seq[first]-'A'][markov_neander_seq[second]-'A'][markov_neander_seq[third]-'A'][markov_neander_seq[curr]-'A']);
    first = second;
    second = third;
    third = curr;
    curr+=1;
  }
  //cout << markov_sequence.length() << "\n";
  //cout << mar_sum << "\n";
  cout << "Neanderthal Third-Order Markov Model log-probability: "<< markov_prob << "\n";


}