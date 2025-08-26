#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 3){
    cout << "Error: Expected 2 fasta files as input.\nUSAGE: ./globalign seq1.fasta seq2.fast\n\n";
    return -1;
  }
  ifstream fin1;
  fin1.open(argv[1]);
  if(!fin1.good()){
    perror("Error opening first file\n");
    return -1;
  }
  ifstream fin2;
  fin2.open(argv[2]);
  if(!fin2.good()){
    perror("Error opening second file\n");
    return -1;
  }
}