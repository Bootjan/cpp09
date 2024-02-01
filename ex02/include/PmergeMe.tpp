/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:18:14 by bschaafs          #+#    #+#             */
/*   Updated: 2024/01/27 22:19:01 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#define LAST true
#define NORMAL false

namespace
{
	// ||================================================||
	// ||==== MERGE PART							 ====||
	// ||================================================||

	template <typename T, typename CONT>
	void	makeSubPair( T el1, T el2, CONT& subPair )
	{
		subPair.push_back(el1);
		subPair.push_back(el2);
	}

	template <typename T, typename CONT>
	void	makeSubPair( T el1, CONT& subPair )
	{
		subPair.push_back(el1);
	}

	template <typename PAIRS, typename CONT>
	void	makePairs( PAIRS& pairs, CONT& container )
	{
		typename CONT::iterator	it1, it2;
		CONT	subPair;

		it1 = container.begin();
		it2 = it1;
		while (it1 != container.end())
		{
			advance(it2, 1);
			if (it2 == container.end())
				{ makeSubPair(*it1, subPair); pairs.push_back(subPair); break; }
			if (*it1 <= *it2)
				makeSubPair(*it1, *it2, subPair);
			else
				makeSubPair(*it2, *it1, subPair);
			pairs.push_back(subPair);
			subPair.clear();
			advance(it1, 2);
			it2 = it1;
		}
		container.clear();
	}

	template <typename ITER>
	ITER	smallestEl( ITER it, size_t len )
	{
		ITER	ret = it;

		for (size_t idx = 0; idx < len; idx++)
		{
			if (*(it->begin()) < *(ret->begin()))
				ret = it;
			advance(it, 1);
		}
		return ret;
	}

	template <typename PAIRS>
	void	sortPairs( PAIRS& pairs, size_t size )
	{
		typename PAIRS::iterator	it1, it2;
		for (size_t idx = 0; idx < size - 1; idx++)
		{
			it1 = pairs.begin();
			advance(it1, idx);
			it2 = smallestEl(it1, size - idx);
			if (it1 != it2)
				it1->swap(*it2);
		}
	}


	// ||================================================||
	// ||==== INSERTION PART						 ====||
	// ||================================================||

	template <typename CONT>
	void	insertElement( CONT& container, int offset, int el )
	{
		typename CONT::iterator	start, insert;

		start = container.begin();
		advance(start, offset);
		insert = std::upper_bound(start, container.end(), el);
		container.insert(insert, el);
	}

	template <typename ITER>
	int		getElement( ITER it, bool isLast )
	{
		int	ret;
		if (isLast)
			ret = *(it->begin());
		else
			ret = *(++(it->begin()));
		return ret;
	}

	template <typename T>
	T	jacobsthalNumbers(T num)
	{
		if (num == -1)
			return 0;
		if (num == 0)
			return 1;
		if (num == 1)
			return 3;
		return jacobsthalNumbers(num - 2) * 2 + jacobsthalNumbers(num - 1);
	}

	template <typename ITER>
	void	updatePointer( ITER& it, int j1, int size )
	{
		int	offset = j1 > (int)size ? size - 1 : j1 - 1;
		advance(it, offset);
	}

	template <typename T>
	void	updateJSN( T& j0, T& j1, size_t idx )
	{
		j0 = jacobsthalNumbers((int)idx - 1);
		j1 = jacobsthalNumbers((int)idx);
	}

	template <typename PAIRS, typename CONT>
	void	insertBottomElements( PAIRS& pairs, CONT& container, size_t size )
	{
		int		j0, j1, totalDone = 0;
		size_t	idx = 0;
		typename PAIRS::iterator	it;
	
		while (totalDone < (int)size)
		{
			updateJSN(j0, j1, idx++);
			it = pairs.begin();
			updatePointer(it, j1, size);
			for (int i = 0; j1 - i > j0 && totalDone < (int)size; i++, totalDone++)
			{
				insertElement(container, j1 - j0 - i, getElement(it, NORMAL));
				if (it != pairs.begin())
					it--;
			}
		}
	}

	template <typename PAIRS, typename CONT>
	void	insertPairs( PAIRS& pairs, CONT& container, size_t size )
	{
		typename PAIRS::iterator	it = pairs.begin();
		size_t	idx;
		for (idx = 0; idx < size; idx++, it++)
			container.push_back(*(it->begin()));
		insertBottomElements(pairs, container, size);
		if (size != pairs.size())
			insertElement(container, 0, getElement(--(pairs.end()), LAST));
		pairs.clear();
	}


	// ||================================================||
	// ||==== PRINTING RESULT						 ====||
	// ||================================================||

	template <typename T>
	void	difftime( T end, T start )
	{
		long long	timeStart = (start.tv_sec * 1000000 + start.tv_usec);
		long long	timeEnd = (end.tv_sec * 1000000 + end.tv_usec);
		long long	timeDiff = timeEnd - timeStart;
		long		beforeComma = timeDiff / 1000;
		long		afterComma = timeDiff % 1000;
		std::cout << beforeComma << ".";
		for (int i = 100; i >= 1; i /= 10)
		{
			std::cout << afterComma / i;
			afterComma %= i;
		}
	}

	template <typename T>
	void	printResult( T end, T start, const std::string& type, size_t size )
	{
		std::cout	<< "Time to process a range of " << size
					<< " elements with std::"
					<< std::left << std::setw(8) << type
					<< ": ";
		difftime(end, start);
		std::cout << " us" << std::endl;
	}
}


// ||================================================||
// ||==== PMERGE MEMBER FUNCTIONS				 ====||
// ||================================================||

template <template <typename ...> class CONT>
CONT<int>	PmergeMe::doSort( int* args, size_t len )
{
	CONT<int>	container;
	for (size_t i = 0; i < len; i++)
		container.push_back(args[i]);
	container = PmergeMe::sort(container);
	return container;
}

template <template <typename ...> class CONT>
CONT<int>	PmergeMe::timedSort( int* args, size_t len, const std::string& type )
{
	CONT<int>	result;
	struct timeval	start, end;
	gettimeofday(&start, NULL);
	result = PmergeMe::doSort<CONT>(args, len);
	gettimeofday(&end, NULL);
	printResult(end, start, type, len);
	return result;
}


template <template <typename ...> class CONT>
CONT<int>	PmergeMe::sort( CONT<int>& container )
{
	size_t	size = container.size() / 2;
	if (size == 0)
		return container;
	CONT<CONT<int>>	pairs;
	makePairs(pairs, container);
	sortPairs(pairs, size);
	insertPairs(pairs, container, size);
	return container;
}

template <typename CONT>
void	PmergeMe::printContainer( CONT& container )
{
	bool	start = true;
	std::cout << "Content of container: ";
	for (int value : container)
		if (start == true) { std::cout << value; start = false; }
		else { std::cout << " " << value; }
	std::cout << std::endl;
}
