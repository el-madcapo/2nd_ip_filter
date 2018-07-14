#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


#define ANY -1

using vec_vec_int = std::vector<std::vector<int>>;

bool isAny(int byte) // is ip byte equal any value [*](as 1.*.*.3)
{
	return byte == ANY;
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

	int how_many_match = 0; // this variable for detecting of condition match 
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

        vec_vec_int ip_pool_sorted;
        
        ipSorting(ip_pool);

        output_filter(ip_pool, ANY, ANY, ANY, ANY);

        output_filter(ip_pool, 1, ANY, ANY, ANY);

        output_filter(ip_pool, 46, 70, ANY, ANY);

        output_filter(ip_pool, 46);
        
        return 0;
   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}