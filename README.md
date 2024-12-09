# Cities-Of-The-World-Management-Program

The Cities of the World Management Program is a C++ application designed to manage information about cities, enabling users to add, modify, delete, and search for city data. It also provides functionality to calculate the distance between cities and save or load city data from a file. This project showcases robust file handling, data organization, and algorithmic capabilities in C++.

## Features:
- Add, modify, delete, and search for city information.
- Calculate distances between cities using geographical coordinates.
- Save city data to a file for persistence across sessions.
- Load city data from a predefined file (cities.txt).
- Handle case-sensitive and duplicate city names with differentiation by country/state.


## Commands and Functionalities:


1. Add City
Allows the user to enter details about the city, such as country, population, and geographical coordinates.
   ```bash
   add <city_name>
   
Example: add Oxford


2. Modify City
Modifies specified details of a city.
   ```bash
   modify <city_name>, <country> <attribute>
   
Example: modify Oxford, UK population


3. Delete City
Removes a city from the database.
   ```bash
   delete <city_name>
   
Example: delete Oxford


4. Search City
Retrieves information about a city.
   ```bash
   search <city_name>

Example: search Oxford


5. Display City Attribute
Displays a specific attribute of a city.
   ```bash
   display <field> <city_name>

Example: display population Oxford


6. Calculate Distance
Calculates the geographical distance between two cities.
   ```bash
   distance <city_name1> <city_name2>

Example: distance London Paris


7. Save Data
Saves all city data to a file for persistence.
   ```bash
   save


8. Quit Program
Saves data and exits the program.
   ```bash
   quit
