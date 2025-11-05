/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:15:57 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/05 12:59:06 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool isSpace (char c)
{
    if (c == ' ' || c == '\f' || 
        c == '\n' || c == '\r' || 
        c == '\t' || c == '\v')
        return (true);
    // printf("NOT a SPACE\n");
    return (false);
}

bool isDigit (char digit)
{
    if (digit >= '0' && digit <= '9') 
        return (true);
    // printf("NOT a valid DIGIT, digit = %d\n", digit);
    return (false);
}

bool isOperator (char op)
{
    if (op == '+' || op == '-'
        || op == '*' || op == '/')
        return (true);

    // printf("NOT a valid OPERATOR, op = %c\n", op);
    return (false);
}

/* Makes sure 100% elements (separated by spaces)
* in argv[1] are valid digits or operator.
*
*   Returns:
*       true = if 100% valid elements (argv[1] is 100% valid)
*       false = when no valid element was found
*/
bool isValdArg (char **argv)
{
    int i = 0;
    // char element;

    /* Passes initial spaces */
    while (isSpace(argv[1][i]))
        i++;
    
    /* 2 checks here:
    * (*1) => Make sure element is valid Digit or Operator
    * (*2) => Make sure there is an space just after the element
    * (*3) => An operator canNOT be followed by another operator element. After spaces, digit mandatory.
    **/
    while (argv[1][i] != '\0')
    {
        if (!isDigit(argv[1][i]) && !isOperator(argv[1][i])) //(*1)
        {
            // printf("here\n");
            return (false);
        }
        else /* If element IS digit or operator */
        {
            // printf("VALID ELEMENT = %c\n", argv[1][i]);

            /* (*2) Next char in argv[1] must be a space */
            if (argv[1][i+1] && !isSpace(argv[1][i+1])) /* (*2) Next element must be a space. If next element exists and is not valid digit or operator*/
                return (false);
        }
        i++;
        /* Pass n spaces in between elements until getting to the next element. */
        while (isSpace(argv[1][i]))
            i++;
    }
    // std::cout << "✅ [VALID ARGS] Let's calculate! :)" << std::endl;
    return (true);
}    

/* Polish notation (PN) is a mathematical notation in which operators
*  precede their operands.
*       E.g.: + 3 4                 E.g.: / 8 2               E.g.: x (- 5 6) 7
*       Result = 7                  Result = 4                Result = -7
*
*  Ours in subject is Reverse Polish Notation.
*  How does RPN work? Operators (*, /, -, +) are applied to the tw most recent
*                    numbers in stack. No brackers are needed.
*
*  Conclusion: we always have to take the first element in line. 
*
*  To stack means 'apilar' in Spanish.
*
*   8 9 * 9 - 9 - 9 - 4 - 1 +
*   72 9 - 9 - 9 - 4 - 1 +
*   63 9 - 9 - 4 - 1 +
*   54 - 9 - 4 - 1 +
*   45 - 4 - 1 +
*   41 1 +
*   42
*
*   7  7  *  7  -
*   49  7  -
*   42
*
*   1  2  *  2  /  2  *  2  4  -  +
*   2  2  /  2  *  2  4  -  +
*   1  2  *  2  4  -  + 
*   2  2  4  -  +
*   2 -2  +
*   0
*   
*   2 / 3 --> / 2 3
*   Polish notation, no need for brackets: 5 (1 + 2) => x 5 + 1 2
*
*
*/
int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: number of arguments must be 2" << std::endl;
        std::cerr << "Try e.g.: ./RPN '8 9 * 9 - 9 - 9 - 4 - 1 +'" << std::endl;
        return (-1);
    }
    if (!isValdArg(argv))
    {
        std::cerr << "Error: invalid arguments" << std::endl;
        std::cerr << "Try e.g.: ./RPN '8 9 * 9 - 9 - 9 - 4 - 1 +' //with double quotation marks" << std::endl;
        return (-1);
    }
    
    std::stack<int> myStack;
    
    char op; /* operator */

    int i = 0;
    while (argv[1][i] != '\0')
    {
        while (isSpace(argv[1][i]))
            i++;
        if (isDigit(argv[1][i]))
        {
            myStack.push(argv[1][i] - '0');
            // showFullStack(myStack);
        }
        else if(isOperator(argv[1][i]))
        {
            op = argv[1][i];
            letsCalculate(&myStack, op);
            // showFullStack(myStack);
        }
        i++;
    }
    // std::cout << "[FINAL RESULT]: ";
    std::cout << myStack.top() << std::endl;
    return (0);
}