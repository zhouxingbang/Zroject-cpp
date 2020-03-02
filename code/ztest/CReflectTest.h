#pragma once
#include "zkernel/reflect.h"
#include <iostream>

class CReflectTest : public REFLECT::IReflectObject
{
    REF_DECLARE_DYNCREATE(CReflectTest);
public:
    CReflectTest();
    ~CReflectTest();

    void print()
    {
        std::cout << "i'm is CReflectTest" << std::endl;
    }
};

