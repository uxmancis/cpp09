#include "PmergeMe.hpp"

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
bool hasPair(std::vector<int> vector, int index)
{
    if ((index + 1) < (int)vector.size())
    {
        // std::cout << "bikotedun";
        return (true);
    }
        
    // std::cout << "solterin";
    return (false);
}

void putVectorAsPairs(std::vector<int> vector)
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

void insertEvenElem(std::vector<int> src, std::vector<int> *dst)
{
    for (int i = 0; i < (int)src.size(); i++)
    {
        if (i % 2 == 0)
            (*dst).push_back(src[i]);
    }
}

void insertOddElem(std::vector<int> src, std::vector<int> *dst)
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

std::vector<int> generateJacobsthalSequence(int n) {
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
    return jacobsthal;
}


std::vector<int> fordJohnson(std::vector<int> input, int mode, unsigned int rlevel)
{
    (void) mode;
    // std::cout << "kaixo berriz! :)" << std::endl;

    /* Next Recursivity Level, elements must be grouped by 2^rlevel
    *       rlevel     groupBy 
    *         1           2 (2¹)
    *         2           4 (2²)             
    *         3           8 (2³)
    *         4           16 (2⁴)
    ****************************************************************/
    rlevel++;
    // sv.groupBy = sv.groupBy * 2; /* always pairs! https://medium.com/@mohammad.ali.ibrahim.525/ford-johnson-algorithm-merge-insertion-4b024f0c3d42 */

    std::cout << "\n*****************************************************************************" << std::endl;
    std::cout << GREEN "⭐ Level " << rlevel << " | Input: ";
    // putVector(input);
    putVectorAsPairs(input);
    std::cout << RESET_COLOUR ;

    /* Sort pairs locally */
    for (int i = 0; i < (int)(input.size() - 1); i+=2)
    {
        if (input[i] > input[i+1])
            std::swap(input[i], input[i+1]);
    }

    std::cout << CYAN "    Input (SORTED): ";
    putVectorAsPairs(input);
    std::cout << RESET_COLOUR;

    /* Create winner and loser sequences */
    if (input.size() > 1) /* when only 1 element in winner will not do anything, not split, neither jacobstal, nor call fordjohnson again :) */
    {
        /* also called 'pend'. If odd, right has 1 more element than left*/
        std::vector<int> winners;
        insertOddElem(input, &winners);
        std::cout << "    Winners (main) = ";
        putVector(winners);

        std::vector<int> losers; /* also called 'main' */
        insertEvenElem(input, &losers);
        std::cout << "    Losers (pend) =  ";
        putVector(losers);

        /* I think nothing should happen here */

        // if (winners.size() >= 1)
        winners = fordJohnson(winners, mode, rlevel);
            

        /* insert losers to winners: jacobstal, binarysearch */
        std::cout << "\n*****************************************************************************" << std::endl;
        std::cout << YELLOW "...we continue in Level " << rlevel << RESET_COLOUR << std::endl;
        std::cout << "    Winners (main) ALREADY 100% SORTED = ";
        putVector(winners);
        std::cout << "    Losers (pend) =  ";
        putVector(losers);

        std::cout << YELLOW << "Let's put pend into main! (here, TODO!)" << RESET_COLOUR << std::endl;
        if (losers.size() == 1 && winners.size() == 1) /* Particular case, handled manually */
        {
            int tmpValue = winners[0];
            winners.clear();
            winners.push_back(losers[0]);
            winners.push_back(tmpValue);
        }
        else
        {
            /* Generate Jacobsthal sequence */
            std::vector<int> jacobsthal = generateJacobsthalSequence(losers.size());
            std::cout << "    Jacobsthal sequence: ";
            putVector(jacobsthal); // Assuming putVector prints a vector

            /* Binary search I: Insert losers into winners using Jacobsthal sequence */
            std::vector<bool> inserted(losers.size(), false); // Track inserted elements
            for (std::vector<int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it) {
                int index = *it;
                if (index < (int)losers.size() && !inserted[index]) {
                    int elem = losers[index];
                    std::vector<int>::iterator it = std::lower_bound(winners.begin(), winners.end(), elem);
                    winners.insert(it, elem);
                    inserted[index] = true;
                }
            }

            /* Binary search II: Insert any remaining losers */
            for (size_t k = 0; k < losers.size(); ++k) {
                if (!inserted[k]) {
                    int elem = losers[k];
                    std::vector<int>::iterator it = std::lower_bound(winners.begin(), winners.end(), elem);
                    winners.insert(it, elem);
                }
            }

            /* Binary search: insert pend in main */
            // for (size_t k = 0; k < losers.size(); ++k)
            // {
            //     int elem = losers[k];
            //     std::vector<int>::iterator it = std::lower_bound(winners.begin(), winners.end(), elem);
            //     winners.insert(it, elem);
                
            //     // count++;
            // }

        }

        

        std::cout << "    RESULT - Winners (main) ALREADY 100% SORTED = ";
        putVector(winners);
        return (winners);
        

        
        std::cout << "*********************************************************" << std::endl;
    }
    else
        std::cout << RED "<<< No more recursion>>> " RESET_COLOUR << std::endl << std::endl; /* when 'Noo more recursion' hits, then "...we continue in Level will be executed n times pending"*/


    return (input); /* not necessary, just becausee we have to return something :)*/
}






















































































/************************************************************************************************************************************************************************************************************** */

// void putVectorPair(std::vector<std::pair<int, int> > MyVector)
// {
//     for (size_t i = 0; i < MyVector.size(); ++i)
//         std::cout << "(" << MyVector[i].first << ", " << MyVector[i].second << ") ";
//     std::cout << std::endl;
// }

// /*
// *   sv: struct vector that contains all needed info to sort vector
// *
// */
// std::vector<int> fordJohnson(sVector &sv, int mode)
// {
//     (void) mode;

//     /* ----- #1 make pairs --------------------------------------------------------------------------------*/
//     size_t size = sv.inputSecond.size();

//     if (size <= 1) /* Already sorted */
//         return (sv.inputSecond);

//     std::cout << YELLOW "Letsgo! " << std::endl;
//     std::cout << "> First: ";
//     putVector(sv.inputFirst);
//     std::cout << "> Second: ";
//     putVector(sv.inputSecond);
//     std::cout << RESET_COLOUR << std::endl;

//     int first;
//     int second;
//     for (int i = 0; i < (int) size; i+=2)
//     {
//         first = sv.inputSecond[i];
//         if (i + 1 < (int)size)
//             second = sv.inputSecond[i + 1];
//         else
//             second = -1; /* Unpaired element */
//         sv.pairs.push_back(std::make_pair(first, second)); /* first and second both share index :) */
//     }
//     sv.inputSecond.clear();
//     std::cout << "#1 Pairs created: ";
//     putVectorPair(sv.pairs);




//     /* ----- #2 sort pairs --------------------------------------------------------------------------------*/
//     for (size_t i = 0; i < sv.pairs.size(); ++i)
//     {
//         // Ensure the pair is in ascending order
//         if (sv.pairs[i].first > sv.pairs[i].second && sv.pairs[i].second != -1) /* Don't swap when number missing (-1)*/
//         {
//             std::swap(sv.pairs[i].first, sv.pairs[i].second);
//         }
//     }
//     std::cout << "#2 Pairs sorted: ";
//     putVectorPair(sv.pairs);



//     // ----- #3 Split: create 2 sequences: ------------------------------------------------------------------------*/
//     for (size_t i = 0; i < sv.pairs.size(); i++)
//     {
//         sv.inputFirst.push_back(sv.pairs[i].first); 
//         sv.inputSecond.push_back(sv.pairs[i].second); 
//     }
//     // std::cout << "#3 Splitted sequences created: " << std::endl;
//     // std::cout << "> First: ";
//     // putVector(sv.inputFirst);
//     // std::cout << "> Second: ";
//     // putVector(sv.inputSecond);

    

//     //#4 Sort Second, recursively
//     std::cout << CYAN "SPLIT DONE - Before calling recursivity! " << std::endl;
//     std::cout << "> First: ";
//     putVector(sv.inputFirst);
//     std::cout << "> Second: ";
//     putVector(sv.inputSecond);
//     std::cout << RESET_COLOUR << std::endl;

//     if (sv.inputSecond.size() > 1)
//     {
//         sVector tempSv;
//         tempSv.inputSecond = sv.inputSecond;
//         tempSv.inputFirst.clear();
//         tempSv.pairs.clear();
        
//         tempSv.inputSecond = fordJohnson(tempSv, mode);

//         sv.inputSecond = tempSv.inputSecond;
//     }
   
//     std::cout << GREEN "COMPLETED Recursivity" RESET_COLOUR << std::endl;

//     // std::sort(sv.inputSecond.begin(), sv.inputSecond.end());

//     //#5 Put rest of numbers into already sorted Second sequence
//     //Jacobstal
//     //Binary search: implemented using std::lower_bound

//     // std::cout << "size of First = " << sv.inputFirst.size() << std::endl;
//     for (size_t i = 0; i < sv.inputFirst.size(); i++)
//     {
//         int elem = sv.inputFirst[i];
//         std::vector<int>::iterator it = std::lower_bound(sv.inputSecond.begin(), sv.inputSecond.end(), elem);
//         sv.inputSecond.insert(it, elem);
//     }
//     std::cout << "#5 Rest elements in First inserted into Second (already sorted): " << std::endl;
//     std::cout << "> First: ";
//     putVector(sv.inputFirst);
//     std::cout << "> Second: ";
//     putVector(sv.inputSecond);

//     // (void) mode;

//     return(sv.inputFirst);
// }