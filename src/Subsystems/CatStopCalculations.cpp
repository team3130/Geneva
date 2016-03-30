#include "CatStopCalculations.h"
#include "../RobotMap.h"
#include "Misc/cSpline.h"

CatStopCalculations* Chassis::m_pInstance = NULL;

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
	pair<double,double> place;
	for(int iii = 0; iii<vector_mainStorage->size(); iii++)
	{
		place = vector_mainStorage[iii];
		vector_distPass->push_back(place.first);
		vector_stopPass->push_back(place.second);
	}
}

void CatStopCalculations::SaveToFile()
{

}

void CatStopCalculations::GetStop()
{

}
