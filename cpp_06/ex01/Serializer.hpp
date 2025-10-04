#pragma once
#include <iostream>
#include <stdint.h> 
struct Data
{
    int i;
};
class Serializer
{
private:
    Serializer();
    ~Serializer();
    Serializer(const Serializer &obj);
    Serializer &operator=(const Serializer &obj);

public:
    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);
};