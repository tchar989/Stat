#include <iostream>
#include <vector>
#include "Stat.h"
using namespace std;

int main()
{
	string select;
	Stat *stat = new Stat();
	stat->takeSample();
	while(1)
	{
		select = "";
		cout << "<Sample Statistics>  <Confidence Interval>  <Null Hypothesis>  <Exit>" << endl << "(type desired)" << endl;
		getline(cin, select);
		getline(cin, select);
		if(select == "")
		{
			goto l1;
		}
		if(select == "Sample Statistics")
		{
			stat->printSampleStats();
			continue;
		}
		else if(select == "Confidence Interval")
		{
			stat->computeConfidenceInterval();
			continue;
		}
		else if(select == "Null Hypothesis")
		{
			stat->nullHypothesis();
			continue;
		}
		else if(select == "Exit")
		{
			return 0;
		}
		else
		{
			l1:	
			cout << "Incorrect Input. Try Again" << endl;
			continue;
		}
	}
return 0;
}