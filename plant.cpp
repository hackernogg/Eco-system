#include "plant.h"

void Womroot::changeLevel(earth* theEarth)
{
    if(theEarth->getTypeInd()==1){
        _level = _level + 2;
    }
    if(theEarth->getTypeInd()==2){
        _level = _level - 2;
    }

    if(theEarth->getTypeInd()==0){
        _level = _level - 1;
    }
}

void Witroot::changeLevel(earth* theEarth)
{
    if(theEarth->getTypeInd()==1){
        _level = _level - 3;
    }
    if(theEarth->getTypeInd()==2){
        _level = _level + 4;
    }

    if(theEarth->getTypeInd()==0){
        _level = _level - 1;
    }
}

void Worroot::changeLevel(earth* theEarth)
{
    if(theEarth->getTypeInd()==1){
        _level = _level + 1;
    }
    if(theEarth->getTypeInd()==2){
        _level = _level + 1;
    }

    if(theEarth->getTypeInd()==0){
        _level = _level - 1;
    }
}
//----------------------------
void Womroot::updateNeedRad()
{
    if(_level>0 && _level<=10)
    {
        _needRad = make_tuple(10,0);
    }
    else
    {
        _needRad = make_tuple(0,0);
    }

}

void Witroot::updateNeedRad()
{
    if(_level>0 && _level<5)
    {
        _needRad = make_tuple(0,4);
    }
    else if(_level>=5 && _level<=10)
    {
        _needRad = make_tuple(0,1);
    }
    else if(_level>10)
    {
        _needRad = make_tuple(0,0);
    }
    else
    {
        _needRad = make_tuple(0,0);
    }
}

void Worroot::updateNeedRad()
{
    _needRad = make_tuple(0,0);
}
