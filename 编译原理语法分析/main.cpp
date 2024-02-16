#include "EliminateLeftRecursion.h"
#include "FirstSet.h"
#include "FollowSet.h"
#include "AnalysisTableConstructor.h"
#include "Utils.h"
#include "StringAnalysis.h"

int main()
{
	MyFirst myFirst;
	MyFollow myFollow;
	std::vector<std::string> grammarList;

	std::vector<std::string> allSentence;

	ReadGrammerFile(grammarList, "code.txt");


	std::cout << "原始文法如下" << std::endl;
	PrintGrammerList(grammarList);

	EliminateLeftRecursion(grammarList);

	std::cout << "消除左递归文法如下" << std::endl;
	PrintGrammerList(grammarList);


	std::vector<std::string> terminatorList;
	std::vector<std::string> nonterminalList;
	std::vector<std::string> allLeftList;
	std::vector<std::string> allRightList;
	std::vector<std::string> allSentenceList;
	std::map<std::string, std::map<std::string, std::string>> analysisTable;
	std::vector<std::vector<std::string>> allStep;
	std::map<std::string, std::set<std::string>> allRightMap;
	std::map<std::string, std::set<std::string>> Follow;
	std::map<std::string, std::set<std::string>> First;
	std::string string0;
	std::string startChar;

	GetTerminator_Nonterminal(grammarList, terminatorList, nonterminalList);

	PrintTerminator(terminatorList);
	PrintNonterminal(nonterminalList);

	GetLeft_Right2(allRightMap, grammarList);

	// 求解全部右部
	allRightList = myFollow.GetGrammarAllRight(allRightMap, nonterminalList);
	// 求解全部左部
	allLeftList = nonterminalList;

	myFirst.GetAllSentence(allSentence, allLeftList, allRightList);


	First = myFirst.GetFirstSet(allSentence, grammarList, terminatorList, nonterminalList);
	myFirst.PrintFirst22(First);

	Follow = myFollow.GetFollowSet(grammarList);
	myFollow.PrintFollow22(Follow);


	// 构造分析表
	analysisTable = AnalysisTableConstructor(First, Follow, terminatorList, nonterminalList, allRightMap);
	
	string0 = "i+i*i";
	startChar = GetFirstChar2(grammarList[0]);

	allStep = StringAnalysis(string0, startChar, analysisTable);
	PrintAllStep(allStep, string0);


	return 0;
}

/*
*
E::=TE'
E'::=+TE'|$
T::=FT'
T'::=*FT'|$
F::=(E)|i

*/