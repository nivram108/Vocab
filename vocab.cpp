#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> 
using namespace std;

string tmpFileName = "vocab.txt";
string tmpFilePath = "tmp";
string historyFilePath = "history";
string historyFileName = "";

vector<string> tmpVocab, historyVocab;
vector<int> tmpWeight, historyWeight;

void listFile();
void selectFile();

void addVocab();
void addVocabDirectly(string v);
void answer();
void recorrect();
void deleteVocab();
void sortVocabMap();

void printData();
void printFullData();
void printFullHistoryData();
void printCmd();

void saveFile();
bool stringCompareLessThan(string stringLeft, string stringRight);



int main(){
	
	listFile();
	selectFile();
	
	fstream iTmpFile, oTmpFile;//(tmpFileName, fstream::in | fstream::out);
	fstream iHistoryFile, oHistoryFile;
	
	iTmpFile.open(tmpFileName, fstream::in/* | fstream::out | fstream::app*/);
	iHistoryFile.open(historyFileName, fstream::in/* | fstream::out | fstream::app*/);

	string cmd;
	int w;
	cout << "LOAD" << endl;
	cout << "file name : " << historyFileName << endl;
	
	while(iTmpFile >> cmd)
	{
		tmpVocab.push_back(cmd);
		iTmpFile >> w;
		tmpWeight.push_back(w);
	}
	iTmpFile.close();
	
	while(iHistoryFile >> cmd)
	{
		historyVocab.push_back(cmd);
		iHistoryFile >> w;
		historyWeight.push_back(w);
	}
	iHistoryFile.close();
	
	printCmd();
	bool flag = false;
	while(cin >> cmd)
	{
		
		if (cmd == "add")
			addVocab();
		
		else if(cmd == "answer")
			answer();
		
		else if(cmd == "recorrect")
			recorrect();
		
		else if (cmd == "delete")
			deleteVocab();
		
		else if(cmd == "ls")
			printFullData();
		else if (cmd == "lsh")
			printFullHistoryData();
		
		else if (cmd == "cls")
			cout << string(50, '\n');
		
		else if(cmd == "exit")
			break;
		
		else 
			addVocabDirectly(cmd);
		
		printData();		
		printCmd();
	}
	
	sortVocabMap();
	saveFile();
	return 0;
}

void listFile()
{
	string cmd;
	vector<string> files;
	bool viewAll = false;
	DIR *dpdf;
	struct dirent *epdf;
	
	cout << "List Files:" << endl ;
	cout << "View only last 7 files ? Y/n" << endl;
	cin >> cmd;
	
	viewAll = (cmd[0] == 'Y' || cmd[0] == 'y') ? false : true;
	
	dpdf = opendir(string("./" + tmpFilePath).c_str());
	dpdf = opendir("./tmp");
	if (dpdf != NULL){
	   while (epdf = readdir(dpdf)){
		  //printf("tmpFileName: %s",epdf->d_name);
		  files.push_back(string(epdf->d_name));
		  //cout << epdf->d_name << endl;
	   }
	}
	else
		cout << "Can't open files dir "<<endl;
	
	cout << "--------" << endl;
	cout << "File Size:" << files.size() << endl;
	for(int i = (viewAll) ? 0 : (files.size() < 7) ? 0 : files.size() - 7; i < files.size(); i++)
	{
		cout << "\033[100m";
		if ( files.size() - i <= 3 )
			cout << "\033[93m" << files[i] << "   <<  " << files.size() - i << "\033[0m" <<endl;
		else if (files.size() - i == 5 || files.size() - i == 6)
			cout << "\033[1;93m" << files[i] << "   <<  " << files.size() - i << "\033[0m" <<endl;
		else
			cout << files[i] << "   <<  " << files.size() - i << "\033[0m"<<endl;
		
		cout << "\033[0m";
	}
	
	cout << "--------" << endl << endl;
	closedir(dpdf);
}

void selectFile()
{
	cout << "Select File:" << endl;
	cin >> tmpFileName;
	cout << "file Name : " << tmpFileName << endl;
	
	if ( tmpFileName.find(".txt") == string::npos)
	{
		cout << "auto-corrected to file form" << endl;
		tmpFileName = tmpFileName + ".txt";
	}
	
	historyFileName = tmpFileName;
	
	cout << "file Name : " << tmpFileName << endl;
	tmpFileName = tmpFilePath + "/" + tmpFileName;	
	historyFileName = historyFilePath + "/" + historyFileName;
	
	return;
}

void addVocab()
{
	int w = 0;
	bool repeated = false;
	string v;
	
	cout << "Input Vocab :";
	cin >> v;
	
	for( int i = 0; i < tmpVocab.size(); i++)
	{
		if( v == tmpVocab[i])
		{
			tmpWeight[i]++;
			w = tmpWeight[i];
			repeated = true;
			break;
		}
	}
	
	if ( repeated == false)
	{
		tmpVocab.push_back(v);
		tmpWeight.push_back(1);
	}
	
	for( int i = 0; i < historyVocab.size(); i++)
	{
		if( v == historyVocab[i])
		{
			historyWeight[i]++;
			w = historyWeight[i];
			repeated = true;
			break;
		}
	}
	
	if ( repeated == false)
	{
		historyVocab.push_back(v);
		historyWeight.push_back(1);
	}
	
	
	cout << string(50, '\n');
	
	sortVocabMap();
	printData();
	
	if( repeated == false)
	{
		cout << v << " is new" << endl;
	}
	else 
	{
		cout << v << " : " << w << endl;
	}
	
	saveFile();
}

void addVocabDirectly(string v)
{
	int w = 0;
	bool repeated = false;
	
	for( int i = 0; i < tmpVocab.size(); i++)
	{
		if( v == tmpVocab[i])
		{
			tmpWeight[i]++;
			w = tmpWeight[i];
			repeated = true;
			break;
		}
	}
	
	if ( repeated == false)
	{
		tmpVocab.push_back(v);
		tmpWeight.push_back(1);
	}
	
	for( int i = 0; i < historyVocab.size(); i++)
	{
		if( v == historyVocab[i])
		{
			historyWeight[i]++;
			w = historyWeight[i];
			repeated = true;
			break;
		}
	}
	
	if ( repeated == false)
	{
		historyVocab.push_back(v);
		historyWeight.push_back(1);
	}
	
	cout << string(50, '\n');
	
	sortVocabMap();
	printData();
	
	if( repeated == false)
	{
		cout << v << " is new" << endl;
	}
	else 
	{
		cout << v << " : " << w << endl;
	}
	
	saveFile();
}

void answer()
{
	string v;
	int w;
	cout << "Input Vocab :";
	cin >> v;
	if ( v == "exit")
		return;
	for( int i = 0; i < tmpVocab.size(); i++)
	{
		if( v == tmpVocab[i])
		{
			tmpWeight[i] = 0;
			break;
		}
	}
	saveFile();
	answer();
}

void recorrect()
{
	string s0, s1;
	cout << "The wrong Vocab : ";
	cin >> s0;
	for(int i = 0; i < tmpVocab.size(); i++)
	{
		if(tmpVocab[i] == s0)
		{
			cout << "Correct to :";
			cin >> s1;
			tmpVocab[i] = s1;
		}
	}
	
	for(int i = 0; i < historyVocab.size(); i++)
	{
		if(historyVocab[i] == s0)
		{
			historyVocab[i] = s1;
		}
	}
	
	saveFile();
}

void deleteVocab()
{
	string s0, s1;
	cout << "The wrong Vocab : ";
	cin >> s0;
	for(int i = 0; i < tmpVocab.size(); i++)
	{
		if(tmpVocab[i] == s0)
		{
			tmpVocab.erase(tmpVocab.begin() + i);
			tmpWeight.erase(tmpWeight.begin() + i);
		}
	}
	
	for(int i = 0; i < historyVocab.size(); i++)
	{
		if(historyVocab[i] == s0)
		{
			historyVocab.erase(historyVocab.begin() + i);
			historyWeight.erase(historyWeight.begin() + i);
		}
	}
	
	saveFile();
}

void printCmd()
{
	cout << "add : add a Vocab" << endl;
	cout << "answer : answer a Vocab" << endl;
	cout << "recorrect : recorrect the wrong input Vocab" << endl;
	cout << "delete : delete a Vocab" << endl;
	cout << "ls : list full Vocab" << endl;
	cout << "lsh : list history Vocab" << endl;
	cout << "exit : exit program" << endl;
	cout << "cls : clean the screen" << endl;
	cout << "Input a command:";
}


void sortVocabMap()
{
	for( int i = 0; i < tmpWeight.size(); i++)
	{
		for( int j = 0; j < tmpWeight.size() - 1; j++)
		{
			int tmpw;
			string tmpv;
			if (stringCompareLessThan(tmpVocab[i], tmpVocab[j]) == true)
			{
				tmpw = tmpWeight[i];
				tmpWeight[i] = tmpWeight[j];
				tmpWeight[j] = tmpw;
				
				tmpv = tmpVocab[i];
				tmpVocab[i] = tmpVocab[j];
				tmpVocab[j] = tmpv;
			}
			if(tmpWeight[i] < tmpWeight[j])
			{
				tmpw = tmpWeight[i];
				tmpWeight[i] = tmpWeight[j];
				tmpWeight[j] = tmpw;
				
				tmpv = tmpVocab[i];
				tmpVocab[i] = tmpVocab[j];
				tmpVocab[j] = tmpv;
			}
		}
	}
	
	for( int i = 0; i < historyWeight.size(); i++)
	{
		for( int j = 0; j < historyWeight.size() - 1; j++)
		{
			int historyw;
			string historyv;
			if (stringCompareLessThan(historyVocab[i], historyVocab[j]) == true)
			{
				historyw = historyWeight[i];
				historyWeight[i] = historyWeight[j];
				historyWeight[j] = historyw;
				
				historyv = historyVocab[i];
				historyVocab[i] = historyVocab[j];
				historyVocab[j] = historyv;
			}
			if(historyWeight[i] < historyWeight[j])
			{
				historyw = historyWeight[i];
				historyWeight[i] = historyWeight[j];
				historyWeight[j] = historyw;
				
				historyv = historyVocab[i];
				historyVocab[i] = historyVocab[j];
				historyVocab[j] = historyv;
			}
		}
	}
	
}

void printData()
{
	cout << "--------------------------------" << endl;
		for( int i = 0; i < tmpVocab.size(); i++)
		{
			if ( tmpWeight[i] == 0)
				continue;
			cout << "| "<< tmpVocab[i] << " : " << tmpWeight[i] << endl;
		}
	cout << "--------------------------------" << endl << endl;
}

void printFullData()
{
	sortVocabMap();
	cout << "--------------------------------" << endl;
		for( int i = 0; i < tmpVocab.size(); i++)
		{
			cout << "| "<< tmpVocab[i] << " : " << tmpWeight[i] << endl;
		}
	cout << "--------------------------------" << endl << endl;
}

void printFullHistoryData()
{
	sortVocabMap();
	cout << "--------------------------------" << endl;
		for( int i = 0; i < historyVocab.size(); i++)
		{
			cout << "| "<< historyVocab[i] << " : " << historyWeight[i] << endl;
		}
	cout << "--------------------------------" << endl << endl;
}

void saveFile()
{
	ofstream oTmpFile;
	oTmpFile.open(tmpFileName, fstream::out);
	for( int i = 0; i < tmpVocab.size(); i++)
	{
		oTmpFile << tmpVocab[i] << " " << tmpWeight[i] << endl;
	}
	oTmpFile.close();
	
	ofstream oHistoryFile;
	oHistoryFile.open(historyFileName, fstream::out);
	for( int i = 0; i < historyVocab.size(); i++)
	{
		oHistoryFile << historyVocab[i] << " " << historyWeight[i] << endl;
	}
	oHistoryFile.close();
}

bool stringCompareLessThan(string stringLeft, string stringRight)
{
	//cout << "compare " << stringLeft << " and " << stringRight;
	int length = (stringRight.size() < stringLeft.size()) ? stringRight.size() : stringLeft.size();
	for(int i = 0 ; i < length; i++)
	{
		if(int(stringLeft[i]) < int(stringRight[i]))
		{
			//cout << " less than" << (stringLeft[i]) << " > " << (stringRight[i]) << endl;
			return true;
		}
		else if(int(stringLeft[i]) > int(stringRight[i]))
		{
			//cout << " larger than" << (stringLeft[i]) << " > " << (stringRight[i]) << endl;
			return false;
		}
			
	}
	//cout << " larger than" << endl;
	return false;
}