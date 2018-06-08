/**
 *
 * @ file STV.h
 *
 */

#ifndef SRC_STV_H_
#define SRC_STV_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include "userInput.h"
#include "Voting_Algorithm.h"

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
  * @brief Constructor class for our STV (Droop Method) Object.
  *
  */


class STV : public VotingAlgorithm {
  public:
    STV(int nCandidates,int nBallots,int nSeats, bool ts);
		void runSTV(void);
		void generateReport(void);
		/// calculate and store the droop quota
		void setDroopQuota(int integer) { droopQuota = integer; }
		/// get the droop quota
		int getDroopQuota(void) { return droopQuota; }
		/// set shuffle on/off
		void setToShuffle(bool shuffle) { toShuffle = shuffle; }
		/// get the shuffle status
		bool getToShuffle(void) { return toShuffle; }
		bool ballotsValid(int* ballot);

	private:
		int droopQuota;
		bool toShuffle;
		//int rand();
		void calculateDroop();
		void shuffleBallots();
		void deleteBallot(int index);
};



 /**
  * @} End of Doxygen Namespace
  */

#endif /* SRC_PLURALITY_H_ */
