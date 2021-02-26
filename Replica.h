# include <iostream>

class Replica
{
private:
    const int ham;  // Hamiltonian for the replica
public:
    Replica(const int state_in);
    const int Ham();
    ~Replica();
};
