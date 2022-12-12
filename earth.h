#ifndef EARTH_H
#define EARTH_H
#pragma once

class earth
{
    public:
        int getTypeInd() const {return _typeInd;}
        virtual bool isNonRad() const {return false;}
        earth* changeEarthRad(int a,int d);
        virtual ~earth() {}

    protected:
        int _typeInd;
        earth(int i) : _typeInd(i){}

};

class Alpha : public earth
{
public:
    static Alpha* getInstance();
    static void destory();
private:
    Alpha(): earth(1){}
    static Alpha* _instance;

};
class Delta : public earth
{
public:
    static Delta* getInstance();
    static void destory();
private:
    Delta(): earth(2){}
    static Delta* _instance;
};
class NonRad : public earth
{
public:
    static NonRad* getInstance();
    static void destory();
    bool isNonRad() const override {return true;}
private:
    NonRad(): earth(0){}
    static NonRad* _instance;

};

#endif // EARTH_H
