#include "iter.hpp"
#include <iostream>

int main()
{
    int arr[] = {1,2,3,4,5};
    ::iter(arr, sizeof(arr) / sizeof(arr[0]), myprint);
}
