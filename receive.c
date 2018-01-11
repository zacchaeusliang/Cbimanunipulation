

/*



File receive.c





Purpose: simulate the receiveing end of a message over the network.  



The program converts a message encodded as an array of short integers into characters.

The input message uses 1-bit error correction code.

As part of the simulation, the program also corrects any 1-bit errors in the receiving message.





Revision:

a. Initial code - Doron Nussbaum





*/





/************************************************************************/



// INCLUDE FILES



#include "stdio.h"

#include "stdlib.h"

#include "string.h"

#include "assert.h"

#include "bit_manipulation.h"





/************************************************************************/

//MACROS  / DEFINES







#define XSTR(A) STR(A)

#define STR(A) #A

#define MAX_INPUT_LENGTH 8192

#define MAX_MSG_LENGTH 2048

#define P1_MASK 0xaa8   // 0b0101010101000

#define P2_MASK 0xcc8	// 0b0110011001000

#define P4_MASK 0x10e0	// 0b1000011100000

#define P8_MASK 0x1e00  // 0b1111000000000





/************************************************************************/

// FUNCTION PROTOTYPES





void short2Char(short encodedChar, char *c);

void correctCode(short *num);

void readEncodedMessage(short *buf, int len, int *numRead);









/**************************************************************************/



int main(int argc, char *argv[])



{

	int rc = 0;		// return code



	char s[MAX_MSG_LENGTH] = { '\0' };  // message

	short encodedMsg[MAX_MSG_LENGTH];

	int numRead = 0;  // number of characters in the message

	int i;



	// read the message

	printf("Please enter the transmitted message: ");

	readEncodedMessage(encodedMsg, MAX_MSG_LENGTH, &numRead);







	// print the corrected message

	printf("\n\n Transmitted Message:\n");

	for (i = 0; i < numRead; i++) {

		char c;

		short2Char(encodedMsg[i], &c);

		printf("%c", c);

    }

    printf("\n");



    // correct the message

	for (i = 0; i < numRead; i++) {

		correctCode(&encodedMsg[i]);

	}







	// print the corrected message

	printf("\n\n Corrected Transmitted Message:\n");

	for (i = 0; i < numRead; i++) {

		char c;

		short2Char(encodedMsg[i], &c);

		printf("%c", c);

	}

	printf("\n");



	return(0);

}





/***********************************************************************************/

/* reads a message from the user



input

len - maximum length of mesage that should be read



output

receivedMsg - contains the message

numRead - the number of characters in the message



*/





void readEncodedMessage(short *receivedMsg, int len, int *numRead)

{

	int i;

	int rc;

	char s[MAX_INPUT_LENGTH+1];

	char *token = NULL;

	*numRead = 0;



	s[MAX_INPUT_LENGTH] = '\0';

	scanf("%"XSTR(MAX_INPUT_LENGTH)"[^\n]s", s);

	token = strtok(s, " ");



	for (i = 0; token != NULL  &&  i < len;token = strtok(NULL, " "), i++) {

		rc = sscanf(token, "%hd", &receivedMsg[i]);

	}



	*numRead = i; // set the number of read integers



    // empty the input buffer

    for( ; getchar() != '\n'; );





}









/*************************************************************************/

/* collect of a short bits 3,5,6,7,9,10,11,12  to bits 0-7 of a char



input

encodedNum - a short with the bits of c



output

c - the char that is embedded in encodedNum



*/





void short2Char(short encodedNum, char *c)



{
  int i;
  int bitSet;

 * c = 0;
  for (i = 0; i < 13; i++) {

    // check if bit i is set
    bitSet = isShortBitSet(encodedNum, i);

    // set the correct bit in the encoded character
    // check if bit i is set

    // set the correct bit in the encoded character
    if (bitSet){

   
    if (i == 3) {
      setCharBit(0, c);

    }
    if (i == 5) {
      setCharBit(1, c);

    }
    if (i == 6) {
      setCharBit(2, c);

    }
    if (i == 7) {
      setCharBit(3, c);
    }
    if (i == 9) {
      setCharBit(4, c);
    }
    if (i == 10) {
      setCharBit(5, c);
    }
    if (i == 11) {
      setCharBit(6, c);
    }
    if (i == 12) {
      setCharBit(7, c);
    }
  }
}

}





/*************************************************************************************/





/* purpose:

performs error corrrections, if needed on the short integer



The function first checks the parity bits for error.  

If there is an error then it fixes it.



input

num - the address of the short number 

*/





void correctCode(short *num)



{
int mask;
  int sum;
  int bitNum = 0; //  bit number with the error bit
  int parity; // a parity bit either 0 or 1
  int storedParity; // the parity bit in the encoded char

  // check parity bit p1
 

  // get the bits related to P1 using P1_MASK
  mask = * num & P1_MASK;

  // count the bits
  sum = countBits(mask);

  // determine if the parity bit should have been set 
  if (sum % 2 == 0) {
	 parity = 0;
  } else {
         parity = 1;
  }
 storedParity = isShortBitSet(*num, 1);

  // get the parity for P1_MASK thatat is stored in *num 	
  if (parity!=storedParity) {
    bitNum += 1;
    
  }

 

  // get the bits related to P1 using P1_MASK
  mask = * num & P2_MASK;

  // count the bits
  sum = countBits(mask);
	

  // determine if the parity bit should have been set 
  if (sum % 2 == 0) {
    parity = 0;
  } else {
    parity = 1;
  } storedParity = isShortBitSet(*num, 2);

  // get the parity for P1_MASK thatat is stored in *num 	
  if (parity!=storedParity) {
    bitNum += 2;
  }

 

  // get the bits related to P1 using P1_MASK
  mask = * num & P4_MASK;
	

  // count the bits
  sum = countBits(mask);


  // determine if the parity bit should have been set 
  if (sum % 2 == 0) {
    parity = 0;
  } else {
    parity = 1;
  }
storedParity = isShortBitSet(*num, 4);

  // get the parity for P1_MASK thatat is stored in *num 	
  if(storedParity!=parity) {
    bitNum += 4;
  }
 

  // get the bits related to P1 using P1_MASK
  mask = * num & P8_MASK;

  // count the bits
  sum = countBits(mask);

  // determine if the parity bit should have been set 
  if (sum % 2 == 0) {
    parity = 0;
  } else {
    parity = 1;
  }
 storedParity = isShortBitSet(*num, 8);
  // get the parity for P1_MASK thatat is stored in *num 	
  if (parity!=storedParity) {
    bitNum += 8;
  }
if(bitNum!=0){
  flipBitShort(bitNum, num);
  
}	

}
