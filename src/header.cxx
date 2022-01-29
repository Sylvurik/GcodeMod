#include "header.h"
#include <string>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int narg(0);
string inFile;
string outFile;
string ndim("XYZ "); // l'espace est important !!
string action;
string* argExtra  = NULL;

void optreader(int argc, char *argv[])
{
	int option(0);

	while ((option = getopt(argc, argv, ":i:o:d:a:hv")) != -1)
	{
		switch (option)
		{
			case 'i': inFile = optarg; break;
			case 'o': outFile = optarg; break;
			case 'd': ndim = optarg; ndim += ' '; break;
			case 'a': action = optarg; break;
			case 'h': help(); break;
			case 'v': cout << "version : 0.4" << endl; break;
		}
	}
	argExtra = new string[argc - optind];
	narg = argc - optind;

	for ( int i(0) ; optind + i < argc ; i++)
	{
		argExtra[i] = argv[optind+i];
	}
}

double stringtodouble(string& stNumber)
{
	double dblNumber(0);
	stringstream changetype(stNumber);
	changetype >> dblNumber;
	return dblNumber;
}

string tostring(int value)
{
	string String = static_cast<ostringstream*>( &(ostringstream() << value) )->str();
	return String;
}

string tostring(double value)
{
	string String = static_cast<ostringstream*>( &(ostringstream() << value) )->str();
	return String;
}

vector<string>* cutsep(string wstring, char const sep)
{
	string temp("");
	vector<string>* table = new vector<string>(0, "");
	
	while ( wstring.size() != 0 )
	{
		if ( wstring[0] == sep )
		{
			table->push_back(temp);
			temp = "" ;
		}
		else
		{
			temp += wstring[0];
		}
		wstring.erase(0, 1);
	}
	return table;
}

unsigned int waxis(const char& charAxis, const string& letters)
{
	unsigned int n(letters.size() - 1); 
	for ( int i(0) ; i < n ; i++ )
	{
		if ( letters[i] == charAxis )
		{
			n = i;
		}
	}
	return n;
}

void help()
{
	cout << "help : gcode -[iodhv] -a [ ACTION ]" << endl;
	cout << "-i		chemin du fichier .gcode d'entrée" << endl;
	cout << "-o		chemin du fichier .gcode de sortie" << endl;
	cout << "-d		choisir le nombre d'axe de direction ( mettre les lettres )" << endl;
	cout << "-h		afficher ce message" << endl;
	cout << "-v		version du programme" << endl;
	cout << endl;
	cout << "infos supplémentaires : [ -d ] et  [ -a ]" << endl;
	cout << "[ -d ] par défault les axes sont XYZ(3 axes)" << endl;
	cout << "		ex : -d XYZA (4 axes) <-- différent de -d YAZX" << endl;
	cout << "		la place de chaques lettres à une importance" << endl;
	cout << "		chaques lettres doit être les coordonnées dans le .gcode" << endl;
	cout << endl;
	cout << "[ -a ] [ ACTION ]={ mcode | changebase | inchtomm | mmtoinch | ... }" << endl;
	cout << endl;
	cout << "		[ mcode ] : pas de paramètre particulier" << endl;
	cout << "		ajoute des M64 et M65 pour activer/désactiver les moteurs (LinuxCNC)" << endl;
	cout << "		-d change le comportement de l'action" << endl;
	cout << endl;
	cout << "		[ changebase ] : effectue un changement de base" << endl;
	cout << "		ex: -a changebase XCx,Cy,Cz, YCx2,Cy2,Cz2(,)<-- ne pas l'oublier ..." << endl;
	cout << "		X et Y sont les vecteurs directeurs de la base" << endl;
	cout << "		X Y sont dans le -d on peut les renommés en A B" << endl;
	cout << endl;
	cout << "		[ inchtomm ] : convertis les inchs en milimètres" << endl;
	cout << endl;
	cout << "		[ mmtoinch ] : convertis les milimètres en inch" << endl;
	cout << endl;
	cout << "		[ translation ]: effectue une translation" << endl;
	cout << "		-d YAZX -a translation Y A Z X" << endl;
	cout << endl;
	cout << "		[ clearance ] : compense les jeux mécanique" << endl;
	cout << "		-d XYZA -a clearance X Y Z A" << endl;
	cout << "		-d YZ -a clearance Y Z" << endl;
	cout << endl;
	cout << "		[ view ] : visualiser un fichier .gcode" << endl;
	cout << endl;
	cout << "Exemples:" << endl;
	cout << "gcode -i <path1> -o <path2> -a mcode" << endl;
	cout << "gcode -i <path1> -o <path2> -d XYZA -a mcode" << endl;
	cout << "gcode -i <path1> -o <path2> -a changebase X~,~,~, Y~,~,~, Z~,~,~," << endl;
	cout << "gcode -i <path1> -o <path2> -d XY -a changebase X~,~, Y~,~," << endl;
}
