#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <map>

// 向栈中插入符号串
void MyPush(std::stack<std::string>& analysisStack, std::string string0);

// 打印栈中的元素
void PrintStack(const std::stack<std::string>& analysisStack);


// 初始化符号串栈
void InitStringStack(std::stack<std::string>& stringStack, std::string string0);

// 初始化分析栈
void InitAnalysisStack(std::stack<std::string>& analysisStack, std::string startChar);

// 根据两个栈顶元素查表返回表格中的值
std::string GetGrammar(std::string analysisTop, 
	std::string stringTop, std::map<std::string, 
	std::map<std::string, std::string>> analysisTable);

// 根据一条产生式返回他的右部
std::string GetRight(std::string oneGrammar);


std::vector<std::vector<std::string>> Func(std::stack<std::string>& analysisStack,
	std::stack<std::string>& stringStack,
	std::map<std::string,
	std::map<std::string, std::string>> analysisTable,
	int& step);


std::vector<std::vector<std::string>> StringAnalysis(std::string string0,
	std::string startChar, std::map<std::string, std::map<std::string,
	std::string>> analysisTable);

// 打印符号串分析的全部过程
void PrintAllStep(const std::vector<std::vector<std::string>>& allStep, std::string string0);