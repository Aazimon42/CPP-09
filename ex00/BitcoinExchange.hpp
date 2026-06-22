/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 21:52:41 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/22 01:47:03 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <string>
# include <map>

class BitcoinExchange
{
    public:
    	BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        void loadDatabase(std::string file);
        void process(std::string file);
        double getRate(std::string date);
        class BitcoinException : public std::exception
        {
            public:
                BitcoinException(const std::string &msg) : _msg(msg) {}
                virtual ~BitcoinException() throw() {}
                virtual const char* what() const throw() { return _msg.c_str(); }

            private:
                std::string _msg;
        };
    private:
        std::map<std::string, double> _db;
        void parseDBLine(std::string line);
        void parseCSVLine(std::string line);
};

#endif