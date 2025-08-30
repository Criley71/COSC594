
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char* argv[]) {
  string file1 = (argc == 3) ? argv[2] : "drosophila.fasta";
  string file2 = (argc == 3) ? argv[1] : "human.fasta";

  ifstream fin1;
  fin1.open(file1);
  if (!fin1.good()) {
    cout << "Error opening " << file1 << "\n";
    perror("");
    return -1;
  }
  ifstream fin2;
  fin2.open(file2);
  if (!fin2.good()) {
    cout << "Error opening " << file2 << "\n";
    perror("");
    return -1;
  }
  string seq1 = "";
  string seq2 = "";
  string line;
  bool skip = true;
  while (getline(fin1, line)) {
    if (skip) {
      skip = false;
      continue;
    }
    seq1 += line;
  }
  skip = true;
  while (getline(fin2, line)) {
    if (skip) {
      skip = false;
      continue;
    }
    seq2 += line;
  }
  fin1.close();
  fin2.close();
  int size_seq1 = seq1.size();
  int size_seq2 = seq2.size();
  vector<vector<int>> align_matrix;
  align_matrix.resize(size_seq1 + 1);
  for (int i = 0; i < size_seq1 + 1; i++) {
    align_matrix[i].resize(size_seq2 + 1, 0);
  }
  // scoring system
  // initialize first column and row to index * gap_penalty
  int match = 2;
  int mismatch_penalty = -1;
  int gap_penalty = -2;
  int diag_score;
  int horz_score;
  int vert_score;
  pair<int, int> max_coord = pair<int, int>(0, 0);
  for (int i = 1; i <= size_seq1; i++) {
    for (int j = 1; j <= size_seq2; j++) {
      diag_score = align_matrix[i - 1][j - 1] + (seq1[i - 1] == seq2[j - 1] ? match : mismatch_penalty);
      horz_score = align_matrix[i][j - 1] + gap_penalty;
      vert_score = align_matrix[i - 1][j] + gap_penalty;
      align_matrix[i][j] = max({diag_score, horz_score, vert_score, 0});
      if (align_matrix[i][j] > align_matrix[max_coord.first][max_coord.second]) {
        max_coord = pair<int, int>(i, j);
      }
    }
  }
  int max_score = align_matrix[max_coord.first][max_coord.second];
  string align_seq1 = "";
  string align_seq2 = "";
  int i = max_coord.first;
  int j = max_coord.second;
  int end_i = i;
  int end_j = j;
  while (align_matrix[i][j] != 0 && (i > 0 || j > 0)) {
    if (i > 0 && j > 0 && align_matrix[i][j] == (align_matrix[i - 1][j - 1] + match)) {
      align_seq1 = seq1[i] + align_seq1;
      align_seq2 = seq2[j] + align_seq2;
      i -= 1;
      j -= 1;
    } else if (i > 0 && align_matrix[i][j] == (align_matrix[i - 1][j] + gap_penalty)) {
      align_seq1 = seq1[i] + align_seq1;
      align_seq2 = "-" + align_seq2;
      i -= 1;
    } else {
      align_seq1 = "-" + align_seq1;
      align_seq2 = seq2[j] + align_seq2;
      j -= 1;
    }
  }
  align_seq1 = seq1[0] + align_seq1;
  align_seq2 = seq2[0] + align_seq2;
  int width = 100;
  for (int i = 0; i < static_cast<int>(align_seq1.length()); i += width) {
    string seq1_substr = align_seq1.substr(i, width);
    string seq2_substr = align_seq2.substr(i, width);

    string match_string = "";
    for (int j = 0; j < static_cast<int>(seq1_substr.size()); j++) {
      if (seq1_substr[j] == seq2_substr[j] && seq1_substr[j] != '-') {
        if (seq1_substr[j] == '\0') continue;
        match_string += "\033[32m|\033[0m";  // if match print green |
      } else if (seq1_substr[j] == '-' || seq2_substr[j] == '-') {
        match_string += "\033[33m-\033[0m";  // if gap match print yellow '-'
      } else {
        match_string += "\033[31mX\033[0m";  // if mismatch print red X
      }
    }

    cout << "Droso: " << seq1_substr << "\n";
    cout << "MATCH: " << match_string << "\n";
    cout << "Human: " << seq2_substr << "\n\n";
  }
  cout << "\nMax Alignment Score: " << max_score << "\n";
  cout << "Sequence starts at Coordinates (" << i << ", " << j <<") and ends at coordinates (" << end_i << ", " << end_j << ")\n";
  cout << "The sequence is " << align_seq1.size() << " nucleotides long\n"; 
}