/**
 * @file userInput.cpp
 *
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include <iostream>
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

userInput::userInput() :
  candidatesCount(0),
  ballotsCount(0),
  seatsCount(0),
  votingAlgorithm(0) {
    toshuffle = 0;
  }


/*******************************************************************************
 * Member Functions
 ******************************************************************************/



void userInput::getUserInput(){
  std::string in;
  int num;

  std::cout << "Please enter the filename: ";
  std::cin >> in;
  setFilePath(in);

  /*std::cout << "Please enter the number of candidates: ";
  std::cin >> num;
  setCandidatesCount(num);

  std::cout << "Please enter the number of ballots: ";
  std::cin >> num;
  setBallotsCount(num);

  std::cout << "Please enter the number of seats to be filled: ";
  std::cin >> num;
  setSeatsCount(num);

  std::cout << "Which Algorithm would you like to use? (Enter 0 for Plurality or 1 for Droop): ";
  std::cin >> num;
  setVotingAlgorithm(num);

  std::cout << "Input " << getFilePath() << " NumCan: " << getCandidatesCount() << " NumBal " << getBallotsCount() << " NumSeats: " << getSeatsCount() << " Algorithm: " << getVotingAlgorithm() << std::endl;
  */
}

void userInput::shuffleInput() {
  int num;
/*  std::cout << "Would you like to shuffle? (Enter 0 for 'no' or 1 for 'yes'): ";
  std::cin >> num; */
  setToShuffle(num);
}

 /**
  * @} End of Doxygen Namespace
  */
