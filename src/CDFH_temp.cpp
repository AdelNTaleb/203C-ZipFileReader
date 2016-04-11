/*
 * CDFH_temp.cpp
 *
 *  Created on: 19 mars 2016
 *      Author: Taleb
 *
 */

#include<iostream>
#include <string.h>
#include "CDFH_temp.hpp"

using namespace std;

CDFH_temp::CDFH_temp(char * block){
	memcpy(this,block,sizeof(CDFH_temp));
};

void CDFH_temp::print_cdfh(){
	cout << "===== Central directory file header  =====" <<endl;
	//cout << "Central directory file header signature : " << hex << sign << endl;
	//cout << "Version made by : " << versionBy << endl;
	//cout << "Version needed to extract (minimum) : " << versionNeeded << endl;
	//cout << "General purpose bit flag :" << bitFlag << endl;
	cout << "Compression method :" << CompressionMethod << endl;
	cout << "File last modification time : " << LastmodifTime <<endl;
	cout << "File last modification date : " << LastmodifDate <<endl;
	//cout << "CRC-32 : " << this.CRC << endl ;
	//cout << "Compressed size : " << dec << CompressedSize << endl;
	cout << "Uncompressed size : " <<  UncompressedSize <<endl ;
	cout << "File name length (n) : "  << FileNameLength <<endl;
	cout << "Extra field length (m) : "  << ExtraLenght <<endl;
	//cout << "File comment length (k) : " << FileCommentLength << endl;
	cout << "Disk number where file starts : " << hex << DisknumberStart << endl;
	//cout << "Internal file attributes : " << InternalFile << endl;
	cout << "External file attributes : " << ExternalFile << endl;
	cout << "Relative offset of local file header : " << hex << Offset <<endl;
	cout << endl;
};
