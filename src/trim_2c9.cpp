#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>
using namespace std;


//-----------------------------------------------------------------//

int main(int argc,char* argv[])
{
	std::ifstream  data1;
	std::ifstream  data2;
	std::ofstream  output;
	if(argc==4){
		data1.open(argv[1]);
		data2.open(argv[2]);
		output.open(argv[3]);
	}
	else{
		data1.open("2c9.p2fp3.cc.cases2");
		data2.open("2c9.m2.cc.cases2");
		output.open("2c9.p2m2fp3.cc.cases");
	}
	int i,j,k, numberOfDescriptors2d = 1444, numberOfDescriptors3d= 431,numberOfDescriptorsf= 881, numberOfDescriptorsm2 = 777, numbersOfCompounds=0;
	std::string line1,line2;
	std::getline(data1,line1); // skip the first row (title row)
	std::getline(data2,line2); // skip the first row (title row)
	while(std::getline(data1,line1)) // for each compound
    {
		//P2
		std::stringstream  lineStream1(line1);
        std::string        cell1;
		std::getline(lineStream1,cell1,'\"'); // skip first '\"'
		std::getline(lineStream1,cell1,'\"'); // compound name
		string compoundname(cell1.c_str());
		std::getline(lineStream1,cell1,','); // skip first ','
		for( i = 0 ; i < numberOfDescriptors2d; i++ ){ //p2
			std::getline(lineStream1,cell1,',');
			if(  (i>=1 && i<=3) || (i>=459 && i<=464) || (i>=581 && i<=636) || (i==1248) || (i==1411) || (i==1442) )
				continue;
			if( cell1.compare("") == 0 || cell1.compare("Infinity") == 0 )
				output << "0,";
			else
				output << cell1.c_str() << ",";
		}
		//m2
		std::getline(data2,line2);
		std::stringstream  lineStream2(line2);
        std::string        cell2;
		std::getline(lineStream2,cell2,'\t'); // skip the first cell ("Name" column)
		for( i = 0 ; i < numberOfDescriptorsm2; i++ ){ //m2
			std::getline(lineStream2,cell2,'\t');
			output << cell2.c_str() << ",";
		}
		// f p3
		std::string out_p3;
		for( i = 0 ; i < numberOfDescriptors3d; i++ ){ //p3
			std::getline(lineStream1,cell1,',');
			if( cell1.compare("") == 0 || cell1.compare("Infinity") == 0 ){
				out_p3.append("0,");
			}else{
				out_p3.append(cell1.c_str());
			    out_p3.append(",");
			}
		}
		
		for( i = 0 ; i < numberOfDescriptorsf; i++ ){ //f
			std::getline(lineStream1,cell1,',');
			output << cell1.c_str() << ",";//f
		}
		output << out_p3.c_str();//p3

		
		std::replace( compoundname.begin(), compoundname.end(), ',', '*'); // replace all 'x' to 'y'
		std::replace( compoundname.begin(), compoundname.end(), ' ', '_');
		output << "A," << "\"" << compoundname.c_str() << "\"" << endl;
	}

	data1.clear();
	data1.close();
	data2.clear();
	data2.close();
	output.clear();
	output.close();
	return 1;
}
/*
int main(void)
{
	
    std::ifstream  data("2c19.p3.cc.cases2");
	
	std::ofstream  output("p3.txt");
	
	int i,j,k, numberOfDescriptors = 431,numbersOfCompounds=0;
	std::string line;
	std::getline(data,line);
	std::stringstream  lineStream(line);
    std::string        cell;
	for( i = 0 ; i < numberOfDescriptors; i++ ){
		std::getline(lineStream,cell,',');
		output <<  "'P3" << setw(3) << setfill('0') << i << "' => '" << cell.c_str() << "'," << endl; //'P20001' => 'Number of group RCO-N< or >N-X=X',
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