/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 15:54:39 by bschaafs      #+#    #+#                 */
/*   Updated: 2024/01/29 16:00:07 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Exchange.hpp"

void	printDate( int date )
{
	int year = date / 10000 + 2000;
	date %= 10000;
	int month = date / 100;
	date %= 100;
	int day = date;
	std::cout << year << "-";
	if (month < 10)
		std::cout << "0";
	std::cout << month << "-";
	if (day < 10)
		std::cout << "0";
	std::cout << day << std::flush;
}

bool	correctDay(int day, int month, int year)
{
	int	values[] = { 4, 6, 9, 11 };
	if (day < 1 || day > 31)
		return false;
	if (month == FEBRUARY && day > 29)
		return false;
	if (day == 29 && month == FEBRUARY && year % 4 != 0)
		return false;
	if (std::count(std::begin(values), std::end(values), month) != 0 && day > 30)
		return false;
	return true;
}

bool	onlySpaces( const char* str )
{
	if (!str)
		return true;
	size_t	len = std::strlen(str);
	for (size_t idx = 0; idx < len; idx++)
		if (!std::isspace(str[idx]))
			return false;
	return true;
}

std::string	trimStr( const std::string& str )
{
	size_t	begin = str.find_first_not_of(' ');
	std::string	cleanStr = str.substr(begin, str.size());
	size_t	end = cleanStr.find_first_of(" ");
	if (end == std::string::npos)
		end = cleanStr.size();
	cleanStr = cleanStr.substr(0, end + 1);
	return cleanStr;
}

bool	insideInt( const std::string& str )
{	
	if (str.size() > 10)
		return false;
	if (str.size() < 10)
		return true;
	return (std::strcmp(str.c_str(), "2147483647") <= 0);
}

bool	correctFormat( const std::string& str )
{
	int	n_minus;

	if (str.find_first_not_of("-0123456789.") != std::string::npos)
		return false;
	if (std::count(str.begin(), str.end(), '.') > 1)
		return false;
	n_minus = std::count(str.begin(), str.end(), '-');
	if (n_minus > 1)
		return false;
	if (n_minus == 1 && str[0] != '-')
		return false;
	return true;
}
