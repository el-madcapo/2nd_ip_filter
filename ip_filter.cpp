#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

<<<<<<< HEAD

#define ANY -1

using vec_vec_int = std::vector<std::vector<int>>;

bool isAny(int byte) // is ip byte equal any value [*](as 1.*.*.3)
{
	return byte == ANY;
=======
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
>>>>>>> 2085cb26bc79f890eef3f6871b9995168fc4cb2d
}


bool isMatch(int byte, int value) // is byte value match our value
{
	return byte == value;
}


void ipSorting(vec_vec_int& vector_original)  // sorting by lexicographical_compare
{                      
	std::sort(vector_original.begin(),vector_original.end(),[](auto &i,auto &j) {
      return std::lexicographical_compare(j.begin(),j.end(),i.begin(),i.end());
    });
}

 
std::vector<int> split(const std::string &str, char d, int times) // function for extracting ip addresses from input stream
{
    std::vector<int> r;
    int count = 0;
    int space_index = str.find_first_of(' ');    
    
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while(stop != std::string::npos || count == times || stop != space_index)
<<<<<<< HEAD
    {        
        std::string ip_byte_in_string = str.substr(start, stop - start);
        int ip_byte_number = (std::stoi(ip_byte_in_string));
        r.emplace_back(ip_byte_number);
=======
    {
        r.emplace_back(std::stoi(str.substr(start, stop - start)));
>>>>>>> 2085cb26bc79f890eef3f6871b9995168fc4cb2d
        ++count;
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    std::string str2 = str.substr(start);
    int number = std::stoi(str2);
    r.emplace_back(number);

    return r;
}

<<<<<<< HEAD

void output_filter(const vec_vec_int& ip_pool, //function for output ip addresses
	   int byte_1, int byte_2, 
	   int byte_3, int byte_4) 
{
	std::map<int, int> matching_bytes;	
	
	bool is_byte1_any = isAny(byte_1);
	if(!is_byte1_any) matching_bytes.insert(std::pair<int, int>(0, byte_1));
	
	bool is_byte2_any = isAny(byte_2);
	if(!is_byte2_any) matching_bytes.insert(std::pair<int, int>(1, byte_2));
	
	bool is_byte3_any = isAny(byte_3);
	if(!is_byte3_any) matching_bytes.insert(std::pair<int, int>(2, byte_3));

	bool is_byte4_any = isAny(byte_4);
	if(!is_byte4_any) matching_bytes.insert(std::pair<int, int>(3, byte_4));

	int how_many_match = 0; // this variable for detecting of match condition 
						//(if it greater than zero - all match, if it's equal zero  -  condition failed) 

	for(auto& ip : ip_pool) 
        {
            if(!matching_bytes.empty()) { // if not all byte are *.*.*.* 

            
            	for(auto& i : matching_bytes) //section for matching our condition
            	{
            	
	            	int byte_index = i.first;
	            	int byte_value = i.second;
	            	
	            	bool is_byte_match = isMatch(ip[byte_index], byte_value);
	            	
	            	if(!is_byte_match) {
	            		how_many_match = 0;
	            		break;
	            	}

	            	++how_many_match;
	            }

            	if(how_many_match > 0)
            	{
            		std::cout << ip[0] << "."
            			  	  << ip[1] << "."
            			  	  << ip[2] << "."
            			  	  << ip[2] << std::endl;
            		how_many_match = 0;
            	}
            }
            else {
            	std::cout << ip[0] << "."
            			  << ip[1] << "."
            			  << ip[2] << "."
            			  << ip[2] << std::endl;
            }            
        }                
}


void output_filter(vec_vec_int& ip_pool, int any_byte)
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
    		    std::cout << ip[0] << "."
            			  << ip[1] << "."
            			  << ip[2] << "."
            			  << ip[3] << std::endl;
    	}
    }
}


=======
>>>>>>> 2085cb26bc79f890eef3f6871b9995168fc4cb2d
int main()
{
    try
    {
        vec_vec_int ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '.', 4);
            ip_pool.emplace_back(v);
        }  
        
        ipSorting(ip_pool);

<<<<<<< HEAD
        output_filter(ip_pool, ANY, ANY, ANY, ANY);

        output_filter(ip_pool, 1, ANY, ANY, ANY);

        output_filter(ip_pool, 46, 70, ANY, ANY);

        output_filter(ip_pool, 46);
        
        return 0;
=======
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
>>>>>>> 2085cb26bc79f890eef3f6871b9995168fc4cb2d
   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}