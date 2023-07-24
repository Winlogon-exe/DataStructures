#include <iostream>
#include"shared_ptr.cpp"
#include "vector.cpp"
int main()
{
    shared_ptr<int> a(new int[5]);
    vector<int> vec1 = { 1,3 };
    return 0;
}
