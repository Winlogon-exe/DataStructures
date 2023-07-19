#include <iostream>
#include"shared_ptr.cpp"
void foo(int x)
{
    int buf[10];
    buf[x] = 0; 
    if (x == 1000) {}   
}

int main()
{
	shared_ptr<int> a(new int[5]);
    foo(1000);
    return 0;
	
}