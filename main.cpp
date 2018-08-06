#include "ip_filter.h"

#include <iostream>
#include <vector>
#include <string>

using vec_vec_int = std::vector<std::vector<int> >;

int main()
{
    try
    {
        vec_vec_int ip_pool;
	    IpFilter filter;
	
        for(std::string line; std::getline(std::cin, line);)
        {
            bool is_ip4_address = filter.isIp4Address(line);
            if(is_ip4_address)
            {
                auto v = filter.split(line, '.', 4);
                ip_pool.emplace_back(v);
            }
        }             
        
        filter.ipSorting(ip_pool);

        filter.output_filter(ip_pool);

        filter.output_filter(ip_pool, 1);

        filter.output_filter(ip_pool, 46, 70);

        filter.output_filter_anywhere(ip_pool, 46);
        
        return 0;
   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
