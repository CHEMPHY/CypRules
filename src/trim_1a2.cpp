#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;


//-----------------------------------------------------------------//

int main(int argc,char* argv[])
{
	std::ifstream  data;
	std::ofstream  output;
	if(argc==3){
		data.open(argv[1]);
		output.open(argv[2]);
	}
	else{
    	data.open("1a2.p2.cc.cases2");
		output.open("1a2.p2.cc.cases");
	}
	int i,j,k, numberOfDescriptors = 1444,numbersOfCompounds=0;
	std::string line;
	std::getline(data,line); // skip the first row (title row)
	while(std::getline(data,line)) // for each compound
    {
		std::stringstream  lineStream(line);
        std::string        cell;
		std::getline(lineStream,cell,','); // compound name
		string compoundname(cell.c_str());
		for( i = 0 ; i < numberOfDescriptors; i++ ){
			std::getline(lineStream,cell,',');
			if(  (i>=1 && i<=3) || (i>=459 && i<=464) || (i>=581 && i<=636) || (i==1248) || (i==1411) || (i==1442) )
				continue;
			if( cell.compare("") == 0 || cell.compare("Infinity") == 0 )
				output << "0,";
			else
				output << cell.c_str() << ",";
		}
		output << "A," << compoundname.c_str() << endl;
	}

	data.clear();
	data.close();
	output.clear();
	output.close();
	return 1;
}
/*
int main(void)
{
	
    std::ifstream  data("1a2.p2.cc.cases2");
	
	std::ofstream  output("p2.txt");
	
	int i,j,k, numberOfDescriptors = 1444,numbersOfCompounds=0;
	std::string line;
	std::getline(data,line); // skip the first row (title row)
	std::stringstream  lineStream(line);
    std::string        cell;
	std::getline(lineStream,cell,','); // skip the first cell ("Name" column)
	for( i = 0 ; i < numberOfDescriptors; i++ ){
		std::getline(lineStream,cell,',');
		output <<  "'P2" << setw(4) << setfill('0') << i << "' => '" << cell.c_str() << "'," << endl; //'P20001' => 'Number of group RCO-N< or >N-X=X',
	}

	data.clear();
	data.close();
	output.clear();
	output.close();
	return 1;
}*/
/*
int main(void)
{
	
    std::ifstream  data("1a2.p2.cc.cases2");
	
	std::ofstream  output("p2_map.txt");
	
	int i,j,k, numberOfDescriptors = 1444,numbersOfCompounds=0;
	std::string line;
	std::getline(data,line); // skip the first row (title row)
	std::stringstream  lineStream(line);
    std::string        cell;
	std::getline(lineStream,cell,','); // skip the first cell ("Name" column)
	j = 0 ;
	for( i = 0 ; i < numberOfDescriptors; i++ ){
		std::getline(lineStream,cell,',');
		if( !( (i>=1 && i<=3) || (i>=459 && i<=464) || (i>=581 && i<=636) || (i==1248) || (i==1411) || (i==1442) )){
			output << "map[" << i << "]=" << j << ";" << endl;
			j++;
		}
	}

	data.clear();
	data.close();
	output.clear();
	output.close();
	return 1;
}*/