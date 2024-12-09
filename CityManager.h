#ifndef CITYMANAGER_H
#define CITYMANAGER_H

#include "City.h"
#include <string>

using namespace std;

/**
 * Class to manage city data using a linked list.
 */
class CityManager
{
private:
    City *head; // Pointer to the first City in the list

    // Private helper functions for merge sort
    void splitList(City *source, City **frontRef, City **backRef);
    City *sortedMerge(City *a, City *b, const string &sortAttribute);
    void mergeSort(City **headRef, const string &sortAttribute);

public:
    /**
     *Constructor initializes the head to nullptr.
     */
    CityManager();

    /**
     *Destructor to free all dynamically allocated memory.
     */
    ~CityManager();

    /**
     *Adds a new city to the list.
     */
    void addCity(string name, string region, int population, int year, string mayorName,
                 string mayorAddress, string history, double latitude, double longitude);

    /**
     *Displays all cities in the list.
     */
    void displayCities() const;

    /**
     *Finds a city by name and region (case-insensitive).
     */
    City *findCity(const string &name, const string &region) const;

    /**
     *Calculates the distance between two cities.
     */
    void calculateDistance(const string &city1Name, const string &region1, const string &city2Name, const string &region2) const;

    /**
     * Deletes a city by name and region.
     */
    void deleteCity(const string &name, const string &region);

    /**
     * Searches for a city and outputs a specific attribute.
     */
    void searchCityAttribute(const string &name, const string &region, const string &attribute) const;

    /**
     * Sorts the cities based on a specified attribute using Merge Sort.
     */
    void sortCities(const string &sortAttribute);

    /**
     * @brief Filters and displays cities based on population range.
     */
    void filterCitiesByPopulation(int minPopulation, int maxPopulation) const;

    /**
     * Filters and displays cities based on region.
     */
    void filterCitiesByRegion(const string &region) const;

    /**
     * Displays statistical summaries of the cities.
     */
    void showStatistics() const;

    /**
     * Modifies a specific attribute of a city.
     */
    void modifyCityAttribute(const string &name, const string &region, const string &attribute);

    /**
     * Saves the cities to a file.
     */
    void saveToFile(const string &filename) const;

    /**
     * Loads cities from a file.
     */
    void loadFromFile(const string &filename);

    /**
     * Displays information for a specific city.
     */
    void displayCity(const string &name, const string &region) const;
};

#endif // CITYMANAGER_H
