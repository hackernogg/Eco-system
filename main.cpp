#include <iostream>
#include <fstream>
#include <vector>

#include "plant.h"

using namespace std;

int plantsToInt(string str)
{
    if(str=="wom") return 1;
    if(str=="wit") return 2;
    if(str=="wor") return 3;
}

string intToRad(int i)
{
    string rad;
    switch(i)
    {
        case 1: rad = "Alpha"; break;
        case 2: rad ="Delta"; break;
        case 0: rad ="Non-Radiation"; break;
    }
    return rad;
}

void create(const string &str, vector<plant*> &plantsList)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}
    int pNum;
    f >> pNum;

    plantsList.resize(pNum);
    for(int i =0; i<pNum;++i)
    {
        string name;
        string type;
        int level;
        f >> name >> type >> level;
        switch(plantsToInt(type)){
            case 1 : plantsList[i] = new Womroot(name,level); break;
            case 2 : plantsList[i] = new Witroot(name,level); break;
            case 3 : plantsList[i] = new Worroot(name,level); break;
        }
    }
}

void simTill2NonRad(vector<plant*> &plantsList)
{
    earth* SimEarth = NonRad::getInstance();
    bool NonRadOne = false;
    bool NonRadTwo = false;

    cout <<"Start Simulate : D "<<endl;

    int day = 0;

    for(;NonRadOne == false || NonRadTwo == false;)
    {
        cout <<endl;
        cout << "day : "<<day<<" Earth Rad type: "<<intToRad(SimEarth->getTypeInd())<<endl;
        cout <<endl;
        int needA = 0;
        int needD = 0;
        NonRadOne = SimEarth->isNonRad();
        for(int i = 0; i <plantsList.size();++i)
        {
            if(plantsList[i]->isAlive())
            {
                plantsList[i]->updateNeedRad();
                tuple<int,int> needRadAD = plantsList[i]->getNeedRad();
                cout <<plantsList[i]->getName()<<" ";
                cout <<plantsList[i]->getLevel()<<" ";
                cout <<"need Alpha: "<<get<0>(needRadAD)<<" "<<"need Delta: "<<get<1>(needRadAD);
                needA = needA+get<0>(needRadAD);
                needD = needD+get<1>(needRadAD);
                plantsList[i]->changeLevel(SimEarth);
            }
            else
            {
                cout <<plantsList[i]->getName()<<" ";
                cout <<plantsList[i]->getLevel()<<" ";
                cout << "dead";
            }
            cout << endl;
        }
        cout<< "Total need Alpha :" << needA <<" Total need Delta :" << needD <<endl;
        cout <<"______________________________________" <<endl;

        SimEarth=SimEarth->changeEarthRad(needA,needD);
        NonRadTwo = SimEarth->isNonRad();
        day++;
    }

}
void destoryEarth()
{
    Alpha::destory();
    Delta::destory();
    NonRad::destory();
}
#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{

    vector <plant*> plantsList;
    create("input.txt",plantsList);
    simTill2NonRad(plantsList);
    plantsList.~vector();
    destoryEarth();
    return 0;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// test make plants

TEST_CASE("make Plant","[Plant]")
{
        //check if the name are Right
        plant* testPlantWom = new Womroot("testPlantWom",5);
        CHECK (testPlantWom->getName() == "testPlantWom");

        plant* testPlantWit = new Witroot("testPlantWit",5);
        CHECK (testPlantWit->getName() == "testPlantWit");
        //check if the Level are Right
        plant* testPlantWor = new Womroot("testPlantWor",4);
        CHECK (testPlantWor->getLevel() == 4);

        CHECK (testPlantWit->getLevel() == 5);

}

TEST_CASE("Plant methods","[Plant]")
{
        //Check isAlive method
        earth* AlphaEarth = Alpha::getInstance();
        earth* DeltaEarth = Delta::getInstance();
        plant* testPlantWom = new Womroot("testPlantWom",9);
        CHECK (testPlantWom->isAlive() == true );
        //Check changeLevel method
        testPlantWom->changeLevel(AlphaEarth);
        CHECK (testPlantWom->getLevel() == 11 );
        CHECK (testPlantWom->isAlive() == false );
        //Check updateNeedRad method
        testPlantWom->updateNeedRad();
        CHECK (get<0>(testPlantWom->getNeedRad()) == 0);
        CHECK (get<1>(testPlantWom->getNeedRad()) == 0);
        testPlantWom->changeLevel(DeltaEarth);
        testPlantWom->updateNeedRad();
        CHECK (get<0>(testPlantWom->getNeedRad()) == 10);
        CHECK (get<1>(testPlantWom->getNeedRad()) == 0);
}

TEST_CASE("make Earth","[Earth]")
{
        //check is the type of Earth right
        earth* AlphaEarth = Alpha::getInstance();
        CHECK(AlphaEarth->getTypeInd()==1);
        earth* DeltaEarth = Delta::getInstance();
        CHECK(DeltaEarth->getTypeInd()==2);
}

TEST_CASE("Earth method","[Earth]")
{
        //check isNonRad method
        earth* AlphaEarth = Alpha::getInstance();
        earth* DeltaEarth = Delta::getInstance();
        earth* NonRadEarth = NonRad::getInstance();
        CHECK(AlphaEarth->isNonRad() == false);
        CHECK(DeltaEarth->isNonRad() == false);
        CHECK(NonRadEarth->isNonRad() == true);
        //check changeEarthRad method
        AlphaEarth=AlphaEarth->changeEarthRad(1,1);
        CHECK(AlphaEarth->getTypeInd()==NonRadEarth->getTypeInd());
        AlphaEarth=AlphaEarth->changeEarthRad(1,8);
        CHECK(AlphaEarth->getTypeInd()==DeltaEarth->getTypeInd());
}
TEST_CASE("simTill2NonRad","[Plant*]")
{
    vector <plant*> plantsList;
    create("input.txt",plantsList);
    simTill2NonRad(plantsList);
    int alive = 0;
    for(int i=0;i<plantsList.size();i++)
    {
        if(plantsList[i]->isAlive())
        {
            alive=alive+1;
        }
    }
    CHECK(alive==1);
    //check with normal input


    vector <plant*> plantsList1;
    create("input1.txt",plantsList1);
    simTill2NonRad(plantsList1);
    int alive1 = 0;
    for(int i=0;i<plantsList1.size();i++)
    {
        if(plantsList1[i]->isAlive())
        {
            alive1=alive1+1;
        }
    }
    CHECK(alive1==0);
    //check will all dead input plant

    vector <plant*> plantsList2;
    create("input2.txt",plantsList2);
    simTill2NonRad(plantsList2);
    int alive2 = 0;
    for(int i=0;i<plantsList2.size();i++)
    {
        if(plantsList2[i]->isAlive())
        {
            alive2=alive2+1;
        }
    }
    CHECK(alive2==3);
    //check will all plant alive by the end
}

#endif
