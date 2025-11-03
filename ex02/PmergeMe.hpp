/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:46 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/03 16:17:26 by uxmancis         ###   ########.fr       */
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

/* PmergeMe.cpp file: */
void informVector(int argc, char **argv, std::vector<int> *MyVector);
void putVector (std::vector<int> MyVector);
void MergeVector(std::vector<int> MyVector);

/* main.cpp file: */
bool isInt(char c);
bool onlyDigits (char *str);
bool validSequence(int argc, char **argv);


#endif