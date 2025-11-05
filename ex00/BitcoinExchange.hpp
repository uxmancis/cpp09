/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:22:43 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/05 16:33:07 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream> //ifstream is read only
#include <map> //std:map container
// #include <cstdio.h> //open
#include <string> //std::stoi
#include <cstdlib> //std::stoi
#include <climits> //INT_MAX, INT_MIN

#define GREEN "\033[32m"
#define RED "\033[0m"
#define CYAN "\033[36m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET_COLOUR "\033[0m"

enum what_to_print
{
    PRINT_ERROR, /* DO print errors*/
    DO_NOT_PRINT /* Do NOT print errors */
};

enum error_mgmt
{
    STOP,
    OK
};

/* BitcoinExchange.cpp file*/
std::string getClosestValue(std::ifstream &dbFile, std::string dateInput);
float       getValueInDate (std::string line);
float       getTotalValue (std::string line);

/* main.cpp file */
bool        isValidDate(std::string date, what_to_print instruction);
bool        isValidValue(std::string valueStr, what_to_print instruction);
bool validLine(std::string line, what_to_print instruction, error_mgmt &mode);
bool        check_args(int argc, char **argv);
bool        check_file(std::ifstream &file);



#endif