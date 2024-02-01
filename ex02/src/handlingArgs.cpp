/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handlingArgs.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 16:05:42 by bschaafs      #+#    #+#                 */
/*   Updated: 2024/01/26 16:06:35 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static std::string	trimStr( const std::string& str )
{
	size_t	begin = str.find_first_not_of(" ");
	std::string	cleanStr = str.substr(begin, str.size());
	size_t	end = cleanStr.find_first_of(" ");
	if (end == std::string::npos)
		end = cleanStr.size();
	cleanStr = cleanStr.substr(0, end + 1);
	return cleanStr;
}

static bool	InsideInt( const std::string& el )
{
	if (el.size() > 10)
		return false;
	if (el.size() < 10)
		return true;
	return (std::strcmp(el.c_str(), "2147483647") <= 0);
}

static bool	containsDuplicates( int* args, int size )
{
	for (int i = 0; i < size - 1; i++)
		for (int j = i + 1; j < size; j++)
			if (args[i] == args[j])
				return true;
	return false;
}

bool	parseArgs(int ac, const char** av, int*& args)
{
	std::string	el;
	for (int idx = 1; idx < ac; idx++)
	{
		el = trimStr(av[idx]);
		if (el.find_first_not_of("0123456789") != std::string::npos)
			return false;
		if (!InsideInt(el))
			return false;
		args[idx - 1] = std::atoi(el.c_str());
	}
	if (containsDuplicates(args, ac - 1))
		return false;
	return true;
}

void	printArgs( int* args, size_t size)
{
	std::cout << "Before:\t";
	size_t	idx;
	for (idx = 0; idx < size && idx < 8; idx++)
		std::cout << args[idx] << " ";
	if (idx < size)
		std::cout << "...";
	std::cout << std::endl;
}

void	printSortedArgs( int* args, size_t size)
{
	std::cout << "After:\t";
	std::list<int> list = PmergeMe::doSort<std::list>(args, size);
	size_t	idx = 0;
	for (listIter it = list.begin(); it != list.end() && idx < 8; it++, idx++)
		std::cout << *it << " ";
	if (idx < size)
		std::cout << "...";
	std::cout << std::endl;
}
