#include "AnalysisTableConstructor.h"
#include <vector>
#include "FirstSet.h"
#include <iomanip>
#include "Utils.h"

std::string GetSartCharByCandidate(std::string candidate, std::map<std::string, std::set<std::string>> allRightMap)
{
	std::string startChar;
	for (std::pair<std::string, std::set<std::string>> oneGrammarRight : allRightMap)
	{
		startChar = oneGrammarRight.first;
		for (std::string right : oneGrammarRight.second)
		{
			if (right == candidate)
			{
				return startChar;
			}
		}
	}
	std::cout << "出错了" << std::endl;
	return "Error";
}

void PrintAnalysisTable(std::map<std::string, std::map<std::string, std::string>> analysisTable,
	const std::vector<std::string>& ROW,
	const std::vector<std::string>& COL)
{
	std::cout << "LL(1) 分析表如下" << std::endl;
	for (std::string i : ROW)
	{
		for (std::string j : COL)
		{
			std::cout << "(" << std::left << std::setw(2) << i << ", " << j << ") = " << std::left << std::setw(10) << analysisTable[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


// 由 FIRST 集构造分析表
void ConstructorAnalysisTableByFirst(
	std::map<std::string, std::map<std::string, std::string>>& analysisTable,
	std::map<std::string, std::set<std::string>> First,
	std::map<std::string, std::set<std::string>> Follow,
	std::map<std::string, std::set<std::string>> allRightMap,
	const std::vector<std::string>& nonterminalList)
{

	for (std::pair<std::string, std::set<std::string>> first : First)
	{
		std::string right = first.first;
		if (IsNonterminal(right, nonterminalList) || right == "$")
		{
			continue;
		}
		for (std::string item : first.second)
		{
			std::string startChar = GetSartCharByCandidate(right, allRightMap);
			std::string i = startChar;
			std::string j = item;
			std::string grammar = startChar + "->" + right;
			analysisTable[i][j] = grammar;
		}
	}
}


// 由 FOLLOW 集构造分析表
void ConstructorAnalysisTableByFollow(
	std::map<std::string, std::map<std::string, std::string>>& analysisTable,
	std::map<std::string, std::set<std::string>> Follow,
	std::map<std::string, std::set<std::string>> allRightMap,
	const std::vector<std::string>& nonterminalList)
{

	for (std::pair<std::string, std::set<std::string>> left_rightSet : allRightMap)
	{
		std::string left = left_rightSet.first;
		std::set<std::string> rightSet = left_rightSet.second;
		for (std::string right : rightSet)
		{
			if (right == "$")
			{
				std::string i = left;
				auto indexList = Follow[left];
				for (std::string j : indexList)
				{
					std::string grammar = left + "->$";
					analysisTable[i][j] = grammar;
				}
			}
		}
	}
}

void InitAnalysisTable(std::map<std::string, std::map<std::string, std::string>>& analysisTable,
	const std::vector<std::string>& ROW, const std::vector<std::string>& COL)
{
	for (std::string i : ROW)
	{
		for (std::string j : COL)
		{
			analysisTable[i][j] = "";
		}
	}
}



std::map<std::string, std::map<std::string, std::string>> AnalysisTableConstructor(
	std::map<std::string, std::set<std::string>> First,
	std::map<std::string, std::set<std::string>> Follow,
	const std::vector<std::string>& terminatorList,
	const std::vector<std::string>& nonterminalList,
	std::map<std::string, std::set<std::string>> allRightMap)
{
	std::map<std::string, std::map<std::string, std::string>>  analysisTable;

	std::vector<std::string> ROW = nonterminalList;
	std::vector<std::string> COL = terminatorList;
	for (int i = 0; i < COL.size(); i++)
	{
		if (COL[i] == "$")
		{
			COL[i] = "#";
			break;
		}
	}

	//PrintTerminator(COL);

	InitAnalysisTable(analysisTable, ROW, COL);

	ConstructorAnalysisTableByFirst(analysisTable, First, Follow, allRightMap, nonterminalList);
	ConstructorAnalysisTableByFollow(analysisTable, Follow, allRightMap, nonterminalList);

	PrintAnalysisTable(analysisTable, ROW, COL);

	return analysisTable;
}