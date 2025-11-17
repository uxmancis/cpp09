#include "PmergeMe.hpp"

// size_t gComparisons = 0;
size_t gVectorComparisons = 0;
size_t gDequeComparisons = 0;

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

void putArgs(int argc, char **argv)
{
    int num;
    for (int i = 1; i < argc; ++i){
        num = atoi(argv[i]);
        std::cout << num << " ";
    }
    std::cout << std::endl;
}


template <typename T>
void putContainer(T vector)
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
/* Explicit instantiations: */
template void putContainer<std::vector<int> >(std::vector<int> vector);
template void putContainer<std::deque<int> >(std::deque<int> vector);

// void putVector(std::vector<int> vector)
// {
//     for (size_t i = 0; i < vector.size(); ++i)
//     {
//         if (i + 1 == vector.size())
//             std::cout << vector[i];
//         else
//             std::cout << vector[i] << ", "; /* ',' only when there are still more oponents */
//     }
//     std::cout << std::endl;
// }


/* F function calculates how many comparisons are needed to sort
*   sequence of n elements.
*
* Function src: https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91
*/
#include <cmath>
int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

bool areEqual(const std::vector<int> &vec, const std::deque<int> &deq)
{
    // Check if sizes are the same
    if (vec.size() != deq.size())
        return false;

    // Use std::equal to compare elements
    return std::equal(vec.begin(), vec.end(), deq.begin());
}


/* Merge sort compares 100% of elements. E.g.:
*       
*       A = [1, 3, 4]   i = 0
*       B = [2, 5, 6]   j = 0
*
*       if (A[i] < B[j]) {C.insert(A[i]); i++;)}
*       else {C.insert(B[j]); j++;)}
*
*       Restult: C = [1, 2, 3, 4, 5, 6]
*
* However, Ford-Johnson uses less comparisons.
*
*
*
*/
int main(int argc, char **argv)
{
    int mode = EVALUATION; /* 🥊 Choose your fighter: EVALUATION or SHOW_ALGORITHM */
    int container;
    sTimeTaken timeTaken;
    
    if (!validateInput(argc, argv))
        return (EXIT_FAILURE);

    std::cout << "Before: ";
    putArgs(argc, argv);

    unsigned int rlevel = 0;

    /********************************************* VECTOR *********************************************/
    container = VECTOR;
    std::vector<int> myVector;
    for (int i = 1; i < argc; i++)
        myVector.push_back(atoi(argv[i]));

    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "Initial input container created: ";
        putContainer(myVector);
    }
        

    myVector = fordJohnson(myVector, mode, rlevel, &timeTaken, container);



    /********************************************* DEQUE *********************************************/
    container = DEQUE;
    std::deque<int> myDeque;
    for (int i = 1; i < argc; i++)
        myDeque.push_back(atoi(argv[i]));
    
    myDeque = fordJohnson(myDeque, mode, rlevel, &timeTaken, container);


    /* Check result */
    if (areEqual(myVector, myDeque))
    {
        std::cout << "After: ";
        putContainer(myVector);
    }
    else
    {
        std::cerr << "Not same output, should not happen" << std::endl;
        return (-1);
    }

    std::cout << "Time to process a range of " << myVector.size() << " elements with st::[..] : " << timeTaken.timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << myDeque.size() << " elements with st::[..] : " << timeTaken.timeDeque << " us" << std::endl;


    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "As size of sequence is " << myVector.size() <<", then " << F(myVector.size()) << " comparisons are needed to sort the sequence." << std::endl;
        std::cout << "My VECTOR implementation has made  " << gVectorComparisons << " comparisons." << std::endl;
        std::cout << "My DEQUE implementation has made  " << gDequeComparisons << " comparisons." << std::endl;
    }
    return (0);
}