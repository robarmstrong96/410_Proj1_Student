/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"
#include <unistd.h>

using namespace std;

//********************** private to this compilation unit **********************

vector<process_stats> data;

bool sorter(process_stats, process_stats);

static SORT_ORDER sort_setting;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	//clear vector for new data
	data.clear();

	//opening file/basic file i/o
	ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		string temp_file_name;
		temp_file_name += "src/"; temp_file_name += filename;
		file.open(temp_file_name);
		if (!file.is_open()) { return COULD_NOT_OPEN_FILE; }
	}

	// reading and adding to vector
	string file_line;
	bool first_line_encounter = false;
	while(getline(file, file_line)) {
		if (ignoreFirstRow && !first_line_encounter) {
			first_line_encounter = true;
		}
		else {
			stringstream stream(file_line);
			string current;
			vector<string> chars;
			while (getline(stream, current, CHAR_TO_SEARCH_FOR)) {
				chars.push_back(current);
			}
			if (chars.size() == 4 && (count(chars.begin(), chars.end(), " ") < 1) && (count(chars.begin(), chars.end(), "") < 1)) {
				process_stats temp_struct;
				temp_struct.process_number = stringToInt(chars[0].c_str());
				temp_struct.start_time = stringToInt(chars[1].c_str());
				temp_struct.cpu_time = stringToInt(chars[2].c_str());
				temp_struct.io_time = stringToInt(chars[3].c_str());
				data.push_back(temp_struct);
				}
			}
		}
		return SUCCESS;
	}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	sort_setting = mySortOrder;
	sort(data.begin(), data.end(), sorter);
}

bool sorter (process_stats a, process_stats b) {
	if (sort_setting == CPU_TIME) {
		if (a.cpu_time < b.cpu_time) { return true; }
		return false;
	}
	if (sort_setting == PROCESS_NUMBER) {
		if (a.process_number < b.process_number) { return true; }
		return false;
	}
	if (sort_setting == START_TIME) {
		if (a.start_time < b.start_time) { return true; }
		return false;
	}
	if (sort_setting == IO_TIME) {
		if (a.io_time < b.io_time) { return true; }
		return false;
	}
}

process_stats getNext() {
	for (int i = 0; i < data.size(); i++) { cout << to_string(data[i].process_number) << " + " << to_string(data[i].start_time) << endl;}
	process_stats myFirst;
	myFirst = data.front(); // Assigns first struct entry to myFirst struct.
	data.erase(data.begin()); // Deletes the first entry from the vector.
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	cout << data.size() << endl;
	return data.size(); // Size of vector = # of rows. Each vector element is a single struct entry, representing a single row.
}
