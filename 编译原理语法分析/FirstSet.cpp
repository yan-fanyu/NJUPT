#include "FirstSet.h"
#include "EliminateLeftRecursion.h"
#include <map>
#include "Utils.h"



void MyFirst::PairSetToVector(std::vector<std::pair<std::string, std::string>>& v, std::set<std::pair<std::string, std::string>>& s)
{
	v.clear();
	for (std::pair<std::string, std::string> item : s)
	{
		v.push_back(item);
	}
}





// 获取句型的首字符
std::string MyFirst::GetFirstChar(std::string sentence)
{
	std::string firstChar = sentence.substr(0, 1);
	if (sentence.length() > 1 && sentence.substr(1, 1) == "'")
	{
		firstChar = sentence.substr(0, 2);
	}
	return firstChar;
}



// 根据开始符号确定文法
std::vector<std::string> MyFirst::GetGrammar(std::string firstChar, const std::vector<std::string>& grammarList)
{
	int grammarIndex;
	std::string grammar;
	std::vector<std::string> rightString;
	for (grammarIndex = 0; grammarIndex < grammarList.size(); grammarIndex++)
	{
		if (firstChar == grammarList[grammarIndex].substr(0, firstChar.length()))
		{
			break;
		}
	}

	std::vector<std::string> left_right = GetOneLeft_Right(grammarList[grammarIndex]);
	// 把最左边的消除，只剩产生式的右侧
	left_right.erase(left_right.begin());
	return left_right;

}

void MyFirst::GetRightString(const std::vector<std::string>& grammarList, std::vector<std::string>& rightStringList)
{
	std::set<std::string> rightStringSet;
	std::vector<std::vector<std::string>> left_rightList;
	GetLeft_RightList(grammarList, left_rightList);
	for (std::vector<std::string> item : left_rightList)
	{
		for (int i = 1; i < item.size(); i++)
		{
			rightStringSet.insert(item[i]);
		}
	}
	SetToVector(rightStringList, rightStringSet);
}

// 打印产生式右侧的符号串
void MyFirst::PrintRightString(const std::vector<std::string>& rightString)
{
	for (std::string item : rightString)
	{
		std::cout << item << " ";
	}
}

// 输入：句型和全部文法
// 返回：该句型的 FIRST 集
void MyFirst::GetOneFirst(std::string& sentence, std::vector<std::string>& First, const std::vector<std::string>& grammarList,
	const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal)
{
	std::string firstChar = GetFirstChar(sentence);
	if (IsTerminator(firstChar, terminator))
	{
		First.push_back(firstChar);
		return;
	}
	else
	{
		std::vector<std::string> rightList = GetGrammar(firstChar, grammarList);
		for (std::string item : rightList)
		{
			sentence = item + sentence.substr(firstChar.length(), sentence.length() - firstChar.length());
			GetOneFirst(sentence, First, grammarList, terminator, nonterminal);
		}
	}

}


void MyFirst::PrintOneFirst(std::string sentence, std::vector<std::string>& First)
{
	std::cout << sentence << ": {";
	for (auto ii : First)
	{
		std::cout << ii << ", ";
	}
	std::cout << "\b\b}" << std::endl;
}


void MyFirst::GetAllSentence(std::vector<std::string>& allSentenceList, const std::vector<std::string>& allLeftList,
	std::vector<std::string>& allRightList)
{
	for (std::string item : allLeftList)
	{
		allSentenceList.push_back(item);
	}
	for (std::string item : allRightList)
	{
		allSentenceList.push_back(item);
	}
}

void MyFirst::PrintAllSentence(const std::vector<std::string>& allSentence)
{
	for (std::string item : allSentence)
	{
		std::cout << item << "  " << std::endl;
	}
}


std::map<std::string, std::set<std::string>> MyFirst::GetFirstSet(const std::vector<std::string>& allSentenceList,
	const std::vector<std::string>& grammarList, const std::vector<std::string>& terminatorList,
	const std::vector<std::string>& nonterminalList)
{
	std::map<std::string, std::set<std::string>> First;
	std::vector<std::string> oneFirst;
	for (std::string sentence : allSentenceList)
	{
		std::string sentenceTemp = sentence;
		oneFirst.clear();
		GetOneFirst(sentence, oneFirst, grammarList, terminatorList, nonterminalList);
		for (std::string item : oneFirst)
		{
			First[sentenceTemp].insert(item);
		}
	}
	return First;
}

void MyFirst::PrintFirst22(std::map<std::string, std::set<std::string>>& First)
{
	std::cout << "FIRST 集如下" << std::endl;
	for (std::pair<std::string, std::set<std::string>> item : First)
	{
		std::cout << item.first << ": {";
		for (std::string ii : item.second)
		{
			std::cout << ii << ", ";
		}
		std::cout << "\b\b}" << std::endl;
	}
	std::cout << std::endl;
}


