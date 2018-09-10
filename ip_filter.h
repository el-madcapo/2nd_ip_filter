
#include <string>
#include <vector>
#include <map>

using vec_vec_int = std::vector<std::vector<int>>;

class IpFilter 
{
public:
    IpFilter() {};
    const int ANY = -1;	
		
    void ipSorting(vec_vec_int&);  // sorting by lexicographical_compare		

    bool isIp4Address(const std::string&); //validation: is this line ip4 address
    
    //print ip address containing this value in any position      
    void outputFilterAnywhere(const vec_vec_int&, const int&); 
    	                  

    // The next function writes data in std::map<position, value> searching mask.
    // For example, if we want to print all ip addresses  1.*.*.3
    // std::map will be looks like std::map<int, int> matching_bytes = {{0, 1} {3, 3}}

    // botom of recursion
    void creatingSearchingMask(std::map<int, int>&, int) {}

    template<class T, class... Ts>
    void creatingSearchingMask(std::map<int, int>& matching_bytes, int map_key_value_counter,
			       const T& arg1, const Ts&... args)
    {
	bool is_byte_any = isAny(arg1); //chrcking is current by is * (or any value)
	//if it isn't * then insert in std::map pair of position and value.
	if(!is_byte_any) matching_bytes.insert(std::pair<int, int>(map_key_value_counter, arg1));

	++map_key_value_counter; // position counter
	creatingSearchingMask( matching_bytes, map_key_value_counter, args...); 
    }


    //function for output ip addresses	   
    template<class... Args>
    void outputFilter(const vec_vec_int& ip_pool, const Args&... args) 
    {
	std::map<int, int> matching_bytes;	
			
	creatingSearchingMask(matching_bytes, 0, args...);

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
	        printIpAddress(ip);
		            
	}                
    }
private:
    bool isAny(const int&); // is ip byte equal any value [*](as 1.*.*.3)		
    bool isMatch(const int& , const int&); // is byte value match our value       
    void printIpAddress(const std::vector<int>&);
};


