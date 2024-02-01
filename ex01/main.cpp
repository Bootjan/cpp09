/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:10:24 by bootjan           #+#    #+#             */
/*   Updated: 2024/01/23 20:40:50 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int		main(int ac, const char** av)
{
	if (ac != 2)
		{ std::cout << "Error: must give 2 arguments" << std::endl; return EXIT_FAILURE; }
	RPN	rpn(av[1]);
	try
	{
		rpn.checkFormat();
		int	ret = rpn.doRPN();
		std::cout << ret << std::endl;
	}
	catch(const RPN::Error& e)
	{
		std::cerr << e.what() << std::endl;
	}
}