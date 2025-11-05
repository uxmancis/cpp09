/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:10:29 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/03 10:34:29 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void showFullStack(std::stack<int> myStack)
{
    std::cout << "[SHOWFULLSTACK]: ";
    size_t sizeMyStack = myStack.size();
    std::cout << "Size = " << sizeMyStack << " => ";

    std::cout << "[";
    while (sizeMyStack > 0)
    {
        std::cout << myStack.top() << ",";
        myStack.pop(); /* Removes the one already shown in previous line */
        sizeMyStack--;
    }
    std::cout << "]" << std::endl;
}

void letsCalculate(std::stack<int> *myStack, char op)
{
    int number1;
    int number2;
    int result = 0; /* -Werro0r asks for it */

    number2 = myStack->top(); /* access to top element and convert to int */
    
    myStack->pop(); /* removes top element*/
    number1 = myStack->top();
    myStack->pop();

    if (op == '+')
        result = number1 + number2;
    else if (op == '-')
        result = number1 - number2;
    else if (op == '*')
        result = number1 * number2;
    else if (op == '/')
        result = number1 / number2;

    myStack->push(result); /* converted back to char */
    // showFullStack(*myStack);
}