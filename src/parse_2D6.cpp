#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
using namespace std;

typedef struct _fingerprint
{
	int index;
	int condition;
	int counter;
}Fingerprint;

int compareTwoFingerprint(const void *arg1, const void *arg2) //由大到小
{
	if ( (*(Fingerprint *)arg1).counter > (*(Fingerprint *)arg2).counter )
		return -1;
	else if ( (*(Fingerprint *)arg1).counter < (*(Fingerprint *)arg2).counter )
		return 1;
	else
		return 0;
}
//qsort((void *)(neighborsM), (size_t)(sizeNM), sizeof(Neighbor), compareTwoAtomType);

//---------------------------RuleSet class---------------------------//
class RuleSet{
public:
	void setValue( int index, string str_descriptor, string str_value, string str_condition );
	string GetDescriptor(int i){return descriptor[i];}
	double GetValue(int i){return value[i];}
	int GetCondition(int i){return condition[i];}
	string GetClass(){ return RuleClass;}
	int GetNumberOfRule(){ return numbersOfRule;}
	RuleSet( int numbersOfRule, string RuleClass );
	RuleSet();
	~RuleSet();
	void CopyRuleSet(const RuleSet& p);
private:
	int numbersOfRule;
	string RuleClass;
	string *descriptor;
	double *value;
	int *condition; // 0 means > ;  1 means <=

};

void RuleSet::setValue( int index, string str_descriptor, string str_value, string str_condition )
{
	if( index >= numbersOfRule )
		return;
	descriptor[index] = str_descriptor;
	value[index] = atof(str_value.c_str());
	if( str_condition.compare(">") == 0 )
		condition[index] = 0; // >
	else
		condition[index] = 1;  // <=
}

RuleSet::RuleSet( int numbersOfRule, string RuleClass )
{
	this->RuleClass = RuleClass;
	this->numbersOfRule = numbersOfRule;
	descriptor = new string[numbersOfRule];
	value = new double[numbersOfRule];
	condition = new int[numbersOfRule];
	for( int i = 0 ; i < numbersOfRule; i++ ){
		descriptor[i] = "";
		value[i] = 0.0f;
		condition[i] = -1;
	}
}
RuleSet::RuleSet(void)
:descriptor(NULL),value(NULL),condition(NULL)
{
}

void RuleSet::CopyRuleSet(const RuleSet& p) { // copy constructor
    if( descriptor != NULL)
		delete [] descriptor;
	if( value != NULL)
		delete [] value;
	if( condition != NULL )
		delete [] condition;
	RuleClass = p.RuleClass;
	numbersOfRule = p.numbersOfRule;
	descriptor = new string[p.numbersOfRule];
	value = new double[p.numbersOfRule];
	condition = new int[p.numbersOfRule];
	for( int i = 0 ; i < p.numbersOfRule; i++ ){
		descriptor[i] = p.descriptor[i];
		value[i] = p.value[i];
		condition[i] = p.condition[i];
	}
}


RuleSet::~RuleSet(void)
{
	if( descriptor != NULL)
		delete [] descriptor;
	if( value != NULL)
		delete [] value;
	if( condition != NULL )
		delete [] condition;
}

//---------------------------Model class---------------------------//
class Model{
public:
	Model(int numbersOfRuleSet);
	Model(void);
	void SetRuleSet(int index, const RuleSet& temp_ruleset);
	void CopyModel(const Model& tempModel);
	string GetDescriptor(int ruleSetNumberIndex, int ruleIndex);
	double GetCut(int ruleSetNumberIndex, int ruleIndex);
	int GetConditoin(int ruleSetNumberIndex, int ruleIndex);
	string GetClass(int ruleSetNumberIndex);
	int GetNumbersOfRuleSet(void);
	int GetNumbersOfRule(int rulesetNumberIndex);
	~Model();
private:
	int numbersOfRuleSet;
	RuleSet *m_ruleset;
};
Model::Model( void )
:numbersOfRuleSet(-1), m_ruleset(NULL)
{

}

Model::Model( int numbersOfRuleSet  )
{
	this->numbersOfRuleSet = numbersOfRuleSet;
	m_ruleset = new RuleSet[numbersOfRuleSet]();

}

void Model::SetRuleSet(int index, const RuleSet& temp_ruleset)
{
	m_ruleset[index].CopyRuleSet(temp_ruleset);
}

void Model::CopyModel(const Model& tempModel)
{
	if( m_ruleset != NULL)
		delete [] m_ruleset;
	this->numbersOfRuleSet = tempModel.numbersOfRuleSet;
	m_ruleset = new RuleSet[this->numbersOfRuleSet]();
	for( int i = 0 ; i < this->numbersOfRuleSet; i++)
		this->SetRuleSet(i,tempModel.m_ruleset[i]);
}

Model::~Model(void)
{
	if( m_ruleset != NULL)
		delete [] m_ruleset;
}

string Model::GetDescriptor(int ruleSetNumberIndex, int ruleIndex)
{
	return this->m_ruleset[ruleSetNumberIndex].GetDescriptor(ruleIndex);
}

double Model::GetCut(int ruleSetNumberIndex, int ruleIndex)
{
	return this->m_ruleset[ruleSetNumberIndex].GetValue(ruleIndex);
}

int Model::GetConditoin(int ruleSetNumberIndex, int ruleIndex)
{
	return this->m_ruleset[ruleSetNumberIndex].GetCondition(ruleIndex);
}

string Model::GetClass(int ruleSetNumberIndex)
{
	return this->m_ruleset[ruleSetNumberIndex].GetClass();
}

int Model::GetNumbersOfRuleSet(void)
{
	return this->numbersOfRuleSet;
}

int Model::GetNumbersOfRule(int ruleSetNumberIndex)
{
	return this->m_ruleset[ruleSetNumberIndex].GetNumberOfRule();
}





//-----------------------------------------------------------------//

int main(int argc, char* argv[])
{

	std::ifstream  data;
	std::ifstream  model;
	std::ofstream  output;
	std::ifstream  descriptorfile;

	if(argc==2){
		char str[200];

		strcpy(str,argv[1]);
		strcat(str,"2d6.f.cc2.predict");
		data.open(str);

		strcpy(str,argv[1]);
		strcat(str,"2d6.f.cc2.rules");
		model.open(str);

		strcpy(str,argv[1]);
		strcat(str,"2d6.f.cc2.statistics");
		output.open(str);

		strcpy(str,argv[1]);
		strcat(str,"2d6.f.cc2.cases");
		descriptorfile.open(str);
	}
	else{
		data.open("2d6.f.cc2.predict");
		model.open("2d6.f.cc2.rules");
		output.open("2d6.f.cc2.statistics");
		descriptorfile.open("2d6.f.cc2.cases");
	}



	int i,j,k, numberOfDescriptors = 881,numbersOfCompounds=0;
	std::string line;
	

	//-----read models-----//
	std::getline(model,line);std::getline(model,line);std::getline(model,line); //skip three rows
	
	Model *ourmodel = new Model[10]();
	//-----read each model
	for( i = 0 ; i < 10; i++ ){// for each model
		std::getline(model,line);
		std::stringstream  dataStream(line);
		string tempString;
		std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
		int numbersOfRuleSet = atoi(tempString.c_str()); // get numbers of ruleset
		Model *tempModel = new Model(numbersOfRuleSet);
		for( j = 0 ; j < numbersOfRuleSet ; j++ ){ // for each ruleset
			std::getline(model,line);
			dataStream.clear();
			dataStream.str(line);
			std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
			int numbersOfCondition = atoi(tempString.c_str()); // get numbers of conditions
			std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
			std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
			string ruleClass = tempString; // get rule class
			RuleSet *tempRuleSet = new RuleSet(numbersOfCondition, ruleClass);
			for( k = 0 ; k < numbersOfCondition ; k++ ){ // for each condition
				std::getline(model,line);
				dataStream.clear();
				dataStream.str(line);
				std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
				string descriptorName = tempString; // descriptor name
				std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
				string cutvalue = tempString; // cut 
				std::getline(dataStream,tempString,'"');std::getline(dataStream,tempString,'"');
				string condition = tempString; // condition
				tempRuleSet->setValue(k,descriptorName, cutvalue, condition);
			}
			tempModel->SetRuleSet(j,*tempRuleSet);
			delete tempRuleSet;
		}
		ourmodel[i].CopyModel(*tempModel);
		delete tempModel;
	}
	
	/*
	for( i = 0 ; i < 10; i++ ){// for each model
		for( j = 0 ; j < ourmodel[i].GetNumbersOfRuleSet() ; j++ ){ // for each ruleset
			for( k = 0 ; k < ourmodel[i].GetNumbersOfRule(j) ; k++ ){ // for each condition
				cout << ourmodel[i].GetDescriptor(j,k) << " " << ourmodel[i].GetCut(j,k) << " " << ourmodel[i].GetConditoin(j,k) << endl;
			}
		}
	}*/
	//-----read descriptor values-----//
	numbersOfCompounds = 0;
	while(std::getline(descriptorfile,line)){ // for each compound
		numbersOfCompounds++;
	}
	descriptorfile.clear();                 // clear fail and eof bits
	descriptorfile.seekg(0, std::ios::beg); // back to the start!
	
	int **descriptorvalue;
	descriptorvalue = new int *[numbersOfCompounds];
	for( i = 0 ; i < numbersOfCompounds; i++){
		descriptorvalue[i] = new int [numberOfDescriptors];
	}
	for( i = 0 ; i < numbersOfCompounds; i++){ // for each compound
		getline(descriptorfile,line);
		std::stringstream  lineStream(line);
        std::string  cell;
        for( j = 0 ; j < numberOfDescriptors; j++ ){
			std::getline(lineStream,cell,',');
			descriptorvalue[i][j] = atoi(cell.c_str());
		}
	}
	


    //-----read results-----//
	std::getline(data,line);std::getline(data,line);std::getline(data,line); //skip the first three rows
	int compound_index = 0;
	while(std::getline(data,line)) // for each compound
    {
        std::istringstream  lineStream(line);
		string cell,compoundName;
		lineStream>>compoundName; // compound name
		lineStream>>cell; // skip the second cell
		
		string predictedClass;
		lineStream>>predictedClass; //predicted class!

		lineStream>>cell; // skip the forth cell
		//get model rules
		Fingerprint fp[1762];
		for( i = 0 ; i < 1762; i++){
			fp[i].counter = 0;
			fp[i].index = -1;
			fp[i].condition = -1;
		}
		while(lineStream>>cell){
			std::stringstream  cellStream(cell);
			string str_modelNumber,str_ruleSetNumber;
			std::getline(cellStream,str_modelNumber,'/');
			std::getline(cellStream,str_ruleSetNumber,'/');
			int modelNumber = atoi(str_modelNumber.c_str());
			int ruleSetNumber = atoi(str_ruleSetNumber.c_str())-1;
			if( predictedClass.compare(ourmodel[modelNumber].GetClass(ruleSetNumber)) != 0 )
				continue;
			for( i = 0; i < ourmodel[modelNumber].GetNumbersOfRule(ruleSetNumber); i++){
				int descriptorNumber = atoi((ourmodel[modelNumber].GetDescriptor(ruleSetNumber,i)).substr(1).c_str());
				int condition = ourmodel[modelNumber].GetConditoin(ruleSetNumber,i);
				fp[descriptorNumber+condition].condition = condition;
				fp[descriptorNumber+condition].index = descriptorNumber;
				fp[descriptorNumber+condition].counter++;
			}
		}
		qsort((void *)(fp), (size_t)(1762), sizeof(Fingerprint), compareTwoFingerprint);
		//output statistics result
		if( predictedClass.compare("A") == 0 )
			output <<  compoundName <<",Inhibitor,";
		else
			output <<  compoundName << ",NonInhibitor,";
		
		int number = 0;
		for( i = 0 ; i < 5; i++){
			if( fp[i].counter > 0 ){
				number++;
			}
		}
		output << number << ",";
		int temp_number = 0;
		for( i = 0 ; i < 5; i++){
			if( fp[i].counter > 0 ){
				output << "F" << setw(3) << setfill('0') << fp[i].index << "," << fp[i].condition << "," << descriptorvalue[compound_index][fp[i].index];
				temp_number++;
			}
			if( temp_number < number )
				output << ",";
		}
		
		output << endl;
		compound_index++;
    }
	data.clear();
	data.close();
	model.clear();
	model.close();
	output.clear();
	output.close();
	descriptorfile.clear();
	descriptorfile.close();
	delete [] ourmodel;
	for( i = 0 ; i < numbersOfCompounds; i++){
		delete [] descriptorvalue[i];
	}
	delete [] descriptorvalue;
	return 1;
 }