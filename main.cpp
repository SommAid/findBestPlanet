#include "myProblem.h"
#include "periodicElements.h"


// This branch has changes not in master branch 
static std::vector<std::string> ELEMENTS { "H", "C", "N", "O", "P", "Ca" };

static void print(std::vector<std::string> a);
static void print(std::vector<std::pair<std::string, int>> a);

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
    std::string curr;
    int count = 0, len = planet.size();
    std::string foundElements = "";
    for(int j = 0; j < len-1; j++)
    {
        curr = planet.substr(j, 2);
        if(isCapital(curr[0]) && !(curr[1] >= 'a' && curr[1] <= 'z')) {
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
            j++;
        }
    }
    // std::cout << "End Check for requirements\n";
    // std::cout << foundElements << "::" << planet << "\n";
    return count >= 6;
}

std::string bestPlanet(const std::vector<std::string>& planets, int liveableSize, std::vector<std::pair<std::string, int>>& possible)
{
    // std::cout << "finding best planet\n";
    int curr_size;
    std::string bestPlanet;
    //std::vector<std::pair<std::string, int>> possible;
    for(const std::string& iter : planets)
    {
        curr_size = getSizePlanet(iter);
        if (curr_size <= liveableSize)
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
    std::string myAnswer;
    bool error = false;
    for (int j = 0; j < 100 && !error; j++)
    {
        std::vector<std::pair<std::string, int>> possible;
        solarSystem mySolarSystem;
        solarSystem::testSolarSystem(mySolarSystem);
        myAnswer = bestPlanet(mySolarSystem.planets, mySolarSystem.maxPlanetSA, possible);
        if (myAnswer != mySolarSystem.ans)
        {
            std::cout << "An Error Occured\n";
            std::cout << "Number of tests passed : " << (j+1) << "\n";
            print(possible);
            std::cout << myAnswer << "\n ***** \n";
            std::cout << mySolarSystem.ans << "\n";
            containsReq(mySolarSystem.ans);
            error = true;
        }
    }
    if (!error)
    {
        std::cout << "You passed all the tests\n";
    }

    return 0;
}

static void print(std::vector<std::string> a) {
    int pos = 0;
    for (const auto& iter : a)
        std::cout << pos++ << " : " << iter << "\n";
}

static void print(std::vector<std::pair<std::string, int>> a) {
    int pos = 0;
    for (const auto& iter : a)
        std::cout << pos++ << " : " << iter.second << "\n";
}