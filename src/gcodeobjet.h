/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gcodeobjet.h
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

#ifndef _GCODEOBJET_H_
#define _GCODEOBJET_H_

#include <vector>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <string>

class Gcodeobjet
{
public:
	 Gcodeobjet();
	 Gcodeobjet(std::ifstream& file, std::string letters);
	 void load(std::ifstream& file, std::string letters);// charge un fichier gcode
	 void save(std::ofstream& file);
	 void base(Eigen::MatrixXd& matrix);
	 void move(double const value);
	 void move(int const value);
	 void move(Eigen::VectorXd& vector);
	 void clearance(double value[]);
	 void toinch();
	 void tomm();
	 double max(int axe) const;
	 double min(int axe) const;
	 // accesseurs //
	 unsigned int haxis() const;
	 unsigned int hline() const;
	 std::vector<Eigen::VectorXd>* getTable();
	 std::string getLetters() const;

protected:

private:
	 std::vector<Eigen::VectorXd> position;// tableau avec toutes les coordonnées
	 unsigned int naxis;
	 unsigned int nline;
	 std::ifstream *path;
	 std::string axis;

};

#endif // _GCODEOBJET_H_

