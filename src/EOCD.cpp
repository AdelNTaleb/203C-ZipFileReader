/*
 * EOCD.cpp
 *
 *  Created on: 20 mars 2016
 *      Author: Taleb
 */


#include <iostream>
#include <string.h>
#include "EOCD.hpp"
#include "tools.hpp"

using namespace std;

EOCD::EOCD(char * memblock){

	memcpy(this,search_magic_header(memblock,'\x05','\x06'),sizeof(EOCD)) ;

}

EOCD::EOCD(){
	sign=0;
	disknum=0;
	diskCDstart=0;
	CDnumOnDisk=0;
	CDtotnum=0;
	CDsize=0;
	CDstart=0;
	CommentLenght=0;
}

void EOCD::print(){
	cout << " ===== End of central directory record ===== " << endl;
	cout << "Number of central directory records on this disk : " << dec << CDnumOnDisk << endl;
	cout << "Total number of central directory records : " << CDtotnum << endl;
	cout << "Size of central directory (bytes) : " << CDsize << endl;
	cout << "Offset of start of central directory, relative to start of archive : " << hex << CDstart << endl ;
	cout << endl;
}



