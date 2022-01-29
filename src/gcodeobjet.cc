/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gcodeobjet.cc
 * Copyright (C) 2021 sylvain <sylvain@debian>
 *
 * gcode is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gcode is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <eigen3/Eigen/Dense>
#include "gcodeobjet.h"
#include "header.h"
#include "filereader.h"

using namespace std;

Gcodeobjet::Gcodeobjet()
{
	naxis = ndim.size() - 1;
	nline = 0;
	path = NULL;
}

Gcodeobjet::Gcodeobjet(ifstream& file, string letters)
{
	naxis = ndim.size() - 1;
	load(file, letters);
	
}

void Gcodeobjet::load(ifstream& file, string letters)
{
	string line;
	path = &file;
	axis = letters;
	nline = hwmline(*path);
	position.clear();
	
	path->clear();
	path->seekg(0, ios::beg); // reviens au début du fichier

	while (getline(*path, line))
	{
		position.push_back(gcodereader (line, axis));
	}
}

void Gcodeobjet::save(ofstream& file)
{
	path->clear();
	path->seekg(0, ios::beg);

	string line;
	
	for ( int i(0) ; i<nline ; i++ )
	{
		getline(*path, line);
		file << gcodemod (position[i], line, axis) << endl;
	}
}

void Gcodeobjet::base(Eigen::MatrixXd& matrix)
{
	Eigen::MatrixXd revMatrix = matrix.inverse ();
	for ( int i (0) ; i<nline ; i++ )
	{
		position[i] = revMatrix * position[i];
	}
}

void Gcodeobjet::move(double const value)
{
	for ( int i (0) ; i<nline ; i++ )
	{
		for (int a(0) ; i < naxis ; i++)
		{
			position[i](a) += value ;
		}
	}
}

void Gcodeobjet::move(int const value)
{
	for ( int i (0) ; i<nline ; i++ )
	{
		for (int a(0) ; i < naxis ; i++)
		{
			position[i](a) += value ;
		}
	}
}

void Gcodeobjet::move(Eigen::VectorXd& vector)
{
	for ( int i (0) ; i<nline ; i++ )
	{
		position[i] += vector;
	}
}

void Gcodeobjet::clearance(double value[])
{
	Eigen::VectorXd delta(naxis);
	Eigen::VectorXd corr(naxis);

	for ( int i (0) ; i<nline - 1 ; i++ )
	{
		delta = position[i+1] - position[i];
		for ( int n (0) ; n<naxis ; n++ )
		{
			if ( delta(n) < 0 )
			{
				corr(n) = value[n] * -1;
			}
			else if ( delta(n) > 0 )
			{
				corr(n) = value[n];
			}
			else
			{
				corr(n) = 0;
			}
		}
		position[i+1] += corr;
	}
}

void Gcodeobjet::toinch()
{
	for ( int i (0) ; i<nline ; i++ )
	{
		position[i] *= 0.039370;
	}
}

void Gcodeobjet::tomm()
{
	for ( int i (0) ; i<nline ; i++ )
	{
		position[i] *= 25.4;
	}
}

double Gcodeobjet::max(int axe) const
{
	const int intAxe(axe);
	double maxValue(position[0](intAxe));
	for ( int i (0) ; i<nline ; i++ )
	{
		if ( position[i](intAxe) > maxValue )
		{
			maxValue = position[i](intAxe);
		}
	}
	return maxValue;
}

double Gcodeobjet::min(int axe) const
{
	const int intAxe(axe);
	double minValue(position[0](intAxe));
	for ( int i (0) ; i<nline ; i++ )
	{
		if ( position[i](intAxe) < minValue )
		{
			minValue = position[i](intAxe);
		}
	}
	return minValue;
}

// accesseurs
unsigned int Gcodeobjet::haxis() const
{
	return naxis;
}

unsigned int Gcodeobjet::hline() const
{
	return nline;
}

vector<Eigen::VectorXd>* Gcodeobjet::getTable()
{
	return &position;
}

string Gcodeobjet::getLetters() const
{
	return axis;
}

