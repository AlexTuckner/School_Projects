/**
 *
 * @ file Plurality.h
 *
 */

#ifndef SRC_PLURALITY_H_
#define SRC_PLURALITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
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
  * @brief Constructor class for our Plurality Object.
  *
  */


class Plurality : public VotingAlgorithm {
  public:
    Plurality(int nCandidates,int nBallots,int nSeats);
    void runPlurality(void);
};

 /**
  * @} End of Doxygen Namespace
  */

#endif /* SRC_PLURALITY_H_ */
