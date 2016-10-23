/*
 * Display.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: mingda
 */

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
	ifstream infile("/home/lisa/vsfm/vsfm/bin/output/accident_45.nvm");
	ofstream outfile("/home/lisa/vsfm/vsfm/bin/output/full.txt");
	string str;
	int num;
	getline(infile,str);
	infile>>num;
	outfile<<num<<endl;
	for(int i=0;i<num;i++){
		getline(infile,str,'/');
		getline(infile,str,'\t');
		outfile<<str<<endl;
		getline(infile,str);
	}
	infile.close();
	outfile.close();

	int width = 4608; // x cols loc[0]
	int height = 3456; // y rows loc[1]
	infile.open("/home/lisa/vsfm/vsfm/bin/output/full.txt");
	string in_maskpath = "/home/lisa/vsfm/vsfm/bin/";
	string out_maskpath = "/home/lisa/vsfm/vsfm/bin/Accident/masks/";
	string filename;
	int n;
	infile>>n;
	Size st(width,height);
	Mat mask;
	Mat bigmask;
	char buffer[20];
	for(int i=0;i<n;i++){
		infile>>filename;
		size_t iPos = filename.find(".");
		filename = filename.substr(0,iPos)+"_mask.png"; //used to say ".m.jpg"
		cout<<filename;
		mask = imread(in_maskpath+filename,CV_8UC1);
		if (mask.rows == 0) {
            cout<<"HELLO\n";
            cout<<in_maskpath+filename;
            cout<<"BYE\n";
		}
		if(mask.rows>0){
			resize(mask,bigmask,st);
			sprintf(buffer,"%08d",i);
			filename = out_maskpath+buffer+".pgm";
			imwrite(filename,bigmask);
			cout << "Here";
		}
	}
}






