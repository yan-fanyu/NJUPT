#pragma once
#include <set>
#include <iostream>
#include <vector>
#include <map>

class MyFirst
{
public:
	

	void PairSetToVector(std::vector<std::pair<std::string, std::string>>& v, std::set<std::pair<std::string, std::string>>& s);





	// 获取句型的首字符
	std::string GetFirstChar(std::string sentence);

	
	// 根据开始符号确定文法
	std::vector<std::string> GetGrammar(std::string firstChar, const std::vector<std::string>& grammarList);


	void GetRightString(const std::vector<std::string>& grammarList, std::vector<std::string>& rightStringList);

	// 打印产生式右侧的符号串
	void PrintRightString(const std::vector<std::string>& rightString);

	// 输入：句型和全部文法
	// 返回：该句型的 FIRST 集
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

