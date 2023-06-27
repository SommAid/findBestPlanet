//
// Created by Aidan Sommer on 6/26/23.
//

#include "myProblem.h"
static std::string ALL_ELEMENTS[118] { "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"};
static std::string REQUIRED_ELEMENTS[6] { "H", "C", "N", "O", "P", "Ca" };
static std::string NON_REQUIRED_ELEMENTS[112] { "He", "Li", "Be", "B", "F", "Ne", "Na", "Mg", "Al", "Si", "S", "Cl", "Ar", "K", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og" }
;

// solarSystemBuilder.cpp : This file contains the 'main' function. Program
// execution begins and ends there.

// Determines if a number `curr` isIn positions
static bool isIn(std::vector<int>& positions, int curr)
{
    for (const int &i: positions)
        if (i == curr)
            return true;
    return false;
}


// Modifies a vector positions to get
static void positionRequiredElements(std::vector<int>& positions, int numElements, int numRequiredElements = 6)
{
    int copy;
    for(int j = 0; j < numRequiredElements; j++)
    {
        positions.push_back(rand()% numElements);
    }
}

/*
creates a planet that is too big
DONE:

Creates a planet that is too big with all the elements
*/
static void planetWrongSize(solarSystem& mySolarSystem) {
    int small_or_large = rand() % 2, contain_required_elements = rand()%2, insertedCorrectElement = 0, insertedNonRequired = 0, element, planetSize;
    std::string planet = "", copy;
    std::vector<int> posNeededElements;
    // creates a planet that is too large if small_or_large == 1 else it creates one that is smaller than the solution
    if(small_or_large)
        planetSize = rand() % mySolarSystem.maxPlanetSA + mySolarSystem.maxPlanetSA + 1;
    else
        planetSize = rand() % mySolarSystem.answerSize;

    // creates a planet with either all the correct elements or random elements
    if(contain_required_elements) {
        positionRequiredElements(posNeededElements, mySolarSystem.numElements);
        for(int i = 0; i < mySolarSystem.numElements; i++)
        {
            if(isIn(posNeededElements, i))
            {
                element = rand() % (6 - insertedCorrectElement);
                planet += REQUIRED_ELEMENTS[element];
                copy = REQUIRED_ELEMENTS[element];
                REQUIRED_ELEMENTS[element] = REQUIRED_ELEMENTS[6 - insertedCorrectElement];
                REQUIRED_ELEMENTS[6 - insertedCorrectElement] = copy;
                insertedCorrectElement++;
            }
            else
            {
                element = rand() % (112 - insertedNonRequired);
                planet += NON_REQUIRED_ELEMENTS[element];
                copy = NON_REQUIRED_ELEMENTS[element];
                NON_REQUIRED_ELEMENTS[element] = NON_REQUIRED_ELEMENTS[112 - insertedNonRequired];
                NON_REQUIRED_ELEMENTS[112 - insertedNonRequired] = copy;
                insertedNonRequired++;
            }
        }
    }
    else
    {
        for(int i = 0; i < mySolarSystem.numElements; i++)
        {
            element = rand() % (118 - i);
            planet += ALL_ELEMENTS[element];
            copy = ALL_ELEMENTS[element];
            ALL_ELEMENTS[element] = ALL_ELEMENTS[118 - i];
            ALL_ELEMENTS[118 - i] = copy;
        }
    }
    planet += "_" + std::to_string(planetSize);
    mySolarSystem.planets.push_back(planet);
}

/*
creates a planet that doesn't have enough elements
DONE:

Creates a planet with not enough of the much-needed human elements
*/
static void planetWrongElements(solarSystem& mySolarSystem) {
    int contain_required_elements = rand()%6, insertedCorrectElement = 0, insertedNonRequired = 0, planetSize, element;
    std::string planet = "", copy;
    std::vector<int> posNeededElements;

    // creates a planet that is the same size as or better than the actual planet
    planetSize = rand()%(mySolarSystem.maxPlanetSA - mySolarSystem.answerSize) + mySolarSystem.answerSize;

    // creates a planet with either not all the correct elements
    positionRequiredElements(posNeededElements, mySolarSystem.numElements,contain_required_elements);
    for(int i = 0; i < mySolarSystem.numElements; i++) {
        if (isIn(posNeededElements, i)) {
            element = rand() % (6 - insertedCorrectElement);
            planet += REQUIRED_ELEMENTS[element];
            copy = REQUIRED_ELEMENTS[element];
            REQUIRED_ELEMENTS[element] = REQUIRED_ELEMENTS[6 - insertedCorrectElement];
            REQUIRED_ELEMENTS[6 - insertedCorrectElement] = copy;
            insertedCorrectElement++;
        }
        else {
            element = rand() % (112 - insertedNonRequired);
            planet += NON_REQUIRED_ELEMENTS[element];
            copy = NON_REQUIRED_ELEMENTS[element];
            NON_REQUIRED_ELEMENTS[element] = NON_REQUIRED_ELEMENTS[112 - insertedNonRequired];
            NON_REQUIRED_ELEMENTS[112 - insertedNonRequired] = copy;
            insertedNonRequired++;
        }
    }
    planet += "_" + std::to_string(planetSize);
    mySolarSystem.planets.push_back(planet);
}

/*
Builds a planet that is the answer to this problem
This has a list of random elements and a list of required elements
it rolls a random number if that random number is within the req elements it
will pull it from their else it will pull an element from the possible elements
in the random elements list

DONE:
This function should be completed and will create a complete planet
*/
static std::string answerBuilder(solarSystem& mySolarSystem) {
    int insertedCorrectElement = 0, insertedNonRequired = 0, planetSize, element;
    std::string planet = "", copy;
    std::vector<int> posNeededElements;

    // creates a planet that is the same size as or better than the actual planet
    planetSize = mySolarSystem.answerSize;

    // creates a planet with either not all the correct elements
    positionRequiredElements(posNeededElements, mySolarSystem.numElements);
    for(int i = 0; i < mySolarSystem.numElements; i++) {
        if (isIn(posNeededElements, i)) {
            element = rand() % (6 - insertedCorrectElement);
            planet += REQUIRED_ELEMENTS[element];
            copy = REQUIRED_ELEMENTS[element];
            REQUIRED_ELEMENTS[element] = REQUIRED_ELEMENTS[6 - insertedCorrectElement];
            REQUIRED_ELEMENTS[6 - insertedCorrectElement] = copy;
            insertedCorrectElement++;
        }
        else {
            element = rand() % (112 - insertedNonRequired);
            planet += NON_REQUIRED_ELEMENTS[element];
            copy = NON_REQUIRED_ELEMENTS[element];
            NON_REQUIRED_ELEMENTS[element] = NON_REQUIRED_ELEMENTS[112 - insertedNonRequired];
            NON_REQUIRED_ELEMENTS[112 - insertedNonRequired] = copy;
            insertedNonRequired++;
        }
    }
    planet += "_" + std::to_string(planetSize);
    mySolarSystem.planets.push_back(planet);

}

static void easySolarSystem(solarSystem& mySolarSystem)
{
    int numPlanets = rand()%300+150, answerPos = rand()%numPlanets;
    mySolarSystem.numElements = rand()%50+10;
    mySolarSystem.maxPlanetSA = 1000;
    mySolarSystem.answerSize = rand()%500+501;
    for(int j = 0; j < numPlanets; j++)
    {
        if(j == answerPos)
            answerBuilder(mySolarSystem);
        else if(j % 2 == 0)
            planetWrongSize(mySolarSystem);
        else
            planetWrongElements(mySolarSystem);
    }
}
static void mediumSolarSystem(solarSystem& mySolarSystem)
{
    int numPlanets = rand()%500+450,answerPos = rand()%numPlanets;
    mySolarSystem.numElements = rand()%50+50;
    mySolarSystem.maxPlanetSA = 10000;
    mySolarSystem.answerSize = rand()%5000+5001;
    for(int j = 0; j < numPlanets; j++)
    {
        if(j == answerPos)
            answerBuilder(mySolarSystem);
        else if(j % 2 == 0)
            planetWrongSize(mySolarSystem);
        else
            planetWrongElements(mySolarSystem);
    }
}
static void hardSolarSystem(solarSystem& mySolarSystem)
{
    int numPlanets = rand()%1000+900, answerPos = rand()%numPlanets;
    mySolarSystem.numElements = rand()%18+100;
    mySolarSystem.maxPlanetSA = 100000;
    mySolarSystem.answerSize = rand()%50000+50001;
    for(int j = 0; j < numPlanets; j++)
    {
        if(j == answerPos)
            answerBuilder(mySolarSystem);
        else if(j % 2 == 0)
            planetWrongSize(mySolarSystem);
        else
            planetWrongElements(mySolarSystem);
    }
}


// use this function for testing before posting, thanks!
static void testSolarSystem(solarSystem& mySolarSystem) {

}

static void print(std::vector<std::string> solarSystem) {
    int pos = 0;
    for (std::string iter : solarSystem)
        std::cout << pos++ << " : " << iter << "\n";
}

