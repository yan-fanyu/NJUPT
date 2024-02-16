#pragma once
#include "FollowSet.h"
#include "FirstSet.h"
#include "Utils.h"

// �����ѡʽ�����ķ���ʼ���� 
std::vector<std::string> MyFollow::GetCandidateStartChar(const std::string candidate, const std::vector<std::string>& nonterminalList, std::map<std::string, std::set<std::string>> left_Right)
{
	std::vector<std::string> startCharList;
	for (std::string key : nonterminalList)
	{
		for (std::string item : left_Right[key])
		{
			if (item == candidate)
			{
				startCharList.push_back(key);
				break;
			}
		}
	}
	return startCharList;
}








int MyFollow::GetNonterminalIndex(std::string oneNonterminal, const std::vector<std::string>& nonterminalList)
{
	for (int i = 0; i < nonterminalList.size(); i++)
	{
		if (oneNonterminal == nonterminalList.at(i));
		{
			return i;
		}
	}
	std::cout << "Ѱ�ҷ��ս���ų���" << std::endl;
	return -1;
}



// ��ȡһ������ʽȫ�����Ҳ��ĺ�ѡʽ
std::vector<std::string> MyFollow::GetOneGrammarAllRight(std::string oneGrammar)
{
	std::vector<std::string> right;
	std::string word = "";
	word = oneGrammar.substr(0, 1);

	int i = 4;

	if (oneGrammar.substr(1, 1) == "'")
	{
		i++;
		word += oneGrammar.substr(1, 1);
	}

	word = "";

	for (; i < oneGrammar.length(); i++)
	{
		if (oneGrammar[i] == '|')
		{
			right.push_back(word);
			word = "";
			continue;
		}
		word += oneGrammar[i];
	}
	right.push_back(word);
	return right;
}

// ��ȡȫ���ķ���ȫ���Ҳ�
std::vector<std::string> MyFollow::GetGrammarAllRight(std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& nonterminalList)
{
	std::vector<std::string> allRightList;
	std::set<std::string> allRightSet;
	for (std::string key : nonterminalList)
	{
		for (std::string item : left_Right[key])
			allRightSet.insert(item);
	}
	SetToVector(allRightList, allRightSet);
	return allRightList;
}

// ��ȡһ����ѡʽ��ȫ���ַ�
std::vector<std::string> MyFollow::GetOneCandidateAllCharacter(std::string str)
{
	std::vector<std::string> characterList;
	std::string ch;
	for (int i = 0; i < str.size(); i++)
	{
		ch = str.substr(i, 1);
		if (i < str.size() - 1 && str.substr(i + 1, 1) == "'")
		{
			ch += "'";
			i++;
		}
		characterList.push_back(ch);
	}
	return characterList;
}

// Ѱ��һ����ѡʽ�� B �� Beta
std::vector<std::pair<std::string, std::string>> MyFollow::FindAlphaBeta(std::string oneRight, const std::vector<std::string>& nonterminal, const std::vector<std::string>& allCharacter)
{
	std::vector<std::pair<std::string, std::string>> B_BetaList;
	int index = 0;
	int chNum = allCharacter.size();
	std::string beta;
	for (int i = 0; i < chNum; i++)
	{
		index += allCharacter.at(i).length();
		if (IsNonterminal(allCharacter.at(i), nonterminal))
		{
			std::string B = allCharacter.at(i);
			beta = oneRight.substr(index);
			beta = beta.size() == 0 ? "$" : beta;
			B_BetaList.push_back(make_pair(B, beta));
		}
	}
	return B_BetaList;
}

// Ѱ��ȫ����ѡʽ�� B �� Beta
std::vector<std::pair<std::string, std::string>> MyFollow::FindAllAlphaBeta(std::vector<std::string> allRight, const std::vector<std::string>& nonterminal)
{
	std::set<std::pair<std::string, std::string>> allB_BetaSet;
	std::vector<std::pair<std::string, std::string>> allB_BetaList;
	std::vector<std::string> allCharacter;
	for (std::string oneRight : allRight)
	{
		allCharacter = GetOneCandidateAllCharacter(oneRight);
		std::vector<std::pair<std::string, std::string>> T = FindAlphaBeta(oneRight, nonterminal, allCharacter);
		for (std::pair<std::string, std::string> item : T)
		{
			allB_BetaSet.insert(item);
		}
	}
	MyFirst myFirst;
	myFirst.PairSetToVector(allB_BetaList, allB_BetaSet);
	return allB_BetaList;
}



// ��� FOLLOW ���� ����һ
void MyFollow::Rule1(std::map<std::string, std::set<std::string>>& Follow, const std::vector<std::string>& grammarList)
{
	MyFirst myFirst;
	std::string startChar = myFirst.GetFirstChar(grammarList[0]);
	Follow[startChar].insert("#");
}

// ��� FOLLOW ���� �����
void MyFollow::Rule2(std::map<std::string, std::set<std::string>>& Follow, std::vector<std::pair<std::string, std::string>> allB_Beta, const std::vector<std::string>& grammarList,
	const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal)
{
	std::vector<std::string> First;
	for (std::pair<std::string, std::string> B_Beta : allB_Beta)
	{
		First.clear();
		std::string B = B_Beta.first;
		std::string beta = B_Beta.second;

		MyFirst myFirst;
		myFirst.GetOneFirst(beta, First, grammarList, terminator, nonterminal);
		for (std::string item : First)
		{
			if (item != "$")
			{
				Follow[B].insert(item);
			}
		}
	}
}

// beta �Ƿ��ܹ����Ƶ��� �շ���
void MyFollow::IsGeneralizedDerivation(std::string lastA, std::pair<std::string, std::string>& B_Beta, std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& terminator, bool& flag, std::set<std::string>& ASet)
{
	std::string beta = B_Beta.second;

	MyFirst myFirst;
	std::string firstCh = myFirst.GetFirstChar(beta);



	if (IsTerminator(firstCh, terminator))
	{
		if (firstCh == "$")
		{
			flag = true;
			ASet.insert(lastA);
		}
		return;

	}
	else
	{
		for (std::string right : left_Right[firstCh])
		{
			std::string newBeta = right + beta.substr(firstCh.size());
			B_Beta.second = newBeta;
			lastA = firstCh;
			IsGeneralizedDerivation(lastA, B_Beta, left_Right, terminator, flag, ASet);
		}
	}
}

// �������ݹ���ֹ����
bool MyFollow::IsRule3Over(std::map<std::string, std::set<std::string>>& Follow, std::map<std::string, std::set<std::string>>& Follow2, const std::vector<std::string>& nonterminal)
{
	for (std::string key : nonterminal)
	{
		if (Follow[key].size() != Follow2[key].size())
		{
			return false;
		}
	}
	return true;
}

// ��� FOLLOW ���� ������
void MyFollow::Rule3(std::map<std::string, std::set<std::string>>& Follow, const std::vector<std::string>& allRight, std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& grammarList,
	const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal)
{
	std::map<std::string, std::set<std::string>> tempFollow = Follow;
	bool flag;
	for (std::string oneRight : allRight)
	{
		std::vector<std::string> allChar = GetOneCandidateAllCharacter(oneRight);
		std::vector<std::pair<std::string, std::string>> allB_Beta = FindAlphaBeta(oneRight, nonterminal, allChar);
		std::vector<std::string> startCharList = GetCandidateStartChar(oneRight, nonterminal, left_Right);
		for (std::pair<std::string, std::string> B_Beta : allB_Beta)
		{
			for (std::string startChar : startCharList)
			{
				std::set<std::string> ASet;
				flag = false;
				std::string B = B_Beta.first;
				std::string beta = B_Beta.second;
				std::string firstCh = startChar;
				IsGeneralizedDerivation(firstCh, B_Beta, left_Right, terminator, flag, ASet);
				if (flag)
				{
					for (std::string key : ASet)
					{
						//std::cout << "A = " << key << "  ";
						//std::cout << key << " ";
						for (std::string item : Follow[key])
						{
							Follow[B].insert(item);
						}
					}
					//std::cout << "����" << B << std::endl;
				}
			}
		}
	}
	// ��������ˣ�������ݹ飻�����������û�и��£������ݹ�
	if (!IsRule3Over(Follow, tempFollow, nonterminal))
	{
		Rule3(Follow, allRight, left_Right, grammarList, terminator, nonterminal);
	}
}

std::map<std::string, std::set<std::string>> MyFollow::GetFollowSet(std::vector<std::string>& grammarList)
{
	std::vector<std::string> terminatorList;
	std::vector<std::string> nonterminalList;

	std::map<std::string, std::set<std::string>> left_Right;

	std::map<std::string, std::set<std::string>> Follow;

	std::vector<std::pair<std::string, std::string>> allB_Beta;



	GetTerminator_Nonterminal(grammarList, terminatorList, nonterminalList);

	GetLeft_Right2(left_Right, grammarList);


	std::vector<std::string> allRight = GetGrammarAllRight(left_Right, nonterminalList);



	allB_Beta = FindAllAlphaBeta(allRight, nonterminalList);

	Rule1(Follow, grammarList);

	//std::cout << "����һ" << std::endl;
	//PrintFollow(Follow);

	Rule2(Follow, allB_Beta, grammarList, terminatorList, nonterminalList);

	//std::cout << "�����" << std::endl;
	//PrintFollow(Follow);

	Rule3(Follow, allRight, left_Right, grammarList, terminatorList, nonterminalList);

	//std::cout << "������" << std::endl;


	return Follow;
}


int MyFollow::PrintFollow22(std::map<std::string, std::set<std::string>>& Follow)
{
	std::cout << "FOLLOW ������" << std::endl;
	for (std::pair<std::string, std::set<std::string>> item : Follow)
	{
		std::cout << item.first << ": {";
		for (std::string ii : item.second)
		{
			std::cout << ii << ", ";
		}
		std::cout << "\b\b}" << std::endl;
	}
	std::cout << std::endl;
	return 0;
}