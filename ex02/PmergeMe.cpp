/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:36 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/05 17:29:09 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

enum{
  ODD, /* par */
  EVEN  /* impar */
};

/* Function to generate the Jacobsthal sequence 
* Jacobstal sequence: determines the order of the insertion.
*
*   Objective: to sort a sequence with the fewest possible comparisons.
* 
*   J(0) = 0
*   J(1) = 1
*   J(n) = J(n-1) + 2 * J(n-2) for n >= 2
*
*   0, 1, 1, 3, 5, 11, 21, 43, ...
*
*   It provides a specific order foor sorting elements into a sorted sequence.
*
*   How does Jacobstal make more efficient secondElem to be sorted into the
*   already sorted FirstElem? It minimizes the number of comparisons required during
*   the merging process.
*
*
*/
std::vector<int> generateJacobsthalSequenceVector(size_t n)
{
    std::vector<int> jacobsthal;
    if (n == 0)
        return jacobsthal;

    jacobsthal.push_back(0); // J(0)
    if (n == 1)
        return jacobsthal;

    jacobsthal.push_back(1); // J(1)
    for (size_t i = 2; i < n; ++i)
    {
        jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]); // J(n) = J(n-1) + 2 * J(n-2)
    }
    return jacobsthal;
}

std::deque<int> generateJacobsthalSequenceDeque(size_t n)
{
    std::deque<int> jacobsthal;
    if (n == 0)
        return jacobsthal;

    jacobsthal.push_back(0); // J(0)
    if (n == 1)
        return jacobsthal;

    jacobsthal.push_back(1); // J(1)
    for (size_t i = 2; i < n; ++i)
    {
        jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]); // J(n) = J(n-1) + 2 * J(n-2)
    }
    return jacobsthal;
}

/* Insertion sort algorithm */
void sortFirstAndSecondVector(std::vector<int> &MyVectorFinal,std::vector<int> &firstElem,std::vector<int> &secondElem)
{
    // Step 1: Insertion sort firstElem (stable, simple)
    for (size_t i = 1; i < firstElem.size(); ++i)
    {
        int key = firstElem[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && firstElem[j] > key)
        {
            firstElem[j + 1] = firstElem[j];
            --j;
        }
        firstElem[j + 1] = key;
    }

    //Step 2: Insert each element from secondElem into the sorted firstElem
    int count = 0;

    
    /* Option a) Jacobstal (more optimized)
    *
    *   Try it with: ./PmergeMe 200 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57
    * 
    *       58 elements
    *       Jacobstal: 7 comparisons
    *       Non-Jacobstal: 29 comparisons
    * */
    // std::vector<int> jacobsthal = generateJacobsthalSequenceVector(secondElem.size()); /* Generates Jacobstal sequence */
    
    // for (size_t k = 0; k < jacobsthal.size(); ++k)
    // {
    //     int index = jacobsthal[k];
    //     if (index < (int)secondElem.size()) // Ensure the index is within bounds
    //     {
    //         int v = secondElem[index];
    //         std::vector<int>::iterator it = std::lower_bound(firstElem.begin(), firstElem.end(), v);
    //         firstElem.insert(it, v);
    //         count++;
    //     }
    // }
    

    /* Previous option: not optimized with Jacobstal */
    for (size_t k = 0; k < secondElem.size(); ++k)
    {
        int v = secondElem[k];
        std::vector<int>::iterator it = std::lower_bound(firstElem.begin(), firstElem.end(), v);
        firstElem.insert(it, v);
        count++;
    }

    // std::cout << "count = " << count << std::endl;
    // Copy the final sorted sequence into MyVector
    MyVectorFinal = firstElem;
}

/* Insertion sort algorithm */
void sortFirstAndSecondDeque(std::deque<int> &MyDequeFinal,std::deque<int> &firstElem,std::deque<int> &secondElem)
{

    // Insertion sort. it sorts firstElem
    /* 
    *   #1 firstElem: sorted using Insertion sort algorithm
    *   #2 generate MyDequeFinal:
    *       > VLOOKUP secondElem, WHERE? firstElem
    */
    for (size_t i = 1; i < firstElem.size(); ++i) /* we iterate though each element in the container, i = 0 already sorted */
    {
        int key = firstElem[i]; /* REFERENCE with which we want to compare our numbers */
        int j = static_cast<int>(i) - 1;

        // std::cout << CYAN "key = " << key << RESET_COLOUR << std::endl;

        /* 
        * We are comparing firstElem[j] with key (reference)
        *   · key = iterates through 100% array
        *   · firstElem[j] = previous element to key element in array
        * 
        * Logic that applies insertion sort:
        *       #1 Bigger element is identified on the RIGHT (key = reference) => enters loop
        *       #2 It compares 100% elements on the left with key = reference (j--)
        *
        * */
        while (j >= 0 && firstElem[j] > key) /* while previous number is bigger, only enters if swap is needed. Element from the right is bigger? Stops moving to the right*/
        {
            // std::cout << "> BEFORE (Left: " << firstElem[j] << ", Right: " << key << ")" << std::endl;
            // std::cout << ": j = " << j << ", i = " << i << ", [j] = " << firstElem[j] << ", [i] = " << firstElem[i] << std::endl; /* firstElem not sorted*/
            firstElem[j + 1] = firstElem[j]; /* we shift the number to the right if bigger than key */
            --j;
        }
        firstElem[j + 1] = key; /* If no swap needed, doesn't chage anything, firstElem[j+1] is the same as key, as it hasn't changed */
        // std::cout << "> AFTER: ";
        // putDeque(firstElem);
        // std::cout << "> AFTER: j = " << j << ", i = " << i << ", [j] = " << firstElem[j+1] << ", [i] = " << firstElem[i] << std::endl;

    }

    //Step 2: Insert each element from secondElem into the sorted firstElem
    /* Option a) Jacobstal (more optimized)
    *
    *   Try it with: ./PmergeMe 200 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57
    * 
    *       58 elements
    *       Jacobstal: 7 comparisons
    *       Non-Jacobstal: 29 comparisons
    * */
    // std::deque<int> jacobsthal = generateJacobsthalSequenceDeque(secondElem.size());

    // // Step 3: Insert each element from secondElem into the sorted firstElem
    // for (size_t k = 0; k < jacobsthal.size(); ++k)
    // {
    //     int index = jacobsthal[k];
    //     if (index < (int)secondElem.size()) // Ensure the index is within bounds
    //     {
    //         int v = secondElem[index];
    //         std::deque<int>::iterator it = std::lower_bound(firstElem.begin(), firstElem.end(), v);
    //         firstElem.insert(it, v);
    //     }
    // } 

    // Insert each element from secondElem into the sorted firstElem
    for (size_t k = 0; k < secondElem.size(); ++k)
    {
        int v = secondElem[k];
        std::deque<int>::iterator it = std::lower_bound(firstElem.begin(), firstElem.end(), v); /* lower bound searches (VLOOKUP) v (secondElement) in firstElem container*/
        firstElem.insert(it, v);
    }

    // Copy the final sorted sequence into MyVector
    MyDequeFinal = firstElem;
}

void extractFirstAndSecondVector(std::vector<std::pair<int, int> > MyVector, std::vector<int> *firstElem, std::vector<int> *secondElem, int mode)
{
    size_t size = MyVector.size();
    // std::cout << "extractFirstAndSecond, size = " << size << std::endl;
    int i = 0;
    while (i < (int) size)
    {
        (*firstElem).push_back(MyVector[i].first);
        if (MyVector[i].second != -1)
        {
            (*secondElem).push_back(MyVector[i].second);
        }
        i++;
    }
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << CYAN "#3  FirstElem and SecondElem containers have been created:" << std::endl;
        std::cout << "      FirstElem Vector: ";
        putVector(*firstElem);
        std::cout << "      SecondElem Vector: ";
        putVector(*secondElem);
    }
}

void extractFirstAndSecondDeque(std::deque<std::pair<int, int> > MyDeque, std::deque<int> *firstElem, std::deque<int> *secondElem, int mode)
{
    size_t size = MyDeque.size();
    // std::cout << "extractFirstAndSecond, size = " << size << std::endl;
    int i = 0;
    while (i < (int) size)
    {
        (*firstElem).push_back(MyDeque[i].first);
        if (MyDeque[i].second != -1)
        {
            (*secondElem).push_back(MyDeque[i].second);
        }
        i++;
    }
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << PINK "#3  FirstElem and SecondElem containers have been created:" << std::endl;
        std::cout << "      FirstElem Vector: ";
        putDeque(*firstElem);
        std::cout << "      SecondElem Vector: ";
        putDeque(*secondElem);
    }
}

void sortPairsVector(std::vector<std::pair<int, int> > *MyVector)
{
    for (size_t i = 0; i < MyVector->size(); ++i)
    {
        // Ensure the pair is in ascending order
        if ((*MyVector)[i].first > (*MyVector)[i].second && (*MyVector)[i].second != -1) /* Don't swap when number missing (-1)*/
        {
            std::swap((*MyVector)[i].first, (*MyVector)[i].second);
        }
    }
}

void sortPairsDeque(std::deque<std::pair<int, int> > *MyDeque)
{
    for (size_t i = 0; i < MyDeque->size(); ++i)
    {
        // Ensure the pair is in ascending order
        if ((*MyDeque)[i].first > (*MyDeque)[i].second && (*MyDeque)[i].second != -1) /* Don't swap when number missing (-1)*/
        {
            std::swap((*MyDeque)[i].first, (*MyDeque)[i].second);
        }
    }
}

void getPairsVector(int argc, char **argv, std::vector<std::pair<int, int> > *MyVector)
{
    int first; 
    int second;
    
    for (int i = 1; i < argc; i+=2 )
    {
        first = atoi(argv[i]);
        if (i + 1 < argc)
            second = atoi(argv[i + 1]);
        else
            second = -1; /* Indicator of missing number */
        MyVector->push_back(std::make_pair(first, second));
    }
}

void getPairsDeque(int argc, char **argv, std::deque<std::pair<int, int> > *MyDeque)
{
    int first; 
    int second;
    
    for (int i = 1; i < argc; i+=2 )
    {
        first = atoi(argv[i]);
        if (i + 1 < argc)
            second = atoi(argv[i + 1]);
        else
            second = -1; /* Indicator of missing number */
        MyDeque->push_back(std::make_pair(first, second));
    }
}

void putArgs(int argc, char **argv)
{
    int num;
    for (int i = 1; i < argc; ++i){
        num = atoi(argv[i]);
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void putVectorPair(std::vector<std::pair<int, int> > MyVector)
{
    for (size_t i = 0; i < MyVector.size(); ++i)
        std::cout << "(" << MyVector[i].first << ", " << MyVector[i].second << ") ";
    std::cout << std::endl;
}

void putDequePair(std::deque<std::pair<int, int> > MyDeque)
{
    for (size_t i = 0; i < MyDeque.size(); ++i)
        std::cout << "(" << MyDeque[i].first << ", " << MyDeque[i].second << ") ";
    std::cout << std::endl;
}

void putVector(std::vector<int> vector)
{
    for (size_t i = 0; i < vector.size(); ++i)
    {
        if (i + 1 == vector.size())
            std::cout << vector[i];
        else
            std::cout << vector[i] << ", "; /* ',' only when there are still more oponents */
    }
    std::cout << std::endl;
}

void putDeque(std::deque<int> deque)
{
    for (size_t i = 0; i < deque.size(); ++i)
    {
        if (i + 1 == deque.size())
            std::cout << deque[i];
        else
            std::cout << deque[i] << ", "; /* ',' only when there are still more oponents */
    }
    std::cout << std::endl;
}

void mergeSortedVectors(const std::vector<int> &left, const std::vector<int> &right, std::vector<int> &result)
{
    result.clear(); // Clear the result vector to store the merged content
    size_t i = 0, j = 0;

    // Merge the two sorted vectors
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
            result.push_back(left[i++]);
        else
            result.push_back(right[j++]);
    }

    // Add any remaining elements from the left vector
    while (i < left.size())
        result.push_back(left[i++]);

    // Add any remaining elements from the right vector
    while (j < right.size())
        result.push_back(right[j++]);
}

s_result sortVector(int argc, char **argv, int mode)
{
    if (mode == SHOW_ALGORITHM)
        std::cout << CYAN " ----------------------- sortVECTOR -----------------------" RESET_COLOUR << std::endl;
    /* ⏱️ Start measuring time */
    clock_t startTimeVector = clock();
    
    std::vector<std::pair<int, int> > MyVector;
    
    /* #1 Divide arguments into pairs and sort each pair */
    getPairsVector(argc, argv, &MyVector); /* => getPairs(): std::vector enables iterations and accesing with index */
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << CYAN "#1  Pairs have been created: ";
        putVectorPair (MyVector);
        std::cout << RESET_COLOUR;
    }
    sortPairsVector(&MyVector); /* => sortPairs(): std::vector enables iterations and accesing with index */
    if (mode == SHOW_ALGORITHM)
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
    extractFirstAndSecondVector(MyVector, &firstElem, &secondElem, mode);
    
    std::vector<int> MyVectorFinal;
    sortFirstAndSecondVector(MyVectorFinal, firstElem, secondElem);
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << CYAN "#4  MyVectorFinal result: ";
        putVector(MyVectorFinal);
        std::cout << RESET_COLOUR;
    }

    /* ⏱️ Stock measuring time */
    clock_t endTimeVector = clock();

    /* ⏱️ Calculate elapsed time in microseconds */
    double timeTakenVector = static_cast<double> (endTimeVector - startTimeVector) * 1000000.0 / CLOCKS_PER_SEC;
    

    /* Returning info to main :) */
    s_result resultVector;
    resultVector.sortedVector = MyVectorFinal;
    resultVector.timeTakenVector = timeTakenVector;

    return (resultVector);
}

s_result sortDeque(int argc, char **argv, int mode)
{
    if (mode == SHOW_ALGORITHM)
        std::cout << PINK "\n ----------------------- sortDEQUE -----------------------" RESET_COLOUR << std::endl;

    /* ⏱️ Start measuring time */
    clock_t startTimeDeque = clock();

    std::deque<std::pair<int, int> > MyDeque;

    (void)argc;
    (void)argv;
    (void)mode;

    
    /* #1 Divide arguments into pairs and sort each pair */
    getPairsDeque(argc, argv, &MyDeque); /* => getPairs(): std::vector enables iterations and accesing with index */
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << PINK "#1  Pairs have been created: ";
        putDequePair (MyDeque);
        std::cout << RESET_COLOUR;
    }
    sortPairsDeque(&MyDeque); /* => sortPairs(): std::vector enables iterations and accesing with index */
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << PINK "#2  Pairs have been sorted: ";
        putDequePair (MyDeque);
        std::cout << RESET_COLOUR;
    }

    /* #2 We'll create 2 containers: first and second and sort each of them
    *       first: first elements of pairs
    *       second: second elements of pairs (if not -1)
    **/
    std::deque<int> firstElem;
    std::deque<int> secondElem;
    extractFirstAndSecondDeque(MyDeque, &firstElem, &secondElem, mode);
    
    std::deque<int> MyDequeFinal;
    sortFirstAndSecondDeque(MyDequeFinal, firstElem, secondElem);
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << PINK "#4  MyVectorFinal result: ";
        putDeque(MyDequeFinal);
        std::cout << RESET_COLOUR << std::endl;
    }

    /* ⏱️ Stock measuring time */
    clock_t endTimeDeque = clock();

    /* ⏱️ Calculate elapsed time in microseconds */
    double timeTakenDeque = static_cast<double> (endTimeDeque - startTimeDeque) * 1000000.0 / CLOCKS_PER_SEC;;

    /* Returning info to main :) */
    s_result resultDeque;
    resultDeque.sortedDeque = MyDequeFinal;
    resultDeque.timeTakenDeque = timeTakenDeque;
    return (resultDeque);
}