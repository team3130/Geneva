#include "CatStopCalculations.h"
#include "../RobotMap.h"
#include "Misc/cSpline.h"
#include <fstream>


CatStopCalculations* CatStopCalculations::m_pInstance = NULL;

CatStopCalculations* CatStopCalculations::GetInstance()
{
	if(!m_pInstance) m_pInstance = new CatStopCalculations;
	return m_pInstance;
}

CatStopCalculations::CatStopCalculations() :
		Subsystem("CatStopCalculations")
{
	vector_mainStorage = new vector<pair<double,double>>;
	vector_distPass = new vector<double>;
	vector_stopPass = new vector<double>;

	stopCurve = NULL;
}

void CatStopCalculations::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void CatStopCalculations::AddPoint(double dist, double stop)
{
	vector_mainStorage->push_back(make_pair(dist, stop));
	sort(vector_mainStorage->begin(), vector_mainStorage->end());

	//Split the vector into two seperate vectors
	pair<double,double> place;
	for(unsigned int iii = 0; iii<vector_mainStorage->size(); iii++)
	{
		place = vector_mainStorage->at(iii);
		vector_distPass->push_back(place.first);
		vector_stopPass->push_back(place.second);
	}

	//Create the curve
	if(stopCurve) delete stopCurve;
	stopCurve = new raven::cSpline(*vector_distPass, *vector_stopPass);
}

void CatStopCalculations::SaveToFile()
{
	ofstream distFILE(distFilePath, ios::out | ios::binary);
	copy(vector_distPass->begin(), vector_distPass->end(), ostreambuf_iterator<char>(distFILE));

	ofstream stopFILE(stopFilePath, ios::out | ios::binary);
	copy(vector_stopPass->begin(), vector_stopPass->end(), ostreambuf_iterator<char>(stopFILE));
}

vector<pair<double,double>> CatStopCalculations::ReadFile()
{
	vector<pair<double,double>> outputVect;

	return outputVect;
}

double CatStopCalculations::GetStop(double dist)
{
	return stopCurve->getY(dist);
}

void CatStopCalculations::WipeSave()
{

}
