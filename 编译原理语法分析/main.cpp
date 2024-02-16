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


	std::cout << "ԭʼ�ķ�����" << std::endl;
	PrintGrammerList(grammarList);

	EliminateLeftRecursion(grammarList);

	std::cout << "������ݹ��ķ�����" << std::endl;
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

	// ���ȫ���Ҳ�
	allRightList = myFollow.GetGrammarAllRight(allRightMap, nonterminalList);
	// ���ȫ����
	allLeftList = nonterminalList;

	myFirst.GetAllSentence(allSentence, allLeftList, allRightList);


	First = myFirst.GetFirstSet(allSentence, grammarList, terminatorList, nonterminalList);
	myFirst.PrintFirst22(First);

	Follow = myFollow.GetFollowSet(grammarList);
	myFollow.PrintFollow22(Follow);


	// ���������
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