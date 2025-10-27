/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:25 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/27 14:25:02 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> //ifstream is read only
#include <map> //std:map container
// #include <cstdio.h> //open
#include <string> //std::stoi
#include <cstdlib> //std::stoi

bool isValidDate(std::string date)
{
    /* Year */
    int year = stoi(date.substr(0,4)); //substr(where to start, how many chars to get)
    std::cout << "Year: " << year << std::endl;

    /* Month */
    int month = stoi(date.substr(5,2)); //substr(where to start, how many chars to get)
    std::cout << "month: " << month << std::endl;

    /* Day */
    int day = stoi(date.substr(8,2));;
    std::cout << "day: " << day << std::endl;


    if (year >= 0 || year <= 2100
        || month < 1 || month > 12
        || date[4] != '-' || date[7] != '-'
        || day < 1 || day > 31)
    {
        std::cerr << "Error: invalid month in date" << std::endl;
        return(false);
    }

    return(true);
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
        isValidDate(date);
    }

    if (line.size() >= 12)
    {
        std::string value = line.substr(12); //get date
        std::cout << "Value: " << value << std::endl;
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