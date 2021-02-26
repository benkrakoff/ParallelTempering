#include "Replica.h"
#include <Eigen/Dense>

using namespace Eigen;

Replica::Replica(MatrixXd & ham_in)
{
    ham = ham_in;
}

Replica::~Replica()
{
}

MatrixXd Replica::Ham(){
    return ham;
}