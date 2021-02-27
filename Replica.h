#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;


class Replica
{
    static const std::string ISING;
    static const std::string BINARY;
private:
    const std::string vartype;
    double energy;
    void flip(int node);
public:
    const MatrixXd ham;  // Hamiltonian for the replica
    double temp; //Temperature, this should be allowed to change
    VectorXd state; // State for the replica

    Replica(const MatrixXd &ham_in, double temp_in, const std::string &vartype);
    double get_energy();
    void step();
    void step(int node);
    ~Replica();
};
