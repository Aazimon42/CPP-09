/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 22:26:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/08/21 14:39:01 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
 
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    _db = other._db;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_db = other._db;
	return (*this);
}
 
BitcoinExchange::~BitcoinExchange() {}

static bool checkDate(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return (false);
    for (int i = 0; i < 10; ++i)
    {
        if (i != 4 && i != 7 && !std::isdigit(date[i]))
            return (false);
    }
    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return (false);
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (leap)
        daysInMonth[1] = 29;
    if (day > daysInMonth[month - 1])
        return (false);
    return (true);
}

void BitcoinExchange::parseDBLine(std::string line)
{
	if (line.empty())
		throw BitcoinException("Error: empty line in file");
	std::size_t comma = line.find(',');
	if (comma == std::string::npos)
		throw BitcoinException("Error: wrong format in file => " + line);
	std::string date = line.substr(0, comma);
	if (!checkDate(date))
		throw BitcoinException("Error: wrong date format in file => " + date);
	std::string rateStr = line.substr(comma + 1);
	double rate = 0.0;
	std::istringstream ss(rateStr);
	if (!(ss >> rate))
		throw BitcoinException("Error: wrong rate format in file => " + rateStr);
	_db[date] = rate;
}

void BitcoinExchange::loadDatabase(std::string file)
{
    std::ifstream infile;

    infile.open(file.c_str());
    if (!infile.is_open())
        throw BitcoinException("Error: unable to open file " + file);
    std::string line;
	std::getline(infile, line);
    if (line != "date,exchange_rate")
		throw BitcoinException("Error: wrong header in file " + file + " (expected: <date,exchange_rate>)");
	while (std::getline(infile, line))
	{
		try { parseDBLine(line); }
		catch (const BitcoinExchange::BitcoinException &e)
		{
			std::cerr << e.what() << std::endl;
			continue ;
		}
	}
}

void BitcoinExchange::parseCSVLine(std::string line)
{
    if (line.empty())
        throw BitcoinException("Error: empty line in file");
    std::size_t pipe = line.find(" | ");
    if (pipe == std::string::npos)
        throw BitcoinException("Error: bad input => " + line);
    std::string date = line.substr(0, pipe);
    if (!checkDate(date))
        throw BitcoinException("Error: bad input => " + line);
    std::string valueStr = line.substr(pipe + 3);
    double value = 0.0;
    std::istringstream ss(valueStr);
    if (!(ss >> value))
        throw BitcoinException("Error: bad input => " + line);
    if (value < 0)
        throw BitcoinException("Error: not a positive number.");
    if (value > 1000)
        throw BitcoinException("Error: too large a number.");
    double rate   = getRate(date);
    double result = value * rate;
    std::cout << date << " => " << value << " = " << result << std::endl;
}

void BitcoinExchange::process(std::string file)
{
    std::ifstream infile(file.c_str());
	if (!infile.is_open())
		throw std::runtime_error("Error: unable to open file " + file);
	std::string line;
	std::getline(infile, line);
	if (line != "date | value")
    	throw BitcoinException("Error: wrong header in file " + file + " (expected: <date | value>)");
	while (std::getline(infile, line))
	{
		try { parseCSVLine(line); }
		catch (const BitcoinExchange::BitcoinException &e)
		{
			std::cerr << e.what() << std::endl;
			continue ;
		}
	}
}

double BitcoinExchange::getRate(std::string date)
{
    std::map<std::string, double>::const_iterator it = _db.lower_bound(date);

	if (it != _db.end() && it->first == date)
		return it->second;
	if (it == _db.begin())
		throw BitcoinException("Error: no earlier date for => " + date);
	--it;
	return (it->second);
}