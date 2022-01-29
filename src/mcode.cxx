#include <string>
#include <eigen3/Eigen/Dense>
#include "mcode.h"
#include "header.h"

using namespace std;
using namespace Eigen;


string mcode( VectorXd axis, const string letters )
{
	int const sizeTable(letters.size() - 1);

	static VectorXd pvalueAxis(sizeTable);
	static bool* boolAxis = new bool[sizeTable];

	string ngc;
	
	for (int i(0); i<sizeTable ; i++)
	{
		if (axis(i) == pvalueAxis(i))
		{
			if (boolAxis[i])
			{
				ngc += string("M65 P")+tostring(i)+'\n';
			}
			boolAxis[i] = false; // désactive le moteur
		}
		if (axis(i) != pvalueAxis(i))
		{
			if (!boolAxis[i])
			{
				ngc += string("M64 P")+tostring(i)+'\n';
			}
			boolAxis[i] = true; // active le moteur
			pvalueAxis(i) = axis(i);
		}
	}
	return ngc;
}
