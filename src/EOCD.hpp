/*
 * EOCD.hpp
 *
 *  Created on: 20 mars 2016
 *      Author: Taleb
 */

#ifndef EOCD_HPP_
#define EOCD_HPP_

struct EOCD {
	unsigned int sign;
	unsigned short disknum;
	unsigned short diskCDstart;
	unsigned short CDnumOnDisk;
	unsigned short CDtotnum;
	unsigned int CDsize;
	unsigned int CDstart;
	unsigned short CommentLenght;


	EOCD();
	EOCD (char * block);
	void print();

} ;


#endif /* EOCD_HPP_ */
