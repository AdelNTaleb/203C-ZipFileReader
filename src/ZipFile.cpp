/*
 * ZIPFILE.cpp
 *
 *  Created on: 20 mars 2016
 *      Author: Taleb
 */

#include "ZipFile.hpp"
#include "CDFH.hpp"
#include <fstream>
#include <iostream>
using namespace std;

ZIPFILE::ZIPFILE(const char* path){
	char *memblock;
	short numDH=0;
	int offsetCD=0;
	fstream File;
	streampos size;

	File.open(path, ios::in|ios::binary|ios::ate);


	if ( File  ){
		size = File.tellg();
		Size = size;
		File.seekg(0,ios::beg);
		memblock=new char  [size];
		File.read(memblock,size);
		File.close();


		eocd = EOCD(memblock);
		do {
			CDFH cdfh = CDFH( &memblock[eocd.CDstart+offsetCD]) ;

			cdfh.setData(&memblock[cdfh.Offset+cdfh.lenghtLFH()]);
			cdfhs.push_back(cdfh);
			offsetCD =offsetCD + cdfh.Size;

			numDH++;
		} while (numDH<eocd.CDtotnum);
	}
};

void ZIPFILE::printEOCD(){
	eocd.print();
}

void ZIPFILE::printCDFH(){
	for (unsigned int i(0); i < cdfhs.size();i++ ){
		cout << "===== Central directory file header number " << i+1 << " =====" <<endl;
		cdfhs[i].print_cdfh();
		cout << endl;
	}
}



void ZIPFILE::tier1(){
	cout << "There are " << dec <<  cdfhs.size() << " file(s) in this zipFile" << endl;
	for (unsigned int i(0); i < cdfhs.size();i++ ){
		cdfhs[i].tier1();
	}
}

void ZIPFILE::print(){
	printEOCD();
	printCDFH();
}

void ZIPFILE::extractall(){
	for (unsigned int i(0); i < cdfhs.size();i++ ){
		if( cdfhs[i].extract(cdfhs[i].Name) ){
			cout << cdfhs[i].Name << " has been extracted" << endl;
		} else
			cerr << cdfhs[i].Name << " hasn't been extracted"<<endl;
	}
}


void ZIPFILE::extract(){
	int userChoice;
	do {
	cout << endl <<  "Please select which file to extract." << endl;
	for (unsigned int i(0); i < cdfhs.size();i++ ){
		cout << i <<". " << cdfhs[i].Name << endl;
	}
	cout << "99. Extract all files" << endl;
	cout << "100. Exit" <<endl <<endl;
	cin >> userChoice;

	if (userChoice <= cdfhs.size()){
		if( cdfhs[userChoice].extract(cdfhs[userChoice].Name) ){
						cout << cdfhs[userChoice].Name << " has successfully been extracted." << endl;
					} else
						cerr << cdfhs[userChoice].Name << " hasn't been extracted."<<endl;
	} else if (userChoice==99){
		extractall();
		break;
	} else if (userChoice==100){
		break;
	} else {
		cerr << "Invalid Number" << endl;
	}
	} while (true);

}
