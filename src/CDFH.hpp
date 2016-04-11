/*
 * CDFH.hpp
 *
 *  Created on: 19 mars 2016
 *      Author: Taleb
 */


#ifndef CDFH_HPP_
#define CDFH_HPP_
#include "CDFH_temp.hpp"

struct CDFH {
	unsigned int sign;
	unsigned short versionBy;
	unsigned short versionNeeded;
	unsigned short bitFlag;
	unsigned short CompressionMethod;
	unsigned short LastmodifTime;
	unsigned short LastmodifDate;
	unsigned int CRC;
	unsigned int CompressedSize;
	unsigned int UncompressedSize;
	unsigned short FileNameLength;
	unsigned short ExtraLenght;
	unsigned short FileCommentLength;
	unsigned short DisknumberStart;
	unsigned short InternalFile;
	unsigned int ExternalFile;
	unsigned int Offset;
	char * Name;
	char* ExtraField;
	char* Comment;
	char * Data;

	int Size;

	CDFH(CDFH_temp);
	CDFH(char *);
	void tier1();
	void print_cdfh();
	int lenghtLFH();
	void setData(char* data);
	int extract(char *);
    char* ownInflate();
    struct tm getTime();
} ;

#endif /* CDFH_HPP_ */
