

struct CDFH_temp {
	unsigned short sign[2];
	unsigned short versionBy;
	unsigned short versionNeeded;
	unsigned short bitFlag;
	unsigned short CompressionMethod;
	unsigned short LastmodifTime;
	unsigned short LastmodifDate;
	unsigned short CRC[2];
	unsigned short CompressedSize[2];
	unsigned short UncompressedSize[2];
	unsigned short FileNameLength;
	unsigned short ExtraLenght;
	unsigned short FileCommentLength;
	unsigned short DisknumberStart;
	unsigned short InternalFile;
	unsigned short ExternalFile[2];
	unsigned short Offset[2];
	
	CDFH_temp(char * );
	CDFH_temp();
	
	void print_cdfh();

};
