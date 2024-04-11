#include "../headers/Parser.h"
#include "../headers/StringUtilities.h"

bool needNoOperands(string s)
{
	s = toUpperCase(s);
	return s.compare("RSUB") == 0 || s.compare("NOBASE") == 0 || s.compare("HIO") == 0 || s.compare("FIX") == 0 || s.compare("NORM") == 0 || s.compare("TIO") == 0 || s.compare("START") == 0 || s.compare("SIO") == 0 || s.compare("FLOAT") == 0 || s.compare("CSECT") == 0;
}

parsedLine parse(string line)
{
	unsigned int i;
	parsedLine pl;
	pl.lable = "";
	pl.opcode = "";
	pl.operand1 = "";
	pl.operand2 = "";

	string s[5] = {"", "", "", "", ""};
	i = 0;
	for (unsigned int j = 0; j < 5 && i < line.length(); j++)
	{
		for (; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++)
			;
		for (; i < line.length() && (line[i] != ' ' && line[i] != '\t'); i++)
			s[j] += line[i];

		if (j == 0)
		{
			string temp = toUpperCase(s[0]);
			if (temp.compare("EXTREF") == 0 || temp.compare("EXTDEF") == 0)
			{
				pl.opcode = s[0];
				for (int k = i; k < line.length(); k++)
					pl.operand1 += line[k];
				return pl;
			}
		}
		else if (j == 1)
		{
			string temp = toUpperCase(s[1]);
			if (temp.compare("EXTREF") == 0 || temp.compare("EXTDEF") == 0)
			{
				pl.lable = s[0];
				pl.opcode = s[1];
				for (int k = i; k < line.length(); k++)
					pl.operand1 += line[k];
				return pl;
			}
		}
	}
	for (; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++)
		;

	if (s[0] != "" && s[0][0] == '.')
	{
		for (i = 0; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++)
			;
		for (; i < line.length(); i++)
			pl.opcode += line[i];
		return pl;
	}

	if (i != line.length())
		throw new string("Too Many Arguments");

	if (s[0] == "")
		return pl;
	else if (s[1] == "")
		pl.opcode = s[0];
	else if (s[2] == "")
	{
		if (needNoOperands(s[1]))
		{
			pl.lable = s[0];
			pl.opcode = s[1];
		}
		else
		{
			pl.opcode = s[0];
			pl.operand1 = s[1];
		}
	}
	else if (s[3] == "")
	{
		if (s[1][s[1].length() - 1] == ',' || s[2][0] == ',')
		{
			pl.opcode = s[0];
			pl.operand1 = s[1] + s[2];
		}
		else
		{
			pl.lable = s[0];
			pl.opcode = s[1];
			pl.operand1 = s[2];
		}
	}
	else if (s[4] == "")
	{
		if (s[2].compare(",") == 0)
		{
			pl.opcode = s[0];
			pl.operand1 = s[1] + s[2] + s[3];
		}
		else
		{
			pl.lable = s[0];
			pl.opcode = s[1];
			pl.operand1 = s[2] + s[3];
		}
	}
	else
	{
		if (s[3].compare(",") != 0)
			throw new string("Too Many Arguments");

		pl.lable = s[0];
		pl.opcode = s[1];
		pl.operand1 = s[2] + s[3] + s[4];
	}

	s[0] = "";
	s[1] = "";
	for (i = 0; i < pl.operand1.length() && pl.operand1[i] != ','; i++)
		s[0] += pl.operand1[i];
	if (i == pl.operand1.length() - 1 && pl.operand1[i] == ',')
		s[1] = ",";
	else
		for (i++; i < pl.operand1.length(); i++)
			s[1] += pl.operand1[i];
	pl.operand1 = s[0];
	pl.operand2 = s[1];
	return pl;
}
