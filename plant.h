#ifndef PLANT_H
#define PLANT_H
#include <iostream>
#include <tuple>
#include "earth.h"
using namespace std;


class plant
{

    protected:
        string _name;
        int _level;
        //bool _alive = isAlive();
        tuple<int,int> _needRad;
        plant(const string &str, int i) :_name(str), _level(i) {}
    public:
        virtual void changeLevel(earth* theEarth) {};
        virtual bool isAlive() const {return _level>0;}
        virtual void updateNeedRad() {}
        string getName() const {return _name;}
        int getLevel() const {return _level;}
        tuple<int,int> getNeedRad() {return _needRad; }

};

class Womroot : public plant
{
public:
    bool isAlive() const override {return _level>0&&_level<=10;}
    Womroot(const string &str, int e) : plant(str,e) {}
    void changeLevel(earth* theEarth) override ;
    void updateNeedRad() override;

};
class Witroot : public plant
{
public:
    Witroot(const string &str, int e) : plant(str,e) {}
    void changeLevel(earth* theEarth) override ;
    void updateNeedRad() override;
};
class Worroot : public plant
{
public:
    Worroot(const string &str, int e) : plant(str,e) {}
    void changeLevel(earth* theEarth) override ;
    void updateNeedRad() override;
};
#endif // PLANT_H
