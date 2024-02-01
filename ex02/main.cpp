/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:24:08 by bootjan           #+#    #+#             */
/*   Updated: 2024/01/27 21:44:24 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


int	main(int ac, const char** av)
{
	if (ac == 1)
		{ std::cerr << "Error" << std::endl; return EXIT_FAILURE; }
	int*	args = new int[ac - 1];
	if (parseArgs(ac, av, args) == false)
		{ delete[] args; std::cerr << "Error" << std::endl; return EXIT_FAILURE; }
	printArgs(args, ac - 1);
	printSortedArgs(args, ac - 1);
	try
	{
		std::list<int> list = PmergeMe::timedSort<std::list>(args, (size_t)ac - 1, "list");
		std::vector<int> vector = PmergeMe::timedSort<std::vector>(args, (size_t)ac - 1, "vector");
		std::deque<int> deque = PmergeMe::timedSort<std::deque>(args, (size_t)ac - 1, "deque");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	delete[] args;
	return EXIT_SUCCESS;
}
