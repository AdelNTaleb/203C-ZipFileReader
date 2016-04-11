//============================================================================
// Name        : ZIPFileReader.cpp
// Author      : Taleb
// Version     :
// Copyright   : Your copyright notice
// Description : C++ ZipFile Reader Master 203
//============================================================================

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "ZipFile.hpp"

using namespace std;

void afficherMenuZip(ZIPFILE zip){
	int menu;
	do
	{
		cout <<endl << endl;
		cout<<"1. Display for each file the full path inside the ZIP file, and the file size "<<endl;
		cout<<"2. Display everything (EOCD and CFDH)"<<endl;
		cout<<"3. Unzip in the local directory"<<endl;
		cout<<"0. Exit"<<endl<<endl;
		cout<<"Choice : ";
		cin>>menu;
		cout<<endl;

		switch(menu)
		{
		case 0 : break;
		case 1 : zip.tier1();
		break;
		case 2 : zip.print();
		break;
		case 3: zip.extract();
		break;
		default: cerr<< "Try again." << endl;
		break;
		}

	}while (menu!=0);
}

void afficherMenu(){
	string path;
	do{
		cout<<endl<<" --------------------------- MENU ---------------------------"<<endl<<endl;
		cout<<endl << "Master 203 - 2016 - C++ Class "<< endl << "J. Berthou & A. Taleb" << endl <<"Welcome on our ZIP File Reader"<<endl;
		cout <<"Please follow the instructions" <<endl << endl;
		cout<<"Do you want to open a ZipFile?"<<endl;
		cout<<"Please enter the path or type 'exit' to quit"<<endl;
		cin >> path ;

		if (path != "exit") {
				afficherMenuZip( ZIPFILE(path.c_str()) );
		} else break;

	} while (true);
}

int main(){

	afficherMenu();
}
