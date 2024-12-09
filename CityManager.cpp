#include "CityManager.h"
#include "Utilities.h"
#include "InputHandler.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;

/**
 * Constructor initializes the head to nullptr.
 */
CityManager::CityManager() : head(nullptr) {}

/**
 * Destructor to free all dynamically allocated memory.
 */
CityManager::~CityManager()
{
    City *current = head;
    while (current != nullptr)
    {
        City *toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

/**
 * Splits the linked list into two halves for merge sort.
 */
void CityManager::splitList(City *source, City **frontRef, City **backRef)
{
    City *slow = source;
    City *fast = source->next;

    // Advance 'fast' two nodes, and 'slow' one node
    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is before the midpoint in the list, so split it in two at that point
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

/**
 * Merges two sorted linked lists based on the sort attribute.
 */
City *CityManager::sortedMerge(City *a, City *b, const string &sortAttribute)
{
    City *result = nullptr;

    // Base cases
    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    // Compare based on the sortAttribute
    bool condition = false;
    if (sortAttribute == "name")
        condition = (a->name < b->name);
    else if (sortAttribute == "population")
        condition = (a->population < b->population);
    else if (sortAttribute == "year")
        condition = (a->year < b->year);
    else if (sortAttribute == "latitude")
        condition = (a->latitude < b->latitude);
    else if (sortAttribute == "longitude")
        condition = (a->longitude < b->longitude);
    else
    {
        cout << "Invalid sort attribute. Sorting by name by default." << endl;
        condition = (a->name < b->name);
    }

    if (condition)
    {
        result = a;
        result->next = sortedMerge(a->next, b, sortAttribute);
    }
    else
    {
        result = b;
        result->next = sortedMerge(a, b->next, sortAttribute);
    }
    return result;
}

/**
 *  Performs merge sort on the linked list.
 */
void CityManager::mergeSort(City **headRef, const string &sortAttribute)
{
    City *headLocal = *headRef;
    City *a;
    City *b;

    // Base case -- length 0 or 1
    if ((headLocal == nullptr) || (headLocal->next == nullptr))
    {
        return;
    }

    // Split head into 'a' and 'b' sublists
    splitList(headLocal, &a, &b);

    // Recursively sort the sublists
    mergeSort(&a, sortAttribute);
    mergeSort(&b, sortAttribute);

    // Merge the two sorted lists together
    *headRef = sortedMerge(a, b, sortAttribute);
}

/**
 *  Adds a new city to the list.
 */
void CityManager::addCity(string name, string region, int population, int year, string mayorName,
                          string mayorAddress, string history, double latitude, double longitude)
{
    // Convert all string inputs to lowercase before storing
    string lowerName = toLowerCase(name);
    string lowerRegion = toLowerCase(region);
    string lowerMayorName = toLowerCase(mayorName);
    string lowerMayorAddress = toLowerCase(mayorAddress);
    string lowerHistory = toLowerCase(history);
    // Check for duplicates
    if (findCity(lowerName, lowerRegion))
    {
        cout << "A city with the name '" << lowerName << "' in region '" << lowerRegion << "' already exists." << endl;
        cout << "Do you want to overwrite it? (yes/no): ";
        string choice;
        getline(cin, choice);
        string lowerChoice = toLowerCase(choice);
        if (lowerChoice != "yes")
        {
            cout << "City not added." << endl;
            return;
        }
        else {
            deleteCity(lowerName, lowerRegion);
        }
    }

    City *newCity = new City(lowerName, lowerRegion, population, year, lowerMayorName, lowerMayorAddress, lowerHistory, latitude, longitude);

    if (head == nullptr)
    {
        head = newCity; // If the list is empty, set the new city as the head
    }
    else
    {
        // Insert the new city at the end of the list
        City *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newCity;
    }
}

/**
 *  Displays all cities in the list.
 */
void CityManager::displayCities() const
{
    if (head == nullptr)
    {
        cout << "No cities available." << endl;
        return;
    }

    City *current = head;
    while (current != nullptr)
    {
        cout << "City: " << current->name << ", Region: " << current->region
             << ", Population: " << current->population << ", Year: " << current->year
             << ", Mayor: " << current->mayorName << ", History: " << current->history
             << ", Latitude: " << current->latitude << ", Longitude: " << current->longitude << endl;
        current = current->next;
    }
}

/**
 *  Finds a city by name and region (case-insensitive).
 */
City *CityManager::findCity(const string &name, const string &region) const
{
    City *current = head;
    while (current != nullptr)
    {
        if (equalsIgnoreCase(current->name, name) && equalsIgnoreCase(current->region, region))
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

/**
 * Calculates the distance between two cities.
 */
void CityManager::calculateDistance(const string &city1Name, const string &region1, const string &city2Name, const string &region2) const
{
    string lowerCity1 = toLowerCase(city1Name);
    string lowerRegion1 = toLowerCase(region1);
    string lowerCity2 = toLowerCase(city2Name);
    string lowerRegion2 = toLowerCase(region2);

    City *city1 = findCity(lowerCity1, lowerRegion1);
    City *city2 = findCity(lowerCity2, lowerRegion2);
    const double EARTH_RADIUS = 6371.0;
    if (!city1 || !city2)
    {
        cerr << "Error: One or both cities not found." << endl;
        return;
    }

    // Convert latitudes and longitudes from degrees to radians
    double lat1 = toRadians(city1->latitude);
    double lat2 = toRadians(city2->latitude);
    double lon1 = toRadians(city1->longitude);
    double lon2 = toRadians(city2->longitude);

    // Haversine formula for distance
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = EARTH_RADIUS * c;

    cout << "Distance between " << city1->name << ", " << city1->region << " and "
         << city2->name << ", " << city2->region << " is: " << distance << " km." << endl;
}

/**
 *  Deletes a city by name and region.
 */
void CityManager::deleteCity(const string &name, const string &region)
{
    if (head == nullptr)
    {
        cout << "No cities available to delete." << endl;
        return;
    }

    // Handle deletion of the head city
    if (equalsIgnoreCase(head->name, name) && equalsIgnoreCase(head->region, region))
    {
        City *toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "City deleted successfully!" << endl;
        return;
    }

    // Traverse the list to find and delete the city
    City *current = head;
    while (current->next != nullptr)
    {
        if (equalsIgnoreCase(current->next->name, name) && equalsIgnoreCase(current->next->region, region))
        {
            City *toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
            cout << "City deleted successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "City not found!" << endl;
}

/**
 *  Searches for a city and outputs a specific attribute.
 */
void CityManager::searchCityAttribute(const string &name, const string &region, const string &attribute) const
{
    string lowerName = toLowerCase(name);
    string lowerRegion = toLowerCase(region);
    City *current = findCity(lowerName, lowerRegion);
    if (current == nullptr)
    {
        cout << "City not found!" << endl;
        return;
    }

    // Output the requested attribute
    if (attribute == "name")
    {
        cout << "Name: " << current->name << endl;
    }
    else if (attribute == "region")
    {
        cout << "Region: " << current->region << endl;
    }
    else if (attribute == "population")
    {
        cout << "Population: " << current->population << endl;
    }
    else if (attribute == "year")
    {
        cout << "Year: " << current->year << endl;
    }
    else if (attribute == "mayorname")
    {
        cout << "Mayor's Name: " << current->mayorName << endl;
    }
    else if (attribute == "mayoraddress")
    {
        cout << "Mayor's Address: " << current->mayorAddress << endl;
    }
    else if (attribute == "latitude")
    {
        cout << "Latitude: " << current->latitude << endl;
    }
    else if (attribute == "longitude")
    {
        cout << "Longitude: " << current->longitude << endl;
    }
    else if (attribute == "history")
    {
        cout << "History: " << current->history << endl;
    }
    else
    {
        cout << "Attribute not found!" << endl;
    }
}

/**
 * Sorts the cities based on a specified attribute using Merge Sort.
 */
void CityManager::sortCities(const string &sortAttribute)
{
    mergeSort(&head, sortAttribute);
    cout << "Cities sorted by " << sortAttribute << " successfully!" << endl;
}

/**
 * Filters and displays cities based on population range.
 */
void CityManager::filterCitiesByPopulation(int minPopulation, int maxPopulation) const
{
    if (head == nullptr)
    {
        cout << "No cities available." << endl;
        return;
    }

    City *current = head;
    bool found = false;
    while (current != nullptr)
    {
        if (current->population >= minPopulation && current->population <= maxPopulation)
        {
            cout << "City: " << current->name << ", Region: " << current->region
                 << ", Population: " << current->population << ", Year: " << current->year
                 << ", Mayor: " << current->mayorName << ", History: " << current->history
                 << ", Latitude: " << current->latitude << ", Longitude: " << current->longitude << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "No cities found within the specified population range." << endl;
    }
}

/**
 * Filters and displays cities based on region.
 */
void CityManager::filterCitiesByRegion(const string &region) const
{
    if (head == nullptr)
    {
        cout << "No cities available." << endl;
        return;
    }

    string targetRegion = toLowerCase(region);
    City *current = head;
    bool found = false;
    while (current != nullptr)
    {
        if (equalsIgnoreCase(current->region, targetRegion))
        {
            cout << "City: " << current->name << ", Region: " << current->region
                 << ", Population: " << current->population << ", Year: " << current->year
                 << ", Mayor: " << current->mayorName << ", History: " << current->history
                 << ", Latitude: " << current->latitude << ", Longitude: " << current->longitude << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "No cities found in the specified region." << endl;
    }
}

/**
 *  Displays statistical summaries of the cities.
 */
void CityManager::showStatistics() const
{
    if (head == nullptr)
    {
        cout << "No cities available to display statistics." << endl;
        return;
    }

    int count = 0;
    long totalPopulation = 0;
    int minPopulation = numeric_limits<int>::max();
    int maxPopulation = numeric_limits<int>::min();
    long totalYear = 0;
    double totalLatitude = 0.0;
    double totalLongitude = 0.0;

    City *current = head;
    while (current != nullptr)
    {
        count++;
        totalPopulation += current->population;
        if (current->population < minPopulation)
            minPopulation = current->population;
        if (current->population > maxPopulation)
            maxPopulation = current->population;
        totalYear += current->year;
        totalLatitude += current->latitude;
        totalLongitude += current->longitude;
        current = current->next;
    }

    double averagePopulation = static_cast<double>(totalPopulation) / count;
    double averageYear = static_cast<double>(totalYear) / count;
    double averageLatitude = totalLatitude / count;
    double averageLongitude = totalLongitude / count;

    cout << "----- Statistical Summary -----" << endl;
    cout << "Total Number of Cities: " << count << endl;
    cout << "Average Population: " << averagePopulation << endl;
    cout << "Minimum Population: " << minPopulation << endl;
    cout << "Maximum Population: " << maxPopulation << endl;
    cout << "Average Year Recorded: " << averageYear << endl;
    cout << "Average Latitude: " << averageLatitude << endl;
    cout << "Average Longitude: " << averageLongitude << endl;
    cout << "-------------------------------" << endl;
}

/**
 *  Modifies a specific attribute of a city.
 */
void CityManager::modifyCityAttribute(const string &name, const string &region, const string &attribute)
{
    string lowerName = toLowerCase(name);
    string lowerRegion = toLowerCase(region);
    City *current = findCity(lowerName, lowerRegion);
    if (current == nullptr)
    {
        cout << "City not found!" << endl;
        return;
    }

    // Modify the requested attribute
    if (attribute == "name")
    {
        string newName = InputHandler::getLineInput("Enter the new name: ");
        if (newName.empty())
        {
            cout << "Name cannot be empty. Modification aborted." << endl;
            return;
        }
        current->name = toLowerCase(newName);
        cout << "Name updated successfully!" << endl;
    }
    else if (attribute == "region")
    {
        string newRegion = InputHandler::getLineInput("Enter the new region: ");
        if (newRegion.empty())
        {
            cout << "Region cannot be empty. Modification aborted." << endl;
            return;
        }
        current->region = toLowerCase(newRegion);
        cout << "Region updated successfully!" << endl;
    }
    else if (attribute == "population")
    {
        const int MAX_POPULATION = 40000000;
        int newPopulation = InputHandler::getValidatedInt("Enter the new population: ", 1, MAX_POPULATION);
        current->population = newPopulation;
        cout << "Population updated successfully!" << endl;
    }
    else if (attribute == "year")
    {
        int newYear = InputHandler::getYearInput("Enter the new year (4-digit year): ");
        current->year = newYear;
        cout << "Year updated successfully!" << endl;
    }
    else if (attribute == "mayorname")
    {
        string newMayorName = InputHandler::getLineInput("Enter the new mayor's name: ");
        if (newMayorName.empty())
        {
            cout << "Mayor's name cannot be empty. Modification aborted." << endl;
            return;
        }
        current->mayorName = toLowerCase(newMayorName);
        cout << "Mayor's name updated successfully!" << endl;
    }
    else if (attribute == "mayoraddress")
    {
        string newMayorAddress = InputHandler::getLineInput("Enter the new mayor's address: ");
        if (newMayorAddress.empty())
        {
            cout << "Mayor's address cannot be empty. Modification aborted." << endl;
            return;
        }
        current->mayorAddress = toLowerCase(newMayorAddress);
        cout << "Mayor's address updated successfully!" << endl;
    }
    else if (attribute == "latitude")
    {
        double newLatitude = InputHandler::getLatitudeInput("Enter the new latitude (between -90 and 90): ");
        current->latitude = newLatitude;
        cout << "Latitude updated successfully!" << endl;
    }
    else if (attribute == "longitude")
    {
        double newLongitude = InputHandler::getLongitudeInput("Enter the new longitude (between -180 and 180): ");
        current->longitude = newLongitude;
        cout << "Longitude updated successfully!" << endl;
    }
    else if (attribute == "history")
    {
        string newHistory = InputHandler::getLineInput("Enter the new history: ");
        if (newHistory.empty())
        {
            cout << "History cannot be empty. Modification aborted." << endl;
            return;
        }
        current->history = toLowerCase(newHistory);
        cout << "History updated successfully!" << endl;
    }
    else
    {
        cout << "Attribute not found!" << endl;
    }
}

/**
 *  Saves the cities to a file.
 */
void CityManager::saveToFile(const string &filename) const
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    City *current = head;
    while (current != nullptr)
    {
        // Enclose string fields in double quotes and escape existing quotes by doubling them
        outFile << escapeQuotes(current->name) << ","
                << escapeQuotes(current->region) << ","
                << current->population << ","
                << current->year << ","
                << escapeQuotes(current->mayorName) << ","
                << escapeQuotes(current->mayorAddress) << ","
                << escapeQuotes(current->history) << ","
                << current->latitude << ","
                << current->longitude << endl;
        current = current->next;
    }
    outFile.close();
    cout << "Cities saved to file successfully!" << endl;
}

/**
 *  Loads cities from a file.
 */
void CityManager::loadFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        // Parse CSV line considering quoted fields
        stringstream ss(line);
        string field;
        string fields[9]; // There are 9 attributes

        for (int i = 0; i < 9; ++i)
        {
            if (ss.peek() == '"')
            {
                // Quoted field
                ss.ignore(); // Ignore the opening quote
                getline(ss, field, '"');
                ss.ignore(); // Ignore the closing quote
                // Ignore the comma after the closing quote
                if (i < 8 && ss.peek() == ',')
                    ss.ignore();
            }
            else
            {
                // Unquoted field
                getline(ss, field, ',');
            }
            fields[i] = trim(field);
        }

        // Convert numeric fields
        int population = 0, year = 0;
        double latitude = 0.0, longitude = 0.0;

        try
        {
            population = stoi(fields[2]);
        }
        catch (...)
        {
            population = 0; // Default value or handle error
        }

        try
        {
            year = stoi(fields[3]);
        }
        catch (...)
        {
            year = 0; // Default value or handle error
        }

        try
        {
            latitude = stod(fields[7]);
        }
        catch (...)
        {
            latitude = 0.0; // Default value or handle error
        }

        try
        {
            longitude = stod(fields[8]);
        }
        catch (...)
        {
            longitude = 0.0; // Default value or handle error
        }

        // Add the city to the linked list
        addCity(fields[0], fields[1], population, year, fields[4], fields[5], fields[6], latitude, longitude);
    }
    inFile.close();
    cout << "Cities loaded from file successfully!" << endl;
}

/**
 * Displays information for a specific city.
 *
 * @param name The name of the city.
 * @param region The region of the city.
 */
void CityManager::displayCity(const string &name, const string &region) const
{
    string lowerName = toLowerCase(name);
    string lowerRegion = toLowerCase(region);
    City *current = findCity(lowerName, lowerRegion);
    if (current == nullptr)
    {
        cout << "City '" << name << "' in region '" << region << "' not found!" << endl;
        return;
    }

    cout << "----- City Information -----" << endl;
    cout << "Name: " << current->name << endl;
    cout << "Region: " << current->region << endl;
    cout << "Population: " << current->population << endl;
    cout << "Year: " << current->year << endl;
    cout << "Mayor's Name: " << current->mayorName << endl;
    cout << "Mayor's Address: " << current->mayorAddress << endl;
    cout << "History: " << current->history << endl;
    cout << "Latitude: " << current->latitude << endl;
    cout << "Longitude: " << current->longitude << endl;
    cout << "-----------------------------" << endl;
}
