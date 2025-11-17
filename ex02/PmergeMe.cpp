#include "PmergeMe.hpp"

/* getPairElem
*
*   Input: winnerElem, the element in winners sequence that we want to look up
*   Return: its pair element in loser sequence
**/
template <typename T>
int getPairElem(int winnerElem, const T pair)
{
    // std::cout << "inside getPairElem, winnerElem = " << winnerElem << std::endl;
    for (int i = 0; i < (int)pair.size(); i++)
    {
        if (pair[i].first == winnerElem) //1st option
            return (pair[i].second);
        else if (pair[i].second == winnerElem) //2nd option
            return (pair[i].first);
    }
    return (-2); /* this should not happen */
}
/* Explicit instantiations: */
template int getPairElem(int winnerElem, const std::vector<std::pair<int, int> > pair);
template int getPairElem(int winnerElem, const std::deque<std::pair<int, int> > pair);


/* even means it's multiple of 2, but 2 + 1*/
bool isEven(int i)
{
    if (i % 2 == 0)
    {
        // std::cout << "Bikoiti";
        return (true);
    }
    else
    {
        // std::cout << "Bakoiti";
        return (false);
    }
        
}


/* 
*   E.g.:  4     7     8
*         [0]   [1]   [2]
*
*   index = 2 has no pair
*   size = 3
*   
*   index + 1 <
*
*/
template <typename T>
bool hasPair(const T container, int index)
{
    if ((index + 1) < (int)container.size())
    {
        // std::cout << "bikotedun";
        return (true);
    }
        
    // std::cout << "solterin";
    return (false);
}
/* Explicit instantiations: */
template bool hasPair(const std::vector<int> container, int index);
template bool hasPair(const std::deque<int> container, int index);



/* const to avoid unnecessary copies */
template <typename T>
void putVectorAsPairs(T container)
{
    // std::cout << RESET_COLOUR "putVectorAsPairs, vector = ";
    // putContainer(vector);
    for (int i = 0; i < (int)container.size(); i++)
    {
        // std::cout << "i = " << i << ", vector[i] = " << vector[i] << std::endl;
        if (isEven(i) && hasPair(container, i)) /* even (bikoiti: 0, 2, 4, 6...)*/
            std::cout << "(" << container[i] << ", " << container[i + 1] << ") ";
        else if(isEven(i) && !hasPair(container, i))
            std::cout << container[i] << std::endl;
        // std::cout <<YELLOW"kaixo:" << i << ", " << vector[i] << RESET_COLOUR;
    }
    std::cout << std::endl;
}
/* Explicit instantiation: */
template void putVectorAsPairs<const std::vector<int> >(const std::vector<int>);
template void putVectorAsPairs<const std::deque<int>  >(const std::deque<int>);


template <typename T>
void insertEvenElem(const T src, T *dst)
{
    for (int i = 0; i < (int)src.size(); i++)
    {
        if (i % 2 == 0)
            (*dst).push_back(src[i]);
    }
}
/* Explicit instantiations: */
template void insertEvenElem(const std::vector<int> src, std::vector<int> *dst);
template void insertEvenElem(const std::deque<int> src, std::deque<int> *dst);



template <typename T>
void insertOddElem(const T src, T *dst)
{
    for (int i = 0; i < (int)src.size(); i++)
    {
        if (i % 2 == 1)
            (*dst).push_back(src[i]);
    }
}
/* Explicit instantiations: */
template void insertOddElem(const std::vector<int> src, std::vector<int> *dst);
template void insertOddElem(const std::deque<int> src, std::deque<int> *dst);



/* Jacobstal sequence: 
*       
*       0, 1, 1, 3, 5, 11, 21, 43, 85, 
*       171, 341, 683, 1365, 2731, 5461, 
*       10923, 21845, 43691, 87381, 
*       174763, 349525, …
*
*    J(0) = 0
*    J(1) = 1
*    J(n) = J(n-1) + 2 * J(n-2), for n >= 2
*
*    current = previous + 2 × (previous of the previous)
*
*    Using the Jacobstal sequence minimizes the number
*    of comparisons required.
*          
*/
template <typename T>
T generateJacobsthalSequence(int n, int mode)
{
    T jacobsthal;
    if (n <= 0) return jacobsthal;

    jacobsthal.push_back(0); // J(0)
    if (n == 1) return jacobsthal;

    jacobsthal.push_back(1); // J(1)
    for (int i = 2; i < n; ++i) {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        if (next >= n) break; // Stop if the sequence exceeds the size of losers
        jacobsthal.push_back(next);
    }
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "        Jacobsthal sequence: ";
        putContainer(jacobsthal); // Assuming putVector prints a vector
    }
    return jacobsthal;
}
/* Explicit instantiation: */
template std::vector<int> generateJacobsthalSequence<std::vector<int> >(int n, int mode);
template std::deque<int> generateJacobsthalSequence<std::deque<int> >(int n, int mode);


/* putVectorPairs*/
template <typename T>
void putPairs(T pairs, int rlevel, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        
        std::cout << CYAN "    ********* In this Level: " << rlevel << " | Show (previously defined) pairs: ********* " RESET_COLOUR << std::endl;;
        for (size_t i = 0; i < pairs.size(); ++i)
            std::cout << "    [" << i << "]: (" << pairs[i].first << ", " << pairs[i].second << ") " << std::endl;
        std::cout << CYAN "    ****************************************" RESET_COLOUR<< std::endl;
    }  
}
template void putPairs<std::vector<std::pair<int,int> > >(std::vector<std::pair<int,int> >, int rlevel, int mode);
template void putPairs<std::deque<std::pair<int,int>  > >(std::deque<std::pair<int,int>  >, int rlevel, int mode);


/* couples are made of 2 members, order which is first/second doesn't matter here
* as vector is still not sorted. That's why chosen names for variables are elem1
* and elem2. 
*
* In the future we'll want to get the couple of 1 element, independent of whether it
* is bigger/smaller, first/second, whatever.*/
template <typename T, typename U>
void storePair (const T inputVector, U *pair, int mode, int rlevel)
{
    int elem1; /* couples*/ 
    int elem2;
    int singleElem = -5; /* no existent, initialization */
    bool isSingle = false;

    (void) singleElem;

    if (!isEven((int)inputVector.size()))
        isSingle = true;

    for (int i = 0; i < (int)inputVector.size(); i+=2)
    {
        if (isSingle && (i + 1) == (int)inputVector.size()) /* single element is stored here */
        {
            isSingle = true;
            singleElem = inputVector[i];
            elem1 = inputVector[i];
            elem2 = -1;
        }
        else if (i % 2 == 0 && hasPair(inputVector, i)) /* pairs are stored  here */
        {
            elem1 = inputVector[i];
            elem2 = inputVector[i+1];
        }
        (*pair).push_back(std::make_pair(elem1, elem2));
    }

    (void) rlevel;
    (void) mode;
}
/* Explicit instantiations: */
template void storePair<std::vector<int>, std::vector<std::pair<int,int> > >(const std::vector<int> inputVector, std::vector<std::pair<int, int> > *pair, int mode, int rlevel);
template void storePair<std::deque<int>,  std::deque<std::pair<int,int>  > >(const std::deque<int> inputVector, std::deque<std::pair<int, int> > *pair, int mode, int rlevel);





template <typename T>
void splitWinnersLosers(T input, T *winners, T *losers, int mode)
{
     insertOddElem(input, winners);
     insertEvenElem(input, losers);

     if (mode == SHOW_ALGORITHM)
     {
        std::cout << "    Winners (main) = ";
        putContainer(*winners);
        
        std::cout << "    Losers (pend) =  ";
        putContainer(*losers);
     } 
}
/* Explicit instantiations: */
template void splitWinnersLosers<std::vector<int> >(std::vector<int> input, std::vector<int> *winners, std::vector<int> *losers, int mode);
template void splitWinnersLosers<std::deque<int> >(std::deque<int> input, std::deque<int> *winners, std::deque<int> *losers, int mode);




template <typename T>
void putResult(T winners, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "        RESULT - Winners (main) ALREADY 100% SORTED = ";
        putContainer(winners);
    }
}
/* Explicit instantiations: */
template void putResult<std::vector<int> >(std::vector<int> winners, int mode);
template void putResult<std::deque<int>  >(std::deque<int> winners, int mode);





struct CountingCompare
{
    int flag;
    CountingCompare(int f = VECTOR) : flag(f) {}
    bool operator()(int a, int b) const
    {
        if (flag == VECTOR)
            ++gVectorComparisons;
        else if (flag == DEQUE)
            ++gDequeComparisons;
        return a < b;
    }
};
// struct CountingCompare
// {
//     int flag;
//     CountingCompare(int f = 0) : flag(f){}
//     bool operator()(int a, int b) const
//     {
//         ++gComparisons;
//         return a < b;
//     }
// };


// helper: map container<T,Alloc> -> container<bool,...>
template <typename Container> struct bool_container_for; // primary (undefined)

template <typename V, typename Alloc>
struct bool_container_for< std::vector<V, Alloc> >
{
    typedef std::vector<bool> type;
};

template <typename V, typename Alloc>
struct bool_container_for< std::deque<V, Alloc> >
{
    typedef std::deque<bool> type;
};


template <typename T, typename U>
void pendIntoMain (T *winners, T losers, int mode, int rlevel, U pair, int container)
{
    /* insert losers to winners: jacobstal, binarysearch */

    (void) rlevel;
    if (mode == SHOW_ALGORITHM)
        std::cout << "    > Let's put pend into main! (here, TODO!)" << std::endl;
    
    if (losers.size() == 1 && (*winners).size() == 1) /* Particular case, handled manually */
    {
        int tmpValue = (*winners)[0];
        (*winners).clear();
        (*winners).push_back(losers[0]);
        (*winners).push_back(tmpValue);
    }
    else
    {
        /* Generate Jacobsthal sequence */
        T jacobsthal = generateJacobsthalSequence<T>(losers.size(), mode);

        CountingCompare cmp(container);
        
        /* Binary search I: Insert losers into winners using Jacobsthal sequence */
        typename bool_container_for<T>::type inserted(losers.size(), false); // Track inserted elements
        // std::vector<bool> inserted(losers.size(), false); // Track inserted elements
        for (typename T::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
            int index = *it;
            if (index < (int)losers.size() && !inserted[index]) {
                int elem = losers[index];
                // std::vector<int>::iterator it = std::lower_bound((*winners).begin(), (*winners).end(), elem, cmp); //Next line is an optimization
                typename T::iterator it = std::lower_bound((*winners).begin(), std::find((*winners).begin(), (*winners).end(), getPairElem(elem, pair)), elem, cmp);
                (*winners).insert(it, elem);
                inserted[index] = true;
            }
        }

        /* Binary search II: Insert any remaining losers */
        for (size_t k = 0; k < losers.size(); ++k) {
            if (!inserted[k]) {
                int elem = losers[k];
                typename T::iterator it = std::lower_bound((*winners).begin(), (*winners).end(), elem, cmp);
                (*winners).insert(it, elem);
            }
        }
    }
    putResult(*winners, mode);

}
/* Explicit instantiations: */
template void pendIntoMain<std::vector<int>, std::vector<std::pair<int,int> > > (std::vector<int> *winners, std::vector<int> losers, int mode, int rlevel, std::vector<std::pair<int, int> > pair, int container);
template void pendIntoMain<std::deque<int>, std::deque<std::pair<int,int> > > (std::deque<int> *winners, std::deque<int> losers, int mode, int rlevel, std::deque<std::pair<int, int> > pair, int container);



template <typename T>
void sortPairsLocally(T *input, int mode, int container)
{
    for (int i = 0; i < (int)((*input).size() - 1); i+=2)
    {
        if ((*input)[i] > (*input)[i+1])
            std::swap((*input)[i], (*input)[i+1]);
        if (container == VECTOR)
            gVectorComparisons++;
        else if (container == DEQUE)
            gDequeComparisons++;
    }

    if (mode == SHOW_ALGORITHM)
    {
        std::cout << CYAN "    Input (SORTED): ";
        putVectorAsPairs(*input);
        std::cout << RESET_COLOUR;
    } 
}
/* Explicit instantiations: */
template void sortPairsLocally<std::vector<int> >(std::vector<int> *input, int mode, int container);
template void sortPairsLocally<std::deque<int> >(std::deque<int> *input, int mode, int container);



/* Initial print in green and blue :) */
template <typename T>
void putLevelAndInitialInput(T input, int rlevel, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "\n*****************************************************************************" << std::endl;
        std::cout << GREEN "⭐ Level " << rlevel << " | Input: ";
        // putVector(input);
        putVectorAsPairs(input);
        std::cout << RESET_COLOUR ;
    }
}
/* Explicit instantiations: */
template void putLevelAndInitialInput<std::vector<int> >(std::vector<int> input, int rlevel, int mode); 
template void putLevelAndInitialInput<std::deque<int> >(std::deque<int> input, int rlevel, int mode); 




/* hasPair2
*
*       Checks whether is winnerElem has or has NOT a pair checking in pair variable.
*
*       Returns true in 2 cases:
*           1) winnerElem appears in 1st position and second position is != -1 (no pair)
*           2) winnerElem appears in 2nd position
*/
template <typename T>
bool hasPair2(int winnerElem, const T pair)
{
    for (int i = 0; i < (int)pair.size(); i++)
    {
        if ((winnerElem == pair[i].first && pair[i].second != -1)
            || winnerElem == pair[i].second)
            return (true);
    }
    return (false);
}
/* Explicit instantiations: */
template bool hasPair2<std::vector<std::pair<int,int> > >(int winnerElem, const std::vector<std::pair<int, int> > pair);
template bool hasPair2<std::deque<std::pair<int,int>  > >(int winnerElem, const std::deque<std::pair<int, int> > pair);


template <typename T, typename U>
void putInfo(const T winners, const T losers, const U pair, int rlevel, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "\n\n*****************************************************************************" << std::endl;
        std::cout << YELLOW "...we continue in Level " << rlevel << ":" RESET_COLOUR << std::endl;
        putPairs(pair, rlevel, mode);
        std::cout << std::endl;
    

        std::cout << PINK "    > What do we have already?" RESET_COLOUR << std::endl;
        std::cout << "        Winners (main) ALREADY 100% SORTED = ";
        putContainer(winners);

        std::cout << PINK "    > Next step is to reorderLosers according to their winner pairs." RESET_COLOUR << std::endl;
        std::cout << "        (Before) Losers before being moved: ";
        putContainer(losers);
    }
}
/* Explicit instantiations: */
template void putInfo<std::vector<int>, std::vector<std::pair<int, int> > >(const std::vector<int> winners, const std::vector<int> losers, const std::vector<std::pair<int, int> > pair, int rlevel, int mode);
template void putInfo<std::deque<int>, std::deque<std::pair<int, int> > >(const std::deque<int> winners, const std::deque<int> losers, const std::deque<std::pair<int, int> > pair, int rlevel, int mode);

template <typename T>
void putInfo2(T losers, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << GREEN "        Losers (pend) ALREADY MOVED ACCORDING TO MAIN =  ";
        putContainer(losers);
        std::cout << RESET_COLOUR << std::endl;
    }
}
/* Explicit instantiations: */
template void putInfo2<std::vector<int> >(std::vector<int> losers, int mode);
template void putInfo2<std::deque<int> >(std::deque<int> losers, int mode);


/* Losers are moved according to its pair in winners (sorted) */
template <typename T, typename U>
void reorderLosers (const T winners, T *losers, const U pair, int rlevel, int mode)
{
    putInfo(winners, *losers, pair, rlevel, mode);


    bool isSingle = false;
    int singleElem = -2;
    /* Single element is stored in case it exists */
    if (losers->size() == winners.size() + 1)
    {
        isSingle = true;
        singleElem = (*losers)[losers->size() - 1]; /* singleElem, element in last position, size -1 */
        // std::cout << "singleElem = " << singleElem << std::endl;
    }
        
    /* New positions for elements in losers according to their pair in winner */
    (*losers).clear();
    for(int i = 0; i < (int)winners.size(); i++)
        (*losers).push_back(getPairElem(winners[i], pair)); /* according to their pair in winners (main)*/
    if (isSingle == true && singleElem!= -2) /* single Elem is pushed back if exists*/
        (*losers).push_back(singleElem);

    putInfo2(*losers, mode);
}
/* Explicit instantiations: */
template void reorderLosers <std::vector<int>, std::vector<std::pair<int,int> > > (const std::vector<int> winners, std::vector<int> *losers, const std::vector<std::pair<int, int> > pair, int rlevel, int mode);
template void reorderLosers <std::deque<int>, std::deque<std::pair<int,int> > >(const std::deque<int> winners, std::deque<int> *losers, const std::deque<std::pair<int, int> > pair, int rlevel, int mode);


template <typename T>
T fordJohnson (T input, int mode, unsigned int rlevel, sTimeTaken *timeTaken, int container)
{
    /* ⏱️ Start measuring time */
    clock_t startTime = clock();
    
    rlevel++;
    putLevelAndInitialInput(input, rlevel, mode); /* show initial state: ⭐ Level | Input in GREEN*/
    
    /* Sort pairs locally: winners is always sorted this way */
    sortPairsLocally(&input, mode, container); /* show Input (SORTED) in CYAN */

    /* if Winners' size > 1, then split-call FordJohnson */
    if (input.size() > 1) /* when only 1 element in winner will not do anything, not split, neither jacobstal, nor call fordjohnson again :) */
    {
        /* #0 Create pairs IDs: new in each level of recursion */
        std::vector<std::pair<int, int> > newPair;
        storePair(input, &newPair, mode, rlevel);

        /* #1 Split Winners and Losers*/
        T winners; /* also called 'main' */
        T losers; /* also called 'pend' */
        splitWinnersLosers(input, &winners, &losers, mode);

        /* #2 Recursively sort Winners*/
        winners = fordJohnson(winners, mode, rlevel, timeTaken, container);

        /* #3 Reorder Losers according to sorted winners */
        reorderLosers(winners, &losers, newPair, rlevel, mode);

        /* #4 Put Pend (Losers) into Main (Winners)*/
        pendIntoMain(&winners, losers, mode, rlevel, newPair, container);

        return (winners); /* result */
    }
    else if (mode == SHOW_ALGORITHM)
        std::cout << RED "<<< No more recursion>>> " RESET_COLOUR << std::endl << std::endl; /* when 'Noo more recursion' hits, then "...we continue in Level will be executed n times pending"*/

    /* ⏱️ Stock measuring time */
    clock_t endTime = clock();
    /* ⏱️ Calculate elapsed time in microseconds */
    double totalTime = static_cast<double> (endTime - startTime) * 1000000.0 / CLOCKS_PER_SEC;
    
    
    if (container == VECTOR)
        timeTaken->timeVector = totalTime;
    else if (container == DEQUE)
        timeTaken->timeDeque = totalTime;

    return (input); /* not necessary, just becausee we have to return something :)*/
}
/* Explicit instantiation: */
template std::vector<int> fordJohnson<std::vector<int> >(std::vector<int>, int, unsigned int, sTimeTaken *timeTaken, int container);
template std::deque<int> fordJohnson<std::deque<int> >(std::deque<int>, int, unsigned int, sTimeTaken *timeTaken, int container);
