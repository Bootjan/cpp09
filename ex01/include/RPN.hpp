/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:01:52 by bschaafs          #+#    #+#             */
/*   Updated: 2024/01/27 21:27:05 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <sstream>

class RPN
{
	public:
	// ||=== CON/DE STRUCTORS ===||
		RPN() {}
		RPN( const std::string& format ) : _format(format) {}
		RPN( const RPN& rhs ) : _stack(rhs._stack), _format(rhs._format) {}
		RPN&	operator=( const RPN& rhs);
		~RPN() {}

	// ||=== PUBLIC FUNCTIONS ===||
		int		doRPN(void);
		void	checkFormat(void);
	private:
	// ||=== VARIABLES ===||
		std::stack<int>	_stack;
		std::string		_format;
	
	// ||=== PRIVATE FUNCTIONS ===||
		bool			correctElement( const std::string& subStr, size_t& n_digits, size_t& n_operators );
		void			executeOperator( char operatr );
	
	// ||=== EXCEPTION ===||
	public:
		struct Error : public std::runtime_error
		{
			Error() : std::runtime_error("Error") {}
		};
};
