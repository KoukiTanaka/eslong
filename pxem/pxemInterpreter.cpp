#include <iostream>
#include <fstream>
#include <string>
#include "pxem.h"

using namespace std;


int print_error(char *hoge,char *hogehoge){
	cerr << hoge << hogehoge << endl;
	return -1;
}

int main(int argc,char **argv){
	if(argc>1){
		string fileName = argv[1];
		ifstream fR(fileName.c_str());
		if(!fR.is_open())
			return print_error("FileOpenError: ",(char*)fileName.c_str());
		string fileContents;
		char c;
		while(fR.get(c))
			fileContents += c;
		fR.close();
		string fileName2;
		if(fileName.rfind('/') == string::npos)
			if(fileName.rfind('\\') != string::npos)
				fileName2 = fileName.substr(1+(int)fileName.rfind('\\'));
			else
				fileName2 = fileName;
		else
			fileName2 = fileName.substr(1+(int)fileName.rfind('/'));
		Pxem pxemi((char*)fileName2.c_str(),(char*)fileContents.c_str());
		pxemi.run();
	}else
		return print_error("usage: pxemi pxem","FileName");
	return 0;
}
