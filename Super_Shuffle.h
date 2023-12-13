
//	  Super_Shuffle
// source: https://github.com/RondeSC/Super_Shuffle
// license: Attribution-NonCommercial-ShareAlike
// Copyright 2023 Ronald R. Miller
// http://www.apache.org/licenses/LICENSE-2.0
//

#define MillerShuffle MillerShuffleAlgo_e
// MillerShuffle source: https://github.com/RondeSC/Miller_Shuffle_Algo 

unsigned int MillerShuffleAlgo_e(unsigned int, unsigned int, unsigned int);  // advance prototype
extern unsigned int userSID;

// ------------------------------------------------------------
//						Super-Shuffle 
// “Super-” prefix: “situated over and above”
// It does not 'shuffle' it orchestrates shuffles
// to provide continuous sets of random items, across multiple shuffles
// insuring an intervals between like items of ~ 0.5 to 1.5 * # of items (+/-1)
//
// While utilizing a MillerShuffle it has the same functional attributes like:
// performing equally well while continuously incrementing the reference 'inx' input instead of changing the 'shuffleID'
unsigned int Super_Shuffle(unsigned int inx, unsigned int shuffleID, unsigned int listSize) {
	unsigned int si, hi, offset;
	int halfSize = listSize / 2;  // for 1/2 the processing range

	shuffleID += 131 * (inx / listSize);  // have inx overflows supported
	si = (inx % listSize);
	if (si < halfSize) {
		hi = si;
		offset = 0;
	} else {
		hi = listSize - 1 - si;
		offset = halfSize;
		halfSize = listSize - halfSize;
		shuffleID++;
	}

	hi = MillerShuffle(hi, shuffleID, halfSize);     // use any STD MSA() shuffle (aka: a PRIG function)
	si = MillerShuffle(hi + offset, userSID, listSize);  // indexing into the baseline shuffle
	return(si);
}

// --------------------------------------------------------------
// Miller Shuffle Algorithm E variant
// 
unsigned int MillerShuffleAlgo_e(unsigned int inx, unsigned int shuffleID, unsigned int listSize) {
	static unsigned int si, r1, r2, r3, r4;
	static unsigned int randR, halfN, rx, rkey;
	const unsigned int p1 = 24317, p2 = 32141, p3 = 63629; // good for shuffling >60,000 indexes

	shuffleID += 131 * (inx / listSize);  // have inx overflow effect the mix
	si = (inx + shuffleID) % listSize;    // cut the deck

	randR = shuffleID;   //local randomizer
	r1 = randR % p3;
	r2 = randR % p1; // Now, per Chinese remainder theorem, (r1,r2,r3) will be a unique set
	r3 = randR % p2;
	r4 = randR % 2749;
	halfN = listSize / 2 + 1;
	rx = (randR / listSize) % listSize + 1;
	rkey = (randR / listSize / listSize) % listSize + 1;

	// perform the conditional multi-faceted mathematical mixing (on avg 2 5/6 shuffle ops done + 2 simple Xors)
	if (si % 3 == 0)       si = (((unsigned long)(si / 3) * p1 + r1) % ((listSize + 2) / 3)) * 3; // spin multiples of 3 
	if (si <= halfN) { si = (si + r3) % (halfN + 1); si = halfN - si; }  // improves large permu distro
	if (si % 2 == 0)       si = (((unsigned long)(si / 2) * p2 + r2) % ((listSize + 1) / 2)) * 2; // spin multiples of 2 
	if (si < halfN)    si = (si * p3 + r3) % halfN;

	if ((si ^ rx) < listSize)   si ^= rx;			// flip some bits with Xor
	si = ((unsigned long)si * p3 + r4) % listSize;  // a relatively prime gears churning operation
	if ((si ^ rkey) < listSize)  si ^= rkey;

	return(si);  // return 'Shuffled' index
}
