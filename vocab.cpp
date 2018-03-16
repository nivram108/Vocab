#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> 
using namespace std;

string fileName = "vocab.txt";

void listFile();
void selectFile();

void addVocab(vector<string> &vocab, vector<int> &weight);
void addVocabDirectly(vector<string> &vocab, vector<int> &weight, string v);
void answer(vector<string> &vocab,vector<int> &weight);
void recorrect(vector<string> &vocab);
void deleteVocab(vector<string> &vocab, vector<int> &weight);
void sortVocabMap(vector<string> &vocab, vector<int> &weight);

void printData(vector<string> &vocab, vector<int> &weight);
void printFullData(vector<string> &vocab, vector<int> &weight);
void printCmd();

void saveFile(vector<string> &vocab, vector<int> &weight);
bool stringCompareLessThan(string stringLeft, string stringRight);



int main(){
	
	listFile();
	selectFile();
	
	fstream ifs, ofs;//(fileName, fstream::in | fstream::out);
	ifs.open(fileName, fstream::in/* | fstream::out | fstream::app*/);
	
	if(!ifs)
	{
		cout << "Cant open" << endl;
		ifs.open(fileName, fstream::in/* | fstream::out | fstream::trunc*/);
		ifs << "\n";
		ifs.close();
	}
	string cmd;
	int w;
	vector<string> vocab;// = new vector<string>();
	vector<int> weight;// = new vector<int>();
	while(ifs >> cmd)
	{
		vocab.push_back(cmd);
		ifs >> w;
		weight.push_back(w);
	}
	ifs.close();
	
	printCmd();
	bool flag = false;
	while(cin >> cmd)
	{
		
		if (cmd == "add")
			addVocab(vocab, weight);
		
		else if(cmd == "answer")
			answer(vocab, weight);
		
		else if(cmd == "recorrect")
			recorrect(vocab);
		
		else if (cmd == "delete")
			deleteVocab(vocab, weight);
		
		else if(cmd == "ls")
			printFullData(vocab, weight);
		
		else if (cmd == "cls")
			cout << string(50, '\n');
		
		else if(cmd == "exit")
			break;
		
		else 
			addVocabDirectly(vocab, weight, cmd);
		
		printData(vocab, weight);		
		printCmd();
	}
	
	sortVocabMap(vocab, weight);
	saveFile(vocab, weight);
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
	
	dpdf = opendir("./files");
	if (dpdf != NULL){
	   while (epdf = readdir(dpdf)){
		  //printf("Filename: %s",epdf->d_name);
		  files.push_back(string(epdf->d_name));
		  //cout << epdf->d_name << endl;
	   }
	}
	else
		cout << "Can't open files dir "<<endl;
	
	cout << "--------" << endl;
	
	for(int i = (viewAll) ? 0 : files.size() - 7; i < files.size(); i++)
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
	cin >> fileName;
	cout << "file Name : " << fileName << endl;
	
	if ( fileName.find(".txt") == string::npos)
	{
		cout << "auto-corrected to file form" << endl;
		fileName = fileName + ".txt";
	}
	
	cout << "file Name : " << fileName << endl;
	fileName = "files/" + fileName;
	return;
}

void addVocab(vector<string> &vocab, vector<int> &weight)
{
	int w = 0;
	bool repeated = false;
	string v;
	
	cout << "Input vocab :";
	cin >> v;
	
	for( int i = 0; i < vocab.size(); i++)
	{
		if( v == vocab[i])
		{
			weight[i]++;
			w = weight[i];
			repeated = true;
			break;
		}
	}
	
	if ( repeated == false)
	{
		vocab.push_back(v);
		weight.push_back(1);
	}
	
	cout << string(50, '\n');
	
	sortVocabMap(vocab, weight);
	printData(vocab, weight);
	
	if( repeated == false)
	{
		cout << v << " is new" << endl;
	}
	else 
	{
		cout << v << " : " << w << endl;
	}
	
	saveFile(vocab, weight);
}

void addVocabDirectly(vector<string> &vocab, vector<int> &weight, string v)
{
	int w = 0;
	bool repeated = false;
	
	for( int i = 0; i < vocab.size(); i++)
	{
		if( v == vocab[i])
		{
			weight[i]++;
			w = weight[i];
			repeated = true;
			break;
		}
	}
	
	if ( repeated == false)
	{
		vocab.push_back(v);
		weight.push_back(1);
	}
	
	cout << string(50, '\n');
	
	sortVocabMap(vocab, weight);
	printData(vocab, weight);
	
	if( repeated == false)
	{
		cout << v << " is new" << endl;
	}
	else 
	{
		cout << v << " : " << w << endl;
	}
	
	saveFile(vocab, weight);
}

void answer(vector<string> &vocab, vector<int> &weight)
{
	string v;
	int w;
	cout << "Input vocab :";
	cin >> v;
	if ( v == "exit")
		return;
	for( int i = 0; i < vocab.size(); i++)
	{
		if( v == vocab[i])
		{
			weight[i] = 0;
			break;
		}
	}
	saveFile(vocab, weight);
	answer(vocab, weight);
}
void recorrect(vector<string> &vocab)
{
	string s0, s1;
	cout << "The wrong vocab : ";
	cin >> s0;
	for(int i = 0; i < vocab.size(); i++)
	{
		if(vocab[i] == s0)
		{
			cout << "Correct to :";
			cin >> s1;
			vocab[i] = s1;
		}
	}
}

void deleteVocab(vector<string> &vocab, vector<int> &weight)
{
	string s0, s1;
	cout << "The wrong vocab : ";
	cin >> s0;
	for(int i = 0; i < vocab.size(); i++)
	{
		if(vocab[i] == s0)
		{
			vocab.erase(vocab.begin() + i);
			weight.erase(weight.begin() + i);
		}
	}
	saveFile(vocab, weight);
}

void printCmd()
{
	cout << "add : add a vocab" << endl;
	cout << "answer : answer a vocab" << endl;
	cout << "recorrect : recorrect the wrong input vocab" << endl;
	cout << "delete : delete a vocab" << endl;
	cout << "ls : list full vocab" << endl;
	cout << "exit : exit program" << endl;
	cout << "cls : clean the screen" << endl;
	cout << "Input a command:";
}


void sortVocabMap(vector<string> &vocab, vector<int> &weight)
{
	for( int i = 0; i < weight.size(); i++)
	{
		for( int j = 0; j < weight.size() - 1; j++)
		{
			int tmpw;
			string tmpv;
			if (stringCompareLessThan(vocab[i], vocab[j]) == true)
			{
				tmpw = weight[i];
				weight[i] = weight[j];
				weight[j] = tmpw;
				
				tmpv = vocab[i];
				vocab[i] = vocab[j];
				vocab[j] = tmpv;
			}
			if(weight[i] < weight[j])
			{
				tmpw = weight[i];
				weight[i] = weight[j];
				weight[j] = tmpw;
				
				tmpv = vocab[i];
				vocab[i] = vocab[j];
				vocab[j] = tmpv;
			}
		}
	}
	
}

void printData(vector<string> &vocab, vector<int> &weight)
{
	cout << "--------------------------------" << endl;
		for( int i = 0; i < vocab.size(); i++)
		{
			if ( weight[i] == 0)
				continue;
			cout << "| "<< vocab[i] << " : " << weight[i] << endl;
		}
	cout << "--------------------------------" << endl << endl;
}

void printFullData(vector<string> &vocab, vector<int> &weight)
{
	sortVocabMap(vocab, weight);
	cout << "--------------------------------" << endl;
		for( int i = 0; i < vocab.size(); i++)
		{
			cout << "| "<< vocab[i] << " : " << weight[i] << endl;
		}
	cout << "--------------------------------" << endl << endl;
}

void saveFile(vector<string> &vocab, vector<int> &weight)
{
	ofstream ofs;
	ofs.open(fileName, fstream::out);
	for( int i = 0; i < vocab.size(); i++)
	{
		ofs << vocab[i] << " " << weight[i] << endl;
	}
	ofs.close();
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