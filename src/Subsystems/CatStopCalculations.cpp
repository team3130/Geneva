#include "CatStopCalculations.h"
#include "../RobotMap.h"
#include "Misc/cSpline.h"

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
	sort(vector_mainStorage->begin()->first, vector_mainStorage->end()->second);

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

}

void CatStopCalculations::GetStop()
{

}
