#ifndef STATEVECTOR_H
#define STATEVECTOR_H
#include <vector>
#include <string>


class StateVector
{
    public:
        StateVector(int initVal, int length);
        virtual ~StateVector();
        void updateVector(StateVector assignment, std::vector<int> cap);
        std::vector<int>* getSV();
        void toString();
        bool isLessThan(StateVector other);
    protected:
    private:
        std::vector<int> sv;
};

#endif // STATEVECTOR_H
