#include "EliminateLeftRecursion.h"

// 分割一条文法的左部和右部
std::vector<std::string> GetOneLeft_Right(const std::string oneGrammer)
{
    std::vector<std::string> left_right;
    std::string word = "";
    word = oneGrammer.substr(0, 1);

    int i = 4;

    if (oneGrammer.substr(1, 1) == "'")
    {
        i++;
        word += oneGrammer.substr(1, 1);
    }

    left_right.push_back(word);

    word = "";

    for (; i < oneGrammer.length(); i++)
    {
        if (oneGrammer[i] == '|')
        {
            left_right.push_back(word);
            word = "";
            continue;
        }
        word += oneGrammer[i];
    }
    left_right.push_back(word);
    return left_right;
}

// 获取所有文法的左部和右部
void GetLeft_RightList(const std::vector<std::string>& grammarList, std::vector<std::vector<std::string>>& left_rightList)
{
    for (std::string oneGrammer : grammarList)
    {
        left_rightList.push_back(GetOneLeft_Right(oneGrammer));
    }
}

// 打印全部文法分割完成的状态
void PrintLeft_RightList(const std::vector<std::vector<std::string>>& left_rightList)
{
    for (std::vector<std::string> left_right : left_rightList)
    {
        for (std::string part : left_right)
        {
            std::cout << part << " ";
        }
        std::cout << std::endl;
    }
}

// 读取文法 TXT 文件
void ReadGrammerFile(std::vector<std::string>& grammarList, std::string url)
{
    std::ifstream in(url);
    std::string filename;
    std::string line;

    if (in) // 有该文件
    {
        while (std::getline(in, line)) // line中不包括每行的换行符
        {
            grammarList.push_back(line);
        }
    }
}

// 打印全部的文法
void PrintGrammerList(const std::vector<std::string>& grammarList)
{
    for (std::string a : grammarList)
    {
        std::cout << a << std::endl;
    }

    std::cout << std::endl;
}

// 是否存在左递归。如果存在，返回是第几个候选式
bool LeftRecursion(const std::vector<std::string>& left_right)
{
    std::string left = left_right[0];
    for (int i = 1; i < left_right.size(); i++)
    {
        if (left == (left_right[i]).substr(0, 1))
        {
            return i;
        }
    }
    return 0;
}

// 找到所有左递归的文法索引及其是第几个侯选式出现左递归的索引对
std::vector<std::pair<int, int>> GetPairIndex(const std::vector<std::vector<std::string>> left_rightList)
{
    std::vector<std::pair<int, int>> leftRecursionIndex;
    for (int i = 0; i < left_rightList.size(); i++)
    {
        if (int j = LeftRecursion(left_rightList[i]))
        {
            leftRecursionIndex.push_back(std::make_pair(i, j));
        }
    }
    return leftRecursionIndex;
}

// 消除一条文法左递归
void EliminateOneLeftRecursion(std::vector<std::string>& grammarList, const std::vector<std::vector<std::string>> left_rightList, std::vector<std::string>& left_right, std::pair<int, int> pairIndex, int ii)
{
    // 左部
    std::string A = left_right[0];
    int grammerIndex = pairIndex.first;
    int leftRecursionIndex = pairIndex.second;
    // 左递归部分的长度
    int partLength = left_right[leftRecursionIndex].length();
    std::string alpha = left_right[leftRecursionIndex].substr(1, partLength);
    std::string beta = left_right[3 - leftRecursionIndex];

    //std::cout << "alpha = " << alpha << "\nbeta = " << beta << std::endl;

    //std::cout << "\n\n";

    grammarList.erase(grammarList.begin() + grammerIndex - ii); // 该处erase处理方法
    std::string grammer1 = A + "::=" + beta + A + "'";
    std::string grammer2 = A + "'::=" + alpha + A + "'|$";
    grammarList.push_back(grammer1);
    grammarList.push_back(grammer2);
}

// 消除全部文法左递归
void EliminateAllLeftRecursion(std::vector<std::string>& grammarList, std::vector<std::vector<std::string>>& left_rightList)
{
    // 索引对
    std::vector<std::pair<int, int>> pairIndex = GetPairIndex(left_rightList);
    for (int i = 0; i < pairIndex.size(); i++)
    {
        EliminateOneLeftRecursion(grammarList, left_rightList, left_rightList[pairIndex[i].first], pairIndex[i], i);
    }
}

// 获取句型的首字符
std::string GetFirstChar2(std::string sentence)
{
    std::string firstChar = sentence.substr(0, 1);
    if (sentence.length() > 1 && sentence.substr(1, 1) == "'")
    {
        firstChar = sentence.substr(0, 2);
    }
    return firstChar;
}

void SetFirstGrammar(std::vector<std::string>& grammarList, std::string startCh)
{
    std::string oneGrammar = grammarList[0];
    std::string firstChar = GetFirstChar2(oneGrammar);
    if (firstChar == startCh)
    {
        return;
    }
    for (int i = 1; i < grammarList.size(); i++)
    {
        oneGrammar = grammarList[i];
        firstChar = GetFirstChar2(oneGrammar);
        if (firstChar == startCh)
        {
            grammarList[i] = grammarList[0];
            grammarList[0] = oneGrammar;
            break;
        }
    }
}

void EliminateLeftRecursion(std::vector<std::string>& grammarList)
{
    std::vector<std::vector<std::string>> left_rightList;   // 文法分为左部和多个右部列表

    std::string startChar = GetFirstChar2(grammarList[0]);

    GetLeft_RightList(grammarList, left_rightList);

    EliminateAllLeftRecursion(grammarList, left_rightList);

    SetFirstGrammar(grammarList, startChar);
}

