#include <iostream>
#include <vector>
using namespace std;

class Stat
{
private:
	int sampleSize;
	vector<double> sample;
	double mean;
	double standardVariance;
public:
	void takeSample();
	void calcMean();
	void calcStandardVar();
	int getSampleSize();
	double getMean();
	double getStandardVariance();
	double getStandardDeviation();
	void computeConfidenceInterval();
	void printSampleStats();
	double RationalApproximation(double t);
	double NormalCDFInverse(double p);
	void nullHypothesis();
	double phi(double x);
};