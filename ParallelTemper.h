#include <fstream>
#include "Replica.h"


const Eigen::MatrixXd read_ham(std::ifstream & mtx_file);
Eigen::VectorXd Temper(const std::string &test_file);
