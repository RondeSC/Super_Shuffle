# Super-Shuffle (“Super-” prefix:  “situated over and above”)
It does not do the shuffling, it orchestrates it.

## Status Quo
Doing a [PRIG](https://docs.google.com/document/d/1UOzZNXHsaTuRHNFvPH_tQwVWfTXUj9xP) or Fisher-Yates shuffle on one's playlist does ensure no repeats as you go through and that you’ll hear all the list items. But some folks are still bothered (esp. with short lists, eg: < 100)  by the fact that a subsequent shuffle can have a few items near the beginning which had been selected near the end of the last shuffle of the items in the playlist. But that's the expected nature of matters; live with it ! or not ?

## A New Reality
I have devised some over lying software that changes this inter-shuffle reality. With, what I’ll call here a “Super_Shuffle” the average interval between replays of any given song/item (across shuffles) is still the length of the playlist, but the minimum & maximum interval goes from being: 1 ‘consecutive’ and ~(2 * #items) to being: ~#items/2 and (1.5 * #items). Which is generally far more desirable.

Basically how it works is: it uses a baseline shuffle from which the first half of those items are doled out using a PRIG indexing into them, then similar is done with the second half of the baseline set. Subsequent shuffles use a new random shuffle ID for the PRIG indexing into the same baseline shuffle. This results in the minimum, average and maximum intervals between like items as stated above.

Using the Super_Shuffle, one retains the functional attributes associated with a Miller Shuffle Algorithm, as implemented here-in.
Note that due to the internal design of the MSA PRIGs, instead of creating new shuffle IDs one could simply continue endlessly incrementing the input reference index for virtually identical results. 

Note that due to processing the playlists in two halves some randomness qualities are lost. Only with very short lists may this possibly be noticed. None of my randomness test suites manage to notice at all.
If the user, for whatever reason wants totally new shuffles, the global shuffle ID used for the baseline shuffle is to be changed.

The code I have in ‘Super_Shuffle()’ has a little more complexity in order to handle odd length lists and to improve long term (inter-shuffle) randomness.

## Demonstration
Sample run of A-Z shuffles. Output of Super_Shuffle_Demo.exe
```
Generating 20 consecutive shuffles for three diverse handlings of playlist shuffles.
The gathered statistics of intervals between instances of any given item
demonstrates the reality of bunching of like items accross shuffles.


Simple use of rand() as a "shuffle":
 BFMSPBMWBYIHQAHNZSGWDETLHM ZQPGEXQSAEMUDCNPUGROEXNCGF
 CUPYHLPJCBABZKUFUOPQIRTKRY AYUPMHGLPBPODZHVIIULHDNUEK
 QTSYFUOZYMWCSLMSUNSOLXIWKW NUJLRFZXQETXTGKZMTKKIYNSIQ
 CUAGWHLYHYEUPOHGDOGYOSZNTO ESAOOZUFXWNZNIHZHWYCRPVBCF
 WJTMNRMOPUGXVZLNRFXULUZGFV EZMYVPAAFFNCFAUWVTCBGBOCFL
 RRIZGNLOHEZPJEVDHBICNSGGLF WLYJFWIPQNDENADZAAIWSMTLDV
 FZGETYEQTNHFUXMPXWEZWWOVEJ WFDNRFKBRTBBJSULNFETLRMQJM
 UOOIERQCUNBLZLBABGVWCZORXJ TDERTCGARQKZBUZBIOOLLSHIUP
 YQELJOIWFOOACHSTTUTWZLXNEF SAEKQZIEDPNPRYEVAECUENPBTX
 VKFRSPAYGNYZDPYKWRYMNJYZIJ YXOVQYTJNAEQXRFESPKXROPLRW

   -----  intervals  -----
  Minimum  Average  Maximum
    1       24.8     195

Straight forward use of a quality shuffle algo:
 ENPZJQKLWVOBIGRCXMFUHYSDTA WCSVAULTHBMYJPGFNORIKZEXQD
 CMGOTHJAYEWZDNBXFIKPURQLVS FPXLQNVJISTARBDOKWGUHYMCEZ
 TOFIHEJQBWNCDULMGXVZSKPARY CUIPNTSAHMLOKXRGEJQVBDWFZY
 LJKRFBQWOGNIYSXVACMZUDPHTE BTUFALJHMGOPZYRSDNEVCKQIWX
 CDMVAJXWGYQHPLTERUFISKNZBO NOAZHPLUICYRMQKXDWVETGFSBJ
 UCOELAMSHGBQIVNKZWPXDTJRFY BKRIDLNEQXPJWOZCMHUATFSVGY
 TZFUHRQVOXLIAGMDBCSKEPNWYJ UGJFBXWTLYPZSICDNKEAMVOHRQ
 ZTOCYMFRGWVNKPDSQXBHIULJAE BQOHKSPZGMJLDARUFCNTXIVWEY
 NKRUXDMZLIFWEPJAHGYCSOQTVB STZNIQHWDAMGXJVEFYRCPLUBKO
 GKTUSCABROMIYFVWLQNXDEPHZJ UGYVPHRBWLEDZSFINKTACMQXJO

   -----  intervals  -----
  Minimum  Average  Maximum
    2       26.0     51

Done with 'Super_Shuffle' utilizing MSA-e:
 JIOKZSTMUWYPFALVEDNCRXHQGB OPJTMISFYWZUKRBHEXALNVCGDQ
 TWUMFZPISOJYKQCBVLNAEHGXRD ZIMSKPUJWFOTYACQVRHLGNBEXD
 FIWMOTPKYJSZUCQXVRAHGDLBNE FKIMYWZPUJOSTHVBEDARNLQXGC
 KTMJYWSZIUFOPAQDELRHCXNVGB OKIMJTYSPZFWUBHVRNGELQAXCD
 TSWOYZUIFJKPMDLGQVNBHXARCE ZOFSUYWIMJPKTCRVGQELNHDXAB
 ZFWMISJKPUYOTGLCHEQRVXBDAN ZIKJWSFYMPUOTHDQGNEVCLRXBA
 UWJOYZIPFKSTMXNDEQRCGAHLVB JYOUTPIFMKWSZNCLXQBEVHARGD
 UYPMJTIKFSZOWRBHEQVGXDLANC MTYKIOPFSJUWZXRCHDQVGBLANE
 JKIFMWYZSUOPTNXHALQVCREGBD MWUITKPYOFSZJCDGVELQHNBXRA
 JUPZFMOSTKYIWGRQEXHBDCVANL IJMYWTOZPKSFURQLBGDXAECVHN

   -----  intervals  -----
  Minimum  Average  Maximum
    14       26.0     38


 With the Super-Shuffle (using a Miller Shuffle) you easily avoid all the
 (inter & intra-shuffle) annoying premature repeats.
 Press enter to perform all new shuffles.
```
