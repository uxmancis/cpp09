/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxuemancisidorlaskurain <uxuemancisidor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:25 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/29 19:36:29 by uxuemancisi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp" 

/* isValidDate
*
*   Prints messages when date is invalid.
*
*   Returns:
*       true -> Valid date
*       false -> Invalid date
*/
bool isValidDate(std::string date, what_to_print instruction)
{
    /* Year */ int year = atoi(date.substr(0,4).c_str()); //substr(where to start, how many chars to get)
    // std::cout << "Year: " << year << std::endl;

    /* Month */ int month = atoi(date.substr(5,2).c_str()); //substr(where to start, how many chars to get)
    // std::cout << "month: " << month << std::endl;

    /* Day */ int day = atoi(date.substr(8,2).c_str());;
    // std::cout << "day: " << day << std::endl;

    /* Invalid date - Generic */
    if (year < 2009 || year > 2025
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

/*
*   Returns:
*        0: Successul program execution
*       -1: Failure at program execution
*
*   Details: 
*       map.insert() method returns pair<iterator, bool>
*
*/
int main(int argc, char **argv)
{ 
    /* #1 Initial check errors and open input file passed through terminal*/
    if (!check_args(argc, argv)) // Checks error: argc must be 2 and file must be input.txt
        return(-1);
    std::ifstream file(argv[1]); //Opens file   
    if (!check_file(file)) // Checks error: file opened successfully 
        return (-1);

    /* #2 We create a map to store valid lines from input file */ 
    std::string line;
    std::map<std::string, float> myMap;

    /* Do not know why, when deleting, throws error, core dumped. */
    getline(file, line); /* 1st time using = a way to ignore first line: "date | value" */

    std::pair<std::map<std::string, float>::iterator, bool> result;
    while(getline(file, line)) //Iteration in each line
    {
        
        if (validLine(line, DO_NOT_PRINT)) /* validLine returns true == Valid line :) */
        { 
            std::cout << GREEN "\n\n-----------------------------------\n[VALID LINE] " RESET_COLOUR;
            /* Inserts new element to map */
            result = myMap.insert(std::make_pair(line, getTotalValue(line))); 
            // result = myMap.insert(std::make_pair(line, 36)); /* this works, getTotlalValue is what's failing */

            /* Displays valid line */
            std::cout << result.first->first.substr(0, 10) << " => " << result.first->first.substr(13) << " = " << result.first->second;
            std::cout << GREEN "[COMPLETED]\n----------------------------------------\n\n" RESET_COLOUR << std::endl; //PRINT HERE
        }
        else /* Invalid line */
        {
            std::cout << RED "[INVALID LINE] " RESET_COLOUR ;
            validLine(line, PRINT_ERROR); /* prints errors */
        }
    }

    return (0);
}