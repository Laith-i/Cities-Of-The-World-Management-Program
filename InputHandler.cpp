#include "InputHandler.h"
#include <iostream>
#include <sstream>

using namespace std;

/**
 * Gets a line of input from the user.
 */
string InputHandler::getLineInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return trim(input);
}

/**
 * Converts a string to an integer with validation.
 */
int InputHandler::getValidatedInt(const string &prompt, int min, int max)
{
    string input;
    int value;
    while (true)
    {
        input = getLineInput(prompt);
        if (input.empty())
        {
            cout << "Input cannot be empty. Please enter a valid integer." << endl;
            continue;
        }

        stringstream ss(input);
        if (!(ss >> value))
        {
            cout << "Invalid input. Please enter a valid integer." << endl;
            continue;
        }

        // Check for extra characters after the number
        char extra;
        if (ss >> extra)
        {
            cout << "Invalid input. Please enter a valid integer without extra characters." << endl;
            continue;
        }

        if (value < min || value > max)
        {
            cout << "Input out of range. Please enter an integer between " << min << " and " << max << "." << endl;
            continue;
        }

        return value;
    }
}

/**
 * Converts a string to a double with validation.
 */
double InputHandler::getValidatedDouble(const string &prompt, double min, double max)
{
    string input;
    double value;
    while (true)
    {
        input = getLineInput(prompt);
        if (input.empty())
        {
            cout << "Input cannot be empty. Please enter a valid number." << endl;
            continue;
        }

        stringstream ss(input);
        if (!(ss >> value))
        {
            cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }

        // Check for extra characters after the number
        char extra;
        if (ss >> extra)
        {
            cout << "Invalid input. Please enter a valid number without extra characters." << endl;
            continue;
        }

        if (value < min || value > max)
        {
            cout << "Input out of range. Please enter a number between " << min << " and " << max << "." << endl;
            continue;
        }

        return value;
    }
}

/**
 * Gets a 4-digit year input from the user with validation.
 */
int InputHandler::getYearInput(const string &prompt)
{
    int year;
    int currentYear = 2024;
    while (true)
    {
        year = getValidatedInt(prompt, 1980, currentYear);
        return year;
    }
}

/**
 * Gets a latitude input between -90 and 90.
 */
double InputHandler::getLatitudeInput(const string &prompt)
{
    double latitude = getValidatedDouble(prompt, -90.0, 90.0);
    return latitude;
}

/**
 * Gets a longitude input between -180 and 180.
 */
double InputHandler::getLongitudeInput(const string &prompt)
{
    double longitude = getValidatedDouble(prompt, -180.0, 180.0);
    return longitude;
}
