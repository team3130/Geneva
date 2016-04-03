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

struct DataPoint
{
    double dist;
    double stop;

    DataPoint() : dist(0.0f), stop(0.0f) { }
    DataPoint(double x, double y) : dist(x), stop(y) { }

    // Compiler supplies copy-constructor and assignment operator.

    // So we can sort Data Points in a std::vector.
    bool operator<(const DataPoint& other) const {
        return ((dist < other.dist) || (!(other.dist < dist) && stop < other.stop));
    }
};

class CatStopCalculations: public Subsystem
{
private:
	static CatStopCalculations* m_pInstance;
	vector<DataPoint> vector_mainStorage;

	const string FilePath = "/home/lvuser/catapult-storage.ini";

	raven::cSpline* stopCurve;

	CatStopCalculations();
	CatStopCalculations& operator=(CatStopCalculations const&);
public:
	static CatStopCalculations* GetInstance();
	void InitDefaultCommand();

	void AddPoint(double dist, double stop);
	void ReloadCurve();
	void SaveToFile();
	vector<DataPoint> ReadFile();
	void WipeSave();
	double GetStop(double dist);
};

#endif
