#include <stdio.h>
#include <string.h>

#include <stdlib.h>
main() {
	int counter,day=0;

	float sum=0,max=-1.0,min=9999999,average=0;
	char* token = NULL;
	FILE *output;
	FILE* file = fopen("test.txt", "r"); /* should check the result */
	char line[256];
	int j=0;
	int dayEnd[6];

	int	dayEndCount=0;
	float* array1,* array2,* array3,* array4;
	char *dates[5]= {"4/18/2017","4/19/2017","4/20/2017","4/21/2017","4/24/2017"};

	int c=0,i=0,dateCount=0;
	char input=NULL;

	int count =0;
	//	dayEnd[dayEndCount++]=0;
	printf("Enter 'd' for detailed report or 's' for summary report: ");
	scanf("%c", &input);

	if (input !='d'&& input !='s'){
		printf("Error: Your input is invalid!\n");
		return;
	}



	while (fgets(line, sizeof(line), file)) {
		count++;
	}

	fclose(file);

	file = fopen("test.txt", "r"); /* should check the result */



	array1 = (float *) malloc((count-7)*sizeof(float));
	array2 = (float *) malloc((count-7)*sizeof(float));
	array3 = (float *) malloc((count-7)*sizeof(float));
	array4 = (float *) malloc((count-7)*sizeof(float));

	while (fgets(line, sizeof(line), file)) {

		if(i>=7)
		{
			token = strtok(line, ",");
			if(token[0]!='a')
			{
				array1[c]=atof(token);			
				token = strtok(NULL, ",");
				array2[c]=atof(token);
				token = strtok(NULL, ",");
				array3[c]=atof(token);
				token = strtok(NULL, ",");
				array4[c]=atof(token);
				c++;
			}
			else
			{
				dayEnd[dayEndCount++]=c;
				//			printf("%s\n",dates[dateCount]);
				dateCount++;

			}

		}

		i++;

	}
	dayEnd[dayEndCount]=c;

	fclose(file);

	//	for(day=0;day<dayEndCount;day++){
	//		printf("%d\n",dayEnd[day]);
	//	}

		output = fopen("test1.txt", "w");
		if (output == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	//-------value	113.22
	day=0;
	if(input=='d')
	{
		fprintf(output,"DETAILED REPORT:\n\n");

		for(day=0;day<dayEndCount;day++)
		{
			for(counter=dayEnd[day];counter<dayEnd[day+1];counter++)
			{
				sum += array2[counter];
				if(array3[counter]>max)
					max= array3[counter];
				if(array4[counter]<min)
					min= array4[counter];
			}

			average = sum/c;
			if (day==0)
				fprintf(output,"%20s %06.2f %06.2f %06.2f %06.2f %06.2f\n",dates[day],113.22,average,max,min,array2[dayEnd[day+1]-1]);
			else 
				fprintf(output,"%20s %06.2f %06.2f %06.2f %06.2f %06.2f\n",dates[day],array2[dayEnd[day]-1],average,max,min,array2[dayEnd[day+1]-1]);

		}
	}
	else
	{
		fprintf(output,"SUMMARY REPORT:\n\n");
		for(day=0;day<dayEndCount;day++)
		{
			fprintf(output,"\nDaily increase/decrease in percentage of ");
			if (day==0)
				//average=100*((array2[dayEnd[day+1]-1]-113.22)/(113.22));
					fprintf(output,"%s, %06.2f\n",dates[day],100*((array2[dayEnd[day+1]-1]-113.22)/(113.22)));
			else
				fprintf(output,"%s, %06.2f\n",dates[day],100*((array2[dayEnd[day+1]-1]-array2[dayEnd[day]-1])/(array2[dayEnd[day]-1])));

		}


	}


	

	fclose(output);



}
