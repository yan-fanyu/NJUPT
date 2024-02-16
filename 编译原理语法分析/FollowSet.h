#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>


class MyFollow {

public:

	// �����ѡʽ�����ķ���ʼ���� 
	std::vector<std::string> GetCandidateStartChar(const std::string candidate, const std::vector<std::string>& nonterminalList, std::map<std::string, std::set<std::string>> left_Right);

	int GetNonterminalIndex(std::string oneNonterminal, const std::vector<std::string>& nonterminalList);


	// ��ȡһ������ʽȫ�����Ҳ��ĺ�ѡʽ
	std::vector<std::string> GetOneGrammarAllRight(std::string oneGrammar);

	// ��ȡȫ���ķ���ȫ���Ҳ�
	std::vector<std::string> GetGrammarAllRight(std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& nonterminalList);

	// ��ȡһ����ѡʽ��ȫ���ַ�
	std::vector<std::string> GetOneCandidateAllCharacter(std::string str);

	// Ѱ��һ����ѡʽ�� B �� Beta
	std::vector<std::pair<std::string, std::string>> FindAlphaBeta(std::string oneRight, const std::vector<std::string>& nonterminal, const std::vector<std::string>& allCharacter);

	// Ѱ��ȫ����ѡʽ�� B �� Beta
	std::vector<std::pair<std::string, std::string>> FindAllAlphaBeta(std::vector<std::string> allRight, const std::vector<std::string>& nonterminal);

	// ��� FOLLOW ���� ����һ
	void Rule1(std::map<std::string, std::set<std::string>>& Follow, const std::vector<std::string>& grammarList);

	// ��� FOLLOW ���� �����
	void Rule2(std::map<std::string, std::set<std::string>>& Follow, std::vector<std::pair<std::string, std::string>> allB_Beta, const std::vector<std::string>& grammarList,
		const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal);

	// beta �Ƿ��ܹ����Ƶ��� �շ���
	void IsGeneralizedDerivation(std::string lastA, std::pair<std::string, std::string>& B_Beta, std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& terminator, bool& flag, std::set<std::string>& ASet);



	// �������ݹ���ֹ����
	bool IsRule3Over(std::map<std::string, std::set<std::string>>& Follow, std::map<std::string, std::set<std::string>>& Follow2, const std::vector<std::string>& nonterminal);

	// ��� FOLLOW ���� ������
	void Rule3(std::map<std::string, std::set<std::string>>& Follow, const std::vector<std::string>& allRight, std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& grammarList,
		const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal);

	std::map<std::string, std::set<std::string>> GetFollowSet(std::vector<std::string>& grammarList);

	int PrintFollow22(std::map<std::string, std::set<std::string>>& Follow);

};















