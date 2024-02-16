#pragma once
#include <set>
#include <iostream>
#include <vector>
#include <map>

class MyFirst
{
public:
	

	void PairSetToVector(std::vector<std::pair<std::string, std::string>>& v, std::set<std::pair<std::string, std::string>>& s);





	// ��ȡ���͵����ַ�
	std::string GetFirstChar(std::string sentence);

	
	// ���ݿ�ʼ����ȷ���ķ�
	std::vector<std::string> GetGrammar(std::string firstChar, const std::vector<std::string>& grammarList);


	void GetRightString(const std::vector<std::string>& grammarList, std::vector<std::string>& rightStringList);

	// ��ӡ����ʽ�Ҳ�ķ��Ŵ�
	void PrintRightString(const std::vector<std::string>& rightString);

	// ���룺���ͺ�ȫ���ķ�
	// ���أ��þ��͵� FIRST ��
	void GetOneFirst(std::string& sentence, std::vector<std::string>& First, const std::vector<std::string>& grammarList,
		const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal);


	void PrintOneFirst(std::string sentence, std::vector<std::string>& First);

	void GetAllSentence(std::vector<std::string>& allSentence, const std::vector<std::string>& allLeftList,
		std::vector<std::string>& allRightList);

	void PrintAllSentence(const std::vector<std::string>& allSentence);

	std::map<std::string, std::set<std::string>> GetFirstSet(const std::vector<std::string>& allSentenceList,
		const std::vector<std::string>& grammarList, const std::vector<std::string>& terminatorList,
		const std::vector<std::string>& nonterminalList);

	void PrintFirst22(std::map<std::string, std::set<std::string>>& First);

	

};

