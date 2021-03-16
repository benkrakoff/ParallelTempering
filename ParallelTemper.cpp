#include "ParallelTemper.h"

Eigen::VectorXd Temper(const std::string & test_file){
    // Read in mtx file
    std::ifstream mtx_file;
    mtx_file.open(test_file); 
    const Eigen::MatrixXd ham = read_ham(mtx_file);
    return ham.col(0);
    // Parallel temper, recording swaps
    // Save lowest energy state

}

const Eigen::MatrixXd read_ham(std::ifstream & mtx_file){
    while(mtx_file.peek() == '%'){
        mtx_file.ignore(2048, '\n');
    }
    int rows, cols, entries;
    mtx_file >> rows >> cols >> entries;

    Eigen::MatrixXd ham(rows, cols);

    while(mtx_file.peek() != EOF){
        int i, j;
        double data;
        mtx_file >> i >> j >> data;
        //.mtx files indexing starts from 1
        ham(i-1, j-1) = data;
    }
    return ham;
}