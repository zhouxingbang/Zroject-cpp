// ztest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "CReflectTest.h"

int main()
{
    CReflectTest* test = REFLECT::Ref_DynCreate_Object<CReflectTest>(L"ReflectTest");
    test->print();
    std::cin.get();
    std::cout << "Hello World!\n";
}
