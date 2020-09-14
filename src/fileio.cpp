/*
 * fileio.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: keith
 */

//============================================================================
// Name        : Proj1_410.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include "utilities.h"
//defaults
const char* 		SOURCE_FILE_H = "TestData_Heading.txt";
const char* 		SOURCE_FILE_NO_H = "TestData_NoHeading.txt";
const char* 		SOURCE_FILE_NO_H_CR = "TestData_NoHeading_CORRUPTED_ROWS.txt";
const char* 		BOGUS_FILE = "BOGUS.txt";
using namespace std;

int test(int iRet, int expected_val, int total_points,int penalty, int test_numb, string info) {
	if (iRet != expected_val) {
		total_points = total_points - penalty;
		cout <<"FAILED "<<test_numb<< ";"<<info <<"; expected value="<<expected_val<<"; actual value="<<iRet<<"; penalty="<<penalty<<" points"<< endl;
	} else
		cout << "Success "<<test_numb << endl;

	cout<<total_points<<endl;
	return total_points;
}

int main() {
	int total_points = 100; //assume success
	int iRet = FAIL;

	//verify return COULD_NOT_OPEN_FILE when opening non existant file
	iRet = loadData(BOGUS_FILE);
	total_points = test(iRet,COULD_NOT_OPEN_FILE, total_points, 20,1, "failed to return COULD_NOT_OPEN_FILE on bogus file" );

	//load valid file, with a heading
	iRet = loadData(SOURCE_FILE_H, true);
	total_points = test(iRet,SUCCESS, total_points, 5,2, "failed to return SUCCESS on correct file" );

	iRet = getNumbRows();
	total_points = test(iRet,10, total_points, 15,3, "failed to return correct numb rows" );

	//load valid file, no heading
	iRet = loadData(SOURCE_FILE_NO_H, false);
	total_points = test(iRet,SUCCESS, total_points, 5,4, "failed to return SUCCESS on correct file" );

	iRet = getNumbRows();
	total_points = test(iRet,10, total_points, 15,5, "failed to return correct numb rows" );

	//load valid file, no heading, messed up rows
	iRet = loadData(SOURCE_FILE_NO_H_CR, false);
	total_points = test(iRet,SUCCESS, total_points, 5,6, "failed to return SUCCESS on correct file" );

	iRet = getNumbRows();
	total_points = test(iRet,8, total_points, 15,7, "failed to return correct numb rows" );

	////////////
	//get the next one in line
	process_stats myStats = getNext();
	if (myStats.process_number!=3 || myStats.start_time !=80 ||myStats.cpu_time !=500 ||myStats.io_time !=1  ){
			total_points =total_points-15;
			cout<<"-20 failed getnext, expected 3,80,500,1 got "<<std::to_string(myStats.process_number) <<","<<std::to_string(myStats.start_time)<<","<<std::to_string(myStats.cpu_time)<<","<<std::to_string(myStats.io_time)<<endl;
	}
	else
		cout<<"Success 8"<<endl;

	//sort the data
	sortData(START_TIME);

	//get the next one in line
	myStats = getNext();
	if (myStats.process_number!=10 || myStats.start_time !=10 ||myStats.cpu_time !=200 ){
		total_points =total_points-20;
		cout<<"-20 failed getnext after sort, expected 10,10,200 got "<<std::to_string(myStats.process_number) <<","<<std::to_string(myStats.start_time)<<","<<std::to_string(myStats.cpu_time)<<endl;
	}
	else
		cout<<"Success 9"<<endl;


	cout<<"TOTAL POINTS FOR STUDENT = "<<std::to_string(total_points)<<endl;
	return iRet;
}
