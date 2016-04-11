/*
 * ZipFile.hpp
 *
 *  Created on: 20 mars 2016
 *      Author: Taleb
 */

#ifndef ZIPFILE_HPP_
#define ZIPFILE_HPP_
#include "EOCD.hpp"
#include "CDFH.hpp"
#include <fstream>
#include <vector>
using namespace std;

struct ZIPFILE {

	EOCD eocd;
	vector<CDFH> cdfhs;

	int Size;


	bool openfile(char* path, fstream File);


	ZIPFILE(const char*);
	ZIPFILE( string );
	void printEOCD();
	void printCDFH();
	void tier1();
	void print();
	void printLFH();
	void extract();
	void extractall();
};



#endif /* ZIPFILE_HPP_ */
