//  * Created: 16/05/2022 21:00:00
//  *  Author: Kaique Ferreira
//  */
/**
 *  QUESTION 3: Implement a function able to calculate and return the average, maximum and minimum value of
    an array with “n” positions. This function must also return a copy of the input array containing
    only the even numbers of the original array, as well as the new array size. Implement this logic
    using the C language and share this code through a public repository on GitHub.
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_ON

struct functionReturn {
    float average;
    int maximum;
    int minimum;
    int *evenNumbers;
    int evenNumbersSize;
};

struct functionReturn functionQuestion3 (int inputArray[]) {
    struct functionReturn functionReturn;
    
    functionReturn.minimum = inputArray[0];
    functionReturn.maximum = inputArray[0];
    functionReturn.average = inputArray[0];
    
    int inputArraySize = sizeof( *inputArray );

    int evenNumbersFullLength[inputArraySize];
    evenNumbersFullLength[0] = inputArray[0] % 2 == 1 ? 0 : inputArray[0];
    
    size_t index; 
    int currentEvenNumberPosition = inputArray[0] % 2 == 1 ? 0 : 1;
    for (index=1; index<=inputArraySize; index++) 
    { 
      functionReturn.minimum = inputArray[index]<functionReturn.minimum ? inputArray[index] : functionReturn.minimum;
      functionReturn.maximum = inputArray[index]>functionReturn.maximum ? inputArray[index] : functionReturn.maximum;
      functionReturn.average = functionReturn.average + inputArray[index];
      
      if(inputArray[index]%2 == 1) continue;
      
      evenNumbersFullLength[currentEvenNumberPosition++] = inputArray[index];
    } 
    
    functionReturn.average = functionReturn.average / inputArraySize;
    functionReturn.evenNumbersSize = currentEvenNumberPosition;

    int i;
 	for (i=0;i<functionReturn.evenNumbersSize ; i++){
    	functionReturn.evenNumbers[i] = evenNumbersFullLength[i];
	}
    
    return functionReturn;
}


int main()
{
    //Example
    int inputArray[4];
    inputArray[0] = 2;
    inputArray[1] = 5;
    inputArray[2] = 50;
    inputArray[3] = 2;
    inputArray[4] = 13;
    
    struct functionReturn example = functionQuestion3(inputArray);

#ifdef DEBUG_ON
    printf("Function Return:");
    printf("\nMin: %i", example.minimum);
    printf("\nMax: %i", example.maximum);
    printf("\nAvg: %f", example.average);
    printf("\nEven array: ", example.evenNumbers[0]);
    int i;
    for (i=0;i<example.evenNumbersSize ; i++){
        if(i==0){
        	printf("%i", example.evenNumbers[i]);
            continue;
        }
    	printf(" - %i", example.evenNumbers[i]);
	}
    printf("\nEven array size: %i", example.evenNumbersSize);
#endif
    
    return 0;
}