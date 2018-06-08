/**
 * @file main.cpp
 *
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <string.h>
#include "userInput.h"
#include "Plurality.h"
#include "STV.h"
#include "CSV_Reader.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/


/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
/// This is the main function that will take the user through the process
int main(int argc, char **argv) {
  std::string fileName;
  // Create a new userInput object and get inputs if not provided
  userInput* input = new userInput();
  if (!argv[1]) {
      input->getUserInput();
      fileName = input->getFilePath();
	  input->setToShuffle(1);
  } else {
	  if(strcmp(argv[1],"-s")==0){ // -s is the secret command to turn off shuffle
	      input->getUserInput();
	      fileName = input->getFilePath();
		  input->setToShuffle(0);
		  std::cout << "Shuffle turned off" << std::endl;
	  }
	  else {
	      fileName = argv[1];
		  input->setToShuffle(1);
	  }
  }

  // Create a new CSV_Reader object and get the data from the the file sent as a parameter
  CSV_Reader cv;
  if (!cv.setCBFromFile(fileName)) {
      std::cout << "Error" << std::endl;
      return 0;
  }

  if(cv.getVotingAlgorithm() == 0){
    // Start Plurality
    std::cout << "Starting Plurality" << std::endl;

    // Create a new Plurality object and run the plurality voting algorithm.
    Plurality* plurality = new Plurality(cv.getCandidatesCount(), cv.getBallotsCount(), cv.getSeatsCount());
    plurality->setCandidates(cv.getCandidatesList());
    plurality->setBallots(cv.getBallotsList());
    plurality->runPlurality();


  } else if (cv.getVotingAlgorithm() == 1){
    std::cout << "Starting Droop" << std::endl;

    STV* stv = new STV(cv.getCandidatesCount(), cv.getBallotsCount(), cv.getSeatsCount(), input->getToShuffle());
    stv->setCandidates(cv.getCandidatesList());
    stv->setBallots(cv.getBallotsList());
    stv->runSTV();

  } else {
    std::cout << "Invalid Algorithm Chosen" << std::endl;
  }

   return 1;
}
