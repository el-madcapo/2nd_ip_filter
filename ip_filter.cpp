#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using vec_vec_int = std::vector<std::vector<int> >;

void ip_sorting(const vec_vec_int& vectorOriginal, vec_vec_int& vectorSorted, 
                      std::vector<unsigned int>& numberIndexesOne, 
                      std::vector<unsigned int>& numberIndexes4670, 
                      std::vector<unsigned int>& numberIndexes46) // sorting by weight of ip address
{
	std::vector<std::pair<long double, int> > weightAndIndex;
		
	for (unsigned int i = 0; i < vectorOriginal.size(); ++i)
	{
		long double ip_weight = 0.0;
		ip_weight = vectorOriginal[i][0] * pow(256.0, 4) + 
		            vectorOriginal[i][1] * pow(256.0, 3) + 
		            vectorOriginal[i][2] * pow(256.0, 2) + 
		            vectorOriginal[i][3] * 256.0;

		std::pair<long double, int> pairWeightAndIndex; 
		pairWeightAndIndex.first = ip_weight;
		pairWeightAndIndex.second = i;
		
		weightAndIndex.emplace_back(pairWeightAndIndex);
	}
	
	std::sort(weightAndIndex.begin(), weightAndIndex.end());
	
	for(int i = weightAndIndex.size()-1; i >= 0; --i) 
	{
        vectorSorted.emplace_back(vectorOriginal[weightAndIndex[i].second]);
        
        if(vectorSorted[vectorSorted.size() - 1][0] == 1) 
        	numberIndexesOne.emplace_back(vectorSorted.size() - 1);
         
        if(vectorSorted[vectorSorted.size() - 1][0] == 46 && vectorSorted[vectorSorted.size() - 1][1] == 70)  
        	numberIndexes4670.emplace_back(vectorSorted.size() - 1 );  

        if(vectorSorted[vectorSorted.size() - 1][0] == 46 || vectorSorted[vectorSorted.size() - 1][1] == 46 
        	|| vectorSorted[vectorSorted.size() - 1][2] == 46 || vectorSorted[vectorSorted.size() - 1][3] == 46)  
        	numberIndexes46.emplace_back(vectorSorted.size() - 1);
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
        std::vector<unsigned int> indexesOne;
        std::vector<unsigned int> indexes4670;
        std::vector<unsigned int> indexes46;

        ip_sorting(ip_pool, ip_pool_sorted, indexesOne, indexes4670, indexes46);

       for(auto ip : ip_pool_sorted) 
        {
            int indexCounter = 0;
            for(auto ip_part : ip)  
            {
                if (indexCounter != 0)  std::cout << ".";
                std::cout << ip_part;
                ++indexCounter;
            }
            std::cout << std::endl;
        }        
        
        for(auto i = 0; i < indexesOne.size(); ++i)
        {
    		std::cout << ip_pool_sorted[indexesOne[i]][0] << "." 
    		          << ip_pool_sorted[indexesOne[i]][1] << "." 
    		          << ip_pool_sorted[indexesOne[i]][2]  << "." 
    		          << ip_pool_sorted[indexesOne[i]][3] << std::endl;
        }
        
        for(auto i = 0; i < indexes4670.size(); ++i)
        {
    		std::cout << ip_pool_sorted[indexes4670[i]][0] << "." 
    		          << ip_pool_sorted[indexes4670[i]][1] << "." 
    		          << ip_pool_sorted[indexes4670[i]][2] << "." 
    		          << ip_pool_sorted[indexes4670[i]][3] << std::endl;
        }

        for(auto i = 0; i < indexes46.size(); ++i)
        {
    		std::cout << ip_pool_sorted[indexes46[i]][0] << "." 
    		          << ip_pool_sorted[indexes46[i]][1] << "." 
    		          << ip_pool_sorted[indexes46[i]][2] 
                      << "." << ip_pool_sorted[indexes46[i]][3] << std::endl;
        }     
   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}