#include "Replica.h"
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <time.h>

using namespace Eigen;
using namespace std;

int main(int argc, char * args[]){

    //Initialization tests
    double temp = 1.0;
    const MatrixXd test_ham(2, 2);
    const string ISING = "ISING";
    const string BINARY = "BINARY";
    Replica * ising_test = new Replica(test_ham, temp, ISING);
    Replica * binary_test = new Replica(test_ham, temp, BINARY);

    assert(ising_test->ham(0, 0) == 0.0);
    cout << "Hamiltonian Initialization Passed!\n";
    assert(ising_test->state(0) == 1.0);
    cout << "State Initialization Passed!\n";
    assert(ising_test->temp == 1.0);
    cout << "Temperature Initialization Passed!\n";
    assert(ising_test->get_energy() == 0.0);
    cout <<"Energy Initialization Passed!\n";

    //Test Metropolis step
    ising_test->step(0);
    assert(ising_test->state(0) == -1.0);
    ising_test->step();
    binary_test->step(0);
    assert(binary_test->state(0) == 0.0);
    binary_test->step();
    cout << "Metropolis steps working!\n";

    //How long a 1e6 steps take
    clock_t begin = clock();
    for (size_t i = 0; i < 1000000; i++)
    {
        ising_test->step();
        binary_test->step();
    }
    clock_t end = clock();
    float time = (float(end) - float(begin))/2;
    cout << fixed;
    cout << setprecision (8);
    cout << "10^6 Metropolis Steps in " << time/CLOCKS_PER_SEC << " s\n";

    return 0;
}