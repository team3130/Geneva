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
	//Add the point to memory
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
	//Copy distance to distFilePath
	ofstream distFILE(distFilePath, ios::out | ios::binary | ios::trunc);
	if(vector_distPass != NULL)copy(vector_distPass->begin(), vector_distPass->end(), ostreambuf_iterator<char>(distFILE));

	//Copy stop angle to stopFilePath
	ofstream stopFILE(stopFilePath, ios::out | ios::binary | ios::trunc);
	if(vector_stopPass != NULL)copy(vector_stopPass->begin(), vector_stopPass->end(), ostreambuf_iterator<char>(stopFILE));
}

vector<pair<double,double>> CatStopCalculations::ReadFile()
{
	//define required intermediary variables
	vector<pair<double,double>> outputVect;
		outputVect.push_back(make_pair(-1,-1));	//Define error output
	vector<double> distVect;
	vector<double> stopVect;

	//Define input files
	ifstream distINFILE(distFilePath, ios::in | ios::binary);
	ifstream stopINFILE(stopFilePath, ios::in | ios::binary);

	//Read file contents into intermediary vectors
	double dist;
	while(distINFILE.read(reinterpret_cast<char *>(&dist), sizeof(dist)))		distVect.push_back(dist);

	double stop;
	while(stopINFILE.read(reinterpret_cast<char *>(&stop), sizeof(stop)))		stopVect.push_back(stop);


	//Check for input sanity: if not equal, would error on next step
	if(stopVect.size() == distVect.size())
	{
		//Recombine Distance and Stop Angle into one vector of pairs
		for(unsigned int iii = 0; iii < distVect.size(); iii++)
		{
			outputVect.push_back(make_pair(distVect[iii],stopVect[iii]));
		}
	}

	return outputVect;
}

double CatStopCalculations::GetStop(double dist)
{
	//sanity check
	if(!stopCurve) return -1;
	return stopCurve->getY(dist);
}

void CatStopCalculations::WipeSave()
{
	//Erase the values of the vectors
	vector_mainStorage->clear();
	vector_distPass->clear();
	vector_stopPass->clear();

	//Empty the files
	ofstream distFile(distFilePath, ios::out | ios::binary | ios::trunc);
	ofstream stopFile(distFilePath, ios::out | ios::binary | ios::trunc);
}
