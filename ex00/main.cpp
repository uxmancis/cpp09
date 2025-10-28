/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:25 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/28 10:59:45 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> //ifstream is read only
#include <map> //std:map container
// #include <cstdio.h> //open
#include <string> //std::stoi
#include <cstdlib> //std::stoi

/* isValidDate
*
*   Prints messages when date is invalid.
*
*   Returns:
*       true -> Valid date
*       false -> Invalid date
*/
bool isValidDate(std::string date)
{
    /* Year */
    int year = atoi(date.substr(0,4).c_str()); //substr(where to start, how many chars to get)
    std::cout << "Year: " << year << std::endl;

    /* Month */
    int month = atoi(date.substr(5,2).c_str()); //substr(where to start, how many chars to get)
    std::cout << "month: " << month << std::endl;

    /* Day */
    int day = atoi(date.substr(8,2).c_str());;
    std::cout << "day: " << day << std::endl;

    /* Invalid date - Generic */
    if (year < 0 || year > 2100
        || month < 1 || month > 12
        || date[4] != '-' || date[7] != '-'
        || day < 1 || day > 31)
    {
        std::cerr << "Error: bad input" <<  " => " << date << std::endl;
        return(false);
    }
    
    /* Invalid date - Particular case: February not leap-year, 28th max*/
    if (month == 2)
    {
        if (day > 28)
        {
            std::cerr << "Error: bad input" <<  " => " << date << std::endl;
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
bool isValidValue(std::string v)
{
    std::cout << "----------------------------" << std::endl;
    std::cout << "isValidValue, Value = " << v << std::endl;
    std::cout << "size = " << v.size() << std::endl;
    
    if (v.size() > 10) /* Cuidado! 10 is max int */
    {
        std::cout << "Error: too large a number." << std::endl;
        return (false);
    }
        

    long int value = atoi(v.c_str());

    

    /* Negative values are not accepted */
    if (value < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return (false);
    }
        
        
    std::cout << "Valueeee :) = " << value << std::endl;
    return (true);
}

void validLine(std::string line, std::map<std::string, float> result)
{
    (void)result;
    /* Line Info: */
    std::cout << "Line = " << line << std::endl;
    std::cout << "Size: " << line.size() << std::endl;
    
    if (line.size() >= 10)
    {
        std::string date = line.substr(0,10); //get date
        std::cout << "Date: " << date << std::endl;
        isValidDate(date); /* prints invalid line errors */
    }

    if (line.size() >= 12)
    {
        std::string value = line.substr(13); //get date
        std::cout << "Value: " << value << std::endl;
        isValidValue(value);
    }

    std::cout << "----------------------\n" << std::endl;
    // std::string value = 
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
    std::map<std::string, float> result;

    while(getline(file, line)) //Iteration in each line
    {
        if (line != "date | value") /* "date | value" 1st line is ignored. */
            validLine(line, result);
            //print
        // std::string date = line.substr(0,10);
        // std::string value = line.substr(12);
        // // std::cout << "Line 1: " << line << std::endl;
        // std::cout << date << " => " << value << std::endl;
    }

    
    char c = file.get();
    
    while (file.good())
    {
        std::cout << c;
        c = file.get();
        std::cout << "=> ";
    }
    file.close();

    
    
    

    return (0);
}