/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:35:23 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/04 19:41:04 by uxmancis         ###   ########.fr       */
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
*   Ford-Johnson algorithm:
*       #1 Divide the input into pairs and sort the pairs => Merge sort
*               Input: [8, 3, 5, 9, 7]
*               Pairs: [(8, 3), (5, 9), (7)]
*               Sorted pairs: [(3, 8), (5, 9), (7)]
*
*       #2 Sort the first elements of each pair => Insert sort
*               Extract first elements: [3, 5, 7]
*               Sorted first elements: [3, 5, 7]
*
*       #3 Merge the remaining elements = Insert sort
*               Extract second elements: [8, 9]
*               Merge second elements: [8, 9]
*               Merge second elements to first elements: [3, 5, 7, 8, 9]
*
*/
int main(int argc, char **argv)
{
    int countNb = 0;
    int timeTaken = 0;
    int mode = EVALUATION; /* 🥊 Choose your fighter: EVALUATION or DEBUG */
    
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
    /* std::VECTOR container has been chosen because of the following reasons: 
    *       · Contiguous Memory: efficient for random access and iteration. Useful to access elements by index.
    *************************************************************************************************************************/
    std::vector<std::pair<int, int> > MyVector;

    std::cout << "Before: ";
    putArgs(argc, argv);
    
    /* #1 Divide arguments into pairs and sort each pair */
    getPairs(argc, argv, &MyVector); /* => getPairs(): std::vector enables iterations and accesing with index */
    if (mode == DEBUG)
    {
        std::cout << CYAN "#1  Pairs have been created: ";
        putVectorPair (MyVector);
        std::cout << RESET_COLOUR;
    }
    sortPairs(&MyVector); /* => sortPairs(): std::vector enables iterations and accesing with index */
    if (mode == DEBUG)
    {
        std::cout << CYAN "#2  Pairs have been sorted: ";
        putVectorPair (MyVector);
        std::cout << RESET_COLOUR;
    }

    /* #2 We'll create 2 containers: first and second and sort each of them
    *       first: first elements of pairs
    *       second: second elements of pairs (if not -1)
    **/
    std::vector<int> firstElem;
    std::vector<int> secondElem;
    extractFirstAndSecond(MyVector, &firstElem, &secondElem, mode);
    
    std::vector<int> MyVectorFinal;
    sortFirstAndSecond(MyVectorFinal, firstElem, secondElem);
    if (mode == DEBUG)
    {
        std::cout << CYAN "#4  MyVectorFinal result: ";
        putVector(MyVectorFinal);
        std::cout << RESET_COLOUR;
    }
    std::cout << "After: ";
    putVector(MyVectorFinal);
    std::cout << "Time to proocess a range of " << countNb << " elements with st::[..] : " << timeTaken << " us" << std::endl;
    std::cout << "Time to proocess a range of " << countNb << " elements with st::[..] : " << timeTaken << " us" << std::endl;

    /****************************************************  std::DEQUE  *****************************************************/
    /* std::DEQUE container has been chosen because of the following reasons: 
    *       · It allows efficient insertion and deletion at b
    ************************************************************************************************************************/
     
    return (0);
}