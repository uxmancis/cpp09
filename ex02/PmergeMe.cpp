#include "PmergeMe.hpp"

/* getPairElem
*
*   Input: winnerElem, the element in winners sequence that we want to look up
*   Return: its pair element in loser sequence
**/
int getPairElem(int winnerElem, const std::vector<std::pair<int, int> > pair)
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

/* isMergePossible
*
*   Checks a hypothesis. Would it be possible to continue merging in next level?
*   It creates a tmp_groupBy, which represents the hypothetical groupBy in potential
*   next level.
*
*   It is used to determine whether if program must call fordJohnson function again in
*   recursion or whether if it's time to start going back from recursion.
*
*/
bool isMergePossible (sVector sv)
{
    int tmp_groupBy = sv.groupBy * 2;

    // std::cout << "updatedVector = " ;
    // putVector(sv.updatedVector);
    if ((int)sv.updatedVector.size() > tmp_groupBy)
        return (true);
    // std::cout << "No More Merge possible, size = " << sv.updatedVector.size() <<", groupBy = " << tmp_groupBy << std::endl;
    return (false);
}

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
bool hasPair(const std::vector<int> vector, int index)
{
    if ((index + 1) < (int)vector.size())
    {
        // std::cout << "bikotedun";
        return (true);
    }
        
    // std::cout << "solterin";
    return (false);
}

/* const to avoid unnecessary copies */
void putVectorAsPairs(const std::vector<int> vector)
{
    // std::cout << RESET_COLOUR "putVectorAsPairs, vector = ";
    // putVector(vector);
    for (int i = 0; i < (int)vector.size(); i++)
    {
        // std::cout << "i = " << i << ", vector[i] = " << vector[i] << std::endl;
        if (isEven(i) && hasPair(vector, i)) /* even (bikoiti: 0, 2, 4, 6...)*/
            std::cout << "(" << vector[i] << ", " << vector[i + 1] << ") ";
        else if(isEven(i) && !hasPair(vector, i))
            std::cout << vector[i] << std::endl;
        // std::cout <<YELLOW"kaixo:" << i << ", " << vector[i] << RESET_COLOUR;
    }
    std::cout << std::endl;
}

void insertEvenElem(const std::vector<int> src, std::vector<int> *dst)
{
    for (int i = 0; i < (int)src.size(); i++)
    {
        if (i % 2 == 0)
            (*dst).push_back(src[i]);
    }
}

void insertOddElem(const std::vector<int> src, std::vector<int> *dst)
{
    for (int i = 0; i < (int)src.size(); i++)
    {
        if (i % 2 == 1)
            (*dst).push_back(src[i]);
    }
}

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

std::vector<int> generateJacobsthalSequence(int n, int mode)
{
    std::vector<int> jacobsthal;
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
        putVector(jacobsthal); // Assuming putVector prints a vector
    }
    return jacobsthal;
}

/* putVectorPairs*/
void putPairs(std::vector<std::pair<int, int> > pairs, int rlevel, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        
        std::cout << CYAN "    ********* In this Level: " << rlevel << " | Show (previously defined) pairs: ********* " RESET_COLOUR << std::endl;;
        for (size_t i = 0; i < pairs.size(); ++i)
            std::cout << "    [" << i << "]: (" << pairs[i].first << ", " << pairs[i].second << ") " << std::endl;
        std::cout << CYAN "    ****************************************" RESET_COLOUR<< std::endl;
    }  
}


/* couples are made of 2 members, order which is first/second doesn't matter here
* as vector is still not sorted. That's why chosen names for variables are elem1
* and elem2. 
*
* In the future we'll want to get the couple of 1 element, independent of whether it
* is bigger/smaller, first/second, whatever.*/
void storePair (const std::vector<int> inputVector, std::vector<std::pair<int, int> > *pair, int mode, int rlevel)
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
    // if (isSingle == true)
        // std::cout << "[single] = " << singleElem << std::endl;

    (void) rlevel;
    (void) mode;
    // if (mode == SHOW_ALGORITHM) /* I think I don't want this print */
    // {
    //     std::cout << std::endl;
    //     putPairs(*pair, rlevel, mode);
    //     std::cout << std::endl;
    // }
}

void splitWinnersLosers(std::vector<int> input, std::vector<int> *winners, std::vector<int> *losers, int mode)
{
     insertOddElem(input, winners);
     insertEvenElem(input, losers);

     if (mode == SHOW_ALGORITHM)
     {
        std::cout << "    Winners (main) = ";
        putVector(*winners);
        
        std::cout << "    Losers (pend) =  ";
        putVector(*losers);
     }
        
}

void putResult(std::vector<int> winners, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "        RESULT - Winners (main) ALREADY 100% SORTED = ";
        putVector(winners);
    }
}

struct CountingCompare
{
    bool operator()(int a, int b) const
    {
        ++gComparisons;
        return a < b;
    }
};

void pendIntoMain (std::vector<int> *winners, std::vector<int> losers, int mode, int rlevel, std::vector<std::pair<int, int> > pair)
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
        std::vector<int> jacobsthal = generateJacobsthalSequence(losers.size(), mode);

        CountingCompare cmp;
        
        /* Binary search I: Insert losers into winners using Jacobsthal sequence */
        std::vector<bool> inserted(losers.size(), false); // Track inserted elements
        for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
            int index = *it;
            if (index < (int)losers.size() && !inserted[index]) {
                int elem = losers[index];
                // std::vector<int>::iterator it = std::lower_bound((*winners).begin(), (*winners).end(), elem, cmp); //Next line is an optimization
                std::vector<int>::iterator it = std::lower_bound((*winners).begin(), std::find((*winners).begin(), (*winners).end(), getPairElem(elem, pair)), elem, cmp);
                (*winners).insert(it, elem);
                inserted[index] = true;
            }
        }

        /* Binary search II: Insert any remaining losers */
        for (size_t k = 0; k < losers.size(); ++k) {
            if (!inserted[k]) {
                int elem = losers[k];
                std::vector<int>::iterator it = std::lower_bound((*winners).begin(), (*winners).end(), elem, cmp);
                (*winners).insert(it, elem);
            }
        }
    }
    putResult(*winners, mode);

}

void sortPairsLocally(std::vector<int> *input, int mode)
{
    for (int i = 0; i < (int)((*input).size() - 1); i+=2)
    {
        if ((*input)[i] > (*input)[i+1])
            std::swap((*input)[i], (*input)[i+1]);
        // gComparisons++;
    }

    if (mode == SHOW_ALGORITHM)
    {
        std::cout << CYAN "    Input (SORTED): ";
        putVectorAsPairs(*input);
        std::cout << RESET_COLOUR;
    } 
}

/* Initial print in green and blue :) */
void putLevelAndInitialInput(std::vector<int> input, int rlevel, int mode)
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

/* hasPair2
*
*       Checks whether is winnerElem has or has NOT a pair checking in pair variable.
*
*       Returns true in 2 cases:
*           1) winnerElem appears in 1st position and second position is != -1 (no pair)
*           2) winnerElem appears in 2nd position
*/
bool hasPair2(int winnerElem, const std::vector<std::pair<int, int> > pair)
{
    for (int i = 0; i < (int)pair.size(); i++)
    {
        if ((winnerElem == pair[i].first && pair[i].second != -1)
            || winnerElem == pair[i].second)
            return (true);
    }
    return (false);
}

void putInfo(const std::vector<int> winners, const std::vector<int> losers, 
    const std::vector<std::pair<int, int> > pair, int rlevel, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << "\n\n*****************************************************************************" << std::endl;
        std::cout << YELLOW "...we continue in Level " << rlevel << ":" RESET_COLOUR << std::endl;
        putPairs(pair, rlevel, mode);
        std::cout << std::endl;
    

        std::cout << PINK "    > What do we have already?" RESET_COLOUR << std::endl;
        std::cout << "        Winners (main) ALREADY 100% SORTED = ";
        putVector(winners);

        std::cout << PINK "    > Next step is to reorderLosers according to their winner pairs." RESET_COLOUR << std::endl;
        std::cout << "        (Before) Losers before being moved: ";
        putVector(losers);
    }
}

void putInfo2(std::vector<int> losers, int mode)
{
    if (mode == SHOW_ALGORITHM)
    {
        std::cout << GREEN "        Losers (pend) ALREADY MOVED ACCORDING TO MAIN =  ";
        putVector(losers);
        std::cout << RESET_COLOUR << std::endl;
    }
}

/* Losers are moved according to its pair in winners (sorted) */
void reorderLosers (const std::vector<int> winners, std::vector<int> *losers, 
        const std::vector<std::pair<int, int> > pair, int rlevel, int mode)
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

/* always pairs! https://medium.com/@mohammad.ali.ibrahim.525/ford-johnson-algorithm-merge-insertion-4b024f0c3d42 */
std::vector<int> fordJohnson(std::vector<int> input, int mode, unsigned int rlevel)
{
    /* ⏱️ Start measuring time */
    clock_t startTimeVector = clock();
    
    rlevel++;
    putLevelAndInitialInput(input, rlevel, mode); /* show initial state: ⭐ Level | Input in GREEN*/
    
    /* Sort pairs locally: winners is always sorted this way */
    sortPairsLocally(&input, mode); /* show Input (SORTED) in CYAN */

    /* if Winners' size > 1, then split-call FordJohnson */
    if (input.size() > 1) /* when only 1 element in winner will not do anything, not split, neither jacobstal, nor call fordjohnson again :) */
    {
        /* #0 Create pairs IDs: new in each level of recursion */
        std::vector<std::pair<int, int> > newPair;
        storePair(input, &newPair, mode, rlevel);

        /* #1 Split Winners and Losers*/
        std::vector<int> winners; /* also called 'main' */
        std::vector<int> losers; /* also called 'pend' */
        splitWinnersLosers(input, &winners, &losers, mode);

        /* #2 Recursively sort Winners*/
        winners = fordJohnson(winners, mode, rlevel);

        /* #3 Reorder Losers according to sorted winners */
        reorderLosers(winners, &losers, newPair, rlevel, mode);

        /* #4 Put Pend (Losers) into Main (Winners)*/
        pendIntoMain(&winners, losers, mode, rlevel, newPair);

        return (winners); /* result */
    }
    else
    {
        if (mode == SHOW_ALGORITHM)
            std::cout << RED "<<< No more recursion>>> " RESET_COLOUR << std::endl << std::endl; /* when 'Noo more recursion' hits, then "...we continue in Level will be executed n times pending"*/
    }

    /* ⏱️ Stock measuring time */
    clock_t endTimeVector = clock();
    /* ⏱️ Calculate elapsed time in microseconds */
    double timeTakenVector = static_cast<double> (endTimeVector - startTimeVector) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "Time to proocess a range of " << input.size() << " elements with st::[..] : " << timeTakenVector << " us" << std::endl;

    return (input); /* not necessary, just becausee we have to return something :)*/
}
