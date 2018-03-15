#ifndef _BLOOM_FILTER_H_
#define _BLOOM_FILTER_H_

#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <random>
#include <time.h>
#include "RandomMatrixHash.h"

//#define NUM_TEST_CASES 100000
#define SET_SIZE 10000
#define FILTER_SIZE 8 * SET_SIZE
//#define FILTER_SIZE 111566

class BloomFilter {
 public:
  BloomFilter(std::size_t bits, std::size_t expectedSetSize);
  void Insert(int x);
  void Insert(std::set<int> S);
  bool Query(int x);

  std::vector<RandomMatrixHash> hash_functions;
  int false_pos = 0;
  int unique_spaces = 0;
  int numHash = 0;
  int bloomArray[ FILTER_SIZE ] = {0};
 private:
};  // BloomFilter

#endif  // _BLOOM_FILTER_H_
