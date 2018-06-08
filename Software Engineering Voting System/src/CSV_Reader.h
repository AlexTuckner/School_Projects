/**
 *
 * @ file CSV_Reader.h
 *
 */

#ifndef SRC_CSV_READER_H_
#define SRC_CSV_READER_H_

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
  * @brief Constructor class for our CSV Reader Object.
  *
  */

class CSV_Reader {
	public:
		/// Set the candidates and ballot lists from the CSV file
		int setCBFromFile(std::string filePath);
		
		/// Get the list of ballots as a 2d Array
		int** getBallotsList() { return ballots_list; }
		
		/// Get the list of candidates as an array
		std::string* getCandidatesList() { return candidates_list; }
        
        int getCandidatesCount() {return info_list[0]; }
        int getBallotsCount() {return info_list[1]; }
        int getSeatsCount() {return info_list[2]; }
        int getVotingAlgorithm() {return info_list[3]; }
	private:
		int* info_list;
		int** ballots_list;
		std::string* candidates_list;
};

#endif /* SRC_CSV_READER_H_ */
