#include <cstdlib>
#include "earth.h"


Alpha* Alpha::_instance = nullptr;

Alpha* Alpha::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Alpha();
    }
    return _instance;
}

void Alpha::destory()
{
    if (_instance != nullptr )
    {
        delete _instance;
    }
    _instance = nullptr;
}
//------------------
Delta* Delta::_instance = nullptr;

Delta* Delta::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Delta();
    }
    return _instance;
}

void Delta::destory()
{
    if (_instance != nullptr )
    {
        delete _instance;
    }
    _instance = nullptr;
}
//-----------------------------
NonRad* NonRad::_instance = nullptr;

NonRad* NonRad::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new NonRad();
    }
    return _instance;
}

void NonRad::destory()
{
    if (_instance != nullptr )
    {
        delete _instance;
    }
    _instance = nullptr;
}
//---------------------------
earth* earth::changeEarthRad(int a,int d)
{
    if(a-d>=3)
    {
        return Alpha::getInstance();
    }
    if(d-a>=3)
    {
        return Delta::getInstance();
    }
    if(abs(a-d)<3)
    {
        return NonRad::getInstance();
    }
}
