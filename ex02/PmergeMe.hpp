#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h> //EXIT_FAILURE
#include <limits.h> //INT_MAX
#include <set>
#include <stdio.h>
#include <ctime> //clock()
#include <algorithm> //std::sort, for tests

/* Colours */
#define GREEN "\033[32m"
#define RED "\033[31m" /* bold letters */
#define CYAN "\033[36m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET_COLOUR "\033[0m"

/* Change text style: */
#define BOLD "\033[1m" /* bold letters */

enum{
    EVALUATION,
    SHOW_ALGORITHM /* Show additional prints if chosen in main */
};

enum{
    DEQUE,
    VECTOR /* Show additional prints if chosen in main */
};

extern size_t gVectorComparisons;
extern size_t gDequeComparisons;

struct sTimeTaken
{
    double timeVector;
    double timeDeque;
};

struct sVector
{
    std::vector<int> originalVector;
    std::vector<int> updatedVector;
    std::vector<int> winnersVector;
    std::vector<int> losersVector;
    int              rlevel; /* Recursivity level */
    int              groupBy; /* Groups are made of n elements = level * 2 */
    int              elem1; /* 2 numbers are compared to decide position */
    int              elem2;

    std::vector<int> inputFirst;
    std::vector<int> inputSecond;
    std::vector<std::pair<int, int> > pairs;
};

/* main.cpp */
template <typename T> void putContainer(T vector);

/* PmergeMe.cpp*/
// void pendIntoMain (std::vector<int> *winners, std::vector<int> losers, int mode, int rlevel, std::vector<std::pair<int, int> > pair);
// void putPairs(std::vector<std::pair<int, int> > pairs, int rlevel, int mode);
// // std::vector<int> fordJohnson(std::vector<int> input, int mode, unsigned int rlevel);
// void storePair (const std::vector<int> originalVector, std::vector<std::pair<int, int> > &originalPairs);

template <typename T> void putLevelAndInitialInput(T input, int rlevel, int mode);

template <typename T> T fordJohnson (T input, int mode, unsigned int rlevel, sTimeTaken *timeTaken, int container);

template <typename T> void putVectorAsPairs(T vector);

template <typename T> void splitWinnersLosers(T input, T *winners, T *losers, int mode);





/************************************************************************** */
// std::vector<int> fordJohnson(sVector &sv, int mode);

/* main.cpp */
// void putVector(std::vector<int> vector);

#endif