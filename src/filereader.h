#ifndef FILEREADER_H_INCLUDED
#define FILEREADER_H_INCLUDED

#include <string>
#include <fstream>
#include <eigen3/Eigen/Dense>

Eigen::VectorXd gcodereader(std::string line, const std::string axis);
std::string gcodemod(Eigen::VectorXd& value, std::string line, const std::string axis);
int hwmline(std::ifstream& inDoc);

#endif
