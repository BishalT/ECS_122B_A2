#include "RandomMatrixHash.h"
#include "gtest/gtest.h"
#include <iostream>
using testing::Test;

#define NUM_TEST_CASES 100000
#define TABLE_SLOTS 256
#define ERROR_THRESHOLD .001

// Sanity check for entries in the random matrix.
// Create NUM_TEST_CASES random matrices,
// then use EXPECT_NEAR(x, y, threshold) where
// threshold = ERROR_THRESHOLD to verify that each entry
// of the matrix is 1 with probability 1/2
TEST(RandomMatrixSanityCheck, EachBitFieldUniformlyGenerated) {
  double zeroAvg = 0;
	double oneAvg = 0;
	for( int i = 0; i < NUM_TEST_CASES; i++ ){			// essentially the sanity check for distrubiton
		RandomMatrixHash mat( TABLE_SLOTS );
		zeroAvg += (double)mat.zeroCount / ( log2( TABLE_SLOTS ) * (sizeof( unsigned int) * 8) );
		oneAvg += (double)mat.oneCount / ( log2( TABLE_SLOTS ) * (sizeof( unsigned int) * 8) );
	}
	EXPECT_NEAR( zeroAvg / NUM_TEST_CASES, oneAvg / NUM_TEST_CASES, ERROR_THRESHOLD );
}

// Sanity check for distribution of keys in the table.
// Create NUM_TEST_CASES integer keys and, for each slot in the table,
// count the number of times a key hashes to that slot. You can randomly
// generate the integer keys but I used 0, 1, ..., NUM_TEST_CASES.
// Then verify that hashing to each slot in the table is roughly equally
// likely using EXPECT_NEAR(x, y, threshold) where threshold = ERROR_THRESHOLD
TEST(RandomMatrixSanityCheck, SimpleUniformHashingAssumption) {
  int array[ TABLE_SLOTS ] = { 0 };
	RandomMatrixHash mat( TABLE_SLOTS );

	for( int i = 0; i < NUM_TEST_CASES; i++ ){
		unsigned int hash = mat.Hash( i );
		array[ hash ]++;
	}
  for( int i = 0; i < TABLE_SLOTS - 1; i++ ){
    for( int j = i + 1; j < TABLE_SLOTS; j++ ){
      EXPECT_NEAR( array[i] / NUM_TEST_CASES, array[j] / NUM_TEST_CASES, ERROR_THRESHOLD );
    }
	}
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
