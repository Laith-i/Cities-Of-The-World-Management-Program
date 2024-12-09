#ifndef CITY_H
#define CITY_H
#include <string>
using namespace std;
/**
 * Class representing a city with various attributes.
 */
class City
{
public:
    string name;
    string region;
    int population;
    int year;
    string mayorName;
    string mayorAddress;
    string history;
    double latitude;
    double longitude;

    City *next; // Pointer to the next City in the linked list

    /**
     * Constructor to initialize a City object.
     */
    City(string name, string region, int population, int year, string mayorName, string mayorAddress,
         string history, double latitude, double longitude);
};

#endif
