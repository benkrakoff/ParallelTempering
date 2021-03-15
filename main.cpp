#include "Replica.h"
#include <fstream>

const Eigen::MatrixXd read_ham(std::istream & mtx_file);

int main(int argc, char * args[]){
    if (argc < 2){
        std::cout << "Need .mtx file argument";
        return 0;
    }

    // Read in mtx file
    std::ifstream mtx_file;
    mtx_file.open(args[1]); 
    const Eigen::MatrixXd ham = read_ham(mtx_file);
    std::cout << ham;
    return 0;
    // Parallel temper, recording swaps
    // Save lowest energy state

}

const Eigen::MatrixXd read_ham (std::ifstream & mtx_file){
    while(mtx_file.peek() == '%'){
        mtx_file.ignore(2048, '\n');
    }
    int rows, cols, entries;
    mtx_file >> rows >> cols >> entries;

    MatrixXd ham(rows, cols);

    while(mtx_file.peek() != EOF){
        int i, j;
        double data;
        mtx_file >> i >> j >> data;
        ham(i, j) = data;
    }

    return ham;
}