/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:36 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/04 19:37:15 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

enum{
  ODD, /* par */
  EVEN  /* impar */
};

void sortFirstAndSecond(std::vector<int> &MyVectorFinal,std::vector<int> &firstElem,std::vector<int> &secondElem)
{
    // Insertion sort firstElem (stable, simple)
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

    // Insert each element from secondElem into the sorted firstElem
    for (size_t k = 0; k < secondElem.size(); ++k)
    {
        int v = secondElem[k];
        std::vector<int>::iterator it = std::lower_bound(firstElem.begin(), firstElem.end(), v);
        firstElem.insert(it, v);
    }

    // Copy the final sorted sequence into MyVector
    MyVectorFinal = firstElem;
}

void extractFirstAndSecond(std::vector<std::pair<int, int> > MyVector, std::vector<int> *firstElem, std::vector<int> *secondElem, int mode)
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
    if (mode == DEBUG)
    {
        std::cout << CYAN "#3  FirstElem and SecondElem containers have been created:" << std::endl;
        std::cout << "      FirstElem Vector: ";
        putVector(*firstElem);
        std::cout << "      SecondElem Vector: ";
        putVector(*secondElem);
        std::cout << RESET_COLOUR << std::endl;
    }
}

void sortPairs(std::vector<std::pair<int, int> > *MyVector)
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

void getPairs(int argc, char **argv, std::vector<std::pair<int, int> > *MyVector)
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

/* 
*   The recursive approach mirrors the divide-and-conquer paradigm.
*/
// void MergeVector(std::vector<int> MyVector)
// {
//     std::vector<int> left;
//     std::vector<int> right;
//     size_t VectorSize = MyVector.size();
//     int iterations;
//     bool type;
    
//     if (VectorSize % 2 == 0)
//     {
//         type = ODD;
//         iterations = VectorSize / 2;        
//     }
//     else
//     {
//         type = EVEN;
//         iterations = (VectorSize / 2) + 1;
        
//     }
//     // std::cout << "It's " << type << " (size = "<< VectorSize <<"), iterations left = " << iterations << std::endl;

//     int i = 0;
//     for (i = 0; i < iterations ; i++)
//         left.push_back(MyVector[i]);

//     for (; iterations < (int)VectorSize; ++iterations, ++i)
//         right.push_back(MyVector[i]);
        

//     std::cout << "Left" << std::endl;
//     putVector(left);
//     std::cout << "Right" << std::endl;
//     putVector(right);

//     if (left.size() > 2) /* #1 Divides the input sequence int pairs of two elements*/
//     {
//         MergeVector(left);
//         MergeVector(right);
//     }
    
//     mergeSortedVectors(left, right, MyVector);

//     std::cout << CYAN "Merged: ";
//     putVector(MyVector);
//     std::cout << RESET_COLOUR << std::endl;
    
// }

// template <typename T>
// void putContainer (T MyContainer)
// {
//     size_t size = MyContainer.size();
//     int i = 0;
//     while (size > 0)
//     {
//         std::cout << MyContainer.at(i) << " ";
//         i++;
//         size--;
//     }
// }


