#include "StringAnalysis.h"
#include <string>
#include <iomanip>

void MyPush(std::stack<std::string>& analysisStack, std::string string0)
{
	std::vector<std::string> charList;
	std::string ch;
	int len = string0.length();
	for (int i = 0; i < len; i++)
	{
		ch = string0.substr(i, 1);
		if (i + 1 < len && string0.substr(i+1, 1) =="'")
		{
			ch = string0.substr(i, 2);
			i++;
		}
		charList.push_back(ch);
	}
	for (int i = charList.size() - 1; i >= 0; i--)
	{
		analysisStack.push(charList[i]);
	}
}

std::string GetAnalysisByStack(const std::stack<std::string>& analysisStack)
{
	std::stack<std::string> tempAnalysisStack = analysisStack;
	std::vector<std::string> charList;
	std::string string0;
	int size = tempAnalysisStack.size();
	for (int i = 0; i < size; i++)
	{
		charList.push_back(tempAnalysisStack.top());
		tempAnalysisStack.pop();
	}
	for (int i = charList.size() - 1; i >= 0; i--)
	{
		string0 += charList[i];
	}
	return string0;
	
}

std::string GetStringByStack(const std::stack<std::string>& stringStack)
{
	std::stack<std::string> tempStringStack = stringStack;
	std::string string0;
	int size = tempStringStack.size();
	for (int i = 0; i < size; i++)
	{
		string0 += tempStringStack.top();
		tempStringStack.pop();
	}
	return string0;
}

void PrintStack(const std::stack<std::string>& analysisStack)
{
	std::stack<std::string> tempStack = analysisStack;
	while (tempStack.size() != 0)
	{
		std::string ch = tempStack.top();
		tempStack.pop();
		std::cout << ch << std::endl;
	}
}



void InitStringStack(std::stack<std::string>& stringStack, std::string string0)
{
	stringStack.push("#");
	MyPush(stringStack, string0);
}

void InitAnalysisStack(std::stack<std::string>& analysisStack, std::string startChar)
{
	analysisStack.push("#");
	analysisStack.push(startChar);
}

// 
std::string GetGrammar(std::string analysisTop, std::string stringTop, std::map<std::string, std::map<std::string, std::string>> analysisTable)
{
	return analysisTable[analysisTop][stringTop];
}


void PrintAllStep(const std::vector<std::vector<std::string>>& allStep, std::string string0)
{
	std::cout << "符号串 " << string0 << " 的分析过程" << std::endl;
	for (std::vector<std::string> oneStep : allStep)
	{
		std::cout << std::left << std::setw(6) << oneStep[0]
			<< std::left << std::setw(10) << oneStep[1]
			<< std::right << std::setw(10) << oneStep[2]	 << "     "
			<< std::left << std::setw(10) << oneStep[3]
			<< std::endl;

	}
}

std::string GetRight(std::string oneGrammar)
{
	std::string firstChar = oneGrammar.substr(0, 1);
	std::string right;
	if (oneGrammar.substr(1, 1) == "'")
	{
		firstChar = oneGrammar.substr(0, 2);
	}
	if (oneGrammar.substr(firstChar.length(), 3) == "::=")
	{
		right = oneGrammar.substr(firstChar.length() + 3);
		return right;
	}	 
	else if (oneGrammar.substr(firstChar.length(), 2) == "->")
	{
		 right = oneGrammar.substr(firstChar.length() + 2);
		 return right;
	}
	else
	{
		std::cout << "right 出错了" << std::endl;
		return "";
	}
	
}

std::vector<std::vector<std::string>> Func(std::stack<std::string>& analysisStack, std::stack<std::string>& stringStack, std::map<std::string, std::map<std::string, std::string>> analysisTable, int& step)
{
	std::string analysisTop;
	std::string stringTop;
	std::string oneGrammar;
	std::string right;

	bool sucess = true;

	std::vector<std::vector<std::string>> allStep;
	std::vector<std::string> oneStep;
	std::string  analysisStackList;
	std::string  stringStackList;

	while (!(analysisStack.top() == "#" && stringStack.top() == "#") || step >= 100)
	{
		step++;
		oneStep.clear();

		oneStep.push_back(std::to_string(step));
		analysisStackList = GetAnalysisByStack(analysisStack);
		stringStackList = GetStringByStack(stringStack);
		oneStep.push_back(analysisStackList);
		oneStep.push_back(stringStackList);
		analysisTop = analysisStack.top();
		stringTop = stringStack.top();
		if (analysisTop == stringTop)
		{
			oneStep.push_back("");
			allStep.push_back(oneStep);
			analysisStack.pop();
			stringStack.pop();
			continue;
		}
		oneGrammar = GetGrammar(analysisTop, stringTop, analysisTable);
		
		oneStep.push_back(oneGrammar);
		allStep.push_back(oneStep);
		if (oneGrammar == "")
		{
			sucess = false;
			break;
		}
		right = GetRight(oneGrammar);
		analysisStack.pop();
		if (right != "$")
		{
			MyPush(analysisStack, right);
		}
	}

	std::vector<std::string> successStep = { std::to_string(++step), "#", "#", "SUCCESS" };
	std::vector<std::string> failStep = { std::to_string(++step), "?", "?", "FAIL" };

	allStep.push_back(sucess ? successStep:failStep);
	//std::cout << "Success" << std::endl;
	return 	allStep;

	
}

std::vector<std::vector<std::string>> StringAnalysis(std::string string0,
	std::string startChar, std::map<std::string, std::map<std::string, 
	std::string>> analysisTable)
{
	
	std::stack<std::string> analysisStack;
	std::stack<std::string> stringStack;


	InitAnalysisStack(analysisStack, startChar);
	InitStringStack(stringStack, string0);

	//PrintStack(stringStack);
	//std::cout << std::endl;
	//PrintStack(analysisStack);

	int step = 0;

	std::vector<std::vector<std::string>> allStep = Func(analysisStack, stringStack, analysisTable, step);

	return allStep;
}