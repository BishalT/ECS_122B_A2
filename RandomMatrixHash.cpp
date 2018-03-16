#include "RandomMatrixHash.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <time.h>

#define KEY_VAL 32
#define TABLE_SLOTS 256
#define NUM_TEST_CASES 100000
#define CURR_NUM 248
#define HASH_BASE 2

using namespace std;

// matrix: b x u
// b: log_2( HASH_TABLE_SIZE )
// u: KEY_VAL, which is the # binary digits in max int

RandomMatrixHash::RandomMatrixHash( unsigned int m ) {		// constructor
	table_size = m;
	int rowCount = ( int ) log2(m);
	matrix.resize( rowCount );	// # rows = rowCount
	for( int row = 0; row < rowCount; row++ ){	// # columns = KEY_VAL
		matrix[ row ].resize( KEY_VAL );
		for( int column = 0; column < KEY_VAL; column++ ){
			matrix[ row ][ column ] = rand() % 2;
			if( matrix[ row ][ column ] == 0){
				zeroCount++;
			}
			else {
				oneCount++;
			}
		}
	}
}

// Use mod 2 matrix multiplication for your hash function.
// matrix multiplication: Rand Matrix and key (in binary, matrix form)

std::size_t RandomMatrixHash::Hash( int key ) const {
	unsigned int hashBrown = 0;

	// change to binary array
	int keyVector[ KEY_VAL ][ 1 ];
	for ( int i = 0; i < KEY_VAL; i++ ) {
    keyVector[ (KEY_VAL - 1) - i ][ 0 ] = ( key >> i ) & 1;
	}

	// matrix multiplication
	int mat_row = (int) log2(table_size), key_col = 1, key_row = KEY_VAL;
	int result[ mat_row ];

	for( int row_index = 0; row_index < mat_row; row_index++ ){
		for( int col_index = 0; col_index < key_col; col_index++ ){
			int sum = 0;
			for( int key_row_index = 0; key_row_index < key_row; key_row_index++ ){
				sum += matrix[ row_index ][ key_row_index ] * keyVector[ key_row_index ][ col_index ];
			}
			result[ row_index ] = sum % 2;
		}
	}
	// convert result (binary value) into decimal number
	for( int index = 0; index < mat_row; index++ ){
		hashBrown += result[ index ] * pow(2, mat_row - index - 1);
	}

	return hashBrown;
}

/*
int main() {

	//RandomMatrixHash mat( TABLE_SLOTS );

	double zeroAvg = 0;
	double oneAvg = 0;
	for( int i = 0; i < NUM_TEST_CASES; i++ ){			// essentially the sanity check for distrubiton
		RandomMatrixHash mat( TABLE_SLOTS );
		zeroAvg += (double)mat.zeroCount / CURR_NUM;
		oneAvg += (double)mat.oneCount / CURR_NUM;
		//out << mat.zeroCount << endl;
		//cout << mat.oneCount << endl;
		//cout << endl;
	}
	cout << "ZERO AVG: " << zeroAvg / NUM_TEST_CASES << endl;
	cout << "ONE AVG: " << oneAvg / NUM_TEST_CASES << endl;


	int array[ TABLE_SLOTS ] = { 0 };
	RandomMatrixHash mat( TABLE_SLOTS );

	for( int i = 0; i < NUM_TEST_CASES; i++ ){
		unsigned int hash = mat.Hash( i );
		array[ hash ]++;
	}

	for( int i = 0; i < TABLE_SLOTS; i++ ){
		cout << "I: " << array[ i ] << endl;
		cout << i << endl;
	}
	//cout << hash << endl; 	return 0;
}
*/
