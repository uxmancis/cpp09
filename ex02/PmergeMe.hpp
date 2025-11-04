/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:46 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/04 19:32:01 by uxmancis         ###   ########.fr       */
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

#define GREEN "\033[32m"
#define RED "\033[0m"
#define CYAN "\033[36m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET_COLOUR "\033[0m"

enum{
    EVALUATION,
    DEBUG
};

/* PmergeMe.cpp file: */
void sortFirstAndSecond(std::vector<int> &MyVector,std::vector<int> &firstElem,std::vector<int> &secondElem);
void extractFirstAndSecond(std::vector<std::pair<int, int> > MyVector, std::vector<int> *firstElem, std::vector<int> *secondElem, int mode);
void putArgs(int argc, char **argv);
void sortPairs(std::vector<std::pair<int, int> > *MyVector);
void getPairs(int argc, char **argv, std::vector<std::pair<int, int> > *MyVector);
void putVectorPair(std::vector<std::pair<int, int> > MyVector);
void putVector(std::vector<int> vector);
void MergeVector(std::vector<int> MyVector);

/* main.cpp file: */
bool isInt(char c);
bool onlyDigits (char *str);
bool validSequence(int argc, char **argv);


#endif