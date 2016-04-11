/*
 * tools.cpp
 *
 *  Created on: 20 mars 2016
 *      Author: Taleb
 */

#include "tools.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

char* search_magic_header(char* block,char c1= '\x01', char c2 = '\x02'){
	int compteur = 0;
	unsigned char caractereActuel = 0;
	unsigned char caractereActuel2 =0;
	unsigned char caractereActuel3 =0;
	unsigned char caractereActuel4 =0;
	do {
		caractereActuel=block[compteur];
		caractereActuel2=block[compteur + 1];
		caractereActuel3=block[compteur + 2];
		caractereActuel4=block[compteur + 3];
		compteur++;
	} while ( caractereActuel != '\x50'  or caractereActuel2 != '\x4b' or caractereActuel3 != c1 or caractereActuel4 != c2) ;
	compteur--;
	//cout << "magic number find pos : " << hex << compteur << endl;
	return &block[compteur];
}


void bin_to_hex(char* buffer){
	//int len =strlen(buffer);
	//cout << len <<endl;
	int j;
	unsigned char m;
	for(j = 0; j < 4; j++) {
		m = buffer[j];
		printf("%02X ", m);}
	cout << endl;
}

void bin_to_hex_short(char* buffer){
	//int len =strlen(buffer);
	//cout << len <<endl;
	int j;
	unsigned char m;
	for(j = 0; j < 2; j++) {
		m = buffer[j];
		printf("%02X ", m);}
	cout << endl;
}


void print_hexa(char* block){
	int compteur = 0;
	char szInput[3] = {0};
	unsigned char  caractereActuel = 0;
	do {
		caractereActuel=block[compteur];
		sprintf(szInput,"%02x",caractereActuel);
		if (compteur%4==3){
			cout << szInput << endl;
		}
		else { cout << szInput;
		}
		compteur++;
	} while ( caractereActuel != 0L  );
}

void print_hexa(char* block, int n){
	int compteur = 0;
	unsigned char  caractereActuel;
	for (compteur =0 ;compteur < n;compteur++ ) {
		caractereActuel = block[compteur];
		printf("%02x",caractereActuel);
	}

}


char* search_magic(char* block){
	int compteur = 0;
	unsigned char caractereActuel = 0;
	unsigned char caractereActuel2 =0;
	do {
		caractereActuel=block[compteur];
		caractereActuel2=block[compteur+1];
		compteur++;
	} while ( caractereActuel != '\x50' or caractereActuel2 != '\x4b' );
	compteur--;
	cout << "magic number find pos : " << hex << compteur << endl;
	return &block[compteur];
}

char* search_magic(char* block,char c1= '\x50', char c2 = '\x4b'){
	int compteur = 0;
	unsigned char caractereActuel = 0;
	unsigned char caractereActuel2 =0;
	do {
		caractereActuel=block[compteur];
		caractereActuel2=block[compteur + 1];
		compteur++;
	} while ( caractereActuel != c1 or caractereActuel2 != c2) ;
	compteur--;
	cout << "magic number find pos : " << hex << compteur << endl;
	return &block[compteur];
}
/*
char* search_magic_header(char* block,char c1= '\x01', char c2 = '\x02'){
	int compteur = 0;
	unsigned char caractereActuel = 0;
	unsigned char caractereActuel2 =0;
	unsigned char caractereActuel3 =0;
	unsigned char caractereActuel4 =0;
	do {
		caractereActuel=block[compteur];
		caractereActuel2=block[compteur + 1];
		caractereActuel3=block[compteur + 2];
		caractereActuel4=block[compteur + 3];
		compteur++;
	} while ( caractereActuel != '\x50'  or caractereActuel2 != '\x4b' or caractereActuel3 != c1 or caractereActuel4 != c2) ;
	compteur--;
	cout << "magic number find pos : " << hex << compteur << endl;
	return &block[compteur];
}
*/
char  search_last_magic(char* block, int size){
	return 'r';
}



