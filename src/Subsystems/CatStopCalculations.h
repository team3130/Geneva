#ifndef CAT_STOP_CALCULATIONS_H
#define CAT_STOP_CALCULATIONS_H

#include "Commands/Subsystem.h"
#include <WPILib.h>

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class CatStopCalculations: public Subsystem
{
private:
	static CatStopCalculations* m_pInstance;
	vector<pair<double,double>> vector_mainStorage;
	vector<double> vector_xPass;
	vector<double> vector_yPass;

	CatStopCalculations();
	CatStopCalculations& operator=(CatStopCalculations const&);
public:
	static CatStopCalculations* GetInstance();
	void InitDefaultCommand();

	void AddPoint();
	void SaveToFile();
	void GetStop();
};

#endif
