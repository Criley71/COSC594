#include <iostream>
#include <fstream>
#include <math.h>
#include <array>
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
  while(getline(fin, line)){
    if(skip){
      skip = false;
      continue;
    }
    neander_sequence += line;
  }
  fin.close();
  //cout << neander_sequence << "\n";
  double prob = 0;
  for(int i = 0; i < neander_sequence.length(); i++){
    switch(neander_sequence[i]){
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
        prob += log(a_prob); //if nucletide is N then add A's probability
        break;
    }

  }
  cout << prob << "\n"; //expected is -452.662
}