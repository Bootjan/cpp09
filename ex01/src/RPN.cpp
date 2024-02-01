/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:33:28 by bootjan           #+#    #+#             */
/*   Updated: 2024/01/27 21:27:13 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// ||=== UTILS ===||
bool	isOperator(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}


// ||=== COPY ASSIGNMENT OPERATOR ===||
RPN&	RPN::operator=( const RPN& rhs )
{
	if (this == &rhs)
		return *this;
	_stack = rhs._stack;
	_format = rhs._format;
	return *this;
}


// ||=== RPN ALGORITHM ===||
void	RPN::executeOperator( char operatr )
{
	int	el1, el2;

	if (_stack.size() <= 1)
		throw Error();
	el1 = _stack.top();
	_stack.pop();
	el2 = _stack.top();
	_stack.pop();
	if (operatr == '/' && el1 == 0)
		throw Error();
	switch(operatr)
	{
		case '+': _stack.push(el2 + el1); break;
		case '-': _stack.push(el2 - el1); break;
		case '/': _stack.push(el2 / el1); break;
		case '*': _stack.push(el2 * el1); break;
	}
}

int	RPN::doRPN( void )
{
	for (char el : _format)
	{
		if (std::isdigit(el))
			_stack.push(el - '0');
		else if (isOperator(el))
			executeOperator(el);
	}
	return _stack.top();
}


// ||=== CHECK FORMAT ===||
bool	RPN::correctElement( const std::string& subStr, size_t& n_digits, size_t& n_operators )
{
	if (subStr.size() != 1)
		return false;
	if (std::isdigit(subStr[0]))
		{ n_digits++; return true; }
	if (isOperator(subStr[0]))
		{ n_operators++; return true; }
	return false;
}

void	RPN::checkFormat( void )
{
	size_t	n_digits, n_operators;
	n_digits = n_operators = 0;

	std::string	subStr;
	std::stringstream	ss(_format);
	while (std::getline(ss, subStr, ' '))
		if (!correctElement(subStr, n_digits, n_operators))
			throw Error();
	if (n_digits != n_operators + 1)
		throw Error();
}
