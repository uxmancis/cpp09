/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:36 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/03 16:46:03 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

enum{
  ODD, /* par */
  EVEN  /* impar */
};

void informVector(int argc, char **argv, std::vector<int> *MyVector)
{
    int num;
    for (int i = 1; i < argc; ++i){
        num = atoi(argv[i]);
        MyVector->push_back(num);
    }
}

void putVector (std::vector<int> MyVector)
{
    size_t size = MyVector.size();
    int i = 0;
    while (size > 0)
    {
        std::cout << MyVector.at(i) << " ";
        i++;
        size--;
    }
    std::cout << std::endl;
}

void MergeVector(std::vector<int> MyVector)
{
    std::vector<int> left;
    std::vector<int> right;
    size_t VectorSize = MyVector.size();
    int iterations;
    bool type;
    
    if (VectorSize % 2 == 0)
    {
        type = ODD;
        iterations = VectorSize / 2;        
    }
    else
    {
        type = EVEN;
        iterations = (VectorSize / 2) + 1;
        
    }
    // std::cout << "It's " << type << " (size = "<< VectorSize <<"), iterations left = " << iterations << std::endl;

    int i = 0;
    for (i = 0; i < iterations ; i++)
        left.push_back(MyVector[i]);

    for (; iterations < (int)VectorSize; ++iterations, ++i)
        right.push_back(MyVector[i]);
        

    std::cout << "Left" << std::endl;
    putVector(left);
    std::cout << "Right" << std::endl;
    putVector(right);

    if (left.size() > 1)
    {
        MergeVector(left);
        MergeVector(right);
    }
        
    
}

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


