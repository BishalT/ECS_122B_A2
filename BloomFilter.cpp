#include "BloomFilter.h"
#include <iostream>
#include "RandomMatrixHash.h"

using namespace std;
// # hash functions = # bits / expectedSetSize * ln(2)
// Initialize the bloom filter: compute k and create k hash functions
// using RandomMatrixHash
BloomFilter::BloomFilter(std::size_t bits, std::size_t expectedSetSize) {
  numHash = ceil(( bits / expectedSetSize ) * log(2));
  //numHash = 12;
  srand(time(NULL));
  for( unsigned int index = 0; index < numHash; index++ ){
    RandomMatrixHash hashMatrix( FILTER_SIZE );
    hash_functions.push_back( hashMatrix );
  }
}

// Insert x into the filter
void BloomFilter::Insert(int x) {
  for( int i = 0; i < this->numHash; i++ ) {
    std::size_t hash_index = hash_functions[i].Hash(x);
    if( bloomArray[ hash_index ] == 0 ){
       unique_spaces++;
    }
    bloomArray[ hash_index ]++;
 }
}

// Insert all of S into the filter
void BloomFilter::Insert(std::set<int> S) {
   for ( int hash_index : S ) {
     Insert( hash_index );
   }
}

// Check if x is in the set
bool BloomFilter::Query(int x) {
  for (int i = 0; i < numHash; i++) {
    std::size_t hash_index = hash_functions[i].Hash(x);
    if( bloomArray[ hash_index ] == 0 ){
      return false;
    }
  }
  return true;
}

/*
int main() {
  BloomFilter bloom( FILTER_SIZE, SET_SIZE );
  //bloom.Insert(15);
  /* //NoFalseNegatives Sanity Check
  int trueCount = 0;
  std::vector<int> omegaLuls;
  for( int i = 0; i < NUM_TEST_CASES; i++ ){
    bloom.Insert(i);
    omegaLuls.push_back(i);
  }

  for( int i = 0; i < NUM_TEST_CASES; i++ ){
    bloom.Query(i);
    trueCount++;
  }

  std::cout << trueCount << std::endl;

  int countTakenSpaces = 0;
  std::vector<int> omegaLuls;
  for( int i = 0; i < SET_SIZE; i++ ){
      bloom.Insert(i);
      countTakenSpaces++;
  }
  int count = 0;
  int false_pos_count = 0;
  srand(time(NULL));

  for( int i = 0; i < 100; i++ ){
    int rand_num = rand() + SET_SIZE;
    if( bloom.Query(rand_num) ){
      false_pos_count++;
    }
    count++;
  }

  cout << "NUM HASH: " << bloom.numHash << endl;
  cout << "SIZE OF FILTER: " << sizeof(bloom.bloomArray)/sizeof(int) << endl;
  std::cout << "SPACES TAKEN: " << countTakenSpaces << std::endl;
  std::cout << "FALSE COUNTS: " << false_pos_count << std::endl;
  std::cout << "RATE OF FALSE COUNTS: " << ((float)false_pos_count) / ((float)FILTER_SIZE) << std::endl;

  return 0;

}*/
