#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>
using namespace std;


//-----------------------------------------------------------------//

int main(int argc, char* argv[])
{
	std::ifstream  data;
	std::ofstream  output;
	if(argc==3){
		data.open(argv[1]);
		output.open(argv[2]);
	}
	else{
    	data.open("2d6.f.cc2.cases2");
		output.open("2d6.f.cc2.cases");
	}
	int i,j,k, numberOfDescriptors = 881,numbersOfCompounds=0;
	std::string line;
	std::getline(data,line);
	while(std::getline(data,line)) // for each compound
    {
		std::stringstream  lineStream(line);
        std::string        cell;
		std::getline(lineStream,cell,'\"'); // skip first '\"'
		std::getline(lineStream,cell,'\"'); // compound name
		string compoundname(cell.c_str());
		std::getline(lineStream,cell,','); // skip first ','
		for( i = 0 ; i < numberOfDescriptors; i++ ){
			std::getline(lineStream,cell,',');
			output << cell.c_str() << ",";
		}
		std::replace( compoundname.begin(), compoundname.end(), ',', '*'); // replace all 'x' to 'y'
		std::replace( compoundname.begin(), compoundname.end(), ' ', '_');
		output << "A," << "\"" << compoundname.c_str() << "\"" << endl;
	}

	data.clear();
	data.close();
	output.clear();
	output.close();
	return 1;
 }