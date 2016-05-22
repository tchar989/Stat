#include <iostream>
#include <vector>
#include <cmath>
#include "Stat.h"
using namespace std;


void Stat::takeSample()
	
{

	cout << "Input your sample size: " << endl;
	cin >> sampleSize;
	cout << "Input your sample elements: " << endl;
	double temp;
	for(int i = 0; i < sampleSize; i++)
	{
		cin >> temp;
		sample.push_back(temp);
	}
	calcMean();
	calcStandardVar();
}
void Stat::calcMean()
{
	double sum = 0;
	for(int i = 0; i < sampleSize; i++)
	{
		sum+=sample.at(i);
	}
	mean = sum/sampleSize;
}

void Stat::calcStandardVar()
{
	double sum = 0;
	for(int i = 0; i < sampleSize; i++)
	{
		sum+=pow(mean-sample.at(i),2);
	}
	standardVariance = sum/(sampleSize-1);
}

double Stat::getMean()
{
	return mean;
}

double Stat::getStandardVariance()
{
	return standardVariance;
}

double Stat::getStandardDeviation()
{
	return pow(getStandardVariance(),0.5);
}
int Stat::getSampleSize()
{
	return sampleSize;
}

void Stat::printSampleStats()
{
	cout << "\u03BC: " << mean << endl;
 	cout << "\u03C3^2: " << standardVariance << endl;
	cout << "\u03C3: " << getStandardDeviation() << endl;
	cout << "n: " << sampleSize << endl << endl;
}

double Stat::RationalApproximation(double t)
{
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) /
                (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}
 
double Stat::NormalCDFInverse(double p)
{
    
 
    // See article above for explanation of this section.
    if (p < 0.5)
    {
        // F^-1(p) = - G^-1(p)
        return -RationalApproximation( sqrt(-2.0*log(p)) );
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return RationalApproximation( sqrt(-2.0*log(1-p)) );
    }
}

void Stat::computeConfidenceInterval()
{
	string temp;
	double percentage;
	double deviation = 0.0;
	cout << "If you know the population deviation, input now then hit <Enter>." << endl
	<< " If not, input -1" << endl;
	cin >> deviation;
	if(deviation == -1)
	{
		deviation = getStandardDeviation()/pow(sampleSize,0.5);
	}
	cout << "Enter the percentage of precision for interval(1-100): " << endl;
	cin >> percentage;
	cout << "Type u for one sided upper interval, l " <<
	"for one sided lower, x for two sided." << endl;
	cin >> temp;
	if(temp == "x")
	{
		double alpha = 1.0-(((100.0-percentage)/100.0)/2.0);
		double lower = mean - NormalCDFInverse(alpha)*(double)deviation;
		double upper = mean + NormalCDFInverse(alpha)*(double)deviation;
		cout << "(" << lower << " , " << upper << ")" << endl;
	}
	else if(temp == "u")
	{
		double alpha = percentage/100.0;
		cout << (mean + NormalCDFInverse(alpha)*(double)deviation) << endl;
	}
	else if(temp == "l")
	{
		double alpha = percentage/100.0;
		cout << (mean - NormalCDFInverse(alpha)*(double)deviation) << endl;
	}
	cout << endl;
	cin.get();
}

double Stat::Norm_Cumul_Prob_Density_Funct(double x)
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}

void Stat::nullHypothesis()
{
	double hypMean;
	string relType;
	short relnum;
	string altOp;
	cout << "Input your hypothetical mean: " << endl;
	cin >> hypMean;
	cout << "Input relational operator for null hypothesis (>,>=,<,<=,=,!=)" << endl;
	cout << "H0: \u03BC    " << hypMean << string(4,'\b');
	cin >> relType;
	if(relType == "!=")
	{
		altOp = "=";
		cout << "H1: \u03BC " << altOp << " " << hypMean << endl;
		relnum = 2;
		goto l1;
	}
	else if(relType == ">=")
	{
		altOp = "<";
		cout << "H1: \u03BC " << altOp << " " << hypMean << endl;
		relnum = 1;
		goto l1;
	}
	else if(relType == "<=")
	{
		altOp = ">";
		cout << "H1: \u03BC " << altOp << " " << hypMean << endl;
		relnum = 1;
		goto l1;
	}
	cout << "Enter relational operator for alternate hypothesis (<,<=,>,>=,!=,=)" << endl;
	cout << "H1: \u03BC    " << hypMean << string(4, '\b');
	cin >> altOp;
	if(altOp == ">" || altOp == ">=")
	{
		relnum = 1;
	}
	else if (altOp == "<" || altOp == "<=")
	{
		relnum = 2;
	}
	else if (altOp == "=")
		relnum = 2;
	else if (altOp == "!=")
		relnum = 3;
	else
	{
		cerr << "invalid relational operator" << endl;
		exit(1);
	}
	l1:
	double z;
	z = (mean-hypMean)/(getStandardDeviation()/sqrt(sampleSize));
	z = Norm_Cumul_Prob_Density_Funct(z);
	if(relnum == 1)
	{
		z = 1-z;
		if(z <= 0.05)
		{
			cout << "Null Hypothesis Rejected with P value of " << z << endl << endl;
			cin.get();
			return;
		}
	}
	else if (relnum == 2)
	{
		if(z <= 0.05)
		{
			cout << "Null Hypothesis Rejected with P value of " << z << endl << endl;
			cin.get();
			return;
		}
	}
	else 
	{
		z=(1-z)*2;
		if(z <= 0.05)
		{
			cout << "Null Hypothesis Rejected with P Value of " << z << endl << endl;
			cin.get();
			return;
		}
	}
	cout << "Null Hypothesis has a non-ignorable chance of occuring with P-value of " << z << endl << endl;	
	cin.get();	
}