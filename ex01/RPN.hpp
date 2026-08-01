/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 02:06:21 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/24 19:35:09 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN
{
    private:
        std::stack<int> myStack;
    public:
        int process(std::string input);
        class RPNException : public std::exception
        {
            public:
                RPNException(const std::string &msg) : _msg(msg) {}
                virtual ~RPNException() throw() {}
                virtual const char* what() const throw() { return _msg.c_str(); }
            private:
                std::string _msg;
        };
};

#endif