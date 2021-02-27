#include "Replica.h"
#include <Eigen/Dense>
#include <stdlib.h>

using namespace Eigen;

const std::string Replica::ISING = "ISING";
const std::string Replica::BINARY = "BINARY";

Replica::Replica(const MatrixXd &ham_in, const std::string &vartype_in) :ham{ham_in}, vartype{vartype_in}
{
    state = VectorXd::Constant(ham_in.rows(), 1.0);
    energy = state.dot(ham*state);
}

double Replica::get_energy(){
    return energy;
}

void Replica::step(int node){
    if(vartype.compare(ISING) == 0){
        state(node) = -1*state(node);
    } else {
        state(node) = 1.0-state(node);
    }
    // TO DO: OPTIMIZE THIS STEP
    energy = state.dot(ham*state);
}

void Replica::step(){
    int node = rand() % state.size();
    step(node);
}

Replica::~Replica()
{
}