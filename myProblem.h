//
// Created by Aidan Sommer on 6/26/23.
//

#ifndef BESTPLANET_MYPROBLEM_H
#define BESTPLANET_MYPROBLEM_H

#include <iostream>
#include <vector>

// numElements, maxPlanetSA, answerSize all needs to be defined before calling the planet builders
struct solarSystem{
    int numElements, maxPlanetSA, answerSize;
    std::string ans;
    std::vector<std::string> planets {};

    static void testSolarSystem();
};


#endif //BESTPLANET_MYPROBLEM_H
