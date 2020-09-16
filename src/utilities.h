/*
* utilities.h
*
*  Created on: Aug 28, 2016
*      Author: Keith
*  part of project1 for OS
*  Changelog
*  9/17/17 sort - clarified meaning - low to high
*          loadData - clarified behaviour - clears vector on load
*          saveData - clarified behaviour - overwrite file contents
*/

#ifndef UTILITIES_H_
#define UTILITIES_H_

const int 			SUCCESS			 				=  0;
const int 			FAIL							=  SUCCESS - 1;
const int 			COULD_NOT_OPEN_FILE				=  SUCCESS - 3;
const int			UNINITIALIZED					=  SUCCESS - 5;
const char			CHAR_TO_SEARCH_FOR				=',';

//this is where the loaded data goes
struct process_stats{
	int process_number	= UNINITIALIZED;
	int	start_time		= UNINITIALIZED;
	int cpu_time		= UNINITIALIZED;
	int io_time			= UNINITIALIZED;
};

enum SORT_ORDER { CPU_TIME, PROCESS_NUMBER, START_TIME, IO_TIME };

//allthe functions available for use

//clears vector (or whatever datastructure you choose) holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to the vector holding these structs
//NOTE: be sure to ignore malformed rows (see 'Project 1 Description')
//
//if ignoreFirstRow ==true then discard the first row
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename, bool ignoreFirstRow = true);

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder);

//returns number of process_stats structs in the vector holding them
int getNumbRows();

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext();


#endif /* UTILITIES_H_ */
