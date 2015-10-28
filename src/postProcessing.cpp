#include <sstream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc,char *argv[]){
	ifstream input;
	ofstream output;
	if(argc==3){
		input.open(argv[1]);
		output.open(argv[2]);
	}
	else{
		input.open("out.txt");
		output.open("out2.txt");
	}
	string line;
	while( input>>line ){
		while( line.find("\"")!=string::npos){
			int pos=line.find("\"");
			line.erase(line.begin()+pos);
		}
		output<<line<<"\n";
	}
}