//============================================================================
// Name        : DeepNeuralNet.cpp
// Author      : Puneet Singh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include<stdio.h>
#include<stdlib.h>
#include<random>
#include<assert.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<string.h>

using std::vector;
using std::cout;
using std::endl;

using namespace std;

vector<float> X= {
										// input matrix
			5.1,3.1,1.4,0.2,
			4.9,3.0,1.4,0.2,
			6.2,3.4,5.4,2.3,
			5.9,3.0,5.1,1.8
	};

vector<float> Y= {
										// output results
			0,
			0,
			1,
			1,

	};

vector<float> W= {
										// random weights
			0.5,
			0.2,
			0.8,
			0.3,

	};



 std::vector<float> sigmoid(const std::vector<float>& v1){


	 long int vec_size = v1.size();
	 std::vector<float> res(vec_size);

	 for(unsigned i=0;i<vec_size;i++){

		 res[i]= 1.0 / (1.0 + expf(-v1[i]));   // defines the sigmoid function
	 }

	 return res;
}


 std::vector <float> sigmoid_d (const std::vector <float>& m1) {

     const unsigned long VECTOR_SIZE = m1.size();
     std::vector <float> output (VECTOR_SIZE);


     for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
         output[ i ] = m1[ i ] * (1 - m1[ i ]);
     }

     return output;
 }


 std::vector <float> dot (const std::vector <float>& m1, const std::vector <float>& m2,
                     const int m1_rows, const int m1_columns, const int m2_columns) {

	 std::vector <float> output (m1_rows*m2_columns);

     for( int row = 0; row != m1_rows; ++row ) {

         for( int col = 0; col != m2_columns; ++col ) {

             output[ row * m2_columns + col ] = 0.f;

             for(int k = 0; k != m1_columns; ++k ) {

                 output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
             }
         }
     }

     return output;
 }

 std::vector<float> operator-(const std::vector<float>& v1, const std::vector<float>& v2){



	 long int vec_size = v1.size();
	 std::vector<float> res(vec_size);

	 for(int i=0;i<vec_size;i++){
		 res[i] = v1[i] - v2[i];

	 }


	 	 return res;

 }

 std::vector<float> operator+(const std::vector<float>& v1, const std::vector<float>& v2){

	 //std::vector<float> res;


	 long int vec_size = v1.size();
	 std::vector<float> res(vec_size);

	 for(int i=0;i<vec_size;i++){
		 res[i] = v1[i]+v2[i];
	 }

	 	 return res;
 }

 std::vector<float> operator*(const std::vector<float>& v1, const std::vector<float>& v2){

	 //std::vector<float> res;

	 long int vec_size = v1.size();
	 std::vector<float> res(vec_size);

	 for(int i=0;i<vec_size;i++){
		 res[i] = v1[i]*v2[i];
	 }

	 return res;
}


 std::vector<float> transpose (float *m, const int C, const int R) {


     std::vector<float> mT (C*R);

     for(int n = 0; n!=C*R; n++) {
         int i = n/C;
         int j = n%C;
         mT[n] = m[R*j + i];
     }

     return mT;
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


 std::vector<float> getlabelVector(int n){

	 std::vector<float> res = {0,0,0,0,0,0,0,0,0,0};

	 switch(n){

	 case 0:res[0]=0;
		 break;
	 case 1:res[1]= 1;
		 break;

	 case 2:res[2]=2;
		 break;

	 case 3:res[3]=3;




	 }


	 return res;
 }

int main(){


printf("into main 3");


	FILE *fp;
	char filename[] = "/home/puneet/Downloads/mnist_test_10.csv";
//  int result = SUCCESS;
	char buff[2000];
	//int activation[1000];
	unsigned i=0;
	char * token;
	int lab;

	std::vector<float> activation(784);

	if ( (fp = fopen(filename, "r") ) == NULL)
	{
		printf("Cannot open %s.\n", filename);
  //  result = FAIL;
	}
	else
	{
		printf("File opened; ready to read.\n");

    //printf("okk");
		while(!feof(fp)){
			i=0;
    //	printf("okk");
			if(fgets(buff, 2000 ,fp )!=NULL){

				token = strtok(buff,",");
				printf("%s\n",token);

				lab = atoi(token);

				while(token!=NULL){

					token = strtok(NULL, ",");
					activation[i]= atof(token); // can use atof to convert to float
    					i++;
				}
				printf("value of i:%d\n",i);

				}


	std::vector<float> label = getlabelVector(lab);


	for (unsigned i = 0; i != 50; ++i) {

		std::vector<float>   pred = sigmoid(dot(X, W, 4, 4, 1 ) );

	         printf("into main 3");

	         std::vector<float>       pred_error = Y - pred;

	         std::vector<float>  pred_delta = pred_error * sigmoid_d(pred);

	         printf("into main 4");

	         std::vector<float>   W_delta = dot(transpose(&X[0],4,4), pred_delta, 4,4, 1); // calculates the weight updates

	         W = W + W_delta;

	        if (i == 49){
	            print ( pred, 4, 1 );
	        };
	    };

		}
   }



	return 0;
}
