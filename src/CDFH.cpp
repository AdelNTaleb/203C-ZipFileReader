/*
 * CDFH.cpp
 *
 *  Created on: 19 mars 2016
 *      Author: Taleb
 */

#include "CDFH.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <utime.h>
#include <sys/types.h>
#include <time.h>
#include "tools.hpp"
#include "zlib/zlib.h"


using namespace std;

CDFH::CDFH (CDFH_temp tmp){
	memcpy(&sign,tmp.sign,sizeof(sign));
	memcpy(&versionBy,&tmp.versionBy,sizeof(versionBy));
	memcpy(&versionNeeded,&tmp.versionNeeded,sizeof(versionNeeded));
	memcpy(&bitFlag,&tmp.bitFlag,sizeof(bitFlag));
	memcpy(&CompressionMethod,&tmp.CompressionMethod,sizeof(CompressionMethod));
	memcpy(&LastmodifTime,&tmp.LastmodifTime,sizeof(LastmodifTime));
	memcpy(&LastmodifDate,&tmp.LastmodifDate,sizeof(LastmodifDate));
	memcpy(&CRC,tmp.CRC,sizeof(CRC));
	memcpy(&CompressedSize,tmp.CompressedSize,sizeof(CompressedSize));
	memcpy(&UncompressedSize,tmp.UncompressedSize,sizeof(UncompressedSize));
	memcpy(&FileNameLength,&tmp.FileNameLength,sizeof(FileNameLength));
	memcpy(&ExtraLenght,&tmp.ExtraLenght,sizeof(ExtraLenght));
	memcpy(&FileCommentLength,&tmp.FileCommentLength,sizeof(FileCommentLength));
	memcpy(&DisknumberStart,&tmp.DisknumberStart,sizeof(DisknumberStart));
	memcpy(&InternalFile,&tmp.InternalFile,sizeof(InternalFile));
	memcpy(&ExternalFile,tmp.ExternalFile,sizeof(ExternalFile));
	memcpy(&Offset,tmp.Offset,sizeof(Offset));
	Name=0;
	ExtraField=0;
	Comment=0;
	Size=sizeof(CDFH_temp);
	Data=0;
}

CDFH::CDFH(char * block) : CDFH ( CDFH_temp(block) ) {
	Name = new char [FileNameLength+1];
	ExtraField = new char [ExtraLenght];
	Comment = new char [FileCommentLength+1];
	Data = new char [CompressedSize+1];
	memcpy(Name,&block[46],FileNameLength);
	memcpy(ExtraField,&block[46+FileNameLength],ExtraLenght);
	memcpy(Comment,&block[46+ExtraLenght],FileCommentLength);
	Name[FileNameLength] = '\0';
	Comment[FileCommentLength]='\0';
	Size=Size+FileNameLength+ExtraLenght+FileCommentLength;
}

void CDFH::setData(char* data){
	memcpy(Data,data,CompressedSize);
	Data[CompressedSize]='\0';
}

void CDFH::print_cdfh(){

	//cout << "Central directory file header signature : " << hex << sign << endl;
	cout << "Version made by : " << versionBy << endl;
	cout << "Version needed to extract (minimum) : " << versionNeeded << endl;
	cout << "General purpose bit flag :" << bitFlag << endl;
	cout << "Compression method :" << CompressionMethod << endl;
	cout << "File last modification time : " << hex <<  LastmodifTime << " ==> ";
	cout << dec << setw(2) << (LastmodifTime >> 11) << ":";
	cout << setw(2) << ((LastmodifTime >> 5) & 0x3F) << ":";
	cout << setw(2) << (LastmodifTime & 0x1F) * 2 << endl;
	cout << "File last modification date : " << hex << LastmodifDate << " ==> ";
	cout << dec << (LastmodifDate & 0x1F) << ".";
	cout << ((LastmodifDate >> 5) & 0x0F) << ".";
	cout << ((LastmodifDate >> 9) & 0x7F) + 1980 << endl;
	cout << "CRC-32 : " << CRC << endl ;
	cout << "Compressed size : " << dec << CompressedSize << endl;
	cout << "Uncompressed size : "<< dec <<  UncompressedSize <<endl ;
	cout << "File name length (n) : "  << dec << FileNameLength <<endl;
	cout << "Extra field length (m) : "  << dec << ExtraLenght <<endl;
	cout << "File comment length (k) : " << FileCommentLength << endl;
	cout << "Disk number where file starts : " << hex << DisknumberStart << endl;
	cout << "Internal file attributes : " << InternalFile << endl;
	cout << "External file attributes : " << ExternalFile << endl;
	cout << "Relative offset of local file header : " << hex << Offset <<endl;
	cout << "File name : "; printf("%s\n",Name);
	cout << "Size of Cdfh : " << dec << Size << endl;
	//printf("%s",Data);

};

void CDFH::tier1(){
	cout << "Path : /"; printf("%s ",Name);
	cout << " -- : "<< dec <<  UncompressedSize << " Octet" <<endl ;
}

int CDFH::lenghtLFH(){
	return 34+FileNameLength+ExtraLenght;
}

struct tm CDFH::getTime(){
	struct tm filetime;
	filetime.tm_year=(LastmodifDate >> 9)+80;
	filetime.tm_mon=((LastmodifDate >> 5) & 0x0F)-1;
	filetime.tm_mday=LastmodifDate & 0x1F;
	filetime.tm_hour=LastmodifTime >> 11;
	filetime.tm_min= (LastmodifTime >> 5) & 0x3F;
	filetime.tm_sec= (LastmodifTime & 0x1F) * 2 ;
	return filetime;
}

int CDFH::extract(char * path){
	char * name = strrchr(path,'/');
	ofstream fichier;
	struct utimbuf new_times;
	struct tm filetime = getTime();
	new_times.modtime =  mktime(&filetime);
	new_times.actime = mktime(&filetime);
	if (name != 0){
		 path = name+1;
	}
	fichier.open(path, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

	if(fichier)  // si l'ouverture a réussi
	{
        if (CompressionMethod==8) {
            cout<< "Compressed FILE : DEFLATE" << endl;
        	fichier.write(ownInflate(),UncompressedSize);

        } else	fichier.write(Data,UncompressedSize);
        fichier.close();  // on referme le fichier
        utime(path,&new_times);
        return true;
	}
	else  // sinon
		cerr << "Error when opening file" << endl;
	return false;
}


char * CDFH::ownInflate(){
    z_stream infstream;
    char * uncompress = new char [UncompressedSize+1] ;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    // setup "b" as the input and "c" as the compressed output
    infstream.avail_in = (uInt)CompressedSize; // size of input
    infstream.next_in = (Bytef *)Data; // input char array
    infstream.avail_out = (uInt)UncompressedSize; // size of output
    infstream.next_out = (Bytef *)uncompress; // output char array
    // the actual DE-compression work.
    inflateInit2(&infstream, -15);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);
    return uncompress;
};
