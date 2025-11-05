/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:35:23 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/05 16:13:14 by uxmancis         ###   ########.fr       */
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

bool areEqual(const std::vector<int> &vec, const std::deque<int> &deq)
{
    // Check if sizes are the same
    if (vec.size() != deq.size())
        return false;

    // Use std::equal to compare elements
    return std::equal(vec.begin(), vec.end(), deq.begin());
}

bool validateInput(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "Error: invalid argument, insert positive integer sequence (duplicates now allowed) as an argument" << std::endl;
        std::cerr << "Valid e.g.: ./PmergeMe 5 77 2 78 1 79 7 80 9 81 74 82 29  83 30" << std::endl;
        return (false);
    }
    if (!validSequence(argc, argv))
    {
        std::cerr << "Error: invalid argument, insert positive integer sequence (duplicates now allowed) as an argument" << std::endl;
        std::cerr << "Valid e.g.: ./PmergeMe 5 77 2 78 1 79 7 80 9 81 74 82 29  83 30" << std::endl;
        return (false);
    }
    return true;
}

int main(int argc, char **argv)
{
    int mode = EVALUATION; /* 🥊 Choose your fighter: EVALUATION or DEBUG */
    
    if (!validateInput(argc, argv))
        return (EXIT_FAILURE);

    /* Line 1 - Evaluation */
    std::cout << "Before: ";
    putArgs(argc, argv);
    
    /****************************************************  std::VECTOR  *****************************************************/
    /* std::VECTOR container has been chosen because of the following reasons: 
    *       · Contiguous Memory: efficient for random access and iteration. Useful to access elements by index.
    *************************************************************************************************************************/
    s_result resultVector = sortVector(argc, argv, mode);


    /****************************************************  std::DEQUE  *****************************************************/
    /* std::DEQUE container has been chosen because of the following reasons: 
    *       · It allows efficient insertion and deletion
    *       · Code implementation is direct based on code for vector, efficient to use already programmed code previously. 
    ************************************************************************************************************************/
    s_result resultDeque = sortDeque(argc, argv, mode);
    
    
    /* Line 2 - Evaluation */
    if (areEqual(resultVector.sortedVector, resultDeque.sortedDeque))
    {
        std::cout << "After: ";
        putVector(resultVector.sortedVector);
    }
    else
    {
        std::cerr << "Not same output, should not happen" << std::endl;
        return (-1);
    }
        
    /* Line 3 - Evaluation */
    std::cout << "Time to proocess a range of " << resultVector.sortedVector.size() << " elements with st::[..] : " << resultVector.timeTakenVector << " us" << std::endl;
    
    /* Line 4 - Evaluation */
    std::cout << "Time to proocess a range of " << resultVector.sortedDeque.size() << " elements with st::[..] : " << resultDeque.timeTakenDeque << " us" << std::endl;

    return (0);
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