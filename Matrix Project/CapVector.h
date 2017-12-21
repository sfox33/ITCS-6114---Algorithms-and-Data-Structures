#ifndef CAPVECTOR_H
#define CAPVECTOR_H
#include <vector>
#include "StateVector.h"
#include <string>


class CapVector
{
    public:
        CapVector();
        CapVector(StateVector input);
        virtual ~CapVector();
        std::vector<int>* getCV();
        std::vector<int>* getBlockValues();
        void toString();
    protected:
    private:
        std::vector<int> cv;
        std::vector<int> blockValues;
};

#endif // CAPVECTOR_H
