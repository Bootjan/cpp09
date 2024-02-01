/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Exchange.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 12:49:50 by bschaafs      #+#    #+#                 */
/*   Updated: 2024/01/29 16:10:02 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <string>
#include <regex>

#define FIRST_LINE_DATA "date,exchange_rate"
#define FIRST_LINE_INFILE "date | value"
#define FEBRUARY 2
#define FIRST_DAY 90102

class Exchange
{
	public:
	// ||=== CON/DE STRUCTOR ===||
		Exchange() { _datafileStream.open(_datafile, std::ios::in); }
		Exchange( const std::string& ag ) : _av(ag) { _datafileStream.open(_datafile, std::ios::in); }
		Exchange( const Exchange& rhs ) : _data(rhs._data), _av(rhs._av) {}
		Exchange&	operator=( const Exchange& rhs);
		~Exchange() {}

	// ||=== PUBLIC FUNCTIONS ===||
		void	loadData( void );
		int		convertDate( const std::string& dateStr ) const;
		int		convertDateInput( const std::string& dateStr ) const;
		void	printData( void ) const;
		void	matchRates( void ) const;
	
	private:
	// ||=== PRIVATE FUNCTIONS ===||
		float	convertRate( const std::string& rateStr ) const;
		float	convertRateData( const std::string& rateStr ) const;
		float	convertRateInput( const std::string& rateStr ) const;
		void	checkOpenDataFile( void );
		void	readDataFile( void );
		void	closeDataFile( void );
		void	matchRate( int date, float rate ) const;
		void	matchForLines( std::ifstream& infile ) const;
		float	searchDataBase( int date ) const;
		void	correctFormatDate( const std::string& str ) const;

	// ||=== VARIABLES ===||
		std::map<int,float>				_data;
		const std::string				_datafile = "data.csv";
		std::string						_av;
		std::ifstream					_datafileStream;
	
	// ||=== EXCEPTIONS ===||
	public:
		struct ExchangeException : public std::runtime_error
		{
			ExchangeException( const std::string& message ) : std::runtime_error(message) {}
		};

		struct LoadFileError : public ExchangeException
		{
			LoadFileError( const std::string& filename ) : ExchangeException("Error: failed to open file: " + filename) {}
		};

		struct WrongDateError : public ExchangeException
		{
			WrongDateError( const std::string& date ) : ExchangeException("Error: bad input => " + date) {}
		};

		struct NegativeNumberError : public ExchangeException
		{
			NegativeNumberError() : ExchangeException("Error: not a positive number.") {}
		};

		struct NumberTooLargeError : public ExchangeException
		{
			NumberTooLargeError() : ExchangeException("Error: too large a number.") {}
		};

		struct BadRateInput : public ExchangeException
		{
			BadRateInput( const std::string& rate ) : ExchangeException("Error: bad input for rate: " + rate) {}
		};

		struct IncorrectFormatError : public ExchangeException
		{
			IncorrectFormatError() : ExchangeException("Error: value is in incorrect format.") {}
		};
};

// ||=== UTILS ===||
void			printDate( int date );
bool			correctDay(int day, int month, int year);
bool			onlySpaces( const char* str );
bool			insideInt( const std::string& str );
bool			correctFormat( const std::string& str );
std::string		trimStr( const std::string& str );
