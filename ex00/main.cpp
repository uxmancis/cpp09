/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:25 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/28 14:19:17 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> //ifstream is read only
#include <map> //std:map container
// #include <cstdio.h> //open
#include <string> //std::stoi
#include <cstdlib> //std::stoi
#include <climits> //INT_MAX, INT_MIN

enum what_to_print
{
    PRINT_ERROR, /* DO print errors*/
    DO_NOT_PRINT /* Do NOT print errors */
};

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
    /* Year */
    int year = atoi(date.substr(0,4).c_str()); //substr(where to start, how many chars to get)
    // std::cout << "Year: " << year << std::endl;

    /* Month */
    int month = atoi(date.substr(5,2).c_str()); //substr(where to start, how many chars to get)
    // std::cout << "month: " << month << std::endl;

    /* Day */
    int day = atoi(date.substr(8,2).c_str());;
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
    /* Negative values are not accepted */
    if (value < 0)
    {
        if (instruction == PRINT_ERROR)
        {
            std::cout << "Error: not a positive number." << std::endl;
        }    
        return (false);
    }
    /* Valid values are positive and in INT range */
    if (value > -1 && value < INT_MAX)
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
int validLine(std::string line, what_to_print instruction)
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
        // isDateValid = isValidDate(date, myMap); /* prints invalid line errors */
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

int main(int argc, char **argv)
{ 
    /* Enter a valid argument to program */
    if (argc != 2 || (std::string)argv[1] != "input.txt")
    {
        std::cerr << "Error: could not open file, try a valid filename" << std::endl;
        std::cout << "E.g.: ./btc input.txt" << std::endl;
        return (-1);
    }
        
    /* Open file */
    std::ifstream file(argv[1]); /* Opens file */
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file, try a valid filename" << std::endl;
        std::cout << "E.g.: ./btc input.txt" << std::endl;
        return (-1);
    }
        


    /* Put Result */ 
    std::string line;
    std::map<std::string, float> myMap;
    // std::map<std::string, float>::const_iterator it = myMap.begin();
    
    // int i = 0; //Used to ignore 1st line

    getline(file, line); /* 1st time using = a way to ignore first line: "date | value" */
    myMap.insert(std::make_pair("", 0));
    myMap.insert(std::make_pair("", 0));

    std::pair<std::map<std::string, float>::iterator, bool> result;
    while(getline(file, line)/* && it!= myMap.end()*/) //Iteration in each line
    {
        // if (i == 0) /* Ignores first line: "date | value" */
        //     i++;
        // else
        // {
        // std::cout << "Processing line: " << line << std::endl;
        // if (valid)    
        
        
        
        if (validLine(line, DO_NOT_PRINT)) /* When not valid, already prints errors */
        {
            // std::cout << "VALID line|";
            
            /* Inserts new element to map */
            result = myMap.insert(std::make_pair(line, 3.5)); /* .insert() method returns pair<iterator, bool> */
            // myMap.insert(std::make_pair(line, 3.5)); 
            
            /* Restarts it to map beginning */
            // it = myMap.begin();
            // it++;
            std::cout << result.first->first << " " << result.first->second << std::endl; //PRINT HERE
        }
        else
        {
            validLine(line, PRINT_ERROR); /* prints errors */
            // std::cout << "INVALID line" << std::endl;
        }
        // if (it == myMap.end())
        //     break;
        
        // it++;
        // std::cout << it->first << " " << it->second << std::endl; //PRINT HERE
    }

    
    return (0);
}