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
#include<fnmatch.h>

using std::vector;
using std::cout;
using std::endl;

using namespace std;


float get_random() {
		return static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
	}

	std::vector<float> init_weights(int rows, int cols) {

		std::vector<float> temp(rows*cols);

		for (int i = 0; i < temp.size(); ++i) {

				temp[i]=get_random();
		}

		return temp;
	}

		const float l2_rows = 15.0;
		const float l2_cols = 784.0;
		const float l3_rows = 10.0;
		const float l3_cols = 15.0;

		std::vector<float>  L2W;// Layer 2 Weights vector
		std::vector<float> L3W;// Layer 3 Weights vector
		std::vector<float> L2B;// Layer 2 Biad vector
		std::vector<float> L3B;// Layer 3 Bias vector

		std::vector<float> A2,A3;
		std::vector<float> A1(784);

		std::vector<float> z2,z3;

		std::vector<float> d2,d3;

		std::vector<float> L2nw(15*784,0.0);// Layer 2 Weights vector
		std::vector<float> L3nw(10*15,0.0);// Layer 3 Weights vector
		std::vector<float> L2nb(15*1,0.0);// Layer 2 Biad vector
		std::vector<float> L3nb(10*1,0.0);// Layer 3 Bias vector


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

	 res[n]=1;

	 return res;
 }

 void update_wandb (vector <float> &a , vector <float> &b){

	 float eta = 0.5;
	 int mini_batch_size = 100;

 	//a = a - ((eta/mini_batch_size) * b);
	 for (int i = 0 ; i < b.size();++i){
 		b[i] = (eta/mini_batch_size) * b[i];
	 }

	 a = a - b;

 	}

int main(){


printf("into main 3");


	FILE *fp;
	char filename1[] = "/home/puneet/Downloads/mnist_train_100.csv";
	char filename2[] = "/home/puneet/Downloads/mnist_test_10.csv";
	char buff[2000];
	float activation[785];
	unsigned i=0;
	char * token;
	int lab=0, batch_size=0;
		L2W = init_weights(l2_rows, l2_cols);// initializing wieghts for layer 2

		L2B = init_weights( l2_cols,1); // initializing weights for layer 3
		/*
		 * Layer 3- 15 * 10 weights initialization vector
		 * 			1 * 10 Bias vector
		 */
		L3W = init_weights(l3_rows, l3_cols);
		//print_vectors(L3W);
		L3B = init_weights(l3_cols,1);
		//print_vectors(L3B);



			if ( (fp = fopen(filename1, "r") ) == NULL)
			{
				printf("Cannot open %s.\n", filename1);
			  //  result = FAIL;
			}
			else{

				printf("File opened; ready to read.\n");

				//printf("okk");
				while(!feof(fp)){
					i=0;
				//	printf("okk");
					if(fgets(buff, 2000 ,fp )!=NULL){

						token = strtok(buff,",");
						//printf("%s\n",token);
						++batch_size;
						//printf("%s\n",token);
							if(batch_size<=100){
								//printf("%s\n",token);
								//printf("\ninto if ");
								//lab = atoi(token);
								//printf("%d",lab);

									while(token!=NULL){
										activation[i]= atof(token); // can use atof to convert to float
										token = strtok(NULL,",");
										i++;
									}
									printf("value of i:%d\n",i);
									std::vector<float> label = getlabelVector(activation[0]);
							// feed forward
									for (int j=0; j<A1.size();j++ )
										A1[j]=activation[j+1];
									z2=dot(L2W,A1,15,784,1)+L2B;
									A2 = sigmoid(z2);
									z3=dot(L3W,A2,10,15,1)+L3B;
									A3 = sigmoid(z3);
													// back propagation
									d3 = (A3-label)*sigmoid_d(z3);
									L3nb = d3 + L3nb;
									L3nw = dot(d3,transpose(&A2[0],1,15),10,1,15) + L3nw; // gradiet discent
									d2 = dot(transpose(&L3W[0],15,10),d3,15,10,1)*sigmoid_d(z2);
									L2nb = d2 + L2nb;
									L2nw = dot(d2,transpose(&A1[0],1,784),15,1,784) + L2nw ; //gradient discent
							}
							else{
								printf("weights updated");
								update_wandb(L3W,L3nw);
								update_wandb(L3B,L3nb);
								update_wandb(L2W,L2nw);
								update_wandb(L2B,L2nb);
								batch_size = 0;
								continue;
							}
					}
					printf("reading line and learning\n");
				}
				printf("activations\n");
				print(A3,10,1);
			}


			if ( (fp = fopen(filename2, "r") ) == NULL)
				{
					printf("Cannot open %s.\n", filename2);
						  //  result = FAIL;
				}
				else{

					printf("File opened; ready to read.\n");
					while(!feof(fp)){
						i=0;
						if(fgets(buff, 2000 ,fp )!=NULL){

							token = strtok(buff,",");
						//	printf("%s\n",token);

							//lab = atoi(token);

							while(token!=NULL){
								//printf("%s\n",token);
								activation[i]= atof(token); // can use atof to convert to float
								token = strtok(NULL, ",");
								i++;
							}
							printf("value of i:%d\n",i);
						 }
						std::vector<float> label = getlabelVector(activation[0]);
							// feed forward

						for (int j=0; j<A1.size();j++ )
							A1[j]=activation[j+1];

						z2=dot(L2W,A1,15,784,1)+L2B;
						A2 = sigmoid(z2);

						z3=dot(L3W,A2,10,15,1)+L3B;
						A3 = sigmoid(z3);


						printf("\nprint results");
						print(A3,10,1);
					}


				}





	return 0;
}
