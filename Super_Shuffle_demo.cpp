//  Super_Shuffle_demo.cpp 

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "Super_Shuffle.h"

unsigned int random(unsigned int);  // advance prototype

// ---------------------  globals
unsigned int userSID; // user's Shuffle ID, is to change when they "reShuffle"
int indx[100+1];  // for testing intervals between given items

/*-----------------------------------------------------------------------*/
/*  Generates 10 samples consecutive shuffles of 26 items A-Z (~songs)   */
/*  Using three greatly differing shuffle means for comparison           */
/*                                                                       */
/*  You may run this a few times to get demonstrative comparisons        */

int main(int argc, char** argv)
{
	unsigned int shuffleID;
	unsigned int wi;
	int nlimit;
	int d, cnt, dcnt, dsum;
	int max, min;
	char cin=0;
	int firstChr;

	printf("\nGenerating 20 consecutive shuffles for three diverse handlings of playlist shuffles.\n");
	printf("The gathered statistics of intervals between instances of any given item\n");
	printf("demonstrates the reality of bunching of like items accross shuffles. \n\n\n");

	/* Initializes random number generator */
	srand((unsigned)time(NULL));

	nlimit = 26; firstChr = 65;
	//nlimit = 100; firstChr = 28;    // use these settings to get results for working with a set of 100 items

	while (1) {
		userSID = random(0);
		for (int a = 1; a < 4; a++) {  //           test 3 shuffle types
			if (a == 1)			printf("Simple use of rand() as a \"shuffle\":\n ");
			else if (a == 2)	printf("Straight forward use of a quality shuffle algo:\n ");
			else if (a == 3)	printf("Done with 'Super_Shuffle' utilizing MSA-e:\n ");
			max = 0;  min = 9999;
			for (int i = 0; i < nlimit; i++) indx[i] = 0;
			cnt = dcnt = dsum = 0;
			for (int l = 0; l < 10; l++) {  // do 10 example lines (with 2 sets each)
				shuffleID = random(0);
				for (int i = 0; i < 2*nlimit; i++) {
					cnt++;

					if (a == 1)			wi = rand() % nlimit;  // worst tolerated shuffle. Often patched with checks & balances, & still its poor
					else if (a == 2)	wi = MillerShuffle(i, shuffleID, nlimit);  // here MSA & FisherYates give ~= results. Best previously achievable (or to be expected)
					else if (a == 3)	wi = Super_Shuffle(i, shuffleID, nlimit);  // NOW: best results that could have been wished for, effectively Ideal.

					if (i==nlimit) printf(" "); // put a space between shuffle sets
					printf("%c", wi + firstChr);
					if (indx[wi]) {
						d = abs(cnt - indx[wi]);
						if (d < min) min = d;  // check for a minimum
						if (d > max) max = d;  // check for a maximum
						dsum += d;
						dcnt++;
					}
					indx[wi] = cnt;
				}
				printf("\n ");
			}
			printf("\n   -----  intervals  -----\n  Minimum  Average  Maximum\n");
			printf("    %d       %.1f     %d \n\n", min, (float)dsum/dcnt, max);
		}


		printf("\n With the Super-Shuffle (using a Miller Shuffle) you easily avoid all the (inter & intra-shuffle) annoying premature repeats.\n");
		printf(" Press enter to perform all new shuffles.\n\n");

		while (cin != 0 && cin != '\n' && cin != EOF) { cin = getchar(); }  // clear out the STDIN buffer, as needed
		do {   // while waiting termination, examine the stdout console, rerun on receiving input
			cin = getchar();
		} while (cin == 0);
		if (cin=='x') { 
			if (nlimit == 26) { nlimit = 100; firstChr = 28; }
			else              { nlimit = 26; firstChr = 65; }
		}
	}
	return(0);
}


//			 Local Utilities
// ------------------------------------


// ------------------------------------
unsigned int random(unsigned int limit) {  // 15 bit to full 32bit PRNG hack (~= arduino 'random()')
	unsigned int randv;

	// -----------  collect 32 bits from 3 15-bit rand() values
	randv = (unsigned int)rand() | (rand() << 15) | (rand() << 30);  // optimized thru testing
	rand();  // + addition of rand() for maximum unique 32bit randomity !!!   Careful compiler optimization will remove this & more.

	if (limit != 0) randv = randv % limit;   // with limit==0 provide maximum range results
	return(randv);
}
