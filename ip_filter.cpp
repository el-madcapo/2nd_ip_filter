#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <regex>

using vec_vec_int = std::vector<std::vector<int>>;

const int ANY = -1;

bool isAny(const int& byte) // is ip byte equal any value [*](as 1.*.*.3)
{
	return byte == ANY;
}


bool isMatch(const int& byte, const int& value) // is byte value match our value
{
	return byte == value;
}


bool isIp4Adress(const std::string& line) //validation: is this line ip4 address
{
    std::regex rgx("(((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9]))(\\.{1})((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9]))(\\.{1})((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9]))(\\.{1})((2[0-5][0-5])|(1[0-9][0-9])|([1-9][0-9])|([0-9])))");
    if(std::regex_search(line, rgx)) 
        return true;
    else
        return false;     
}


void ipSorting(vec_vec_int& vector_original)  // sorting by lexicographical_compare
{                      
	std::sort(vector_original.begin(),vector_original.end(),[](auto &i,auto &j) 
    {
      return std::lexicographical_compare(j.begin(),j.end(),i.begin(),i.end());
    });
}


void printIpAddress(const std::vector<int>& ip_address)
{
    std::cout << ip_address[0] << "."
              << ip_address[1] << "."
              << ip_address[2] << "."
              << ip_address[3] << std::endl;
}


// botom of recursion
void creatingWichByteIsNotAny(std::map<int, int>& matching_bytes, int map_key_value_counter) {};
                  

template<class T, class... Ts>
void creatingWichByteIsNotAny(std::map<int, int>& matching_bytes, int map_key_value_counter,
                  const T& arg1, const Ts&... args)
{
    bool is_byte_any = isAny(arg1);
    if(!is_byte_any) matching_bytes.insert(std::pair<int, int>(map_key_value_counter, arg1));
    ++map_key_value_counter;
    creatingWichByteIsNotAny( matching_bytes, map_key_value_counter, args...); 
}


template<class... Args>
void output_filter(const vec_vec_int& ip_pool, const Args&... args) //function for output ip addresses	   
{
	std::map<int, int> matching_bytes;	
	
	creatingWichByteIsNotAny(matching_bytes, 0, args...);

	int how_many_match = 0; // this variable for detecting the match condition  
						//(if it's greater than zero - all match, if it's equal zero  -  condition failed) 

	for(auto& ip : ip_pool) 
        {
            if(!matching_bytes.empty()) // if not all byte are *.*.*.*
            {  
            	for(auto& i : matching_bytes) //section for matching our condition
            	{            	
	            	int byte_index = i.first;
	            	int byte_value = i.second;
	            	bool is_byte_match = isMatch(ip[byte_index], byte_value);
	            	if(!is_byte_match) 
                    {
	            		how_many_match = 0;
	            		break;
	            	}

	            	++how_many_match;
	            }
            	
                if(how_many_match > 0)
            	{
            		printIpAddress(ip);
            		how_many_match = 0;
            	}
            }
            else 
            {
            	printIpAddress(ip);
            }            
        }                
}


void output_filter_anywhere(const vec_vec_int& ip_pool, const int& any_byte)
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

int main()
{
    try
    {
        vec_vec_int ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            bool is_ip4_address = isIp4Adress(line);
            if(is_ip4_address)
            {
                auto v = split(line, '.', 4);
                ip_pool.emplace_back(v);
            }
        }             
        
        ipSorting(ip_pool);

        output_filter(ip_pool);

        output_filter(ip_pool, 1);

        output_filter(ip_pool, 46, 70);

        output_filter_anywhere(ip_pool, 46);
        
        return 0;
   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}