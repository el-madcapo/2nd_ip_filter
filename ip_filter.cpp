#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using vec_vec_int = std::vector<std::vector<int>>;

void ip_sorting(const vec_vec_int& vector_original, vec_vec_int& vector_sorted, 
                      std::vector<unsigned int>& number_indexes_1, 
                      std::vector<unsigned int>& number_indexes_4670, 
                      std::vector<unsigned int>& number_indexes_46) // sorting by weight of ip address
{
	std::vector<std::pair<long double, int>> weight_and_index; 
		
	for (unsigned int i = 0; i < vector_original.size(); ++i)
	{
		long double ip_weight = 0.0;
		ip_weight = vector_original[i][0] * pow(256.0, 4) + 
		            vector_original[i][1] * pow(256.0, 3) + 
		            vector_original[i][2] * pow(256.0, 2) + 
		            vector_original[i][3] * 256.0;

		std::pair<long double, int> pair_weight_and_index; 
		pair_weight_and_index.first = ip_weight;
		pair_weight_and_index.second = i;
		
		weight_and_index.emplace_back(pair_weight_and_index);
	}
	
	std::sort(weight_and_index.begin(), weight_and_index.end());
	
	for(int i = weight_and_index.size()-1; i >= 0; --i) 
	{
        vector_sorted.emplace_back(vector_original[weight_and_index[i].second]);
        
        if(vector_sorted[vector_sorted.size() - 1][0] == 1) 
        	number_indexes_1.emplace_back(vector_sorted.size() - 1);
         
        if(vector_sorted[vector_sorted.size() - 1][0] == 46 
        	&& vector_sorted[vector_sorted.size() - 1][1] == 70)  
        	   { number_indexes_4670.emplace_back(vector_sorted.size() - 1 ); }  

        if(vector_sorted[vector_sorted.size() - 1][0] == 46 
        	|| vector_sorted[vector_sorted.size() - 1][1] == 46 
        	|| vector_sorted[vector_sorted.size() - 1][2] == 46 
        	|| vector_sorted[vector_sorted.size() - 1][3] == 46)  
        	    { number_indexes_46.emplace_back(vector_sorted.size() - 1); }
    }
}


std::vector<int> split(const std::string &str, char d, int times)
{
    std::vector<int> r;
    int count = 0;
    int spaceIndex = str.find_first_of(' ');    
    
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while(stop != std::string::npos || count == times || stop != spaceIndex)
    {
        r.emplace_back(std::stoi(str.substr(start, stop - start)));
        ++count;
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(std::stoi(str.substr(start)));

    return r;
}

int main(int argc, char const *argv[])
{
    try
    {
        vec_vec_int ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '.', 4);
            ip_pool.emplace_back(v);
        }     

        vec_vec_int ip_pool_sorted;
        std::vector<unsigned int> indexes_1;
        std::vector<unsigned int> indexes_4670;
        std::vector<unsigned int> indexes_46;

        ip_sorting(ip_pool, ip_pool_sorted, indexes_1, indexes_4670, indexes_46);

        for(const auto& ip : ip_pool_sorted) 
        {
            for(auto i = 0; i < 4; ++i)  
            {
                if (i != 0)  std::cout << ".";
                std::cout << ip[i];
            }
            std::cout << std::endl;
        }        
        
        for(auto i = 0; i < indexes_1.size(); ++i)
        {
    		std::cout << ip_pool_sorted[indexes_1[i]][0] << "." 
    		          << ip_pool_sorted[indexes_1[i]][1] << "." 
    		          << ip_pool_sorted[indexes_1[i]][2]  << "." 
    		          << ip_pool_sorted[indexes_1[i]][3] << std::endl;
        }
        
        for(auto i = 0; i < indexes_4670.size(); ++i)
        {
    		std::cout << ip_pool_sorted[indexes_4670[i]][0] << "." 
    		          << ip_pool_sorted[indexes_4670[i]][1] << "." 
    		          << ip_pool_sorted[indexes_4670[i]][2] << "." 
    		          << ip_pool_sorted[indexes_4670[i]][3] << std::endl;
        }

        for(auto i = 0; i < indexes_46.size(); ++i)
        {
    		std::cout << ip_pool_sorted[indexes_46[i]][0] << "." 
    		          << ip_pool_sorted[indexes_46[i]][1] << "." 
    		          << ip_pool_sorted[indexes_46[i]][2] << "." 
    		          << ip_pool_sorted[indexes_46[i]][3] << std::endl;
        }     
   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}