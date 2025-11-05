/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:46 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/05 16:12:36 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define GREEN "\033[32m"
#define RED "\033[0m"
#define CYAN "\033[36m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET_COLOUR "\033[0m"

enum{
    EVALUATION,
    SHOW_ALGORITHM /* Show additional prints if chosen in main */
};

struct s_result
{
    std::vector<int> sortedVector;
    double timeTakenVector;
    
    std::deque<int> sortedDeque;
    double timeTakenDeque;  
};

/* PmergeMe.cpp file: */
void sortFirstAndSecondVector(std::vector<int> &MyVectorFinal,std::vector<int> &firstElem,std::vector<int> &secondElem);
void sortFirstAndSecondDeque(std::deque<int> &MyDequeFinal,std::deque<int> &firstElem,std::deque<int> &secondElem);
void extractFirstAndSecondVector(std::vector<std::pair<int, int> > MyVector, std::vector<int> *firstElem, std::vector<int> *secondElem, int mode);
void extractFirstAndSecondDeque(std::deque<std::pair<int, int> > MyDeque, std::deque<int> *firstElem, std::vector<int> *secondElem, int mode);
void putArgs(int argc, char **argv);
void sortPairsVector(std::vector<std::pair<int, int> > *MyVector);
void sortPairsDeque(std::deque<std::pair<int, int> > *MyDeque);
void getPairsVector(int argc, char **argv, std::vector<std::pair<int, int> > *MyVector);
void getPairsDeque(int argc, char **argv, std::deque<std::pair<int, int> > *MyDeque);
void putVectorPair(std::vector<std::pair<int, int> > MyVector);
void putDequePair(std::deque<std::pair<int, int> > MyDeque);
void putVector(std::vector<int> vector);
void putDeque(std::deque<int> deque);
void MergeVector(std::vector<int> MyVector);
s_result sortVector(int argc, char **argv, int mode);
s_result sortDeque(int argc, char **argv, int mode);

/* main.cpp file: */
bool isInt(char c);
bool onlyDigits (char *str);
bool validSequence(int argc, char **argv);


#endif