/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 02:06:18 by edi-maio          #+#    #+#             */
/*   Updated: 2026/08/21 14:39:05 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <climits>

int RPN::process(std::string input)
{
    for (int i = 0; input[i]; i++)
    {
        if (i % 2 != 0)
        {
            if (input[i] != ' ')
                throw RPN::RPNException("Error");
        }
        else if (isdigit(input[i]))
            myStack.push(input[i] - '0');
        else if (myStack.size() >= 2)
        {
            int n1 = myStack.top();
            myStack.pop();
            int n2 = myStack.top();
            myStack.pop();
            if (input[i] == '+')
            {
                if (n2 + n1 > INT_MAX)
                    throw RPN::RPNException("Error");
                myStack.push(n2 + n1);
            }
            else if (input[i] == '-')
            {
                if (n2 - n1 < INT_MIN)
                    throw RPN::RPNException("Error");
                myStack.push(n2 - n1);
            }
            else if (input[i] == '*')
            {
                if (n2 * n1 > INT_MAX || n2 * n1 < INT_MIN)
                    throw RPN::RPNException("Error");
                myStack.push(n2 * n1);
            }
            else if (input[i] == '/')
            {
                if (n1 == 0)
                    throw RPN::RPNException("Error");
                myStack.push(n2 / n1);
            }
            else
                throw RPN::RPNException("Error");
        }
        else
            throw RPN::RPNException("Error");   
    }
    if (myStack.size() != 1)
        throw RPN::RPNException("Error");
    return (myStack.top());
}