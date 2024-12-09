# Cities-Of-The-World-Management-Program

The Cities of the World Management Program is a C++ application designed to manage information about cities, enabling users to add, modify, delete, and search for city data. It also provides functionality to calculate the distance between cities and save or load city data from a file. This project showcases robust file handling, data organization, and algorithmic capabilities in C++.

Features:
-Add, modify, delete, and search for city information.
-Calculate distances between cities using geographical coordinates.
-Save city data to a file for persistence across sessions.
-Load city data from a predefined file (cities.txt).
-Handle case-sensitive and duplicate city names with differentiation by country/state.


Commands and Functionalities:
User Commands-

-Add City
add <city_name>
Example: add Oxford
Allows the user to enter details about the city, such as country, population, and geographical coordinates.

-Modify City
modify <city_name>, <country> <attribute>
Example: modify Oxford, UK population
Modifies specified details of a city.

-Delete City
delete <city_name>
Example: delete Oxford
Removes a city from the database.

-Search City
search <city_name>
Example: search Oxford
Retrieves information about a city.

-Display City Attribute
display <field> <city_name>
Example: display population Oxford
Displays a specific attribute of a city.

-Calculate Distance
distance <city_name1> <city_name2>
Example: distance London Paris
Calculates the geographical distance between two cities.

-Save Data
save
Saves all city data to a file for persistence.

-Quit Program
-quit
-Saves data and exits the program.
