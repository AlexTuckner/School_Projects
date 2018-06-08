/**
 * @file Plurality.cpp
 *
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "userInput.h"
#include "Plurality.h"
#include "Voting_Algorithm.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

 /**
  * \namespace csci5801
  * @{
  */


/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* We're doing this under the assumption that ballots is an array of tuples,
 * so that we can iterate through it and count the 1's for Plurality and add them
 * to the ballotsCounter[] array.
 */
Plurality::Plurality(int nCandidates,int nBallots,int nSeats) :
	VotingAlgorithm(nCandidates, nBallots, nSeats) {}



void Plurality::runPlurality(void) {

	printBallots();

	for (int i = 0; i < ballotsCount; i++){

		//Iterating through each ballot
		for (int x = 0; x < ballotsCount; x++) {

			//Iterating through each vote on the current ballot
			if (ballots[i][x] == 1){
				ballotsCounter[x] += 1;

			}
		}
	}//end of for loop

	int a = 0;


std::cout << "Winners: " << std::endl;
//seatsCount from UserInput
	while (a < seatsCount) {
		int index;
		for (int i = 0; i < sizeof(candidates); i++) {
			if (i == 0) {
				index = 0;
			}
			else {
				//If current candidate has more votes than previous largest
				if (ballotsCounter[i] > ballotsCounter[index]) {
					index = i;
				}
				//If current candidates has an equal number of votes, randomly choose one and continue iterating
				if (ballotsCounter[i] == ballotsCounter[index]) {
					int random_draw = rand() & 1;
					if (random_draw == 0){
						index = i;
						//setElected(i);
					}
				}
			}
		}//for bracket

		//take highest vote getter and move them into elected[]
		std::cout << candidates[index] << ", ";
		ballotsCounter[index] = -1;
		a++;

	}//while bracket


std::cout << std::endl;
}



 /**
  * @} End of Doxygen Namespace
  */
