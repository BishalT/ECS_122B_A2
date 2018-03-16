#include "BloomFilter.h"
#include "gtest/gtest.h"
#include "RandomMatrixHash.h"
#include <iostream>
#include <random>
#include <stdlib.h>
using testing::Test;

using namespace std;
#define NUM_TEST_CASES 10000000
#define SET_SIZE 16384	// 2^14
#define FILTER_SIZE 8 * SET_SIZE	// 2^17
#define ERROR_THRESHOLD .01
#define FALSE_POSITIVE_RATE_TARGET .027

// Sanity check for no false negatives.
// Initialize your bloom filter to have FILTER_SIZE bits.
// Add SET_SIZE elements to both a bloom filter and
// to an STL data structure (I used a vector).
// Then check that every element inserted returns "true"
// when Query is called.

TEST(BloomFilterSanityCheck, NoFalseNegatives) {
  BloomFilter bloom( FILTER_SIZE, SET_SIZE );
  int trueCount = 0;

  for( int i = 0; i < SET_SIZE; i++ ){
    bloom.Insert(i);
  }
  
  for( int i = 0; i < SET_SIZE; i++ ){
    if ( bloom.Query(i) ) {
      trueCount++;
    }
  }

  EXPECT_EQ( trueCount, SET_SIZE );
}

// Sanity check for false positive rate.
// Initialize your bloom filter to have FILTER_SIZE bits.
// Add SET_SIZE elements to the bloom filter then
// check NUM_TEST_CASES randomly generated keys
// not in the set of added elements to approximate
// the false positive rate.

TEST(BloomFilterSanityCheck, FalsePositiveRate) {
  BloomFilter bloom( FILTER_SIZE, SET_SIZE );
  int count = 0;
  int false_pos_count = 0;
  srand(time(NULL));

  for( int i = 0; i < SET_SIZE; i++ ){
    bloom.Insert(i);
  }	// insert numbers 0 to SET_SIZE - 1
  for( int i = 0; i < NUM_TEST_CASES; i++ ){
    int randNum = rand() + SET_SIZE;
    //cout << randNum << endl;
    if( bloom.Query( randNum ) ){
      false_pos_count++;
    }	// check NUM_TEST_CASES with SET_SIZE as an offset
  }
  /*
  for( int i = SET_SIZE; i < NUM_TEST_CASES + SET_SIZE; i++ ){
    if( bloom.Query( i ) ){
      false_pos_count++;
    }	// check NUM_TEST_CASES with SET_SIZE as an offset
  }
*/
 //std::cout << bloom.unique_spaces << std::endl;
 //std::cout << false_pos_count << std::endl;
  EXPECT_NEAR( ((float)false_pos_count) / ((float)(NUM_TEST_CASES)), FALSE_POSITIVE_RATE_TARGET, ERROR_THRESHOLD );
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
