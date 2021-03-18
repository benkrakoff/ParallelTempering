#ifndef REPLICA_H
#define REPLICA_H
#include <iostream>
#include </home/bkrakoff/eigen/Eigen/Dense>
//#include <Eigen/Dense>

using namespace Eigen;

class Replica
{
    static const std::string ISING; // +- 1
    static const std::string BINARY; // 0 or 1
private:
    const std::string vartype; //Variable type
    double energy; //Current energy
    double lowest_energy; //Lowest energy seen by replica
    void flip(int node);
public:
    const MatrixXd ham;  // Hamiltonian for the replica
    double temp; //Temperature, this should be allowed to change
    VectorXd state; // State for the replica
    VectorXd lowest_state; //Lowest state seen by replica

    Replica(const MatrixXd &ham_in, double temp_in, const std::string &vartype);
    double get_energy();
    double get_lowest_energy();
    void step();
    void step(int node);
    ~Replica();
};

#endif