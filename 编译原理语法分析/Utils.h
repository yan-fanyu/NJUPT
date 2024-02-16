#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>

void GetOneLeft_Right2(const std::string oneGrammer, std::map<std::string, std::set<std::string>>& left_Right);

void GetLeft_Right2(std::map<std::string, std::set<std::string>>& left_Right, const std::vector<std::string> grammarList);

void PrintLeft_Right2(std::map<std::string, std::set<std::string>>& left_Right);

// �ж��Ƿ����ս����
bool IsTerminator(std::string ch, const std::vector<std::string>& terminator);

// �ж��Ƿ��Ƿ��ս����
bool IsNonterminal(std::string ch, const std::vector<std::string>& nonterminal);

void PrintTerminator(const std::vector<std::string>& terminatorList);


void PrintNonterminal(const std::vector<std::string>& nonterminalList);

// ��ȥ�ص� set ���� ��ֵ�� vector ����
void SetToVector(std::vector<std::string>& v, const std::set<std::string>& s);

// ����ս���ż� �� ���ս���ż�
void GetTerminator_Nonterminal(const std::vector<std::string>& grammarList, 
	std::vector<std::string>& terminatorList, 
	std::vector<std::string>& nonterminalList);