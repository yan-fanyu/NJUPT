#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>

void PrintAnalysisTable(std::map<std::string, std::map<std::string, std::string>> analysisTable,
	const std::vector<std::string>& terminatorList,
	const std::vector<std::string>& nonterminalList);

void InitAnalysisTable(std::map<std::string, std::map<std::string, std::string>>& analysisTable,
	const std::vector<std::string>& terminatorList, const std::vector<std::string>& nonterminalList);

std::string GetSartCharByCandidate(std::string candidate, std::map<std::string, std::set<std::string>> allRightMap);

void ConstructorAnalysisTableByFirst(
	std::map<std::string, std::map<std::string, std::string>>& analysisTable,
	std::map<std::string, std::set<std::string>> First,
	std::map<std::string, std::set<std::string>> Follow,
	std::map<std::string, std::set<std::string>> allRightMap,
	const std::vector<std::string>& nonterminalList
);

void ConstructorAnalysisTableByFollow(
	std::map<std::string, std::map<std::string, std::string>>& analysisTable,
	std::map<std::string, std::set<std::string>> Follow,
	std::map<std::string, std::set<std::string>> allRightMap,
	const std::vector<std::string>& nonterminalList);



std::map<std::string, std::map<std::string, std::string>> AnalysisTableConstructor(
	std::map<std::string, std::set<std::string>> First,
	std::map<std::string, std::set<std::string>> Follow,
	const std::vector<std::string>& terminatorList,
	const std::vector<std::string>& nonterminalList,
	std::map<std::string, std::set<std::string>> allRightMap);