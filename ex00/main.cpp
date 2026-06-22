/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 21:50:52 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/22 01:45:43 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
 
int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: Program must take one file as an argument" << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange btc;
		btc.loadDatabase("data.csv");
		btc.process(av[1]);
	}
	catch (const BitcoinExchange::BitcoinException &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
