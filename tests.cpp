#include "Replica.h"
#include <iostream>
#include <assert.h>

using namespace Eigen;
using namespace std;

int main(int argc, char * args[]){

    //Initialization tests
    const MatrixXd test_ham(2, 2);
    const string ISING = "ISING";
    const string BINARY = "BINARY";
    Replica * ising_test = new Replica(test_ham, ISING);
    Replica * binary_test = new Replica(test_ham, BINARY);

    assert(ising_test->ham(0, 0) == 0.0);
    cout << "Hamiltonian Initialization Passed!\n";
    assert(ising_test->state(0) == 1.0);
    cout << "State Initialization Passed!\n";
    assert(ising_test->get_energy() == 0.0);
    cout <<"Energy Initialization Passed!\n";

    //Test Metropolis step
    ising_test->step(0);
    assert(ising_test->state(0) == -1.0);
    ising_test->step();
    binary_test->step(0);
    assert(binary_test->state(0) == 0.0);
    binary_test->step(0);
    cout << "Metropolis steps working!\n";

    return 0;
}