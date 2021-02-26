#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

class Replica
{
private:
    MatrixXd ham;  // Hamiltonian for the replica
public:
    Replica(MatrixXd & ham_in);
    MatrixXd Ham();
    ~Replica();
};
