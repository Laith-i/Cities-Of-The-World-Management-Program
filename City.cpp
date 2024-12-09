#include "City.h"


/**
 * @brief Constructor to initialize a City object.
 */
City::City(string name, string region, int population, int year, string mayorName, string mayorAddress,
           string history, const double latitude, double longitude)
    : name(std::move(name)), region(std::move(region)), population(population), year(year), mayorName(std::move(mayorName)), mayorAddress(std::move(mayorAddress)),
      history(std::move(history)), latitude(latitude), longitude(longitude), next(nullptr)
{
}
