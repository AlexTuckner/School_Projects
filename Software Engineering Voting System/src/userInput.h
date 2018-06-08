/**
 *
 * @ file userInput.h
 *
 */

#ifndef SRC_USER_INPUT_H_
#define SRC_USER_INPUT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

 /**
  * \namespace csci5801
  * @{
  */

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/


  /**
  * @brief Constructor class for our userInput Object.
  *
  */

class userInput {
  public:
    userInput();
	/// get the file path
    std::string getFilePath() {return filepath;}
    /// set the file path
    void setFilePath(std::string fp) {filepath = fp;}
	/// get the number of candidates
    int getCandidatesCount() {return candidatesCount;}
	/// get the number of candidates
    void setCandidatesCount(int n) {candidatesCount = n;}
	/// get the number of ballots
    int getBallotsCount() {return ballotsCount;}
    /// set the number of ballots
    void setBallotsCount(int n) {ballotsCount = n;}
	/// get the number of seats
    int getSeatsCount() {return seatsCount;}
    /// set the number of seats
    void setSeatsCount(int n) {seatsCount = n;}
	/// get the voting alogrithm chosen
    int getVotingAlgorithm() {return votingAlgorithm;}
	/// set the voting algorithm
    void setVotingAlgorithm(int b) {votingAlgorithm = b;}
	/// get the shuffle status
    int getToShuffle() {return toshuffle;}
    /// set the shuffle status
    void setToShuffle(int b) {toshuffle = b;} 

    void getUserInput();

    void shuffleInput();


  private:
    std::string filepath;
    int candidatesCount;
    int ballotsCount;
    int seatsCount;
    int votingAlgorithm;
    int toshuffle;

};

 /**
  * @} End of Doxygen Namespace
  */

#endif /* SRC_USER_INPUT_H_ */
