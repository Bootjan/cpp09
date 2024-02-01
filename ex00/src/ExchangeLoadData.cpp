/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ExchangeLoadData.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 13:08:29 by bschaafs      #+#    #+#                 */
/*   Updated: 2024/01/29 16:11:05 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Exchange.hpp"

// ||=== ASSINGMENT OPERATOR ===||
Exchange&	Exchange::operator=( const Exchange& rhs )
{
	if (this == &rhs)
		return *this;
	_data = rhs._data;
	_av = rhs._av;
	return *this;
}


// ||=== PRINT DATA ===||
void	Exchange::printData( void ) const
{
	for (auto el : _data)
		std::cout << "Key:\t" << el.first << ".\tVal:\t" << el.second << std::endl;
}


// ||=== HANDLING DATA FILE ===||
void	Exchange::checkOpenDataFile( void )
{
	if (!_datafileStream.is_open())
		throw LoadFileError(_datafile);
}

void	Exchange::closeDataFile( void )
{
	_datafileStream.close();
}


// ||=== CONVERT DATA ===||
int	Exchange::convertDate( const std::string& dateStr ) const
{
	int	date, year, month, day;
	date = year = month = day = 0;

	year = std::atoi(dateStr.substr(0, 4).c_str());
	if (year < 2009 || year > 2023)
		throw WrongDateError(dateStr);
	date += (year - 2000) * 10000;

	month = std::atoi(dateStr.substr(5, 2).c_str());
	if (month < 1 || month > 12)
		throw WrongDateError(dateStr);
	date += month * 100;

	day = std::atoi(dateStr.substr(8, 2).c_str());
	if (!correctDay(day, month, year))
		throw WrongDateError(dateStr);
	date += day;

	return date;
}

float	Exchange::convertRateData( const std::string& rateStr ) const
{
	size_t	begin = rateStr.find_first_of(',') + 1;
	std::string	numStr = rateStr.substr(begin, rateStr.size());
	numStr =  trimStr(numStr);
	return convertRate(numStr);
}

float	Exchange::convertRate( const std::string& rateStr ) const
{
	char	*pend;

	if (!correctFormat(rateStr))
		throw IncorrectFormatError();
	if (!insideInt(rateStr))
		throw NumberTooLargeError();
	float	ret = std::strtof(rateStr.c_str(), &pend);

	if (!onlySpaces(pend))
		throw BadRateInput(rateStr);
	if (ret < 0)
		throw NegativeNumberError();
	if (ret > (float)INT32_MAX || ret < (float)INT32_MIN)
		throw NumberTooLargeError();
	return ret;
}


// ||=== LOAD DATA FILE ===||
void	Exchange::readDataFile( void )
{
	std::string	line;
	int			convertedDate = 0;
	float		convertedRate = 0;

	while (!_datafileStream.eof())
	{
		std::getline(_datafileStream, line);
		if (line == FIRST_LINE_DATA || onlySpaces(line.c_str()))
			continue;
		try
		{
			convertedDate = convertDate(line);
			convertedRate = convertRateData(line);
		}
		catch(const ExchangeException& e)
		{
			std::cerr << e.what() << std::endl;
			continue;
		}
		_data.insert({ convertedDate, convertedRate});
	}
}

void	Exchange::loadData( void )
{
	checkOpenDataFile();
	readDataFile();
	closeDataFile();
}
