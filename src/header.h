#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>

extern int narg;// nombre d'arguments Extra
extern std::string inFile;
extern std::string outFile;
extern std::string action;
extern std::string ndim;
extern std::string *argExtra;

void optreader(int argc, char* argv[]);
void help();
double stringtodouble(std::string& stNumber);
std::string tostring(int value);
std::string tostring(double value);
std::vector<std::string>* cutsep(std::string wstring, char const sep);
unsigned int waxis(const char& charAxis, const std::string& letters);

#endif
