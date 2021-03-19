#include "ParallelTemper.h"

Eigen::VectorXd Temper(const std::string & test_file, const std::string &vartype, const int num_replicas, const double temps[]){
    // Read in mtx file
    std::ifstream mtx_file;
    mtx_file.open(test_file); 
    const Eigen::MatrixXd ham = read_ham(mtx_file);
    mtx_file.close();

    //Initialize replicas at stated temperatures
    Replica * replica[num_replicas];
    for (int i = 0; i < num_replicas; i++)
    {
        replica[i] = new Replica(ham, temps[i], vartype);
    }
    
    // Parallel temper, recording swaps
    int steps = replica[0]->ham.rows();
    for (int i = 0; i < steps; i++)
    {   
        std::vector<std::thread> threads;
        //Initialize threads
        for (int j = 0; j < num_replicas; j++)
        {
            threads.push_back(std::thread(TemperReplica, replica[j]));
        }
        //Wait to finish
        std::for_each(threads.begin(), threads.end(), [](std::thread &t) 
        {
            t.join();
        });

        //Metropolis swap step
        int swap = rand() % (num_replicas-1);
        double temp_diff = 1.0/replica[swap]->temp - 1.0/replica[swap+1]->temp;
        double energy_diff = replica[swap+1]->get_energy() - replica[swap]->get_energy();
        double probability = exp(temp_diff*energy_diff);
        if (rand() / double(RAND_MAX) < probability){
            Replica * temp = replica[swap];
            replica[swap] = replica[swap+1];
            replica[swap+1] = temp;
        }
    }
    
    // Save lowest energy state, delete replicas
    double lowest_energy = replica[0]->get_lowest_energy();
    Eigen::VectorXd lowest_state = replica[0]->lowest_state;
    for (int i = 0; i < num_replicas; i++)
    {
        if (replica[i]->get_lowest_energy() < lowest_energy){
            lowest_energy = replica[i]->get_lowest_energy();
            lowest_state = replica[i]->lowest_state;
        }
        delete replica[i];
    }
    return lowest_state;
}

void TemperReplica(Replica * replica){
    int steps = replica->ham.rows();
    for (int i = 0; i < steps; i++)
    {
        replica->step();
    }
}

const Eigen::MatrixXd read_ham(std::ifstream & mtx_file){
    while(mtx_file.peek() == '%'){
        mtx_file.ignore(2048, '\n');
    }
    int rows, cols, entries;
    mtx_file >> rows >> cols >> entries;

    Eigen::MatrixXd ham(rows, cols);
    ham = MatrixXd::Zero(rows, cols);

    while(mtx_file.peek() != EOF){
        int i, j;
        double data;
        mtx_file >> i >> j >> data;
        //.mtx files indexing starts from 1
        ham(i-1, j-1) = data;
    }
    return ham;
}