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
	ReadFile();
	stopCurve = NULL;
	ReloadCurve();
}

void CatStopCalculations::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

//
// Inserter
//
std::ostream& operator<<(std::ostream& s, const DataPoint& p)
{
    return s << '(' << p.dist << ',' << p.stop << ')';
}

//
// Extractor -- assume the format produced by the inserter.
//
std::istream& operator>>(std::istream& s, DataPoint& p)
{
    // A Point must be expressed as "(x,y)" (whitespace is ignored).
    double x = 0.0f, y = 0.0f;
    char c = '\0';

    bool got_a_point = false;

    s >> c;
    if (c == '(') {
        s >> x >> c;
        if (c == ',') {
            s >> y >> c;
            if (c == ')') {
                got_a_point = true;
            }
        }
    } else {
        s.putback(c);
    }

    if (got_a_point) {
        p.dist = x;
        p.stop = y;
    } else {
        s.clear(std::ios_base::badbit);
    }

    return s;
}

void CatStopCalculations::AddPoint(double dist, double stop)
{
	//Add the point to memory
	vector_mainStorage.push_back(DataPoint(dist, stop));
	sort(vector_mainStorage.begin(), vector_mainStorage.end());
	SaveToFile();
	ReloadCurve();
}

void CatStopCalculations::ReloadCurve()
{
	//Split the vector into two seperate vectors
	vector<double> vector_distPass;
	vector<double> vector_stopPass;
	for(unsigned int iii = 0; iii<vector_mainStorage.size(); iii++)
	{
		vector_distPass.push_back(vector_mainStorage.at(iii).dist);
		vector_stopPass.push_back(vector_mainStorage.at(iii).stop);
	}

	if(vector_distPass.size() != vector_stopPass.size()) SmartDashboard::PutNumber("Test stop curve",-10);
	//Create the curve
	if(stopCurve) delete stopCurve;
	if (vector_mainStorage.size() >= 3) {
		stopCurve = new raven::cSpline(vector_distPass, vector_stopPass);
	}
}

void CatStopCalculations::SaveToFile()
{
	//Copy distance to distFilePath
	std::ofstream distFILE(FilePath, std::ofstream::trunc);
	if (distFILE.good()) {
		std::copy(
    		vector_mainStorage.begin(),
    		vector_mainStorage.end(),
			std::ostream_iterator<DataPoint>(distFILE, "\n") );
	}
}

void CatStopCalculations::ReadFile()
{
	vector_mainStorage.clear();

	//Define input files
	std::ifstream distINFILE(FilePath);

	//Read file contents into intermediary vector
	/*		std::copy(
					std::istream_iterator<DataPoint>(distINFILE),
		    		std::istream_iterator<DataPoint>(),
					vector_mainStorage.begin() ); */
	while (distINFILE.good()) {
		DataPoint d;
		distINFILE >> d;
		vector_mainStorage.push_back(d);
		while (distINFILE.good()) {
			char c;
			distINFILE >> c;
			if (c == '(') {
				distINFILE.putback(c);
				break;
			}
		}
	}
	sort(vector_mainStorage.begin(), vector_mainStorage.end());
	ReloadCurve();
}

double CatStopCalculations::GetStop(double dist)
{
	//sanity check
	if(stopCurve and stopCurve->IsSane()) {
		return stopCurve->getY(dist);
	}
	return -1;
}

void CatStopCalculations::WipeSave()
{
	//Erase the values of the vectors
	vector_mainStorage.clear();
	vector_mainStorage.push_back(DataPoint(0,6.66));
	vector_mainStorage.push_back(DataPoint(1000,20));
	SaveToFile();
}
