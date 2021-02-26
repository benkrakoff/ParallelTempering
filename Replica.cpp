#include "Replica.h"

Replica::Replica(const int ham_in) : ham{ham_in}
{
}

Replica::~Replica()
{
}

const int Replica::Ham(){
    return ham;
}