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
	double cut;
}Fingerprint;

int compareTwoFingerprint(const void *arg1, const void *arg2) //パ
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

int main(int argc,char* argv[])
{
	int map[1444];
	map[0]=0;
	map[4]=1;
	map[5]=2;
	map[6]=3;
	map[7]=4;
	map[8]=5;
	map[9]=6;
	map[10]=7;
	map[11]=8;
	map[12]=9;
	map[13]=10;
	map[14]=11;
	map[15]=12;
	map[16]=13;
	map[17]=14;
	map[18]=15;
	map[19]=16;
	map[20]=17;
	map[21]=18;
	map[22]=19;
	map[23]=20;
	map[24]=21;
	map[25]=22;
	map[26]=23;
	map[27]=24;
	map[28]=25;
	map[29]=26;
	map[30]=27;
	map[31]=28;
	map[32]=29;
	map[33]=30;
	map[34]=31;
	map[35]=32;
	map[36]=33;
	map[37]=34;
	map[38]=35;
	map[39]=36;
	map[40]=37;
	map[41]=38;
	map[42]=39;
	map[43]=40;
	map[44]=41;
	map[45]=42;
	map[46]=43;
	map[47]=44;
	map[48]=45;
	map[49]=46;
	map[50]=47;
	map[51]=48;
	map[52]=49;
	map[53]=50;
	map[54]=51;
	map[55]=52;
	map[56]=53;
	map[57]=54;
	map[58]=55;
	map[59]=56;
	map[60]=57;
	map[61]=58;
	map[62]=59;
	map[63]=60;
	map[64]=61;
	map[65]=62;
	map[66]=63;
	map[67]=64;
	map[68]=65;
	map[69]=66;
	map[70]=67;
	map[71]=68;
	map[72]=69;
	map[73]=70;
	map[74]=71;
	map[75]=72;
	map[76]=73;
	map[77]=74;
	map[78]=75;
	map[79]=76;
	map[80]=77;
	map[81]=78;
	map[82]=79;
	map[83]=80;
	map[84]=81;
	map[85]=82;
	map[86]=83;
	map[87]=84;
	map[88]=85;
	map[89]=86;
	map[90]=87;
	map[91]=88;
	map[92]=89;
	map[93]=90;
	map[94]=91;
	map[95]=92;
	map[96]=93;
	map[97]=94;
	map[98]=95;
	map[99]=96;
	map[100]=97;
	map[101]=98;
	map[102]=99;
	map[103]=100;
	map[104]=101;
	map[105]=102;
	map[106]=103;
	map[107]=104;
	map[108]=105;
	map[109]=106;
	map[110]=107;
	map[111]=108;
	map[112]=109;
	map[113]=110;
	map[114]=111;
	map[115]=112;
	map[116]=113;
	map[117]=114;
	map[118]=115;
	map[119]=116;
	map[120]=117;
	map[121]=118;
	map[122]=119;
	map[123]=120;
	map[124]=121;
	map[125]=122;
	map[126]=123;
	map[127]=124;
	map[128]=125;
	map[129]=126;
	map[130]=127;
	map[131]=128;
	map[132]=129;
	map[133]=130;
	map[134]=131;
	map[135]=132;
	map[136]=133;
	map[137]=134;
	map[138]=135;
	map[139]=136;
	map[140]=137;
	map[141]=138;
	map[142]=139;
	map[143]=140;
	map[144]=141;
	map[145]=142;
	map[146]=143;
	map[147]=144;
	map[148]=145;
	map[149]=146;
	map[150]=147;
	map[151]=148;
	map[152]=149;
	map[153]=150;
	map[154]=151;
	map[155]=152;
	map[156]=153;
	map[157]=154;
	map[158]=155;
	map[159]=156;
	map[160]=157;
	map[161]=158;
	map[162]=159;
	map[163]=160;
	map[164]=161;
	map[165]=162;
	map[166]=163;
	map[167]=164;
	map[168]=165;
	map[169]=166;
	map[170]=167;
	map[171]=168;
	map[172]=169;
	map[173]=170;
	map[174]=171;
	map[175]=172;
	map[176]=173;
	map[177]=174;
	map[178]=175;
	map[179]=176;
	map[180]=177;
	map[181]=178;
	map[182]=179;
	map[183]=180;
	map[184]=181;
	map[185]=182;
	map[186]=183;
	map[187]=184;
	map[188]=185;
	map[189]=186;
	map[190]=187;
	map[191]=188;
	map[192]=189;
	map[193]=190;
	map[194]=191;
	map[195]=192;
	map[196]=193;
	map[197]=194;
	map[198]=195;
	map[199]=196;
	map[200]=197;
	map[201]=198;
	map[202]=199;
	map[203]=200;
	map[204]=201;
	map[205]=202;
	map[206]=203;
	map[207]=204;
	map[208]=205;
	map[209]=206;
	map[210]=207;
	map[211]=208;
	map[212]=209;
	map[213]=210;
	map[214]=211;
	map[215]=212;
	map[216]=213;
	map[217]=214;
	map[218]=215;
	map[219]=216;
	map[220]=217;
	map[221]=218;
	map[222]=219;
	map[223]=220;
	map[224]=221;
	map[225]=222;
	map[226]=223;
	map[227]=224;
	map[228]=225;
	map[229]=226;
	map[230]=227;
	map[231]=228;
	map[232]=229;
	map[233]=230;
	map[234]=231;
	map[235]=232;
	map[236]=233;
	map[237]=234;
	map[238]=235;
	map[239]=236;
	map[240]=237;
	map[241]=238;
	map[242]=239;
	map[243]=240;
	map[244]=241;
	map[245]=242;
	map[246]=243;
	map[247]=244;
	map[248]=245;
	map[249]=246;
	map[250]=247;
	map[251]=248;
	map[252]=249;
	map[253]=250;
	map[254]=251;
	map[255]=252;
	map[256]=253;
	map[257]=254;
	map[258]=255;
	map[259]=256;
	map[260]=257;
	map[261]=258;
	map[262]=259;
	map[263]=260;
	map[264]=261;
	map[265]=262;
	map[266]=263;
	map[267]=264;
	map[268]=265;
	map[269]=266;
	map[270]=267;
	map[271]=268;
	map[272]=269;
	map[273]=270;
	map[274]=271;
	map[275]=272;
	map[276]=273;
	map[277]=274;
	map[278]=275;
	map[279]=276;
	map[280]=277;
	map[281]=278;
	map[282]=279;
	map[283]=280;
	map[284]=281;
	map[285]=282;
	map[286]=283;
	map[287]=284;
	map[288]=285;
	map[289]=286;
	map[290]=287;
	map[291]=288;
	map[292]=289;
	map[293]=290;
	map[294]=291;
	map[295]=292;
	map[296]=293;
	map[297]=294;
	map[298]=295;
	map[299]=296;
	map[300]=297;
	map[301]=298;
	map[302]=299;
	map[303]=300;
	map[304]=301;
	map[305]=302;
	map[306]=303;
	map[307]=304;
	map[308]=305;
	map[309]=306;
	map[310]=307;
	map[311]=308;
	map[312]=309;
	map[313]=310;
	map[314]=311;
	map[315]=312;
	map[316]=313;
	map[317]=314;
	map[318]=315;
	map[319]=316;
	map[320]=317;
	map[321]=318;
	map[322]=319;
	map[323]=320;
	map[324]=321;
	map[325]=322;
	map[326]=323;
	map[327]=324;
	map[328]=325;
	map[329]=326;
	map[330]=327;
	map[331]=328;
	map[332]=329;
	map[333]=330;
	map[334]=331;
	map[335]=332;
	map[336]=333;
	map[337]=334;
	map[338]=335;
	map[339]=336;
	map[340]=337;
	map[341]=338;
	map[342]=339;
	map[343]=340;
	map[344]=341;
	map[345]=342;
	map[346]=343;
	map[347]=344;
	map[348]=345;
	map[349]=346;
	map[350]=347;
	map[351]=348;
	map[352]=349;
	map[353]=350;
	map[354]=351;
	map[355]=352;
	map[356]=353;
	map[357]=354;
	map[358]=355;
	map[359]=356;
	map[360]=357;
	map[361]=358;
	map[362]=359;
	map[363]=360;
	map[364]=361;
	map[365]=362;
	map[366]=363;
	map[367]=364;
	map[368]=365;
	map[369]=366;
	map[370]=367;
	map[371]=368;
	map[372]=369;
	map[373]=370;
	map[374]=371;
	map[375]=372;
	map[376]=373;
	map[377]=374;
	map[378]=375;
	map[379]=376;
	map[380]=377;
	map[381]=378;
	map[382]=379;
	map[383]=380;
	map[384]=381;
	map[385]=382;
	map[386]=383;
	map[387]=384;
	map[388]=385;
	map[389]=386;
	map[390]=387;
	map[391]=388;
	map[392]=389;
	map[393]=390;
	map[394]=391;
	map[395]=392;
	map[396]=393;
	map[397]=394;
	map[398]=395;
	map[399]=396;
	map[400]=397;
	map[401]=398;
	map[402]=399;
	map[403]=400;
	map[404]=401;
	map[405]=402;
	map[406]=403;
	map[407]=404;
	map[408]=405;
	map[409]=406;
	map[410]=407;
	map[411]=408;
	map[412]=409;
	map[413]=410;
	map[414]=411;
	map[415]=412;
	map[416]=413;
	map[417]=414;
	map[418]=415;
	map[419]=416;
	map[420]=417;
	map[421]=418;
	map[422]=419;
	map[423]=420;
	map[424]=421;
	map[425]=422;
	map[426]=423;
	map[427]=424;
	map[428]=425;
	map[429]=426;
	map[430]=427;
	map[431]=428;
	map[432]=429;
	map[433]=430;
	map[434]=431;
	map[435]=432;
	map[436]=433;
	map[437]=434;
	map[438]=435;
	map[439]=436;
	map[440]=437;
	map[441]=438;
	map[442]=439;
	map[443]=440;
	map[444]=441;
	map[445]=442;
	map[446]=443;
	map[447]=444;
	map[448]=445;
	map[449]=446;
	map[450]=447;
	map[451]=448;
	map[452]=449;
	map[453]=450;
	map[454]=451;
	map[455]=452;
	map[456]=453;
	map[457]=454;
	map[458]=455;
	map[465]=456;
	map[466]=457;
	map[467]=458;
	map[468]=459;
	map[469]=460;
	map[470]=461;
	map[471]=462;
	map[472]=463;
	map[473]=464;
	map[474]=465;
	map[475]=466;
	map[476]=467;
	map[477]=468;
	map[478]=469;
	map[479]=470;
	map[480]=471;
	map[481]=472;
	map[482]=473;
	map[483]=474;
	map[484]=475;
	map[485]=476;
	map[486]=477;
	map[487]=478;
	map[488]=479;
	map[489]=480;
	map[490]=481;
	map[491]=482;
	map[492]=483;
	map[493]=484;
	map[494]=485;
	map[495]=486;
	map[496]=487;
	map[497]=488;
	map[498]=489;
	map[499]=490;
	map[500]=491;
	map[501]=492;
	map[502]=493;
	map[503]=494;
	map[504]=495;
	map[505]=496;
	map[506]=497;
	map[507]=498;
	map[508]=499;
	map[509]=500;
	map[510]=501;
	map[511]=502;
	map[512]=503;
	map[513]=504;
	map[514]=505;
	map[515]=506;
	map[516]=507;
	map[517]=508;
	map[518]=509;
	map[519]=510;
	map[520]=511;
	map[521]=512;
	map[522]=513;
	map[523]=514;
	map[524]=515;
	map[525]=516;
	map[526]=517;
	map[527]=518;
	map[528]=519;
	map[529]=520;
	map[530]=521;
	map[531]=522;
	map[532]=523;
	map[533]=524;
	map[534]=525;
	map[535]=526;
	map[536]=527;
	map[537]=528;
	map[538]=529;
	map[539]=530;
	map[540]=531;
	map[541]=532;
	map[542]=533;
	map[543]=534;
	map[544]=535;
	map[545]=536;
	map[546]=537;
	map[547]=538;
	map[548]=539;
	map[549]=540;
	map[550]=541;
	map[551]=542;
	map[552]=543;
	map[553]=544;
	map[554]=545;
	map[555]=546;
	map[556]=547;
	map[557]=548;
	map[558]=549;
	map[559]=550;
	map[560]=551;
	map[561]=552;
	map[562]=553;
	map[563]=554;
	map[564]=555;
	map[565]=556;
	map[566]=557;
	map[567]=558;
	map[568]=559;
	map[569]=560;
	map[570]=561;
	map[571]=562;
	map[572]=563;
	map[573]=564;
	map[574]=565;
	map[575]=566;
	map[576]=567;
	map[577]=568;
	map[578]=569;
	map[579]=570;
	map[580]=571;
	map[637]=572;
	map[638]=573;
	map[639]=574;
	map[640]=575;
	map[641]=576;
	map[642]=577;
	map[643]=578;
	map[644]=579;
	map[645]=580;
	map[646]=581;
	map[647]=582;
	map[648]=583;
	map[649]=584;
	map[650]=585;
	map[651]=586;
	map[652]=587;
	map[653]=588;
	map[654]=589;
	map[655]=590;
	map[656]=591;
	map[657]=592;
	map[658]=593;
	map[659]=594;
	map[660]=595;
	map[661]=596;
	map[662]=597;
	map[663]=598;
	map[664]=599;
	map[665]=600;
	map[666]=601;
	map[667]=602;
	map[668]=603;
	map[669]=604;
	map[670]=605;
	map[671]=606;
	map[672]=607;
	map[673]=608;
	map[674]=609;
	map[675]=610;
	map[676]=611;
	map[677]=612;
	map[678]=613;
	map[679]=614;
	map[680]=615;
	map[681]=616;
	map[682]=617;
	map[683]=618;
	map[684]=619;
	map[685]=620;
	map[686]=621;
	map[687]=622;
	map[688]=623;
	map[689]=624;
	map[690]=625;
	map[691]=626;
	map[692]=627;
	map[693]=628;
	map[694]=629;
	map[695]=630;
	map[696]=631;
	map[697]=632;
	map[698]=633;
	map[699]=634;
	map[700]=635;
	map[701]=636;
	map[702]=637;
	map[703]=638;
	map[704]=639;
	map[705]=640;
	map[706]=641;
	map[707]=642;
	map[708]=643;
	map[709]=644;
	map[710]=645;
	map[711]=646;
	map[712]=647;
	map[713]=648;
	map[714]=649;
	map[715]=650;
	map[716]=651;
	map[717]=652;
	map[718]=653;
	map[719]=654;
	map[720]=655;
	map[721]=656;
	map[722]=657;
	map[723]=658;
	map[724]=659;
	map[725]=660;
	map[726]=661;
	map[727]=662;
	map[728]=663;
	map[729]=664;
	map[730]=665;
	map[731]=666;
	map[732]=667;
	map[733]=668;
	map[734]=669;
	map[735]=670;
	map[736]=671;
	map[737]=672;
	map[738]=673;
	map[739]=674;
	map[740]=675;
	map[741]=676;
	map[742]=677;
	map[743]=678;
	map[744]=679;
	map[745]=680;
	map[746]=681;
	map[747]=682;
	map[748]=683;
	map[749]=684;
	map[750]=685;
	map[751]=686;
	map[752]=687;
	map[753]=688;
	map[754]=689;
	map[755]=690;
	map[756]=691;
	map[757]=692;
	map[758]=693;
	map[759]=694;
	map[760]=695;
	map[761]=696;
	map[762]=697;
	map[763]=698;
	map[764]=699;
	map[765]=700;
	map[766]=701;
	map[767]=702;
	map[768]=703;
	map[769]=704;
	map[770]=705;
	map[771]=706;
	map[772]=707;
	map[773]=708;
	map[774]=709;
	map[775]=710;
	map[776]=711;
	map[777]=712;
	map[778]=713;
	map[779]=714;
	map[780]=715;
	map[781]=716;
	map[782]=717;
	map[783]=718;
	map[784]=719;
	map[785]=720;
	map[786]=721;
	map[787]=722;
	map[788]=723;
	map[789]=724;
	map[790]=725;
	map[791]=726;
	map[792]=727;
	map[793]=728;
	map[794]=729;
	map[795]=730;
	map[796]=731;
	map[797]=732;
	map[798]=733;
	map[799]=734;
	map[800]=735;
	map[801]=736;
	map[802]=737;
	map[803]=738;
	map[804]=739;
	map[805]=740;
	map[806]=741;
	map[807]=742;
	map[808]=743;
	map[809]=744;
	map[810]=745;
	map[811]=746;
	map[812]=747;
	map[813]=748;
	map[814]=749;
	map[815]=750;
	map[816]=751;
	map[817]=752;
	map[818]=753;
	map[819]=754;
	map[820]=755;
	map[821]=756;
	map[822]=757;
	map[823]=758;
	map[824]=759;
	map[825]=760;
	map[826]=761;
	map[827]=762;
	map[828]=763;
	map[829]=764;
	map[830]=765;
	map[831]=766;
	map[832]=767;
	map[833]=768;
	map[834]=769;
	map[835]=770;
	map[836]=771;
	map[837]=772;
	map[838]=773;
	map[839]=774;
	map[840]=775;
	map[841]=776;
	map[842]=777;
	map[843]=778;
	map[844]=779;
	map[845]=780;
	map[846]=781;
	map[847]=782;
	map[848]=783;
	map[849]=784;
	map[850]=785;
	map[851]=786;
	map[852]=787;
	map[853]=788;
	map[854]=789;
	map[855]=790;
	map[856]=791;
	map[857]=792;
	map[858]=793;
	map[859]=794;
	map[860]=795;
	map[861]=796;
	map[862]=797;
	map[863]=798;
	map[864]=799;
	map[865]=800;
	map[866]=801;
	map[867]=802;
	map[868]=803;
	map[869]=804;
	map[870]=805;
	map[871]=806;
	map[872]=807;
	map[873]=808;
	map[874]=809;
	map[875]=810;
	map[876]=811;
	map[877]=812;
	map[878]=813;
	map[879]=814;
	map[880]=815;
	map[881]=816;
	map[882]=817;
	map[883]=818;
	map[884]=819;
	map[885]=820;
	map[886]=821;
	map[887]=822;
	map[888]=823;
	map[889]=824;
	map[890]=825;
	map[891]=826;
	map[892]=827;
	map[893]=828;
	map[894]=829;
	map[895]=830;
	map[896]=831;
	map[897]=832;
	map[898]=833;
	map[899]=834;
	map[900]=835;
	map[901]=836;
	map[902]=837;
	map[903]=838;
	map[904]=839;
	map[905]=840;
	map[906]=841;
	map[907]=842;
	map[908]=843;
	map[909]=844;
	map[910]=845;
	map[911]=846;
	map[912]=847;
	map[913]=848;
	map[914]=849;
	map[915]=850;
	map[916]=851;
	map[917]=852;
	map[918]=853;
	map[919]=854;
	map[920]=855;
	map[921]=856;
	map[922]=857;
	map[923]=858;
	map[924]=859;
	map[925]=860;
	map[926]=861;
	map[927]=862;
	map[928]=863;
	map[929]=864;
	map[930]=865;
	map[931]=866;
	map[932]=867;
	map[933]=868;
	map[934]=869;
	map[935]=870;
	map[936]=871;
	map[937]=872;
	map[938]=873;
	map[939]=874;
	map[940]=875;
	map[941]=876;
	map[942]=877;
	map[943]=878;
	map[944]=879;
	map[945]=880;
	map[946]=881;
	map[947]=882;
	map[948]=883;
	map[949]=884;
	map[950]=885;
	map[951]=886;
	map[952]=887;
	map[953]=888;
	map[954]=889;
	map[955]=890;
	map[956]=891;
	map[957]=892;
	map[958]=893;
	map[959]=894;
	map[960]=895;
	map[961]=896;
	map[962]=897;
	map[963]=898;
	map[964]=899;
	map[965]=900;
	map[966]=901;
	map[967]=902;
	map[968]=903;
	map[969]=904;
	map[970]=905;
	map[971]=906;
	map[972]=907;
	map[973]=908;
	map[974]=909;
	map[975]=910;
	map[976]=911;
	map[977]=912;
	map[978]=913;
	map[979]=914;
	map[980]=915;
	map[981]=916;
	map[982]=917;
	map[983]=918;
	map[984]=919;
	map[985]=920;
	map[986]=921;
	map[987]=922;
	map[988]=923;
	map[989]=924;
	map[990]=925;
	map[991]=926;
	map[992]=927;
	map[993]=928;
	map[994]=929;
	map[995]=930;
	map[996]=931;
	map[997]=932;
	map[998]=933;
	map[999]=934;
	map[1000]=935;
	map[1001]=936;
	map[1002]=937;
	map[1003]=938;
	map[1004]=939;
	map[1005]=940;
	map[1006]=941;
	map[1007]=942;
	map[1008]=943;
	map[1009]=944;
	map[1010]=945;
	map[1011]=946;
	map[1012]=947;
	map[1013]=948;
	map[1014]=949;
	map[1015]=950;
	map[1016]=951;
	map[1017]=952;
	map[1018]=953;
	map[1019]=954;
	map[1020]=955;
	map[1021]=956;
	map[1022]=957;
	map[1023]=958;
	map[1024]=959;
	map[1025]=960;
	map[1026]=961;
	map[1027]=962;
	map[1028]=963;
	map[1029]=964;
	map[1030]=965;
	map[1031]=966;
	map[1032]=967;
	map[1033]=968;
	map[1034]=969;
	map[1035]=970;
	map[1036]=971;
	map[1037]=972;
	map[1038]=973;
	map[1039]=974;
	map[1040]=975;
	map[1041]=976;
	map[1042]=977;
	map[1043]=978;
	map[1044]=979;
	map[1045]=980;
	map[1046]=981;
	map[1047]=982;
	map[1048]=983;
	map[1049]=984;
	map[1050]=985;
	map[1051]=986;
	map[1052]=987;
	map[1053]=988;
	map[1054]=989;
	map[1055]=990;
	map[1056]=991;
	map[1057]=992;
	map[1058]=993;
	map[1059]=994;
	map[1060]=995;
	map[1061]=996;
	map[1062]=997;
	map[1063]=998;
	map[1064]=999;
	map[1065]=1000;
	map[1066]=1001;
	map[1067]=1002;
	map[1068]=1003;
	map[1069]=1004;
	map[1070]=1005;
	map[1071]=1006;
	map[1072]=1007;
	map[1073]=1008;
	map[1074]=1009;
	map[1075]=1010;
	map[1076]=1011;
	map[1077]=1012;
	map[1078]=1013;
	map[1079]=1014;
	map[1080]=1015;
	map[1081]=1016;
	map[1082]=1017;
	map[1083]=1018;
	map[1084]=1019;
	map[1085]=1020;
	map[1086]=1021;
	map[1087]=1022;
	map[1088]=1023;
	map[1089]=1024;
	map[1090]=1025;
	map[1091]=1026;
	map[1092]=1027;
	map[1093]=1028;
	map[1094]=1029;
	map[1095]=1030;
	map[1096]=1031;
	map[1097]=1032;
	map[1098]=1033;
	map[1099]=1034;
	map[1100]=1035;
	map[1101]=1036;
	map[1102]=1037;
	map[1103]=1038;
	map[1104]=1039;
	map[1105]=1040;
	map[1106]=1041;
	map[1107]=1042;
	map[1108]=1043;
	map[1109]=1044;
	map[1110]=1045;
	map[1111]=1046;
	map[1112]=1047;
	map[1113]=1048;
	map[1114]=1049;
	map[1115]=1050;
	map[1116]=1051;
	map[1117]=1052;
	map[1118]=1053;
	map[1119]=1054;
	map[1120]=1055;
	map[1121]=1056;
	map[1122]=1057;
	map[1123]=1058;
	map[1124]=1059;
	map[1125]=1060;
	map[1126]=1061;
	map[1127]=1062;
	map[1128]=1063;
	map[1129]=1064;
	map[1130]=1065;
	map[1131]=1066;
	map[1132]=1067;
	map[1133]=1068;
	map[1134]=1069;
	map[1135]=1070;
	map[1136]=1071;
	map[1137]=1072;
	map[1138]=1073;
	map[1139]=1074;
	map[1140]=1075;
	map[1141]=1076;
	map[1142]=1077;
	map[1143]=1078;
	map[1144]=1079;
	map[1145]=1080;
	map[1146]=1081;
	map[1147]=1082;
	map[1148]=1083;
	map[1149]=1084;
	map[1150]=1085;
	map[1151]=1086;
	map[1152]=1087;
	map[1153]=1088;
	map[1154]=1089;
	map[1155]=1090;
	map[1156]=1091;
	map[1157]=1092;
	map[1158]=1093;
	map[1159]=1094;
	map[1160]=1095;
	map[1161]=1096;
	map[1162]=1097;
	map[1163]=1098;
	map[1164]=1099;
	map[1165]=1100;
	map[1166]=1101;
	map[1167]=1102;
	map[1168]=1103;
	map[1169]=1104;
	map[1170]=1105;
	map[1171]=1106;
	map[1172]=1107;
	map[1173]=1108;
	map[1174]=1109;
	map[1175]=1110;
	map[1176]=1111;
	map[1177]=1112;
	map[1178]=1113;
	map[1179]=1114;
	map[1180]=1115;
	map[1181]=1116;
	map[1182]=1117;
	map[1183]=1118;
	map[1184]=1119;
	map[1185]=1120;
	map[1186]=1121;
	map[1187]=1122;
	map[1188]=1123;
	map[1189]=1124;
	map[1190]=1125;
	map[1191]=1126;
	map[1192]=1127;
	map[1193]=1128;
	map[1194]=1129;
	map[1195]=1130;
	map[1196]=1131;
	map[1197]=1132;
	map[1198]=1133;
	map[1199]=1134;
	map[1200]=1135;
	map[1201]=1136;
	map[1202]=1137;
	map[1203]=1138;
	map[1204]=1139;
	map[1205]=1140;
	map[1206]=1141;
	map[1207]=1142;
	map[1208]=1143;
	map[1209]=1144;
	map[1210]=1145;
	map[1211]=1146;
	map[1212]=1147;
	map[1213]=1148;
	map[1214]=1149;
	map[1215]=1150;
	map[1216]=1151;
	map[1217]=1152;
	map[1218]=1153;
	map[1219]=1154;
	map[1220]=1155;
	map[1221]=1156;
	map[1222]=1157;
	map[1223]=1158;
	map[1224]=1159;
	map[1225]=1160;
	map[1226]=1161;
	map[1227]=1162;
	map[1228]=1163;
	map[1229]=1164;
	map[1230]=1165;
	map[1231]=1166;
	map[1232]=1167;
	map[1233]=1168;
	map[1234]=1169;
	map[1235]=1170;
	map[1236]=1171;
	map[1237]=1172;
	map[1238]=1173;
	map[1239]=1174;
	map[1240]=1175;
	map[1241]=1176;
	map[1242]=1177;
	map[1243]=1178;
	map[1244]=1179;
	map[1245]=1180;
	map[1246]=1181;
	map[1247]=1182;
	map[1249]=1183;
	map[1250]=1184;
	map[1251]=1185;
	map[1252]=1186;
	map[1253]=1187;
	map[1254]=1188;
	map[1255]=1189;
	map[1256]=1190;
	map[1257]=1191;
	map[1258]=1192;
	map[1259]=1193;
	map[1260]=1194;
	map[1261]=1195;
	map[1262]=1196;
	map[1263]=1197;
	map[1264]=1198;
	map[1265]=1199;
	map[1266]=1200;
	map[1267]=1201;
	map[1268]=1202;
	map[1269]=1203;
	map[1270]=1204;
	map[1271]=1205;
	map[1272]=1206;
	map[1273]=1207;
	map[1274]=1208;
	map[1275]=1209;
	map[1276]=1210;
	map[1277]=1211;
	map[1278]=1212;
	map[1279]=1213;
	map[1280]=1214;
	map[1281]=1215;
	map[1282]=1216;
	map[1283]=1217;
	map[1284]=1218;
	map[1285]=1219;
	map[1286]=1220;
	map[1287]=1221;
	map[1288]=1222;
	map[1289]=1223;
	map[1290]=1224;
	map[1291]=1225;
	map[1292]=1226;
	map[1293]=1227;
	map[1294]=1228;
	map[1295]=1229;
	map[1296]=1230;
	map[1297]=1231;
	map[1298]=1232;
	map[1299]=1233;
	map[1300]=1234;
	map[1301]=1235;
	map[1302]=1236;
	map[1303]=1237;
	map[1304]=1238;
	map[1305]=1239;
	map[1306]=1240;
	map[1307]=1241;
	map[1308]=1242;
	map[1309]=1243;
	map[1310]=1244;
	map[1311]=1245;
	map[1312]=1246;
	map[1313]=1247;
	map[1314]=1248;
	map[1315]=1249;
	map[1316]=1250;
	map[1317]=1251;
	map[1318]=1252;
	map[1319]=1253;
	map[1320]=1254;
	map[1321]=1255;
	map[1322]=1256;
	map[1323]=1257;
	map[1324]=1258;
	map[1325]=1259;
	map[1326]=1260;
	map[1327]=1261;
	map[1328]=1262;
	map[1329]=1263;
	map[1330]=1264;
	map[1331]=1265;
	map[1332]=1266;
	map[1333]=1267;
	map[1334]=1268;
	map[1335]=1269;
	map[1336]=1270;
	map[1337]=1271;
	map[1338]=1272;
	map[1339]=1273;
	map[1340]=1274;
	map[1341]=1275;
	map[1342]=1276;
	map[1343]=1277;
	map[1344]=1278;
	map[1345]=1279;
	map[1346]=1280;
	map[1347]=1281;
	map[1348]=1282;
	map[1349]=1283;
	map[1350]=1284;
	map[1351]=1285;
	map[1352]=1286;
	map[1353]=1287;
	map[1354]=1288;
	map[1355]=1289;
	map[1356]=1290;
	map[1357]=1291;
	map[1358]=1292;
	map[1359]=1293;
	map[1360]=1294;
	map[1361]=1295;
	map[1362]=1296;
	map[1363]=1297;
	map[1364]=1298;
	map[1365]=1299;
	map[1366]=1300;
	map[1367]=1301;
	map[1368]=1302;
	map[1369]=1303;
	map[1370]=1304;
	map[1371]=1305;
	map[1372]=1306;
	map[1373]=1307;
	map[1374]=1308;
	map[1375]=1309;
	map[1376]=1310;
	map[1377]=1311;
	map[1378]=1312;
	map[1379]=1313;
	map[1380]=1314;
	map[1381]=1315;
	map[1382]=1316;
	map[1383]=1317;
	map[1384]=1318;
	map[1385]=1319;
	map[1386]=1320;
	map[1387]=1321;
	map[1388]=1322;
	map[1389]=1323;
	map[1390]=1324;
	map[1391]=1325;
	map[1392]=1326;
	map[1393]=1327;
	map[1394]=1328;
	map[1395]=1329;
	map[1396]=1330;
	map[1397]=1331;
	map[1398]=1332;
	map[1399]=1333;
	map[1400]=1334;
	map[1401]=1335;
	map[1402]=1336;
	map[1403]=1337;
	map[1404]=1338;
	map[1405]=1339;
	map[1406]=1340;
	map[1407]=1341;
	map[1408]=1342;
	map[1409]=1343;
	map[1410]=1344;
	map[1412]=1345;
	map[1413]=1346;
	map[1414]=1347;
	map[1415]=1348;
	map[1416]=1349;
	map[1417]=1350;
	map[1418]=1351;
	map[1419]=1352;
	map[1420]=1353;
	map[1421]=1354;
	map[1422]=1355;
	map[1423]=1356;
	map[1424]=1357;
	map[1425]=1358;
	map[1426]=1359;
	map[1427]=1360;
	map[1428]=1361;
	map[1429]=1362;
	map[1430]=1363;
	map[1431]=1364;
	map[1432]=1365;
	map[1433]=1366;
	map[1434]=1367;
	map[1435]=1368;
	map[1436]=1369;
	map[1437]=1370;
	map[1438]=1371;
	map[1439]=1372;
	map[1440]=1373;
	map[1441]=1374;
	map[1443]=1375;
	
    std::ifstream  data;
	std::ifstream  model;
	std::ofstream  output;
	std::ifstream  descriptorfile;

	if(argc==2){
		char str[200];

		strcpy(str,argv[1]);
		strcat(str,"1a2.p2.cc.predict");
		data.open(str);

		strcpy(str,argv[1]);
		strcat(str,"1a2.p2.cc.rules");
		model.open(str);

		strcpy(str,argv[1]);
		strcat(str,"1a2.p2.cc.statistics");
		output.open(str);

		strcpy(str,argv[1]);
		strcat(str,"1a2.p2.cc.cases");
		descriptorfile.open(str);
	}
	else{
		data.open("1a2.p2.cc.predict");
		model.open("1a2.p2.cc.rules");
		output.open("1a2.p2.cc.statistics");
		descriptorfile.open("1a2.p2.cc.cases");
	}
	int i,j,k, numberOfDescriptors = 1376,numbersOfCompounds=0;
	std::string line;
	

	//-----read models-----//
	std::getline(model,line);std::getline(model,line); //skip TWO rows   ぃ﹚铬碭︽璶CHECK
	
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
	
	double **descriptorvalue;
	descriptorvalue = new double *[numbersOfCompounds];
	for( i = 0 ; i < numbersOfCompounds; i++){
		descriptorvalue[i] = new double [numberOfDescriptors];
	}
	for( i = 0 ; i < numbersOfCompounds; i++){ // for each compound
		getline(descriptorfile,line);
		std::stringstream  lineStream(line);
        std::string  cell;
        for( j = 0 ; j < numberOfDescriptors; j++ ){
			std::getline(lineStream,cell,',');
			descriptorvalue[i][j] = atof(cell.c_str());
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
		Fingerprint fp[2752]; //癘眔эΘdescriptor 计ヘx2
		for( i = 0 ; i < 2752; i++){  //癘眔эΘdescriptor 计ヘx2
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
				int descriptorNumber = atoi((ourmodel[modelNumber].GetDescriptor(ruleSetNumber,i)).substr(2).c_str());  //substr(2)柑计惠璶笆
				int condition = ourmodel[modelNumber].GetConditoin(ruleSetNumber,i);
				double cutvalue = ourmodel[modelNumber].GetCut(ruleSetNumber,i);
				fp[descriptorNumber+condition].condition = condition;
				fp[descriptorNumber+condition].index = descriptorNumber;
				fp[descriptorNumber+condition].counter++;
				fp[descriptorNumber+condition].cut = cutvalue;
			}
		}
		qsort((void *)(fp), (size_t)(2752), sizeof(Fingerprint), compareTwoFingerprint);  //癘眔эΘdescriptor 计ヘx2
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
		for( i = 0 ; i < 5; i++){  //癘眔эformat
			if( fp[i].counter > 0 ){
				output << "P2" << setw(4) << setfill('0') << fp[i].index << "," << fp[i].condition << "," << fp[i].cut <<"," << descriptorvalue[compound_index][map[fp[i].index]];
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