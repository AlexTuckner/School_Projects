/**
 *
 * @ file Voting_Algorithm.h
 *
 */

#ifndef SRC_VOTING_ALGORITHM_H_
#define SRC_VOTING_ALGORITHM_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

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
  * @brief Constructor class for our Voting Algorithm Object.
  *
  */


class VotingAlgorithm {
  public:
	/// Create General Voting Algorithm with the number of candidates, ballots and seats
	VotingAlgorithm(int nCandidates,int nBallots,int nSeats){
	/// number of candidates
	candidatesCount = nCandidates;
	/// number of ballots
	ballotsCount = nBallots;
	/// number of seats
	seatsCount = nSeats;
	elected = new int[candidatesCount];
	nonElected = new int[candidatesCount];
	ballotsCounter = new int[candidatesCount];
	for (int i = 0; i <= sizeof(ballotsCounter); i++) {
		elected[i] = 0;
		nonElected[i] = 0;
		ballotsCounter[i] =0;
	}
	ballots = new int*[ballotsCount];
	candidates = new std::string[candidatesCount];
/*	for(int i = 0; i < ballotsCount; ++i)
		ballots[i] = new int[candidatesCount];
		for(int x = 0; x < candidatesCount; x++) {
			ballots[i][x] = 0;
		} */
	}

  void printBallots(void);
  void printElected(void);
	/// get the elected candidates
	int *getElected(void) { return elected; }
	/// get the eliminated candidates
	int *getNonElected(void) { return nonElected; }
	/// set the ballots
	void setBallots(int** new_ballots) {
		ballots = new_ballots;
}
	/// get the ballots
	int **getBallots(void) { return ballots; }

	/// set the elected candidates
	void setElected(int winner);
	/// set the eliminated candidates
	void setNonElected(int loser);
	/// set the candidates
	void setCandidates(std::string* new_candidates);
	/// get all candidates
	std::string* getCandidates(void) { return candidates; }
	protected:
		/// number of candidates
		int candidatesCount;
		/// number of ballots
		int ballotsCount;
		/// number of seats
		int seatsCount;
		/// elected candidates array
		int* elected;
		/// eliminated cadidates array
		int* nonElected;
		/// number of winning ballots for a given candidate
		int* ballotsCounter;
		/// the ballots in a 2d array
		int** ballots;
		/// the candidates in an array
		std::string* candidates;
};


//NAMESPACE_END(csci5801);

 /**
  * @} End of Doxygen Namespace
  */

#endif /* SRC_VOTING_ALGORITHM_H_ */
