#include <iostream>
#include <string>
#include "CityManager.h"
#include "InputHandler.h"
#include "Utilities.h"
#include <cstdlib>

using namespace std;

/**
 * Parses the input command string into tokens, handling quoted strings.
 */
int parseCommand(const string &command, string tokens[], int maxTokens)
{
    int tokenCount = 0;
    size_t i = 0;
    size_t len = command.length();

    while (i < len && tokenCount < maxTokens)
    {
        // Skip any leading whitespace
        while (i < len && isspace(command[i]))
            i++;

        if (i >= len)
            break;

        if (command[i] == '"') // Quoted token
        {
            i++; // Skip the opening quote
            string token = "";
            while (i < len && command[i] != '"')
            {
                token += command[i++];
            }
            tokens[tokenCount++] = token;
            if (i < len && command[i] == '"')
                i++; // Skip the closing quote
        }
        else // Unquoted token
        {
            string token = "";
            while (i < len && !isspace(command[i]))
            {
                token += command[i++];
            }
            tokens[tokenCount++] = token;
        }
    }

    return tokenCount;
}

/**
 *Processes user commands and interacts with the CityManager.
 */
void processCommand(const string &command, CityManager &manager, const string &filename)
{
    const int MAX_TOKENS = 10;
    string tokens[MAX_TOKENS];
    int tokenCount = parseCommand(command, tokens, MAX_TOKENS);

    if (tokenCount == 0)
    {
        cout << "No command entered!" << endl;
        return;
    }


    string cmd = toLowerCase(tokens[0]);

    if (cmd == "add")
    {
        // Handle "add <cityname>"
        if (tokenCount < 2)
        {
            cout << "Usage: add <cityname>" << endl;
            cout << "Note: If the city name consists of multiple words, enclose it in double quotes (\")." << endl;
            return;
        }
        string cityName = tokens[1]; // Preserve original case for display

        string region, mayorName, mayorAddress, history;
        int population, year;
        double latitude, longitude;

        cout << "Enter region: ";
        getline(cin, region);
        region = trim(region);
        while (region.empty())
        {
            cout << "Region cannot be empty. Please enter region: ";
            getline(cin, region);
            region = trim(region);
        }

        population = InputHandler::getValidatedInt("Enter population: ", 1, 40000000);
        year = InputHandler::getYearInput("Enter year recorded (4-digit year): ");

        mayorName = InputHandler::getLineInput("Enter mayor's name: ");
        while (mayorName.empty())
        {
            cout << "Mayor's name cannot be empty. ";
            mayorName = InputHandler::getLineInput("Enter mayor's name: ");
        }

        mayorAddress = InputHandler::getLineInput("Enter mayor's address: ");
        while (mayorAddress.empty())
        {
            cout << "Mayor's address cannot be empty. ";
            mayorAddress = InputHandler::getLineInput("Enter mayor's address: ");
        }

        history = InputHandler::getLineInput("Enter a short history: ");
        while (history.empty())
        {
            cout << "History cannot be empty. ";
            history = InputHandler::getLineInput("Enter a short history: ");
        }

        latitude = InputHandler::getLatitudeInput("Enter latitude (between -90 and 90): ");
        longitude = InputHandler::getLongitudeInput("Enter longitude (between -180 and 180): ");

        manager.addCity(cityName, region, population, year, mayorName, mayorAddress, history, latitude, longitude);
        cout<< "City Is Added Successfully "<<endl;
    }
    else if (cmd == "delete")
    {
        // Expected format: delete <cityname> <region>
        if (tokenCount < 3)
        {
            cout << "Usage: delete <cityname> <region>" << endl;
            cout << "Note: If the city name consists of multiple words, enclose it in double quotes (\")." << endl;
            return;
        }
        string cityName = tokens[1];
        string region = tokens[2];

        manager.deleteCity(cityName, region);
    }
    else if (cmd == "modify")
    {
        // Expected format: modify <cityname> <region> <attribute>
        if (tokenCount < 4)
        {
            cout << "Usage: modify <cityname> <region> <attribute>" << endl;
            cout << "Note: If the city name consists of multiple words, enclose it in double quotes (\")." << endl;
            return;
        }
        string cityName = tokens[1];
        string region = tokens[2];
        string attribute = toLowerCase(tokens[3]);

        manager.modifyCityAttribute(cityName, region, attribute);
    }
    else if (cmd == "search")
    {
        // Expected format: search <cityname> <region> <attribute>
        if (tokenCount < 4)
        {
            cout << "Usage: search <cityname> <region> <attribute>" << endl;
            cout << "Note: If the city name consists of multiple words, enclose it in double quotes (\")." << endl;
            return;
        }
        string cityName = tokens[1];
        string region = tokens[2];
        string attribute = toLowerCase(tokens[3]);
        manager.searchCityAttribute(cityName, region, attribute);
    }
    else if (cmd == "display")
    {
        if (tokenCount == 1)
        {
            // Display all cities
            manager.displayCities();
        }
        else if (tokenCount == 3)
        {
            // Display specific city
            string cityName = tokens[1];
            string region = tokens[2];
            manager.displayCity(cityName, region);
        }
        else
        {
            cout << "Usage:" << endl;
            cout << "  display                      - Display all cities." << endl;
            cout << "  display <cityname> <region>  - Display a specific city." << endl;
            cout << "Note: If the city name consists of multiple words, enclose it in double quotes (\")." << endl;
        }
    }
    else if (cmd == "save")
    {
        manager.saveToFile(filename);
    }
    else if (cmd == "load")
    {
        manager.loadFromFile(filename);
    }
    else if (cmd == "sort")
    {
        // Expected format: sort <attribute>
        if (tokenCount < 2)
        {
            cout << "Usage: sort <attribute>" << endl;
            cout << "Available attributes: name, population, year, latitude, longitude" << endl;
            return;
        }
        string sortAttribute = toLowerCase(tokens[1]);
        manager.sortCities(sortAttribute);
    }
    else if (cmd == "filter")
    {
        // Expected formats:
        // filter population <min> <max>
        // filter region <region>

        if (tokenCount < 2)
        {
            cout << "Usage: filter <attribute> [parameters]" << endl;
            cout << "Available attributes: population, region" << endl;
            return;
        }

        string filterAttribute = toLowerCase(tokens[1]);

        if (filterAttribute == "population")
        {
            if (tokenCount < 4)
            {
                cout << "Usage: filter population <min> <max>" << endl;
                return;
            }
            int minPop = 0;
            int maxPop = 0;
            try
            {
                minPop = stoi(tokens[2]);
                maxPop = stoi(tokens[3]);
            }
            catch (...)
            {
                cout << "Invalid population range. Please enter valid integers." << endl;
                return;
            }
            if (minPop > maxPop)
            {
                cout << "Minimum population cannot be greater than maximum population." << endl;
                return;
            }
            manager.filterCitiesByPopulation(minPop, maxPop);
        }
        else if (filterAttribute == "region")
        {
            if (tokenCount < 3)
            {
                cout << "Usage: filter region <region>" << endl;
                return;
            }
            string region = toLowerCase(tokens[2]);
            manager.filterCitiesByRegion(region);
        }
        else
        {
            cout << "Invalid filter attribute. Available attributes: population, region" << endl;
        }
    }
    else if (cmd == "stats")
    {
        // Display statistical summaries
        manager.showStatistics();
    }
    else if (cmd == "help")
    {
        // Display help information
        cout << "\n================== Help Menu ==================\n";
        cout << "Available Commands:\n";
        cout << "-----------------------------------------------\n";
        cout << "add <cityname>                   - Add a new city to the database.\n";
        cout << "                                   Note: If the city name consists of multiple words,\n";
        cout << "                                   enclose it in double quotes (\").\n\n";
        cout << "delete <cityname> <region>       - Delete a city from the database.\n";
        cout << "                                   Note: If the city name consists of multiple words,\n";
        cout << "                                   enclose it in double quotes (\").\n\n";
        cout << "modify <cityname> <region> <attribute> - Modify a specific attribute of a city.\n";
        cout << "                                       Note: If the city name consists of multiple words,\n";
        cout << "                                       enclose it in double quotes (\").\n\n";
        cout << "search <cityname> <region> <attribute> - Search for a specific attribute of a city.\n";
        cout << "                                       Note: If the city name consists of multiple words,\n";
        cout << "                                       enclose it in double quotes (\").\n\n";
        cout << "display                          - Display all cities in the database.\n";
        cout << "display <cityname> <region>      - Display a specific city.\n";
        cout << "                                   Note: If the city name consists of multiple words,\n";
        cout << "                                   enclose it in double quotes (\").\n\n";
        cout << "sort <attribute>                 - Sort cities based on the specified attribute.\n";
        cout << "                                   Available attributes: name, population, year, latitude, longitude.\n\n";
        cout << "filter <attribute> [parameters]   - Filter and display cities based on the specified attribute.\n";
        cout << "                                   Available attributes:\n";
        cout << "                                     - population <min> <max>\n";
        cout << "                                     - region <region>\n\n";
        cout << "stats                            - Display statistical summaries of the cities.\n\n";
        cout << "save                             - Save the current list of cities to the data file.\n\n";
        cout << "load                             - Load cities from the data file.\n\n";
        cout << "distance <city1name> <region1> <city2name> <region2> - Calculate the distance between two cities.\n";
        cout << "                                   Note: If city names consist of multiple words,\n";
        cout << "                                   enclose them in double quotes (\").\n\n";
        cout << "help                             - Display this help menu.\n";
        cout << "exit                             - Save changes and exit the program.\n";
        cout << "=================================================\n";
    }
    else if (cmd == "exit")
    {
        cout << "Terminating program and saving any changes..." << endl;
        manager.saveToFile(filename);
        exit(0);
    }
    else if (cmd == "distance")
    {
        // Expected format: distance <city1name> <region1> <city2name> <region2>
        if (tokenCount < 5)
        {
            cout << "Usage: distance <city1name> <region1> <city2name> <region2>" << endl;
            cout << "Note: If city names consist of multiple words, enclose them in double quotes (\")." << endl;
            return;
        }
        string city1Name = tokens[1];
        string region1 = tokens[2];
        string city2Name = tokens[3];
        string region2 = tokens[4];

        manager.calculateDistance(city1Name, region1, city2Name, region2);
    }
    else
    {
        cout << "Unknown command! Type 'help' to see available commands." << endl;
    }
}

/**
 * Main function to run the program.
 */
int main()
{
    CityManager manager;
    string filename = "data.txt";
    // Load cities from the file at the start
    manager.loadFromFile(filename);

    string command;
    cout << "Hello, Welcome to our City Management Program! Type 'help' to see available commands." << endl;

    while (true)
    {
        cout << "\nEnter command: ";
        getline(cin, command);
        command = trim(command);
        processCommand(command, manager, filename);
    }

    return 0;
}
