#include "ip_filter.h"

#include <ctype.h>

#include <algorithm>
#include <iostream>



bool IpFilter::isAny(const int& byte) // is ip byte equal ANY value [*](as 1.*.*.3)
{
	return byte == ANY;
}


bool IpFilter::isMatch(const int& byte, const int& value) // is byte value match our value
{
	return byte == value;
}


// validation: is this line containig ip4 address
bool IpFilter::isIp4Address(const std::string& line)
{
    unsigned char a = line[0];//checking the first symbol in the string    
    if(!std::isdigit(a))
	return false;
    
    int index = 0;
    unsigned int previous_separator = 0;
    long unsigned int separator_index = 0;
    int dots_quantity = 0;
    while (true)
    {
	std::string temp_str;
	separator_index = line.find_first_of('.', index + 1);        
				
	if (separator_index == std::string::npos) // if we reached end of string 
	{
	    if (dots_quantity != 3) // if we haven't 3 dots  *.*.*.* 
	          return false;
	   
	    int i  = 2;
            // i = 2 because the first symbol after separator has been
	    // checked and it's correct(it's a digit)

	    // cycle for checking 3 last symbols after last separator
	    // Ok. You got me. Not 3 symbols. Only 2 (previous_separator+2 and prev.separator+3)
	    while(i < 4) 
	    {
		int cur_position = previous_separator + i;
		char a  = line[cur_position];
		if (!std::isdigit(a))
		    break;
		++i;
	    }

	    // checking: is number in ip range
	    temp_str = line.substr(previous_separator +1,
				       previous_separator + i - 1);
	        int byte_number = std::stoi(temp_str);
	        if(( byte_number < 0) || (byte_number > 255))
		    return false;
		else
		    return true;		
	}

	// checking quantity of symbols between tbe begining of string and first separator
	if(previous_separator == 0 && separator_index > 3)
	    return false;

	// checking quantity of symbols between two separators
	if(previous_separator != 0)
	{	    
            int byte_length = separator_index - previous_separator;
	    if(byte_length > 4)
	    return false;
	}

	// checking symbol before and after separator
	char pre_dot_symbol = line[separator_index-1];	
	if(!std::isdigit(pre_dot_symbol))
	    return false;

	char post_dot_symbol = line[separator_index+1];
	if(!std::isdigit(post_dot_symbol))
	    return false;	

	// checking ip range of first byte
	if (index == 0 && separator_index !=1)
	{
	    temp_str = line.substr(index, separator_index);
	        int byte_number = std::stoi(temp_str);
	        if(( byte_number < 0) || (byte_number > 255))
		    return false;		
	}

	// checking ip range of 2nd,3rd and 4th bytes 
	if (index != 0 && separator_index != 1)
	{
		temp_str = line.substr(previous_separator +1,
				       separator_index - previous_separator + 1);
	        int byte_number = std::stoi(temp_str);
	        if(( byte_number < 0) || (byte_number > 255))
		    return false;
	}
	
	if (dots_quantity > 3)
	    return false;	

	previous_separator = separator_index;
	++dots_quantity;
	index = separator_index + 1;
    }

    if (dots_quantity == 3)
	return true;
    else        
	return false;
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


void IpFilter::outputFilterAnywhere(const vec_vec_int& ip_pool, const int& any_byte)
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



