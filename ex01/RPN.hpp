/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:11:08 by uxmancis          #+#    #+#             */
/*   Updated: 2025/10/30 18:13:21 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream> //std::cerr, std::endl
#include <stdio.h>
#include <stack>

#define GREEN "\033[32m"
#define RED "\033[0m"
#define CYAN "\033[36m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET_COLOUR "\033[0m"

/* RPN.cpp file */
void showFullStack(std::stack<int> myStack);
void letsCalculate(std::stack<int> *myStack, char op);

/* main.cpp file */
bool isSpace (char c);
bool isDigit (char digit);
bool isOperator (char op);
bool isValdArg (char **argv);


#endif