/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:35:23 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/03 16:17:06 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool isInt(char c)
{
    (void)c;
    return (true);
}


bool onlyDigits (char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}

bool validSequence(int argc, char **argv)
{ 
    std::set<int> seenNumbers; /* To track duplicates */
    for (int i = 1; i < argc ; i++)
    {
        /* Check 1: 100% elements are positive integers */
        if (!onlyDigits(argv[i])) /* 1.1.- Only digits are allowed */
            return (false);
        
        long int num = std::atoi(argv[i]); /* 1.2.- Only positive*/
        if (num < 0 || num > INT_MAX)
            return (false);

        /* Check 2: duplicated elements are not allowed*/
        if (seenNumbers.find(num) != seenNumbers.end()) /* if it finds it = duplicate*/
            return (false);
            
        seenNumbers.insert(num);
    }
    return (true);
}

/* Merge-Insertion Sort is a Divide and Conquer algorithm.
*  It combines: merge sort and insertion sortA
*
*   Insertion sort: https://www.youtube.com/watch?v=JU767SDMDvA
*       · From left to right
*       · Move each element to the right position in array
*
*
*   Merge sort: https://www.youtube.com/watch?v=4VqmGXwpLqc
*       · Usually done recursively
*       · Divide and conquer: problem divided into smaller problems
*  
*
*/
int main(int argc, char **argv)
{
    int countNb = 0;
    int timeTaken = 0;

    
    
    if (argc == 1)
    {
        std::cerr << "Error: invalid argument, insert positive integer sequence (duplicates now allowed) as an argument" << std::endl;
        std::cerr << "Valid e.g.: ./PmergeMe 3 5 9 7 4" << std::endl;
        return (EXIT_FAILURE);
    }
    if (!validSequence(argc, argv))
    {

        std::cerr << "Error: invalid argument, insert positive integer sequence (duplicates now allowed) as an argument" << std::endl;
        std::cerr << "Valid e.g.: ./PmergeMe 3 5 9 7 4" << std::endl;
        return (EXIT_FAILURE);
    }
    
    /****************************************************  std::VECTOR  *****************************************************/
    std::vector<int> MyVector;
    informVector(argc, argv, &MyVector);
    std::cout << "Before: ";
    // putContainer(MyVector);
    putVector (MyVector);

    //get it sorted
    MergeVector(MyVector);    
    
    std::cout << "After: " << std::endl;
    std::cout << "Time to proocess a range of " << countNb << " elements with st::[..] : " << timeTaken << " us" << std::endl;
    std::cout << "Time to proocess a range of " << countNb << " elements with st::[..] : " << timeTaken << " us" << std::endl;
     
    return (0);
}