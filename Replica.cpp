#include "Replica.h"

using namespace Eigen;

const std::string Replica::ISING = "ISING";
const std::string Replica::BINARY = "BINARY";

Replica::Replica(const MatrixXd &ham_in, double temp_in, const std::string &vartype_in) : vartype{vartype_in}, ham{ham_in}, temp{temp_in}
{
    state = VectorXd::Constant(ham_in.rows(), 1.0);
    lowest_state = state;
    energy = state.dot(ham*state);
    lowest_energy = energy;
}

double Replica::get_energy(){
    return energy;
}

double Replica::get_lowest_energy(){
    return lowest_energy;
}

void Replica::flip(int node){
    if(vartype.compare(ISING) == 0){
        state(node) = -1.0*state(node);
    } else {
        state(node) = 1.0-state(node);
    }
}

void Replica::step(int node){
    flip(node);
    // TO DO: OPTIMIZE THIS STEP
    double new_energy = state.dot(ham*state);

    //Record state if energy is lower
    if (new_energy < lowest_energy){
        lowest_state = state;
    }

    //Metropolis step
    if (rand() / double(RAND_MAX) < exp((energy - new_energy)/temp)){
        energy = new_energy;
    } else {
        flip(node);
    }
}

void Replica::step(){
    int node = rand() % state.size();
    step(node);
}

Replica::~Replica()
{
}