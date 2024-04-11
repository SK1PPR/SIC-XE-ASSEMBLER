#include "../headers/Pass1.h"
#include "../headers/IO.h"
#include "../headers/Pass2.h"

ifstream ipfile;
ofstream opfile;

bool started;
bool ended;

map<string, OpInfo *> *mainOpTab;

void openInitialStreams(string in, string out)
{
	// This function opens the file for reading and writing data
	ipfile.open(in.c_str());
	deleteFile(out.c_str());
	opfile.open(out.c_str(), std::ios::app);
}

bool isCSect(parsedLine pl)
{
	// This function checks if Control section is encountered or not.
	return (toUpperCase(pl.opcode).compare("CSECT") == 0) ? true : false;
}

parsedLine readAndParse()
{
	string before = readLine(&ipfile);
	string x = trim(before);
	return parse(x);
}

void finish()
{
	// This function is called in last to close all opened file streams.
	opfile.close();
	ipfile.close();
	deleteOpTab();
}

void finish2()
{
	opfile.close();
	ipfile.close();
	deleteOpTab2();
}
void finish3()
{
	opfile.close();
	ipfile.close();
	deleteOpTab3();
}

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		cout << "\aInvalid number of parameters" << endl;
		return 1;
	}

	printf("Assembler Started\n");
	openInitialStreams(argv[1], "../output/listFile.txt");
	printf("Input Files is being read form %s\n", argv[1]);
	bool successfullPass1 = true;
	bool successfullPass2 = true;
	writeHeader(&opfile);
	mainOpTab = getOpTab();
	vector<parsedLine> currCSect;
	vector<cSect> cSects;
	parsedLine pl;
	vector<string> names;
	int idx = 0;

	started = false;
	ended = false;

	while (!ipfile.eof())
	{
		pl = readAndParse();

		if (!isCSect(pl))
		{
			string upper = toUpperCase(pl.opcode);
			if (upper.compare("START") == 0)
			{
				names.push_back(pl.lable);
			}
			currCSect.push_back(pl);
			continue;
		}

		if (isCSect(pl))
		{
			names.push_back(pl.lable);
			cSect old = runPass1(currCSect, &started, &ended, &successfullPass1, names, idx);
			idx += 1;
			cSects.push_back(old);
			currCSect.clear();		 // Already Handled statements
			currCSect.push_back(pl); // Add 'cSect' to the new parsedLines
		}
	}

	cSects.push_back(runPass1(currCSect, &started, &ended, &successfullPass1, names, idx));
	currCSect.clear();

	// Write that text to a file
	for (unsigned int i = 0; i < cSects.size(); i++)
	{
		for (unsigned int j = 0; j < cSects[i].dataSect.size(); j++)
		{
			toWrite x = cSects[i].dataSect.at(j);
			if (x.type == -1)
			{
				writeError(&opfile, x.data);
			}
			else if (x.type == 0)
			{
				writeComment(&opfile, x.data);
			}
			else if (x.type == 1)
			{
				writeLine(&opfile, x.data);
			}
			else
			{
			}
		}
		writeBorder(&opfile);
		writeSymTab(&opfile, &cSects[i].symTab);
	}

	if (!ended)
	{
		// Check whether program is having a END Clause or not.
		writeError(&opfile, "The program has no END clause");
	}

	if (!successfullPass1)
	{
		finish();
		return 0;
	}

	runPass2(&opfile, &cSects, successfullPass2);
	if (!successfullPass2)
	{
		finish3();
		return 0;
	}
	printf("Done Assembling :)\n");
	finish2();
	return 0;
}
