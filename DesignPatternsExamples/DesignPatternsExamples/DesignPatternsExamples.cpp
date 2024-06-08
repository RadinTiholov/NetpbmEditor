#include <iostream>
#include "SingletonClass.h"

class Base 
{
public:
    virtual void A() const = 0;
    virtual ~Base() = default;
};

class Der1 : public Base 
{
public:
    void A() const override
    {
        std::cout << "Der1";
    }
};

class Der2 : public Base 
{
public:
    void A() const override
    {
        std::cout << "Der2";
    }
};

class BaseFactory 
{
public:
    virtual Base* create() const = 0;
    virtual ~BaseFactory() = default;
};

class Der1Factory : public BaseFactory 
{
public:
    Base* create() const override 
    {
        return new Der1();
    }
};

class Der2Factory : public BaseFactory
{
public:
    Base* create() const override
    {
        return new Der2();
    }
};

// Simple factory
BaseFactory* factoryOfFactories(bool useDer1) {
    if (useDer1) {
        return new Der1Factory();
    }
    else {
        return new Der2Factory();
    }
}

int main()
{
    /*BaseFactory* factory = factoryOfFactories(1);
    Base* der = factory->create();
    der->A();*/
    SingletonClass& ins1 = SingletonClass::getInstance(); // It needs to be reference just because if it is copy we need to construct it
    ins1.doStuff();
    SingletonClass& ins2 = SingletonClass::getInstance();
    ins2.doStuff();
}