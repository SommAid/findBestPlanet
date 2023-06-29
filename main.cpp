#include "myProblem.h"
#include "periodicElements.h"

static std::vector<std::string> ELEMENTS { "H", "C", "N", "O", "P", "Ca" };

template <typename T>
static void print(std::vector<T> a);

int getSizePlanet(const std::string& a)
{
    int pos = int(std::find(a.begin(), a.end(), '_') - a.begin());
    if(pos) {
        std::string num(a.cbegin() + pos + 1, a.cend());
        return std::stoi(num);
    }
    return pos;
}

bool isCapital(const char& let)
{
    return (let >= 'A' && let <= 'Z');
}

bool containsReq(const std::string& planet)
{
    //std::cout << "Checking if planet meets requirements\n";
    std::string curr; int count = 0;
    std::string foundElements = "";
    for(int j = 0; j < planet.size()-1; j++)
    {
        if(j+1 >= planet.size())
            std::cout << "Found the error\n";
        curr = planet.substr(j, 2);
        if(isCapital(curr[0]) && isCapital(curr[1])) {
            if (std::find_if(ELEMENTS.cbegin(), ELEMENTS.cend(),
                             [curr](auto a) {return a == std::string(1, curr[0]); }) < ELEMENTS.end())
            {
                foundElements += curr[0];
                count++;
            }

        }
        else if(isCapital(curr[0]) && !isCapital(curr[1])) {
                if (std::find_if(ELEMENTS.cbegin(), ELEMENTS.cend(),
                                 [curr](auto a) { return a == curr; }) < ELEMENTS.cend())
                {
                    foundElements += curr[0];
                    count++;
                }
            }
    }
    //std::cout << "End Check for requirements\n";
    std::cout << foundElements << "::" << planet << "\n";
    return count >= 6;
}

std::string bestPlanet(const std::vector<std::string>& planets, int liveableSize)
{
    //std::cout << "finding best planet\n";
    int curr_size;
    std::string bestPlanet;
    std::vector<std::pair<std::string, int>> possible;
    for(const std::string& iter : planets)
    {
        curr_size = getSizePlanet(iter);
        if(curr_size <= liveableSize)
            possible.emplace_back(iter, curr_size);
    }
    // now we want to return the largest planet with all required elements
    std::sort(possible.rbegin(), possible.rend(), [](auto a, auto b) { return  a.second < b.second; });
    int i = 0;
    for(const auto& iter : possible)
    {
        if(containsReq(iter.first))
            return iter.first;
    }
    return "You didn't find it";
}

int main() {
    srand(time(0));
    solarSystem mySolarSystem;
    solarSystem::testSolarSystem(mySolarSystem);
    //print(mySolarSystem.planets);
    std::cout << "Answer Position : " << mySolarSystem.answerPos << "\nLargest Size : " << mySolarSystem.maxPlanetSA << "\nnumPlanets : " << mySolarSystem.planets.size() << "\n";
    std::cout << "REAL ANSWER : " << mySolarSystem.ans << "\n";
    //std::cout << "Number of planets : " << mySolarSystem.planets.size() << "\n";
    std::string myAnswer = bestPlanet(mySolarSystem.planets, mySolarSystem.maxPlanetSA);
    std::cout << "My Answer : " << myAnswer << "\n";
    std::cout << "Are we correct : " << (myAnswer == mySolarSystem.ans) << "\n";

    return 0;
}

template <typename T>
static void print(std::vector<T> a) {
    int pos = 0;
    for (const auto& iter : a)
        std::cout << pos++ << " : " << iter << "\n";
}