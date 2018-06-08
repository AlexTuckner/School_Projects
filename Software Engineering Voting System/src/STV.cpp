/**
 * @file STV.cpp
 *
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "userInput.h"
#include "STV.h"
#include "Voting_Algorithm.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

 /**
  * \namespace csci5801
  * @{
  */


/*******************************************************************************
 * Static Variables
 ******************************************************************************/


/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

 	STV::STV(int nCandidates,int nBallots,int nSeats, bool ts) :
		VotingAlgorithm(nCandidates, nBallots, nSeats),
		toShuffle(ts) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

  /**
  * @brief This is the class that will actually run the STV Voting Algorithm.
  *
  */


void STV::runSTV(void) {
	//@todo
  //@todo add shuffle only if shuffle is on (Default)
  std::cout << "shuffle:" << std::endl;
	shuffleBallots();
  calculateDroop();

  // For testing REMOVE
  //droopQuota = 1;
  //seatsCount = 2;
  // End testing

  int winnercounter = 0;
  int nextLowest = 1;
  int j = 0;
  bool ballotNotAllocated = true;
  bool breakout = false;

  std::cout << "BallotsCount: " << ballotsCount << std::endl;
  std::cout << "Droop Quota: " << droopQuota << std::endl;
  std::cout << "SeatsCount: " << seatsCount << std::endl;
  std::cout << std::endl;

  printElected();

  while(winnercounter < seatsCount) {
    for(int i = 0; i < ballotsCount; i++) {
      //std::cout << "I: " << i << std::endl;
      ballotNotAllocated = true;
      nextLowest = 1;
		if (ballotsValid(ballots[i])) {
		  while(ballotNotAllocated) {
			//std::cout << "J: " << j << std::endl;
			ballotsValid(ballots[i]);
			if (ballots[i][j] == nextLowest) {
			  if(elected[j] != 1) {
				//std::cout << "In Not elected" << std::endl;
				ballotsCounter[j]++;
				if(ballotsCounter[j] == droopQuota) {
				  elected[j] = 1;
				  winnercounter++;
				  // Print Statements for testing
				  std::cout << "Assigned Winner" << std::endl;
				  printElected();

				  if(winnercounter == seatsCount){
				  std::cout << "Breaking out of Loops: " << std::endl;
				  breakout = true;
				  break;
				  }
				}
				ballotNotAllocated = false;
			  } else {
				nextLowest++;
			  }
			}
			j = (j + 1) % candidatesCount;
			if(breakout) break;
		  }
		}
      if(breakout) break;
    }
    if(breakout) break;
  }


  std::cout << "Finished Droop" << std::endl;
  generateReport();
}

  /**
  * @brief
  *
  */

void STV::generateReport(void) {
	//@todo
  std::cout << std::endl;
  std::cout << "Winners: ";
  for(int i = 0; i < candidatesCount; i++){
    if(elected[i] == 1){
      std::cout << candidates[i] << ", ";
    }
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

void STV::calculateDroop(void) {
  droopQuota = int(ceil((ballotsCount/ (seatsCount  + 1)) + 1));
}

void STV::shuffleBallots() {
	std::cout << "Before Shuffle " << std::endl;
	printBallots();
	int swapPosition;
	int* tempBallot;
	int numShuffles = 5;
	srand(time(0)); // This will ensure a really randomized number by help of time.
	for (int k = 0; k < numShuffles; k ++){
		for (int i = 0; i < ballotsCount; i++) {
			int swapPosition = rand() % ballotsCount;
			tempBallot = ballots[i];
			ballots[i] = ballots[swapPosition];
			ballots[swapPosition] = tempBallot;
	  }
  	// std::cout << "Next Iteration " << std::endl;
  	// printBallots();
	}
	std::cout << std::endl;
	std::cout << "After Shuffle " << std::endl;

	printBallots();
}

bool STV::ballotsValid(int* ballots) {
	int half = (candidatesCount / 2) + 1;
	int aboveHalfCount = 0;
	for (int i = 0; i < candidatesCount; i++) {
		if (ballots[i] > 0) {
			aboveHalfCount++;
		}
	}
	if (aboveHalfCount >= half) {
		//std::cout << "Above" << std::endl;
		return true;
	} else {
		//std::cout << "Below" << std::endl;
		return false;
	}
}

 /**
  * @} End of Doxygen Namespace
  */
