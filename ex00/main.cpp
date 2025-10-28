/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:25 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/28 19:12:36 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp" 

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
            /* Inserts new element to map */
            result = myMap.insert(std::make_pair(line, getTotalValue(line))); 

            /* Displays valid line */
            std::cout << CYAN "[LINE] " RESET_COLOUR << result.first->first.substr(0, 10) << " => " << result.first->first.substr(13) << " = " << result.first->second << std::endl; //PRINT HERE
        }
        else /* Invalid line */
            validLine(line, PRINT_ERROR); /* prints errors */
    }
    return (0);
}