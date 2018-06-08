#include "CSV_Reader.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

int CSV_Reader::setCBFromFile(std::string filePath) {
	// input file to stream from
	std::ifstream inFile;
    
    // Info Array (candidates, ballots, seats, algorithm)
	std::string info[4];
    
    // Open file to get info
    inFile.open(filePath.c_str());
	if (!inFile) {
		std::cout << "Unable to open file\n";
        return 0;
	}
    
    // Prepare to get the first line
    std::string info_line;
    
    // Get the first line
	std::getline(inFile, info_line, '\n');
    
    // Close the file
    inFile.close();
    
    // Prepare to parse info_line
    std::istringstream info_ss(info_line);
    
    // Parse it
    for (int i = 0; i < 4; i++) {
        std::string substr;
		getline( info_ss, substr, ',' );
        info[i] = substr;
    }
    
    // Turn info into list of ints
	int* info_int = new int[4];
	for (int i = 0; i < 4; i++) {
		int x;
		std::istringstream temp(info[i]);
		temp >> x;
		info_int[i] = x;
	}
	
    // Setting the private variable
	info_list = info_int;
    
    
    // Candidates
	int cols = info_list[0];
	
	// Ballots + 2 (first row for the info, second row for candidates)
	int rows = info_list[1]+2;
	
	// Raw data from CSV
	std::string raw_data[rows];
	
	
	
	// Candidates array
	std::string candidates[cols];
	
	// Ballots string array
	std::string ballots[rows-2][cols];
	
	// Ballots int array
	//int** ballots_int = new int*[rows-2][cols];
	
	//std::cout << "Got here\n";
	
	int **ballots_int = new int*[rows-2];
	for(int i = 0; i < rows-2; ++i) {
		ballots_int[i] = new int[cols];
	}
	
	//std::cout << "Got here2\n";
	
	std::string line;
	
	// string to store the row when retrieved from the CSV file
	std::string row;
	
	// Open the file in inFile and error check
	inFile.open(filePath.c_str());
	if (!inFile) {
		std::cout << "Unable to open file\n";
	}
	
	// Iterate through rows
	for (int i=0; i<rows; i++) {
		
		// Get the line at iteration i and put into line
		std::getline(inFile, line, '\n');
        
		// Put the line into the raw data
		raw_data[i] = line;
		//std::cout << raw_data[i] << "\n";
		
		// Prepare line to be parsed
		std::istringstream ss(line);
		
		// Iterate through 
		for (int j=0; j<cols; j++) {
			// substr is the individual cell of the CSV
			std::string substr;
			getline( ss, substr, ',' );
			if (i == 0) {
				info[i] = substr;
			}
			else if (i == 1) {
				candidates[j] = substr;
			} else {
				if (substr.compare("") != 0) {
					ballots[i-2][j] = substr;
				} else {
					ballots[i-2][j] = "0";
				}
			}
		}
	}
	
	// Convert ballots to integers.
	for (int i = 0; i < rows-2; i++) {
		for (int j = 0; j < cols; j++) {
			int x;
			std::istringstream temp(ballots[i][j]);
			temp >> x;
			ballots_int[i][j] = x;
			//std::cout << ballots_int[i][j] << "\n";
		}
	}
	
    // Setting the private variables
	ballots_list =  ballots_int;
	candidates_list = candidates;
    
    // Closing the file
    inFile.close();
    
    // return success
    return 1;
}