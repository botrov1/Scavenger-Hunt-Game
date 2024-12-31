#include <stdio.h>
#include <stdlib.h>

#include "myStringLib.h"


//  This is then your very first reusable custom C library 
int my_strlen(const char * const str1)
{
	
	int strlength=0;

	while(str1[strlength]!='\0'){
		strlength++;
	}

	return strlength;
	
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character
	
}

int my_strcmp(const char * const str1, const char * const str2)

{

	int i;
	if (my_strlen(str1)!=my_strlen(str2)){
		return 0;
	} 

	//if their sizes are equal

	for (i=0; i<my_strlen(str1);i++){
		if (str1[i]!=str2[i]){
			return 0;
		} 
			
	}

	return 1;

}


int my_strcmpOrder(const char * const str1, const char * const str2)
{
	int i;
	//seeing the the two strings are the same
	if (my_strcmp(str1,str2)==1){
		return -1;
	} 
	//If str2 is alphabetically smaller than str1 (comes before str1),
	
	for (i=0; str1[i]!='\0' && str1[i]!='\0';i++){
		if (str1[i]>str2[i]){
			return 1;
		} else if(str1[i] < str2[i]) {
            return 0;  // str1 is "smaller" than str2
        }
	}
	
	if (str1[i]!='\0'){
		return 1;
	}

	return 0;

	
	
	
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/

	// if two strings are completely identical in order, return -1.

	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII character

	
}


char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;
	int i=0;
	int j=0;
	/*write your implementation here*/
	
	z=(char*)malloc((my_strlen(str1)+my_strlen(str2)+1)*sizeof(char)); // allocating memory for the concatendated strings and for the null terminator
	//using pointer aritmetic:
	while(i<my_strlen(str1))
	{
		*(z+i)=str1[i];
		i++;

	}
	while(j<my_strlen(str2))
	{
		*(z+i+j)=str2[j];
		j++;
	}
	// including null terminator
	*(z+i+j)='\0';


	
	/* finally, return the string*/
	return z;
	

	// IMPORTANT!!  Where did the newly allocated memory being released?
	// THINK ABOUT MEMORY MANAGEMENT
	
}
