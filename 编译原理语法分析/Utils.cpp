#pragma once
#include "Utils.h"

void GetOneLeft_Right2(const std::string oneGrammer, std::map<std::string, std::set<std::string>>& left_Right)
{
	std::string word = "";
	word = oneGrammer.substr(0, 1);

	int i = 4;

	if (oneGrammer.substr(1, 1) == "'")
	{
		i++;
		word += oneGrammer.substr(1, 1);
	}

	std::string key = word;

	word = "";

	for (; i < oneGrammer.length(); i++)
	{
		if (oneGrammer[i] == '|')
		{
			left_Right[key].insert(word);
			word = "";
			continue;
		}
		word += oneGrammer[i];
	}
	left_Right[key].insert(word);
}



void GetLeft_Right2(std::map<std::string, std::set<std::string>>& left_Right, const std::vector<std::string> grammarList)
{
	for (std::string oneGrammar : grammarList)
	{
		GetOneLeft_Right2(oneGrammar, left_Right);
	}
}

void PrintLeft_Right2(std::map<std::string, std::set<std::string>>& left_Right)
{
	for (auto item : left_Right)
	{
		std::cout << item.first << ": {";
		for (auto ii : item.second)
		{
			std::cout << ii << ", ";
		}
		std::cout << "\b\b}" << std::endl;
	}
}

// 判断是否是终结符号
bool IsTerminator(std::string ch, const std::vector<std::string>& terminator)
{
	for (std::string item : terminator)
	{
		if (ch == item)
		{
			return true;
		}
	}
	return false;
}

// 判断是否是非终结符号
bool IsNonterminal(std::string ch, const std::vector<std::string>& nonterminal)
{
	for (std::string item : nonterminal)
	{
		if (ch == item)
		{
			return true;
		}
	}
	return false;
}

void PrintTerminator(const std::vector<std::string>& terminatorList)
{
	std::cout << "终结符号集 = { ";
	for (std::string item : terminatorList)
	{
		std::cout << item << ", ";
	}
	std::cout << "\b\b";
	std::cout << " }" << std::endl;
}


void PrintNonterminal(const std::vector<std::string>& nonterminalList)
{
	std::cout << "非终结符号集 = { ";
	for (std::string item : nonterminalList)
	{
		std::cout << item << ", ";
	}
	std::cout << "\b\b";
	std::cout << " }" << std::endl << std::endl;
}

// 将去重的 set 集合 赋值给 vector 集合
void SetToVector(std::vector<std::string>& v, const std::set<std::string>& s)
{
	v.clear();
	for (std::string item : s)
	{
		v.push_back(item);
	}
}

// 求解终结符号集 和 非终结符号集
void GetTerminator_Nonterminal(const std::vector<std::string>& grammarList, std::vector<std::string>& terminatorList, std::vector<std::string>& nonterminalList)
{
	std::set<std::string> terminator;
	std::set<std::string> nonterminal;
	for (std::string oneGrammar : grammarList)
	{
		int len = oneGrammar.length();
		for (int i = 0; i < len; i++)
		{
			if (oneGrammar[i] == '|')
			{
				continue;
			}
			else if (i < len - 1 && oneGrammar[i] == '-' && oneGrammar[i + 1] == '>')
			{
				i++;
				continue;
			}
			else if (i < len - 2 && oneGrammar[i] == ':' && oneGrammar[i + 1] == ':' && oneGrammar[i + 2] == '=')
			{
				i += 2;
				continue;
			}
			else if (oneGrammar[i] >= 'A' && oneGrammar[i] <= 'Z')
			{
				if (i < len - 1 && oneGrammar[i + 1] == '\'')
				{
					nonterminal.insert(oneGrammar.substr(i, 1) + "'");
					i++;
				}
				else
				{
					nonterminal.insert(oneGrammar.substr(i, 1));
				}
			}
			else
			{
				terminator.insert(oneGrammar.substr(i, 1));
			}
		}
	}
	SetToVector(nonterminalList, nonterminal);
	SetToVector(terminatorList, terminator);
}


