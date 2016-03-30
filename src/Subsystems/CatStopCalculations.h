#ifndef CAT_STOP_CALCULATIONS_H
#define CAT_STOP_CALCULATIONS_H

#include "Commands/Subsystem.h"
#include "Misc/cSpline.h"
#include <WPILib.h>

#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class CatStopCalculations: public Subsystem
{
private:
	static CatStopCalculations* m_pInstance;
	vector<pair<double,double>>* vector_mainStorage;
	vector<double>* vector_distPass;
	vector<double>* vector_stopPass;

	const string distFilePath = "/home/lvuser/targetdist-storage.ini";
	const string stopFilePath = "/home/lvuser/stopangle-storage.ini";

	raven::cSpline* stopCurve;

	CatStopCalculations();
	CatStopCalculations& operator=(CatStopCalculations const&);
public:
	static CatStopCalculations* GetInstance();
	void InitDefaultCommand();

	void AddPoint(double dist, double stop);
	void SaveToFile();
	vector<pair<double,double>> ReadFile();
	void WipeSave();
	double GetStop(double dist);
};

#endif
