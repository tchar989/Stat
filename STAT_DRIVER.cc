#include <iostream>
#include <vector>
#include "Stat.h"
using namespace std;

const static string p[3] = {"Sample Statistics", "Confidence Interval", "Null Hypothesis"};
int main()
{	

	string temp;
	string select;
	Stat *stat = new Stat();
	stat->takeSample();
	cin.get();
	while(1)
	{
		select = "";
		cout << "-----------------PICK----YOUR----SAMPLE----ANALYSIS------------------" << endl;
		cout << "<Sample Statistics>  <Confidence Interval>  <Null Hypothesis>  <Exit>" << endl;
		getline(cin,select);
		cout << endl;
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
			cout << "Incorrect Input. Try Again" << endl;
			continue;
		}
	}
return 0;
}

