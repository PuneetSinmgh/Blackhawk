#include <stdio.h>
#include<stdlib.h>
#include<random>
#include<assert.h>
#include<iostream>
#include<vector>


using std::vector;
using std::cout;
using std::endl;

 std::vector<float> sigmoid(const std::vector<float>& v1){


	 long int vec_size = v1.size();
	 std::vector<float> res[vec_size];

	 for(int i=0;i<vec_size;i++){

		 res[i]= 1/(1+(exp(-v1[i])));   // defines the sigmoid function
	 }



	 return 0;
}

 std::vector<float> dot(const std::vector<float>& v1, const std::vector<float>& v2, const int v1_rows,
		 const int v1_column, const int v2_rows, const int v2_column){                                // dot product of vectors
	 std::vector<float> res;

	 for(int i=0, k=0, j=0;i<v1_rows;++i){

		 int row;

		 for(j=0;j<v1_column;++j){

			 int prod;
			  for(k=0;k<v2_column;++k){

				  prod= v1[i][j] * v2[j][k];

			  }
				  row = row+prod;
		 }

		 res[i][k]= row;
	 }



	 return res;
 }

 std::vector<float> operator-(const std::vector<float>& v1, const std::vector<float>& v2){

	 std::vector<float> res;

	 long int vec_size = v1.size();

	 for(int i=0;i<vec_size;i++){
		 res[i] = v1[i] - v2[i];
	 }


	 	 return res;

 }

 std::vector<float> operator+(const std::vector<float>& v1, const std::vector<float>& v2){

	 std::vector res;


	 long int vec_size = v1.size();

	 for(int i=0;i<vec_size;i++){
		 res[i] = v1[i]+v2[i];
	 }

	 	 return res;
 }

 std::vector<float> operator*(const std::vector<float>& v1, const std::vector<float>& v2){

	 std::vector res;

	 long int vec_size = v1.size();

	 for(int i=0;i<vec_size;i++){
		 res[i] = v1[i]*v2[i];
	 }

	 return res;
}


 void print ( const vector <float>& v1, int v1_rows, int v1_columns ) {


	 for( int i = 0; i != v1_rows; ++i ) {
         for( int j = 0; j != v1_columns; ++j ) {
             cout << v1[ i * v1_columns + j ] << " ";
         }
         cout << '\n';
     }
     cout << endl;
 }


int main(int argc, const char * argv[]){


	std::vector<float> X= {
										// input matrix
			5.1,3.1,1.4,0.2,
			4.9,3.0,1.4,0.2,
			6.2,3.4,5.4,2.3,
			5.9,3.0,5.1,1.8
	};

	std::vector<float> Y= {
										// output results
			0,
			0,
			1,
			1,

	};

	std::vector<float> W= {
										// random weights
			0.5,
			0.2,
			0.8,
			0.3,

	};


	std::vector<float> pred = {};
	vector<float> pred_error;
	vector<float> pred_delta;
	vector<float> W_delta ;



	for (unsigned i = 0; i != 50; ++i) {

	         pred = sigmoid(dot(X, W, 4, 4, 4, 1 ) );
	         pred_error = Y - pred;
	         pred_delta = pred_error * sigmoid(pred);
	         W_delta = dot(X, pred_delta, 4,4, 4, 1);
	        W = W + W_delta;

	        if (i == 49){
	            print ( pred, 4, 1 );
	        };
	    };

			// overload addition , subtraction and multiplication operators in order to operate on the vectors.




	return 0;
}
