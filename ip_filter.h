
#include <string>
#include <vector>
#include <map>


using vec_vec_int = std::vector<std::vector<int>>;

class IpFilter 
{
	public:
	    IpFilter() {};
	    const int ANY = -1;

	    bool isAny(const int&); // is ip byte equal any value [*](as 1.*.*.3)		
	    bool isMatch(const int& , const int&); // is byte value match our value		
	    bool isIp4Address(const std::string&); //validation: is this line ip4 address
		
	    void ipSorting(vec_vec_int&);  // sorting by lexicographical_compare		
	    void printIpAddress(const std::vector<int>&);
		void output_filter_anywhere(const vec_vec_int&, const int&);

	    std::vector<int> split(const std::string&, char, int); // function for extracting ip addresses from input stream
			  
	    // botom of recursion
	    void creatingWichByteIsNotAny(std::map<int, int>& matching_bytes, int map_key_value_counter) {}
	                  

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

};


