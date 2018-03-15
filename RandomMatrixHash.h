#ifndef _RANDOM_MATRIX_HASH_H_
#define _RANDOM_MATRIX_HASH_H_

#include <vector>
using namespace std;

class RandomMatrixHash {
 public:
  RandomMatrixHash(unsigned int m);
  std::size_t Hash(int key) const;
  std::vector<vector<int>> matrix;


  int zeroCount = 0, oneCount = 0;
  int table_size = 0;
 private:
	//std::vector<int> matrix;
}; // RandomMatrixHash

#endif  // _RANDOM_MATRIX_HASH_H_
