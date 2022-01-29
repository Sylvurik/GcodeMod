/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2020 sylvain <sylvain@debian>
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <eigen3/Eigen/Dense>
#include "mcode.h"
#include "filereader.h"
#include "header.h"
#include "gcodeobjet.h"
#include "irrlicht_function.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
	string line;

	optreader(argc, argv);

	ifstream inDoc(inFile.c_str());
	ofstream outDoc(outFile.c_str(), ios::app);

	if (inDoc) // test le document
	{
		cout << "[ . ] Chargement du .gcode" << endl;
		Gcodeobjet model(inDoc, ndim);

		if (action == "mcode") // action: mcode
		{
			cout << "[ a ] modification du GCODE" << endl;
			for ( int i(0); i<model.hline(); i++)
			{
				getline(inDoc, line);// récupère la ligne
				outDoc << mcode(gcodereader (line, model.getLetters()), model.getLetters());
				outDoc << line << endl;
			}
		}
		else if (action == "changebase")// action: changebase
		{
			int n(0), j(0);
			unsigned int const mdim(model.haxis());
			Eigen::MatrixXd matrixT(mdim, mdim);
			vector<string>* vecD = NULL;

			cout << "[ . ] création de la matrice" << endl;
			for ( int i(0) ; i < mdim ; i++ )// rempli la matrice matrixT
			{
				j = waxis(argExtra[i][0], model.getLetters());// quel chiffre pour quel lettre ??
				vecD = cutsep(argExtra[i].erase(0, 1), ',');// fonction qui renvoie un pointer de tableau
				for ( n = 0 ; n < mdim ;  n++ )
				{
					matrixT(n, j) = stringtodouble(vecD->at(n));
				}
			}// fin du remplissage matrixT

			cout << "[ a ] changement de base" << endl;
			model.base (matrixT);
			cout << "[ s ] création du nouveau .gcode" << endl;
			model.save (outDoc);
		}
		else if (action == "translation")// action: translation
		{
			Eigen::VectorXd vector(model.haxis ());
			
			if ( sizeof(*argExtra) != model.haxis ())
			{
				cout << "[ ! ] Erreur" << endl;
				cout << "[ . ] Pas assez d'arguments" << endl;
				return 1;
			}
			for ( int i(0) ; i < model.haxis () ; i++ )
			{
				vector(i) = stringtodouble (argExtra[i]);
			}
			cout << "[ a ] translation" << endl;
			model.move (vector);
			cout << "[ s ] création du nouveau .gcode" << endl;
			model.save (outDoc);
		}
		else if (action == "inchtomm")// action: intomm
		{
			cout << "[ a ] convert inch to milimeter" << endl;
			model.tomm ();
			cout << "[ s ] création du nouveau .gcode" << endl;
			model.save (outDoc);
		}
		else if (action == "mmtoinch")// action: mmtoin
		{
			cout << "[ a ] convert milimeter to inch" << endl;
			model.toinch ();
			cout << "[ s ] création du nouveau .gcode" << endl;
			model.save (outDoc);
		}
		else if (action == "clearance")// action: clearance
		{
			double value[model.haxis()];
			VectorXd vector(model.haxis());
			
			if ( sizeof(*argExtra) != model.haxis ())
			{
				cout << "[ ! ] Erreur" << endl;
				cout << "[ . ] Pas assez arguments" << endl;
				return 1;
			}
			for ( int i (0) ; i<model.haxis() ; i++ )
			{
				value[i] = stringtodouble (argExtra[i]);
				vector(i) = value[i];
			}
			cout << "[ a ] compensation du jeu mécanique" << endl;
			model.clearance (value);
			cout << "[ . ] translation" << endl;
			model.move (vector);
			cout << "[ s ] création du nouveau .gcode" << endl;
			model.save (outDoc);
		}
		else if (action == "max")
		{
			cout << "[ a ] maximum" << endl;
			for ( int i(0) ; i < model.haxis() ; i++ )
			{
				cout << "[ " << model.getLetters()[i] << " ] " << model.max (i) << endl;
			}
		}
		else if (action == "min")
		{
			cout << "[ a ] minimum" << endl;
			for ( int i(0) ; i < model.haxis () ; i++ )
			{
				cout << "[ " << model.getLetters()[i] << " ] " << model.min (i) << endl;
			}
		}
		else if (action == "view")
		{
			render(&model);
		}

	}	
	else
	{
		cout << endl << "[ ! ] Pas de fichier d'entrée, FIN" << endl;
		cout << "[ i ] faite -h pour voir l'aide" << endl;
	}
	return 0;
}



