/*
 ============================================================================
 Name        : Fileoperations.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

enum {SUCCESS, FAIL};


int main(void) {

	FILE *fp;
	  char filename[] = "/home/puneet/Downloads/mnist_test_10.csv";
	  int result = SUCCESS;
	  char buff[2000];
	  int activation[1000];
	  unsigned i=0;
	  char * token;


	  if ( (fp = fopen(filename, "r") ) == NULL)
	  {
	    printf("Cannot open %s.\n", filename);
	    result = FAIL;
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

	    		while(token!=NULL){

	    			activation[i]= atoi(token);

	    			token = strtok(NULL, ",");
	    					i++;
	    		}

	    		printf("value of i:%d\n",i);
	    		while (i<1000){
	    			activation[i]=0;
	    			i++;
	    		}
	    	}

	    	for(i=0; i<1000; i++ ){
	    		printf("%d",activation[i]);

	    	}

	    	printf("end of line:\n");
	    }

	  }




	return EXIT_SUCCESS;
}
