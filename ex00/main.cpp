/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 19:20:47 by bootjan       #+#    #+#                 */
/*   Updated: 2024/01/23 16:44:28 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Exchange.hpp"

int	main(int argc, const char** argv)
{
	if (argc != 2)
		{ std::cerr << "Error: must give two arguments" << std::endl; return EXIT_FAILURE; }
	if (access(argv[1], R_OK) == -1)
		{ std::cerr << "Error: file '" << argv[1] << "' doesn't exist or can't be accessed" << std::endl; return EXIT_FAILURE; }
	Exchange	btc(argv[1]);
	try
	{
		btc.loadData();
		// btc.printData();
		btc.matchRates();
	}
	catch(const Exchange::ExchangeException& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
