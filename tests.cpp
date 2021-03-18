#include "ParallelTemper.h"
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
    MatrixXd test_ham(2, 2);
    test_ham = MatrixXd::Zero(2, 2);
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
    
    //Test lowest state and energy recording
    MatrixXd test_low(2, 2);
    test_low << 0, 1, 1, 0;
    Replica * ising_low = new Replica(test_low, 1, "ISING");
    ising_low->step(0);
    assert(ising_low->lowest_state(0) == -1.0);
    cout << "Lowest state being tracked!\n";
    delete ising_low;

    //How long a 1e4 steps take
    clock_t begin = clock();
    for (size_t i = 0; i < 10000; i++)
    {
        ising_test->step();
        binary_test->step();
    }
    clock_t end = clock();
    float time = (float(end) - float(begin))/2;
    cout << fixed;
    cout << setprecision (8);
    cout << "10^4 Metropolis Steps in " << time/CLOCKS_PER_SEC << " s\n";
    delete ising_test;
    delete binary_test;

    //Testing ParallelTemper
    const std::string test_file("test_ham.mtx");
    double temps[10];
    for (size_t i = 0; i < 10; i++)
    {
        temps[i] = (i+1)/10.0;
    }
    VectorXd state = Temper(test_file, ISING, 10, temps);
    cout << "ParallelTemper Running!\n";
    return 0;
}