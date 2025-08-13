#include <fstream>
#include <iostream>
#include <map>
#include <array>
using namespace std;


int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    perror("Usage ./frequency_analysis sequence.fasta\n");
    return 1;
  }
  
  ifstream fin(argv[1]);
  if(!fin.good()){
    perror("Error can not open ");
    cout << argv[1] << "\n";
    return 1;
  }
  string line;
  string sequence = "";
  bool skip = true;
  while(getline(fin, line)){
    if(skip){
      skip = false;
      continue;
    }
    sequence += line;
  }
  cout << sequence << "\n";
  fin.close();
  
  array<int, 256> nucleotides;
  map<string, int> dinucleotides;

  nucleotides['A'] = 0;
  nucleotides['T'] = 0;
  nucleotides['C'] = 0;
  nucleotides['G'] = 0;

  dinucleotides["AA"] = 0;
  dinucleotides["AT"] = 0;
  dinucleotides["AG"] = 0;
  dinucleotides["AC"] = 0;
  dinucleotides["TA"] = 0;
  dinucleotides["TT"] = 0;
  dinucleotides["TG"] = 0;
  dinucleotides["TC"] = 0;
  dinucleotides["GA"] = 0;
  dinucleotides["GT"] = 0;
  dinucleotides["GG"] = 0;
  dinucleotides["GC"] = 0;
  dinucleotides["CA"] = 0;
  dinucleotides["CT"] = 0;
  dinucleotides["CG"] = 0;
  dinucleotides["CC"] = 0;

  int left = 0;
  int right = 1;
  
  while(right < sequence.length()){
    string combine = "";
    combine += sequence[left];
    combine += sequence[right];
    nucleotides[sequence[left]] += 1;
    dinucleotides[combine] += 1;
    left++;
    right++;
  }
  nucleotides[sequence[left]] += 1;
  cout << "A:  " <<  nucleotides['A'] << '\n';
  cout << "T:  " <<  nucleotides['T'] << '\n';
  cout << "G:  " <<  nucleotides['G'] << '\n';
  cout << "C:  " <<  nucleotides['C'] << '\n';
  cout << "AA: " << dinucleotides["AA"] << "\n";
  cout << "AT: " << dinucleotides["AT"] << "\n";
  cout << "AG: " << dinucleotides["AG"] << "\n";
  cout << "AC: " << dinucleotides["AC"] << "\n";
  cout << "TA: " << dinucleotides["TA"] << "\n";
  cout << "TT: " << dinucleotides["TT"] << "\n";
  cout << "TG: " << dinucleotides["TG"] << "\n";
  cout << "TC: " << dinucleotides["TC"] << "\n";
  cout << "GA: " << dinucleotides["GA"] << "\n";
  cout << "GT: " << dinucleotides["GT"] << "\n";
  cout << "GG: " << dinucleotides["GG"] << "\n";
  cout << "GC: " << dinucleotides["GC"] << "\n";
  cout << "CA: " << dinucleotides["CA"] << "\n";
  cout << "CT: " << dinucleotides["CT"] << "\n";
  cout << "CG: " << dinucleotides["CG"] << "\n";
  cout << "CC: " << dinucleotides["CC"] << "\n";
  int sum = 0;
  for(auto itr = dinucleotides.begin(); itr != dinucleotides.end(); itr++){
    sum += itr->second; 
  }
  cout << sum << "\n";
return 0;


}