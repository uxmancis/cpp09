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

void putArgs(int argc, char **argv)
{
    int num;
    for (int i = 1; i < argc; ++i){
        num = atoi(argv[i]);
        std::cout << num << " ";
    }
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
    int mode = SHOW_ALGORITHM; /* 🥊 Choose your fighter: EVALUATION or DEBUG */
    
    if (!validateInput(argc, argv))
        return (EXIT_FAILURE);

    std::cout << "Before: ";
    putArgs(argc, argv);

    // sVector sv; /*sv, Struct Vector */

    std::vector<int> originalVector;
    for (int i = 1; i < argc; i++)
        originalVector.push_back(atoi(argv[i]));

    std::cout << "Initial input container created: ";
    putVector(originalVector);


    /* Values' inizialization */
    // sv.rlevel = 0;
    // sv.groupBy = 1;
    // sv.updatedVector = sv.originalVector;


    
    unsigned int rlevel = 0;
    fordJohnson(originalVector, mode, rlevel);

    (void) mode;
    return (0);
}