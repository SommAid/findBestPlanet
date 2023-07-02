//
// Created by Aidan Sommer on 6/26/23.
//

#ifndef BESTPLANET_MYPROBLEM_H
#define BESTPLANET_MYPROBLEM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// numElements, maxPlanetSA, answerSize all needs to be defined before calling the planet builders
struct solarSystem{
    int numElements, maxPlanetSA, answerSize, answerPos;
    std::string ans;
    std::vector<std::string> planets {};

   static void testSolarSystem(solarSystem& mySolarSystem);
};


#endif //BESTPLANET_MYPROBLEM_H
