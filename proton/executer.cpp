#include "executer.hpp"
#include "file.hpp"
#include "stringtools.hpp"
#include "logger.hpp"
#include "random.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <cmath>

#define PI 3.14159265

using namespace proton;
using namespace std;
using Random = effolkronium::random_static;

//template <typename T>
//vector<vector<string>, vector<T>> variables;

void startExec(string ntline, string filePath);

struct point
{
	string name;
	int line;
	int endline;
	string file;
};

map<string, string> strVars;
map<string, int> intVars;
map<string, double> doubleVars;

vector<point> points;

int lastLineIndex = 1;

pair<double, double> getMathPartPairValue(string exp);
double getMathOneValue(string exp);

void initMemory()
{
	strVars.insert(pair<string, string>("end", "\r\n"));
	strVars.insert(pair<string, string>("back", "\b"));

	intVars.insert(pair<string, int>("null", 0));
}

void dumpMemory()
{
	strVars.clear();
	intVars.clear();
	doubleVars.clear();
}

bool varExists(string var)
{
	for (auto v : strVars)
	{
		if(v.first == var)
		{
			return true;
		}
	}

	for (auto v : intVars)
	{
		if (v.first == var)
		{
			return true;
		}
	}

	for (auto v : doubleVars)
	{
		if (v.first == var)
		{
			return true;
		}
	}

	return false;
}

string getVarType(string var) 
{
	for (auto v : strVars)
	{
		if (v.first == var)
		{
			return "string";
		}
	}

	for (auto v : intVars)
	{
		if (v.first == var)
		{
			return "int";
		}
	}

	for (auto v : doubleVars)
	{
		if (v.first == var)
		{
			return "double";
		}
	}

	return "";
}

string getStringVarValue(string var)
{
	for (auto v : strVars)
	{
		if (v.first == var)
		{
			return v.second;
		}
	}

	return "ERROR";
}

int getIntVarValue(string var)
{
	for (auto v : intVars)
	{
		if (v.first == var)
		{
			return v.second;
		}
	}

	return 0;
}

double getDoubleVarValue(string var)
{
	for (auto v : doubleVars)
	{
		if (v.first == var)
		{
			return v.second;
		}
	}

	return 0;
}

string getExpType(string exp)
{
	if (exp[0] == '"' && exp.back() == '"')
	{
		return "string";
	}

	stringstream convertor;

	double dbnumber;

	convertor << exp;
	convertor >> dbnumber;

	if (!convertor.fail())
	{
		return "double";
	}

	convertor.str("");

	int number;

	convertor << exp;
	convertor >> number;

	if (!convertor.fail())
	{
		return "int";
	}


	vector<string> parts = splitstr(exp, ' ');

	if(parts[0] == "math")
	{
		return "double";
	}

	if(parts[0] == "read")
	{
		return "string";
	}

	return "none";
}

int getExpIntVal(string exp)
{
	stringstream convertor;

	int number;

	convertor << exp;
	convertor >> number;

	if (!convertor.fail())
	{
		return number;
	}
}

double getExpDoubleVal(string exp)
{
	stringstream convertor;

	double dbnumber;

	convertor << exp;
	convertor >> dbnumber;

	if (!convertor.fail())
	{
		return dbnumber;
	}

	vector<string> parts = splitstr(exp, ' ');

	if(parts[0] == "math")
	{
		if(parts[1] == "sum")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			return vals.first + vals.second;
		}
		else if (parts[1] == "sub")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			return vals.first - vals.second;
		}
		else if (parts[1] == "mul")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			return vals.first * vals.second;
		}
		else if (parts[1] == "div")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			return vals.first / vals.second;
		}
		else if (parts[1] == "mod")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			return fmod(vals.first, vals.second);
		}
		else if (parts[1] == "pow")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			return pow(vals.first, vals.second);
		}
		else if (parts[1] == "cos")
		{
			double val = getMathOneValue(exp);

			return cos(val * PI / 180);
		}
		else if (parts[1] == "tan")
		{
			double val = getMathOneValue(exp);

			return tan(val * PI / 180);
		}
		else if (parts[1] == "sin")
		{
			double val = getMathOneValue(exp);

			return sin(val * PI / 180);
		}
		else if (parts[1] == "rand")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			double randvar = Random::get((int)vals.first, (int)vals.second);

			return randvar;
		}
		else if (parts[1] == "randf")
		{
			pair<double, double> vals = getMathPartPairValue(exp);

			double randvar = Random::get(vals.first, vals.second);

			return randvar;
		}
	}
}

double getMathOneValue(string exp) 
{
	//  0    1   2
	// math xxx abc

	vector<string> parts = splitstrcount(exp, ' ', 2);
	
	double val1 = 0;
	
	if (varExists(parts[2]))
	{
		string type = getVarType(parts[2]);
	
		if (type == "int")
		{
			val1 = getIntVarValue(parts[2]);
		}
		else if (type == "double")
		{
			val1 = getDoubleVarValue(parts[2]);
		}
	}
	else
	{
		val1 = getExpDoubleVal(parts[2]);
	}
	
	return val1;
}

pair<double, double> getMathPartPairValue(string exp)
{
	vector<string> parts = splitstr(exp, ' ');

	double val1;
	double val2;

	if (varExists(parts[2]))
	{
		string type = getVarType(parts[2]);

		if (type == "int")
		{
			val1 = getIntVarValue(parts[2]);
		}
		else if (type == "double")
		{
			val1 = getDoubleVarValue(parts[2]);
		}
	}
	else
	{
		val1 = getExpDoubleVal(parts[2]);
	}

	string part2 = splitstrcount(exp, ' ', 3)[3];

	if (varExists(part2))
	{
		string type = getVarType(part2);

		if (type == "int")
		{
			val2 = getIntVarValue(part2);
		}
		else if (type == "double")
		{
			val2 = getDoubleVarValue(part2);
		}
	}
	else
	{
		val2 = getExpDoubleVal(part2);
	}

	return pair<double, double>(val1, val2);
}


string getExpStringVal(string exp)
{
	if(exp == "read")
	{
		string tx;

		cin >> tx;

		return tx;
	}

	if (exp[0] == '"' && exp.back() == '"')
	{
		string returnstr = deleteAtIndex(deleteAtIndex(exp, exp.length() - 1), 0);

		return returnstr;
	}
}

void setIntVar(string var, int val)
{
	intVars[var] = val;
}

void setStringVar(string var, string val)
{
	strVars[var] = val;
}

void setDoubleVar(string var, double val)
{
	doubleVars[var] = val;
}

bool tryConvInt(string exp)
{
	stringstream convertor;

	int number;

	convertor << exp;
	convertor >> number;

	if (!convertor.fail())
	{
		return true;
	}

	return false;
}

int lineindex = 1;

bool initializingPoint = false;
bool inpoint = false;

point currentpoint;

bool skippoint = false;

string lastFile;

string currentfile;

int executeLine(string line)
{
	vector<string> parts = splitstr(line, ' ');
	vector<string> oneparts = splitstrcount(line, ' ', 1);

	if (initializingPoint)
	{
		if (parts[0] == "endpoint")
		{
			currentpoint.endline = lineindex;
			points.push_back(currentpoint);
			initializingPoint = false;
		}

		return 1;
	}

	if (inpoint)
	{
		if (parts[0] == "endpoint")
		{
			lineindex = lastLineIndex;// + 1;
			currentfile = lastFile;
			inpoint = false;

			//cout << "point bitti geri gönülüyor... " << lineindex << endl;
		}

		//return 1;
	}

	if (skippoint)
	{
		if (parts[0] == "endpoint")
		{
			skippoint = false;
		}

		return 1;
	}

	if (parts[0] == "assign")
	{
		vector<string> partsparts = splitstrcount(oneparts[1], ' ', 1);

		// assign a 7
		//   0    0 1

		string varname = partsparts[0];
		string exp = partsparts[1];
		
		if (varExists(varname))
		{
			string vartype = getVarType(varname);

			if (vartype == "string")
			{
				setStringVar(varname, getExpStringVal(exp));
			}
			else if (vartype == "int")
			{
				setIntVar(varname, getExpIntVal(exp));
			}
			else if (vartype == "double")
			{
				setDoubleVar(varname, getExpDoubleVal(exp));
			}

			return 1;
		}

		string typeofexp = getExpType(exp);

		if (typeofexp == "string")
		{
			string val = getExpStringVal(exp);

			strVars.insert(pair<string, string>(varname, val));
		}
		else if (typeofexp == "int")
		{
			int val = getExpIntVal(exp);

			intVars.insert(pair<string, int>(varname, val));
		}
		else if (typeofexp == "double")
		{
			double val = getExpDoubleVal(exp);

			doubleVars.insert(pair<string, double>(varname, val));
		}
	}
	else if (parts[0] == "write")
	{
		string exp = oneparts[1];

		if(varExists(exp))
		{
			string vartype = getVarType(exp);

			if (vartype == "string")
			{
				cout << getStringVarValue(exp);
			}
			else if (vartype == "int")
			{
				cout << getIntVarValue(exp);
			}
			else if (vartype == "double")
			{
				cout << getDoubleVarValue(exp);
			}

			return 1;
		}
		
		string typeofexp = getExpType(exp);

		if (typeofexp == "string")
		{
			string val = getExpStringVal(exp);

			cout << val;
		}
		else if (typeofexp == "int")
		{
			int val = getExpIntVal(exp);

			cout << val;
		}
		else if (typeofexp == "double")
		{
			double val = getExpDoubleVal(exp);

			cout << val;
		}
	}
	else if (parts[0] == "meminit")
	{
		initMemory();
	}
	else if(parts[0] == "memdump")
	{
		dumpMemory();
	}
	else if (parts[0] == "exit")
	{
		if(parts.size() == 1)
		{
			exit(0);
		}
		else
		{
			if(tryConvInt(parts[1]))
			{
				exit(getExpIntVal(parts[1]));
			}
			else
			{
				return -35;
			}
		}
	}
	else if (parts[0] == "convert")
	{
		string vartype = getVarType(parts[2]);

		if (vartype == "string")
		{
			string val = getStringVarValue(parts[2]);

			if (parts[1] == "int")
			{
				try
				{
					int vll = stoi(val);

					intVars.insert(pair<string, int>(parts[2], vll));
				}
				catch (const std::exception&)
				{
					return -5;
				}
			}
			else if (parts[1] == "double")
			{
				try
				{
					double vll = stod(val);

					doubleVars.insert(pair<string, double>(parts[2], vll));
				}
				catch (const std::exception&)
				{
					return -5;
				}
			}

			strVars.erase(parts[2]);
		}
		else if (vartype == "int")
		{
			int val = getIntVarValue(parts[2]);

			if (parts[1] == "string")
			{
				strVars.insert(pair<string, string>(parts[2], to_string(val)));
			}
			else if (parts[1] == "double")
			{
				doubleVars.insert(pair<string, double>(parts[2], val));
			}

			intVars.erase(parts[2]);
		}
		else if (vartype == "double")
		{
			double val = getDoubleVarValue(parts[2]);

			if (parts[1] == "string")
			{
				strVars.insert(pair<string, string>(parts[2], to_string(val)));
			}
			else if (parts[1] == "int")
			{
				return -5;
			}

			doubleVars.erase(parts[2]);
		}
	}
	else if (parts[0] == "go")
	{
		if (parts[1] == "line")
		{
			try
			{
				string exp = splitstrcount(line, ' ', 2)[2];

				int line = getExpIntVal(exp);

				lineindex = line - 1;
			}
			catch (const std::exception&)
			{
				return -5;
			}
		}
		else
		{
			for (point p : points)
			{
				//cout << p.name << endl;

				if (p.name == parts[1])
				{
					lastLineIndex = lineindex;
					lineindex = p.line;
					inpoint = true;

					lastFile = currentfile;

					currentfile = p.file;

					//cout << p.line << " lineli " << p.name << " pointine gidiliyor..." << endl;
					//cout << initializingPoint << skippoint << inpoint << endl;
				}
			}
		}
	}
	else if (parts[0] == "if")
	{
		vector<string> ifparts = splitstrcount(line, ' ', 4);

		if (varExists(ifparts[1]))
		{
			string vartype = getVarType(ifparts[1]);

			if (vartype == "string")
			{
				string val = getStringVarValue(ifparts[1]);
				string val2 = "ERROR";

				if (varExists(ifparts[3]))
				{
					string vartype = getVarType(ifparts[3]);
					
					if (vartype == "string")
					{
						val2 = getStringVarValue(ifparts[3]);
					}
				}
				else
				{
					if (getExpType(ifparts[3]) == "string")
					{
						val2 = getExpStringVal(ifparts[3]);
					}
				}

				string operatorstr = ifparts[2];

				if (operatorstr == "is")
				{
					if (val == val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "not")
				{
					if (val != val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "<")
				{
					if (val < val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == ">")
				{
					if (val > val2)
					{
						return executeLine(ifparts[4]);
					}
				}
			}
			else if (vartype == "double")
			{
				double val = getDoubleVarValue(ifparts[1]);
				double val2 = 0;

				if (varExists(ifparts[3]))
				{
					string vartype = getVarType(ifparts[3]);

					if (vartype == "double")
					{
						val2 = getDoubleVarValue(ifparts[3]);
					}
				}
				else
				{
					if (getExpType(ifparts[3]) == "double")
					{
						val2 = getExpDoubleVal(ifparts[3]);
					}
				}

				string operatorstr = ifparts[2];

				if (operatorstr == "is")
				{
					if (val == val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "not")
				{
					if (val != val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "<")
				{
					if (val < val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == ">")
				{
					if (val > val2)
					{
						return executeLine(ifparts[4]);
					}
				}
			}
			else if (vartype == "int")
			{
				int val = getIntVarValue(ifparts[1]);
				int val2 = 0;

				if (varExists(ifparts[3]))
				{
					string vartype = getVarType(ifparts[3]);

					if (vartype == "int")
					{
						val2 = getIntVarValue(ifparts[3]);
					}
				}
				else
				{
					if (getExpType(ifparts[3]) == "int")
					{
						val2 = getExpIntVal(ifparts[3]);
					}
				}

				string operatorstr = ifparts[2];

				if (operatorstr == "is")
				{
					if (val == val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "not")
				{
					if (val != val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "<")
				{
					if (val < val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == ">")
				{
					if (val > val2)
					{
						return executeLine(ifparts[4]);
					}
				}
			}
		}
		else
		{
			string exptype = getExpType(ifparts[1]);

			if (exptype == "string")
			{
				string val = getExpStringVal(ifparts[1]);
				string val2 = "ERROR";

				if (varExists(ifparts[3]))
				{
					string vartype = getVarType(ifparts[3]);

					if (vartype == "string")
					{
						val2 = getStringVarValue(ifparts[3]);
					}
				}
				else
				{
					if (getExpType(ifparts[3]) == "string")
					{
						val2 = getExpStringVal(ifparts[3]);
					}
				}

				string operatorstr = ifparts[2];

				if (operatorstr == "is")
				{
					if (val == val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "not")
				{
					if (val != val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "<")
				{
					if (val < val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == ">")
				{
					if (val > val2)
					{
						return executeLine(ifparts[4]);
					}
				}
			}
			else if (exptype == "double")
			{
				double val = getExpDoubleVal(ifparts[1]);
				double val2 = 0;

				if (varExists(ifparts[3]))
				{
					string vartype = getVarType(ifparts[3]);

					if (vartype == "double")
					{
						val2 = getDoubleVarValue(ifparts[3]);
					}
				}
				else
				{
					if (getExpType(ifparts[3]) == "double")
					{
						val2 = getExpDoubleVal(ifparts[3]);
					}
				}
				string operatorstr = ifparts[2];

				if (operatorstr == "is")
				{
					if (val == val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "not")
				{
					if (val != val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "<")
				{
					if (val < val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == ">")
				{
					if (val > val2)
					{
						return executeLine(ifparts[4]);
					}
				}
			}
			else if (exptype == "int")
			{
				int val = getExpIntVal(ifparts[1]);
				int val2 = 0;

				if (varExists(ifparts[3]))
				{
					string vartype = getVarType(ifparts[3]);

					if (vartype == "int")
					{
						val2 = getIntVarValue(ifparts[3]);
					}
				}
				else
				{
					if (getExpType(ifparts[3]) == "int")
					{
						val2 = getExpIntVal(ifparts[3]);
					}
				}

				string operatorstr = ifparts[2];

				if (operatorstr == "is")
				{
					if (val == val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "not")
				{
					if (val != val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == "<")
				{
					if (val < val2)
					{
						return executeLine(ifparts[4]);
					}
				}
				else if (operatorstr == ">")
				{
					if (val > val2)
					{
						return executeLine(ifparts[4]);
					}
				}
			}
		}
	}
	else if(parts[0] == "point")
	{
		for (point p : points)
		{
			if (p.name == parts[1])
			{
				skippoint = true;
				return 1;
			}
		}

		initializingPoint = true;
		currentpoint.name = parts[1];
		currentpoint.line = lineindex;
		currentpoint.file = currentfile;
	}
	else if(parts[0] == "seperator")
	{
		return 1;
	}
	else if (parts[0] == "endpoint")
	{
		if (inpoint)
		{
			return 1;
		}
	}
	else if (parts[0] == "eat")
	{
		string headerpath = getExpStringVal(parts[1]);

		file f;

		vector<string> headerlines = f.ReadAllLines(headerpath);

		int lastl = lineindex;

		lastFile = currentfile;

		for (lineindex = 1; lineindex <= headerlines.size(); lineindex++)
		{
			string ln = headerlines[lineindex - 1];

			currentfile = headerpath;
			startExec(ln, headerpath);
		}

		currentfile = lastFile;

		lineindex = lastl;

		/*for (point p : points)
		{
			cout << p.name << " " << p.file << " " << p.line << " " << p.endline << endl;
		}*/
	}
	else 
	{
		return -2;
	}

	return 1;
}

/*string replaceAllEscape(string npline)
{
	string line = npline;

	line = replacestr(line, "\\n", "\n");
	line = replacestr(line, "\\r", "\r");
	//line = replacestr(line, "\\b", "\b");

	return line;
}*/

void startExec(string ntline, string filePath)
{
	//currentfile = filePath;

	string line = trim(ntline);

	logger log;

	if (line[0] != '#' && line != "")
	{
		int code = executeLine(line);

		if (code != 1)
		{
			cout << endl;
			log.Error("at " + filePath + ":" + to_string(lineindex) + " Error Code: " + to_string(code));
			exit(-1);
		}
	}
}

void executer::executeProgram(string inputPath)
{
	srand(time(NULL));

	file f;

	currentfile = inputPath;
	
	vector<string> lines = f.ReadAllLines(inputPath);

	for (lineindex = 1; lineindex <= lines.size(); lineindex++)
	{
		vector<string> lines = f.ReadAllLines(currentfile);
		string ntline = lines[lineindex - 1];

		startExec(ntline, inputPath);

		//string line = replaceAllEscape(npline);
	}
}