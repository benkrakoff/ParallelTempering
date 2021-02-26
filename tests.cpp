#include "Replica.h"
#include <iostream>
#include <assert.h>

using namespace Eigen;
using namespace std;

int main(int argc, char * args[]){

    //Test
    MatrixXd test_ham(2, 2);
    Replica * Test = new Replica(test_ham);
    assert(Test->Ham()(0, 0) == 0.0);
    cout << "Initialization passed!\n";

    //Test

    return 0;
}