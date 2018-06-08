/**
 * @file Voting_Algorithm.cpp
 *
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include "Voting_Algorithm.h"
#include "userInput.h"

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



/*******************************************************************************
 * Member Functions
 ******************************************************************************/



//VotingAlgorithm:: VotingAlgorithm() :
//    {}

void VotingAlgorithm::setElected(int winner) {
    elected[winner] = 1;
}

void VotingAlgorithm::setNonElected(int winner) {
    nonElected[winner] = 1;
}
void VotingAlgorithm::setCandidates(std::string* new_candidates) {
	for (int i = 0; i < sizeof(candidates); i++) {
		candidates[i] = new_candidates[i];
	}
}

void VotingAlgorithm::printBallots() {
  std::cout << "Num Ballots: " << ballotsCount << ", Num Seats: " << seatsCount << ", Num Candidates: " << candidatesCount << std::endl;
  for (int i = 0; i < ballotsCount; i++) {
    std::cout << "Ballot " << i << ": ";
    for (int j = 0; j < candidatesCount; j++) {
      std::cout << ballots[i][j] << ", ";
    }
    std::cout << std::endl;
  }
}


void VotingAlgorithm::printElected() {
  std::cout << "Elected Array: " << std::endl;
  for(int i = 0; i < candidatesCount; i++) {
    if(i < candidatesCount - 1){
    std::cout << elected[i] << " , ";

    } else {
    std::cout << elected[i];
    }
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

 /**
  * @} End of Doxygen Namespace
  */
