#include <stdio.h>
#include <stdlib.h>

/* Brute Force Password Generator v2.1.0
   Written by: @je 
   About: this program generates wordlist with keywords provided by user. 
   	      wordlist is saved in a file and the file could be used in brute force attacks.
   	      the generated file,s name is "pa$$.txt".
*/

// Global Variables Definition
int cntr = 0;
int index = 0;
int max;
int min;

void guessPass(char* total_info[],int total_info_size,char* pa$$[],FILE * pa$$$);
int MinMaxThrowException(int min , int max);

int main(int argc, char *argv[]) {
	
	char info[80][30]; 
	int column_num[30], row_num=0, j, count=-1;
	char tmp;
	
	printf("########################################################################################\n::.Password Generator v2.1.0.::\n\n Written by: @je\n\n About:\n you as a user should provide this program some of your victim,s basic information.\n this makes program guessing the victim,s password.\n you can use the output file (wordlist) as an input for brute force programs!\n Generated file,s name is \"pa$$.txt\" \n########################################################################################\n\n");
	
	// Creating text file for writing passwords into.
	FILE *pa$$$ = fopen("pa$$.txt" , "w");
	
	do{
		printf("> Enter minimum size of the word for ouput passwords?\n");
		scanf("%d", &min);
	
		printf("> Enter maximum size of the word for ouput passwords?\n");
		scanf("%d", &max);
	} // end do
	while(MinMaxThrowException(min,max));
	
	printf("> add keywords and any important information about the victim like firstname,lastname,birth date and ...: (if you finished,enter '.')\n");
	
	do{
		count++;
		if(count > 0) 		printf("\n\n> Error: you have entered not enough words according to the 'max' amount!\n> Please try again\n\n"); 	// catch Exception
		j = 0;
		while(1){
			scanf("%s", &info[j]);
			if(info[j][0] == '.') 	break;
			else 	j++;			
		} // end while
	
		row_num = j;
	} // end do
	while(row_num < max ? 1 : 0);
	 	
	
	
	printf("\n> wordlist:\n\n");

	
	// Detecting user input strings sizes.
	int size[row_num];
	int i;
	for(i=0;i<row_num;i++){	
	    int j = 0;
		tmp = info[i][0];
		while(tmp != '\0'){
			tmp = info[i][++j];			
		} // end while	
		size[i] = j;
	} // end for
	
		
	char* info_ptr[row_num];
	
	int r,t=row_num-1;
	for(r=0;r<row_num;r++){
		info_ptr[t] = (char*)info[r];
		t--;
	} // end for
		
	cntr = 0;				
	char* pass[row_num];
	guessPass(info_ptr,row_num,pass,pa$$$);		
	
	fclose(pa$$$);
	return 0;
} // end main


// Recursive function. 
void guessPass(char* total_info[],int total_info_size,char* pa$$[],FILE * pa$$$){

	int LAST_IDX=0;
	int loop;
	for(loop=total_info_size-1;loop>=0;loop--){ 
		
		if(index == max-1) 	LAST_IDX = 1;
		pa$$[index] = total_info[loop];
		
		if(index>=min-1 && index<=max-1){
			int prt_lp;
			for(prt_lp=0;prt_lp<=index;prt_lp++){
				printf("%s" , pa$$[prt_lp]);
				fprintf(pa$$$,"%s",pa$$[prt_lp]);
		 	} // end for
		 	printf("\n");
			fprintf(pa$$$,"\n");	
		} // end if 
		
			
		if(!LAST_IDX){ 
			index++;				
		    char* total_info_tmp[total_info_size-1];
	  		int itr1;
			for(itr1=0;itr1<total_info_size;itr1++){
				if(itr1 == total_info_size-1) 	break;
				if(itr1 >= loop) 	 total_info_tmp[itr1] = total_info[itr1+1];
				else	total_info_tmp[itr1] = total_info[itr1];
			} 	
			guessPass(total_info_tmp,total_info_size-1,pa$$,pa$$$); 
		} // end if 
		
		if(loop == 0) 	index--;
		
	} // end for 
		
		return ;
} // end guessPass()



int MinMaxThrowException(int min , int max){
	
	if(min > max){
		printf("\n\n> Error: maximum should be higher than minimum!\n> Please try again\n\n");
		return 1;
	} // end if
	
	if(min <= 0){
		printf("\n\n> Error: 'minimum' should be at least '1'!\n> Please try again\n\n");
		return 1;
	} 	
	
	return 0;
	
} // end MinMaxThrowException()
