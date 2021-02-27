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
public:
    Replica(const MatrixXd &ham_in, const std::string &vartype);
    const MatrixXd ham;  // Hamiltonian for the replica
    VectorXd state; // State for the replica
    double get_energy();
    void step();
    void step(int node);
    ~Replica();
};
