#include <iostream>
#include"shared_ptr.cpp"
int main()
{
    shared_ptr<int> a(new int[5]);
    return 0;
}
