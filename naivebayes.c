#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>
//find the maximum in an array and get the corresponding index
int max(float A[])
{
	float m=A[0];
	int i,index;
	for(i=0;i<10;i++)
	{
		if(m<A[i])
		{
			m=A[i];
			index=i;
		}
	}
	
return index;
}

int main()
{
	int train[6670][193],test[3333][193],train_label[6670],test_label[3333];
	float bayes[10][192][5];
	int i,j,k,l;
	FILE* f = fopen("pp_tra.txt", "r");
	//Scan the training set file and store the values in a 2D array and class labels in a 1D array
   
    	while(getc(f) != EOF)
    	{
		for(i=0;i<6670;i++)
        	{
			for(j=0;j<193;j++)
	    		{
				if(j == 192){
                	    	fscanf(f,"%d ",&train_label[i]);
			   	}
                		else{
                	    	fscanf(f,"%d ",&train[i][j]);
                		}
			}
		}	
	}
	fclose(f);
	FILE* f1 = fopen("pp_tes.txt", "r");
	//Scan the test set file and store the values in a 2D array and class labels in a 1D array
   
    	while(getc(f1) != EOF)
    	{
		for(i=0;i<3333;i++)
        	{
			for(j=0;j<193;j++)
	    		{
				if(j == 192){
                	    	fscanf(f1,"%d ",&test_label[i]);
			   	}
                		else{
                	    	fscanf(f1,"%d ",&test[i][j]);
                		}
			}
		}	
	}
	fclose(f1);
	//Consider a 3D array with class label and features and the value of feature as 3 indexes.
	//Initialise them with zeros.
	for(i=0;i<10;i++)
	{
		for(k=0;k<192;k++)
		{
			for(l=0;l<5;l++)
			{
				
				bayes[i][k][l]=0;
				
			}	
		}
	}
	
	//Increment its value by 1 in the corresponding class label index by checking the value of feature in training set
		int m;
		for(j=0;j<6670;j++)
		{
			m=train_label[j];
			for(k=0;k<192;k++)
			{
				for(l=0;l<5;l++)
				{
					if(train[j][k]==l)
					{
						bayes[m][k][l]=bayes[m][k][l]+1;
					}
				}	
			}
		}
	//Divide the matrix by 667 since the training set is equi propable		
		for(i=0;i<10;i++)
		{
			for(k=0;k<192;k++)
			{
				for(l=0;l<5;l++)
				{
					bayes[i][k][l]=bayes[i][k][l]/667.0;
				}	
			}
		}	
		float p[10];
		int index,counter=0;
		//Apply the naive bayes formula and get the correctly classified count
		for(i=0;i<3333;i++)
		{
			for(l=0;l<10;l++)
			{
				p[l]=0;
			}
			for(j=0;j<10;j++)
			{
				for(k=0;k<192;k++)
				{
					p[j]=p[j]+log(bayes[j][k][test[i][k]]);
				}			
				p[j]=p[j]+log(0.1);
			}
			
			index=max(p);
			if(index==test_label[i])
			{
				counter++;
			}
		}
	
		float accuracy=((counter)/3333.0)*100;
		printf("accuracy=%f\n",accuracy);
		printf("correctly classified=%d\n",counter);
return 0;
}
