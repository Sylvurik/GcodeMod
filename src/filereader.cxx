#include "filereader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Dense>
#include "header.h"

using namespace std;
using namespace Eigen;

VectorXd gcodereader(string line, const string axis)
{	
	int const tableSize(axis.size());
	int i(0);

	static string* axisString = new string[tableSize]; // position actuelle: { x y z a } ( en chaîne de caractère )
	static VectorXd axisVector(tableSize - 1); // position ( en nombre a virgule )
	static VectorXd axisPVector(tableSize - 1); // ancienne valeur conserver
	int axe(tableSize - 1);

	// vider le tableau axisString
	for ( i = 0 ; i < tableSize ; i++ )
	{
		axisString[i] = "";
	}
	
	while (line.size() != 0 && line[0] != ';')// début de lecture de ligne gcode
	{
		for ( i = 0 ; i < tableSize ; i++ )
		{
			if ( line[0] == ndim[i] )
			{
				axe = i;
			}
		}
		axisString[axe] += line[0];
		line.erase(0, 1);
	}// fin de lecture de ligne

	for ( i = 0 ; i < tableSize - 1 ; i++ )
	{
		if ( axisString[i] == "" )
		{
			axisVector(i) = axisPVector(i);
		}
		else
		{
		axisVector(i) = stringtodouble(axisString[i].erase(0, 1));
		}
	}
	
	// on sauvegarde les valeurs
	for ( i = 0 ; i < tableSize - 1 ; i++ )
	{
		axisPVector(i) = axisVector(i);
	}
	return axisVector;
}

string gcodemod(VectorXd& value, string line, const string axis)
{
	int i(0);
	int axe(-1);
	string newInstruction;

	while ( line.size() != 0 && line[0] != ';' )
	{
		for ( i = 0 ; i < axis.size()-1 ; i++ )
		{
			if ( line[0] == axis[i] )
			{
				axe = i;
			}
			else if ( line[0] == ' ' )
			{
				axe = -1;
			}
		}
		if ( axe != -1 )
		{
			newInstruction += axis[axe];
			newInstruction += tostring(value(axe));
			while ( line[0] != ' ' )
			{
				line.erase(0,1);
			}
		}
		else
		{
			newInstruction += line[0];
			line.erase(0, 1);
		}
	}
	newInstruction += line;
	return newInstruction;
}

int hwmline(ifstream& inDoc)
{
	int i(0);
	string line;
	
	cout << "[ . ] détermine le nombre de ligne" << endl;

	inDoc.clear();
	inDoc.seekg(0, ios::beg); // reviens au début du fichier

	while (getline(inDoc, line)) //compte le nombre de ligne
	{
		i++;
	}

	return i;
}
