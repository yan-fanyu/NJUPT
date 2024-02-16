#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>


class MyFollow {

public:

	// 输入侯选式返回文法开始符号 
	std::vector<std::string> GetCandidateStartChar(const std::string candidate, const std::vector<std::string>& nonterminalList, std::map<std::string, std::set<std::string>> left_Right);

	int GetNonterminalIndex(std::string oneNonterminal, const std::vector<std::string>& nonterminalList);


	// 获取一条产生式全部的右部的侯选式
	std::vector<std::string> GetOneGrammarAllRight(std::string oneGrammar);

	// 获取全部文法的全部右部
	std::vector<std::string> GetGrammarAllRight(std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& nonterminalList);

	// 获取一条侯选式的全部字符
	std::vector<std::string> GetOneCandidateAllCharacter(std::string str);

	// 寻找一条侯选式的 B 和 Beta
	std::vector<std::pair<std::string, std::string>> FindAlphaBeta(std::string oneRight, const std::vector<std::string>& nonterminal, const std::vector<std::string>& allCharacter);

	// 寻找全部侯选式的 B 和 Beta
	std::vector<std::pair<std::string, std::string>> FindAllAlphaBeta(std::vector<std::string> allRight, const std::vector<std::string>& nonterminal);

	// 求解 FOLLOW 集合 规则一
	void Rule1(std::map<std::string, std::set<std::string>>& Follow, const std::vector<std::string>& grammarList);

	// 求解 FOLLOW 集合 规则二
	void Rule2(std::map<std::string, std::set<std::string>>& Follow, std::vector<std::pair<std::string, std::string>> allB_Beta, const std::vector<std::string>& grammarList,
		const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal);

	// beta 是否能广义推导出 空符号
	void IsGeneralizedDerivation(std::string lastA, std::pair<std::string, std::string>& B_Beta, std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& terminator, bool& flag, std::set<std::string>& ASet);



	// 规则三递归终止条件
	bool IsRule3Over(std::map<std::string, std::set<std::string>>& Follow, std::map<std::string, std::set<std::string>>& Follow2, const std::vector<std::string>& nonterminal);

	// 求解 FOLLOW 集合 规则三
	void Rule3(std::map<std::string, std::set<std::string>>& Follow, const std::vector<std::string>& allRight, std::map<std::string, std::set<std::string>> left_Right, const std::vector<std::string>& grammarList,
		const std::vector<std::string>& terminator, const std::vector<std::string>& nonterminal);

	std::map<std::string, std::set<std::string>> GetFollowSet(std::vector<std::string>& grammarList);

	int PrintFollow22(std::map<std::string, std::set<std::string>>& Follow);

};















