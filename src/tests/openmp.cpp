#include <iostream>
#include <omp.h>

int main()
{
#pragma omp parallel
    {
        std::cout << "Calculation from : " << omp_get_thread_num() << "\n";
    }
    return 0;
}