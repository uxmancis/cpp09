/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:02 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/28 19:45:07 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* Gets lower date which is the closest */
std::string getClosestValue(std::ifstream &dbFile, std::string dateInput)
{
    std::cout << "HERE WE ARE " << std::endl;
    // int year2find = atoi(dateInput.substr(0,4).c_str());
    // int month2find = atoi(dateInput.substr(5,2).c_str());
    // int day2find = atoi(dateInput.substr(8,2).c_str());;

    //year 1
        //is there closer month? No? up to low in months, until next year
    //year 0
    //year -1

    std::string dbLine;
    while(getline(dbFile, dbLine))
    {
        int yrDB = atoi(dateInput.substr(0,4).c_str());
        int moDB = atoi(dateInput.substr(5,2).c_str());
        int dayDB = atoi(dateInput.substr(8,2).c_str());;
        std::cout << CYAN "[DBLINE]" RESET_COLOUR " yrDB = " << yrDB << ", mo = " << moDB << ", dayDB = " << dayDB << std::endl;
    }
    (void) dbFile;
    (void) dateInput;
    return ("kaixo");
}

float getValueInDate (std::string line)
{
    // std::cout <<  GREEN "getValueInDate KAIXOKAIXOO ------------------------ " RESET_COLOUR << std::endl;
    std::string dateInput = line.substr(0,10).c_str();
    

    std::ifstream dbFile("data.csv");
    if (!dbFile.is_open()) /* Should never happen */
    {
        std::cerr << "Error: could not open file" << std::endl;
    }

    std::string dbLine; /* database where to find */
    float bitcoinValueInDate = -1;

    /* We read 100% to see if we find the exact date :)*/
    while(getline(dbFile, dbLine))
    {
        // std::cout << "Let's check :) " << std::endl;
        // std::cout << "dateInput = " << dateInput << std::endl;
        // std::cout << "dbLine = " << dbLine << std::endl;
        if (dbLine.substr(0,10).c_str() == dateInput) /* Yes this is the exact day! */
            bitcoinValueInDate = atoi(dbLine.substr(12).c_str());
    }

    if (bitcoinValueInDate == -1)
    {
        std::cout << RED << "❌ Date not found" RESET_COLOUR << std::endl;
        dbLine = getClosestValue(dbFile, dateInput);
    }
    else
    {
        std::cout << GREEN << "✅ Date found: " << dateInput <<  RESET_COLOUR << std::endl;
        std::cout << "bitcoinValueInDate = " << bitcoinValueInDate << std::endl;
    }
        

    return (bitcoinValueInDate);
}

float getTotalValue (std::string line)
{
    std::cout << "\n\ngetTotalValue ------------------------ " << std::endl;
    float howManyBitcoins = atoi(line.substr(12).c_str());
    std::cout << "howManyBitcoins = " << howManyBitcoins << std::endl;
    float bitcoinValue_in_date = getValueInDate(line);
    

    std::cout << "> Bitcoin's value we'll use: " << CYAN << bitcoinValue_in_date << RESET_COLOUR << std::endl;
    
    float resultToPrint = howManyBitcoins * bitcoinValue_in_date;
    std::cout << "-----------------------------------\n\n " << std::endl;
    return (resultToPrint);
}

/* isValidDate
*
*   Prints messages when date is invalid.
*
*   Returns:
*       true -> Valid date
*       false -> Invalid date
*/

// bool isValidDate(std::string date, std::map<std::string, float> myMap)
bool isValidDate(std::string date, what_to_print instruction)
{
    /* Year */ int year = atoi(date.substr(0,4).c_str()); //substr(where to start, how many chars to get)
    // std::cout << "Year: " << year << std::endl;

    /* Month */ int month = atoi(date.substr(5,2).c_str()); //substr(where to start, how many chars to get)
    // std::cout << "month: " << month << std::endl;

    /* Day */ int day = atoi(date.substr(8,2).c_str());;
    // std::cout << "day: " << day << std::endl;

    /* Invalid date - Generic */
    if (year < 0 || year > 2100
        || month < 1 || month > 12
        || date[4] != '-' || date[7] != '-'
        || day < 1 || day > 31)
    {
        if (instruction == PRINT_ERROR)
        {
            std::cerr << "Error: bad input" <<  " => " << date << std::endl;
        }        
        return(false);
    }
    
    /* Invalid date - Particular case: February not leap-year, 28th max*/
    if (month == 2)
    {
        if (day > 28)
        {
            if (instruction == PRINT_ERROR)
            {
                std::cerr << "Error: bad input" <<  " => " << date << std::endl;
            }    
            return(false);
        }
    }
    return(true);
}

/* isValidValue
*
*   Prints messages when value is invalid.
*
*   Returns:
*       true -> Valid value
*       false -> Invalid value
*/
bool isValidValue(std::string v, what_to_print instruction)
{
    // std::cout << "----------------------------" << std::endl;
    // std::cout << "isValidValue, Value = " << v << std::endl;
    // std::cout << "size = " << v.size() << std::endl;

    long int value = atoi(v.c_str());

    // PENDIENTEEEEEEEEEEEEE
    // float value = stof(v.c_str());
    /* Negative values are not accepted */
    if (value < 0)
    {
        if (instruction == PRINT_ERROR)
        {
            std::cout << "Error: not a positive number." << std::endl;
        }    
        return (false);
    }
    /* Valid values are range [0-1000] */
    if (value >= 0 && value <= 1000)
    {
        // std::cout << "Value is in INT range." << std::endl;
        return (true);
    }
    else
    {
        if (instruction == PRINT_ERROR)
        {
            std::cout << "Error: too large a number." << std::endl;
        }   
        return (false);
    }
}

/* validLine
*
*   Checks if both date and value in line are valid.
*
*   Returns:
*       true -> Both date and value are valid
*       false -> Either date or value is invalid
*/

// int validLine(std::string line, std::map<std::string, float> myMap)
bool validLine(std::string line, what_to_print instruction)
{
    bool isDateValid = false;
    bool isValueValid = false;
    /* Line Info: */
    // std::cout << "Line = " << line << std::endl;
    // std::cout << "Size: " << line.size() << std::endl;
    
    if (line.size() >= 10)
    {
        std::string date = line.substr(0,10); //get date
        // std::cout << "Date: " << date << std::endl;
        isDateValid = isValidDate(date, instruction); /* prints invalid line errors */
    }
    if (line.size() >= 12)
    {
        std::string value = line.substr(13); //get date
        // std::cout << "Value: " << value << std::endl;
        isValueValid = isValidValue(value, instruction); /* prints invalid line errors */
    }
    if (isDateValid && isValueValid) /* When Date and Value both are valid */
        return (true);
    return (false);
}

/* check_args
*
*   Makes sure we enter a valid argument from console.
*
*   Returns:
*       true: Successful
*       false: Failure, Error found
*/
bool check_args(int argc, char **argv)
{
    /* Enter a valid argument to program */
    if (argc != 2 || (std::string)argv[1] != "input.txt")
    {
        std::cerr << "Error: could not open file, try a valid filename" << std::endl;
        std::cout << "E.g.: ./btc input.txt" << std::endl;
        return (false);
    }
    return (true);
}

/* check_file
*
*   Checks whether if file has been correctly opened when generated.
*
*   Returns:
*       true: Successful
*       false: Failure, Error found 
*/
bool check_file(std::ifstream &file)
{
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file, try a valid filename" << std::endl;
        std::cout << "E.g.: ./btc input.txt" << std::endl;
        return (false);
    }
    return (true);
}