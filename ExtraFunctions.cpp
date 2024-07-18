#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>


using namespace std;

unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
auto rng2 = std::default_random_engine {seed2};


std::string upperCase(const std::string x)
{
    string z = x;
    for(unsigned int i =0; i < x.size(); i++)
     z[i] = toupper(x[i]);

    return z;
}

// trim from start (in place)
std::string ltrim(std::string s) {
    std::string s2 = s;
    s2.erase(s2.begin(), std::find_if(s2.begin(), s2.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s2;
}

// trim from end (in place)
std::string rtrim(std::string s) {
    std::string s2 = s;
    s2.erase(std::find_if(s2.rbegin(), s2.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s2.end());

    return s2;
}

// trim from both ends
std::string trim(const std::string &s) {
    return ltrim(rtrim(s));
}


void shuffleVector(vector<string> &vecToShuf)
{
    std::shuffle(std::begin(vecToShuf), std::end(vecToShuf), rng2);
}

