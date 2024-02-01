/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ExchangeMatchRates.cpp                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 15:54:17 by bschaafs      #+#    #+#                 */
/*   Updated: 2024/01/29 16:11:08 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Exchange.hpp"

// ||=== CONVERT DATE ===||
void	Exchange::correctFormatDate( const std::string& str ) const
{
	if (str.size() != 11)
		throw WrongDateError(str);
	if (std::regex_match(str, std::regex("[0-9]{4}-[0-9]{2}-[0-9]{2} ")) == false)
		throw WrongDateError(str);
}

int	Exchange::convertDateInput( const std::string& dateStr ) const
{
	size_t	idx = dateStr.find_first_of('|');
	if (idx == std::string::npos)
		throw IncorrectFormatError();
	std::string	subStr = dateStr.substr(0, idx);
	correctFormatDate(subStr);

	return convertDate(subStr);
}


// ||=== CONVERT RATE ===||
float	Exchange::convertRateInput( const std::string& rateStr ) const
{
	size_t	begin = rateStr.find_first_of('|') + 1;
	std::string	numStr = rateStr.substr(begin, rateStr.size());
	if (numStr[0] != ' ')
		throw IncorrectFormatError();
	numStr =  trimStr(numStr);
	return convertRate(numStr);
}


// ||=== SEARCH DATABASE ===||
float	Exchange::searchDataBase( int date ) const
{
	std::map<int,float>::const_iterator it = _data.lower_bound(date);
	if (it == _data.end())
		return (--_data.end())->second;
	else if (it->first != date && date > FIRST_DAY)
		return (--it)->second;
	return it->second;
}


// ||=== MATCH RATES ===||
void	Exchange::matchRate( int date, float rate ) const
{
	float	multiplier = searchDataBase(date);
	float	ret = rate * multiplier;
	printDate(date);
	std::cout << " => " << rate << " = " << ret << std::endl;
}

void	Exchange::matchForLines( std::ifstream& infile ) const
{
	std::string	line;
	int			convertedDate;
	float		convertedRate;
	while (!infile.eof())
	{
		std::getline(infile, line);
		if (line == FIRST_LINE_INFILE || onlySpaces(line.c_str()))
			continue;
		try
		{
			convertedDate = convertDateInput(line);
			convertedRate = convertRateInput(line);
			if (convertedRate > 1000)
				throw NumberTooLargeError();
		}
		catch(const ExchangeException& e)
		{
			std::cerr << e.what() << std::endl;
			continue;
		}
		matchRate(convertedDate, convertedRate);
	}
}

void	Exchange::matchRates( void ) const
{
	std::ifstream	infile;
	infile.open(_av);
	if (!infile.is_open())
		throw LoadFileError(_av);
	matchForLines(infile);
	infile.close();
}
