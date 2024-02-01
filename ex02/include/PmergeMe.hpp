/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 11:44:45 by bootjan       #+#    #+#                 */
/*   Updated: 2024/01/26 16:17:01 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <list>
#include <vector>
#include <deque>

#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <unistd.h>


typedef long long t_time;
typedef std::list<int>::iterator listIter;


// ||=== UTILS ===||
t_time	gettime(void);

// ||=== HANDLING ARGS ===||
void	printSortedArgs( int* args, size_t size);
void	printArgs( int* args, size_t size);
bool	parseArgs(int ac, const char** av, int*& args);

namespace PmergeMe
{
	// ||=== SORT WITH TIME ===||
	template <template <typename ...> class CONT>
	CONT<int>	timedSort( int* args, size_t len, const std::string& type );

	// ||=== SORT FUNCTIONS ===||
	template <template <typename ...> class CONT>
	CONT<int>	doSort( int* args, size_t len );

	template <template <typename ...> class CONT>
	CONT<int>	sort( CONT<int>& container );

	// ||=== PRINT CONTENT OF CONTAINER ===||
	template <typename CONT>
	void		printContainer( CONT& container );
	
}

#include "PmergeMe.tpp"
