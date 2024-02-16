#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <map>

// ��ջ�в�����Ŵ�
void MyPush(std::stack<std::string>& analysisStack, std::string string0);

// ��ӡջ�е�Ԫ��
void PrintStack(const std::stack<std::string>& analysisStack);


// ��ʼ�����Ŵ�ջ
void InitStringStack(std::stack<std::string>& stringStack, std::string string0);

// ��ʼ������ջ
void InitAnalysisStack(std::stack<std::string>& analysisStack, std::string startChar);

// ��������ջ��Ԫ�ز���ر���е�ֵ
std::string GetGrammar(std::string analysisTop, 
	std::string stringTop, std::map<std::string, 
	std::map<std::string, std::string>> analysisTable);

// ����һ������ʽ���������Ҳ�
std::string GetRight(std::string oneGrammar);


std::vector<std::vector<std::string>> Func(std::stack<std::string>& analysisStack,
	std::stack<std::string>& stringStack,
	std::map<std::string,
	std::map<std::string, std::string>> analysisTable,
	int& step);


std::vector<std::vector<std::string>> StringAnalysis(std::string string0,
	std::string startChar, std::map<std::string, std::map<std::string,
	std::string>> analysisTable);

// ��ӡ���Ŵ�������ȫ������
void PrintAllStep(const std::vector<std::vector<std::string>>& allStep, std::string string0);