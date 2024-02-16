#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>

void GetOneLeft_Right2(const std::string oneGrammer, std::map<std::string, std::set<std::string>>& left_Right);

void GetLeft_Right2(std::map<std::string, std::set<std::string>>& left_Right, const std::vector<std::string> grammarList);

void PrintLeft_Right2(std::map<std::string, std::set<std::string>>& left_Right);

// 判断是否是终结符号
bool IsTerminator(std::string ch, const std::vector<std::string>& terminator);

// 判断是否是非终结符号
bool IsNonterminal(std::string ch, const std::vector<std::string>& nonterminal);

void PrintTerminator(const std::vector<std::string>& terminatorList);


void PrintNonterminal(const std::vector<std::string>& nonterminalList);

// 将去重的 set 集合 赋值给 vector 集合
void SetToVector(std::vector<std::string>& v, const std::set<std::string>& s);

// 求解终结符号集 和 非终结符号集
void GetTerminator_Nonterminal(const std::vector<std::string>& grammarList, 
	std::vector<std::string>& terminatorList, 
	std::vector<std::string>& nonterminalList);