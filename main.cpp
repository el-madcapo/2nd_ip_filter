#include "ip_filter.h"

#include <iostream>
#include <vector>
#include <string>


// function for extracting ip addresses from input stream
std::vector<int> split(const std::string &str, char d, int times) 
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

int main()
{
    try
    {
        vec_vec_int ip_pool;
        IpFilter filter;
	
        for(std::string line; std::getline(std::cin, line);)
        {
            bool is_ip4_address = filter.isIp4Address(line);//validation of input data
            if(is_ip4_address)
            {
                auto v = split(line, '.', 4);
	        ip_pool.emplace_back(v);
            }
        }             
        
        filter.ipSorting(ip_pool);

        filter.outputFilter(ip_pool);

        filter.outputFilter(ip_pool, 1);

        filter.outputFilter(ip_pool, 46, 70);

        filter.outputFilterAnywhere(ip_pool, 46);
        
        return 0;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
