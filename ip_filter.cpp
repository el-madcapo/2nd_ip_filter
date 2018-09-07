#include "ip_filter.h"

#include <algorithm>
#include <regex>
#include <iostream>

using vec_vec_int = std::vector<std::vector<int>>;

const int ANY = -1;

bool IpFilter::isAny(const int& byte) // is ip byte equal ANY value [*](as 1.*.*.3)
{
	return byte == ANY;
}


bool IpFilter::isMatch(const int& byte, const int& value) // is byte value match our value
{
	return byte == value;
}


bool IpFilter::isDigit(const char a)
{
    if(a <= '9' && a >='0')
    	return true;    
    else
    	return false;
}


bool IpFilter::isIp4Address(const std::string& line) //validation: is this line ip4 address
{
    char a = line[0];
    bool is_Digit = isDigit(a);
    if(!is_Digit)
	return false;
    
    int index = 0;
    unsigned int previous_separator = 0;
    long unsigned int separator_index = 0;
    int dots_quantity = 0;
    while (true)
    {
	std::string temp_str;
	separator_index = line.find_first_of('.', index + 1);	
				
	if (separator_index == std::string::npos)
	{
	    if (dots_quantity != 3)
	          return false;
	    
	    int i  = 2;
            // i = 2 because the first symbol after separator has been
	    // checked and it's correct(it's a digit)
	    while(i < 4)
	    {
		int cur_position = previous_separator + i;
		char a  = line[cur_position];
		if ((a < '0') || (a > '0'))
		    break;
		++i;
	    }

	    temp_str = line.substr(previous_separator +1,
				       previous_separator + i - 1);
	        int byte_number = std::stoi(temp_str);
	        if(( byte_number < 0) || (byte_number > 255))
		    return false;
		else
		    return true;		
	}
					   
	char pre_dot_symbol = line[separator_index-1];
	is_Digit = isDigit(pre_dot_symbol);
	if(!is_Digit)
	    return false;

	char post_dot_symbol = line[separator_index+1];
	is_Digit = isDigit(post_dot_symbol);
	if(!is_Digit)
	    return false;	

	if (index == 0 && separator_index !=1)
	{
	    temp_str = line.substr(index, separator_index);
	        int byte_number = std::stoi(temp_str);
	        if(( byte_number < 0) || (byte_number > 255))
		    return false;		
	}
	    
	if (index != 0 && separator_index != 1)
	{
		temp_str = line.substr(previous_separator +1,
				       separator_index - previous_separator + 1);
	        int byte_number = std::stoi(temp_str);
	        if(( byte_number < 0) || (byte_number > 255))
		    return false;
	}
	
	previous_separator = separator_index;
	++dots_quantity;

	if (dots_quantity > 3)
	    return false;	

	index = separator_index + 1;
    }

    if (dots_quantity == 3)
	return true;
    else
    {
	std::cout << "not enough dots" << std::endl;
	return false;
    }
}


void IpFilter::ipSorting(vec_vec_int& vector_original)  // sorting by lexicographical_compare
{                      
	std::sort(vector_original.begin(),vector_original.end(),[](auto &i,auto &j) 
    {
      return std::lexicographical_compare(j.begin(),j.end(),i.begin(),i.end());
    });
}


void IpFilter::printIpAddress(const std::vector<int>& ip_address)
{
    std::cout << ip_address[0] << "."
              << ip_address[1] << "."
              << ip_address[2] << "."
              << ip_address[3] << std::endl;
}

void IpFilter::output_filter_anywhere(const vec_vec_int& ip_pool, const int& any_byte)
{
    for(auto& ip : ip_pool)
    {
    	bool is_byte1_match = isMatch(ip[0], any_byte);
    	bool is_byte2_match = isMatch(ip[1], any_byte);
    	bool is_byte3_match = isMatch(ip[2], any_byte);
    	bool is_byte4_match = isMatch(ip[3], any_byte);
    	if (is_byte1_match || is_byte2_match
    		|| is_byte3_match || is_byte4_match)
    	{
    		    printIpAddress(ip);
    	}
    }
}

// function for extracting ip addresses from input stream
std::vector<int> IpFilter::split(const std::string &str, char d, int times) 
{
    std::vector<int> r;
    int count = 0;      
    
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while(stop != std::string::npos || count == times)
    {        
        std::string ip_byte_in_string = str.substr(start, stop - start);
        int ip_byte_number = (std::stoi(ip_byte_in_string));	
        r.emplace_back(ip_byte_number);
        ++count;
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    
    std::string str2 = str.substr(start);
    int number = std::stoi(str2);    
    r.emplace_back(number);

    return r;
}

