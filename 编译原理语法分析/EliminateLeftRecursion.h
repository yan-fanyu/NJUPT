#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// �ָ�һ���ķ����󲿺��Ҳ�
std::vector<std::string> GetOneLeft_Right(const std::string oneGrammer);

// ��ȡ�����ķ����󲿺��Ҳ�
void GetLeft_RightList(const std::vector<std::string>& grammarList, std::vector<std::vector<std::string>>& left_rightList);

// ��ӡȫ���ķ��ָ���ɵ�״̬
void PrintLeft_RightList(const std::vector<std::vector<std::string>>& left_rightList);

// ��ȡ�ķ� TXT �ļ�
void ReadGrammerFile(std::vector<std::string>& grammarList, std::string url);

// ��ӡȫ�����ķ�
void PrintGrammerList(const std::vector<std::string>& grammarList);

// �Ƿ������ݹ顣������ڣ������ǵڼ�����ѡʽ
bool LeftRecursion(const std::vector<std::string>& left_right);

// �ҵ�������ݹ���ķ����������ǵڼ�����ѡʽ������ݹ��������
std::vector<std::pair<int, int>> GetPairIndex(const std::vector<std::vector<std::string>> left_rightList);

// ����һ���ķ���ݹ�
void EliminateOneLeftRecursion(std::vector<std::string>& grammarList, const std::vector<std::vector<std::string>> left_rightList, std::vector<std::string>& left_right, std::pair<int, int> pairIndex, int ii);

// ����ȫ���ķ���ݹ�
void EliminateAllLeftRecursion(std::vector<std::string>& grammarList, std::vector<std::vector<std::string>>& left_rightList);

// ��ȡ���͵����ַ�
std::string GetFirstChar2(std::string sentence);

void SetFirstGrammar(std::vector<std::string>& grammarList, std::string startCh);

void EliminateLeftRecursion(std::vector<std::string>& grammarList);