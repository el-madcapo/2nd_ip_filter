#include "ip_filter.h"

#include <algorithm>
#include <regex>
#include <iostream>

using vec_vec_int = std::vector<std::vector<int>>;

const int ANY = -1;

bool IpFilter::isAny(const int& byte) // is ip byte equal any value [*](as 1.*.*.3)
{
	return byte == ANY;
}


bool IpFilter::isMatch(const int& byte, const int& value) // is byte value match our value
{
	return byte == value;
}


bool IpFilter::isIp4Address(const std::string& line) //validation: is this line ip4 address
{
    std::regex rgx("(((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9]))(\\.{1})((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9]))(\\.{1})((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9]))(\\.{1})((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9])))");
    if(std::regex_search(line, rgx)) 
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


std::vector<int> IpFilter::split(const std::string &str, char d, int times) // function for extracting ip addresses from input stream
{
    std::vector<int> r;
    int count = 0;
    int space_index = str.find_first_of(' ');    
    
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while(stop != std::string::npos || count == times || stop != space_index)
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

