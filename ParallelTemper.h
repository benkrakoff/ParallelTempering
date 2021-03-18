#include <fstream>
#include <thread>
#include "Replica.h"


const Eigen::MatrixXd read_ham(std::ifstream & mtx_file);
void TemperReplica(Replica *replica);
Eigen::VectorXd Temper(const std::string & test_file, const std::string &vartype, const int num_replicas, const double temps[]);
