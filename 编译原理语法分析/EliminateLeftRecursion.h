#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// 分割一条文法的左部和右部
std::vector<std::string> GetOneLeft_Right(const std::string oneGrammer);

// 获取所有文法的左部和右部
void GetLeft_RightList(const std::vector<std::string>& grammarList, std::vector<std::vector<std::string>>& left_rightList);

// 打印全部文法分割完成的状态
void PrintLeft_RightList(const std::vector<std::vector<std::string>>& left_rightList);

// 读取文法 TXT 文件
void ReadGrammerFile(std::vector<std::string>& grammarList, std::string url);

// 打印全部的文法
void PrintGrammerList(const std::vector<std::string>& grammarList);

// 是否存在左递归。如果存在，返回是第几个候选式
bool LeftRecursion(const std::vector<std::string>& left_right);

// 找到所有左递归的文法索引及其是第几个侯选式出现左递归的索引对
std::vector<std::pair<int, int>> GetPairIndex(const std::vector<std::vector<std::string>> left_rightList);

// 消除一条文法左递归
void EliminateOneLeftRecursion(std::vector<std::string>& grammarList, const std::vector<std::vector<std::string>> left_rightList, std::vector<std::string>& left_right, std::pair<int, int> pairIndex, int ii);

// 消除全部文法左递归
void EliminateAllLeftRecursion(std::vector<std::string>& grammarList, std::vector<std::vector<std::string>>& left_rightList);

// 获取句型的首字符
std::string GetFirstChar2(std::string sentence);

void SetFirstGrammar(std::vector<std::string>& grammarList, std::string startCh);

void EliminateLeftRecursion(std::vector<std::string>& grammarList);