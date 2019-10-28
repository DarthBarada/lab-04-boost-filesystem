#include "../include/BrokerSearcher.hpp"
#include <iostream>

void BrokerSearcher::search(const std::filesystem::path &path,int level) 
	{
	   std::string string;
	   for (const std::filesystem::directory_entry& EnteryDir : std::filesystem::directory_iterator{path})
			{
		       string = EnteryDir.path().string();
			   for (int index = 0; index <= level;++index) 
					{
							std::cout<<"\t";            
					}
			   std::cout << "|--"<<string.substr(2,string.size()) << "\n";
			   if (EnteryDir.is_directory()) 
				   {
                       search(EnteryDir.path(),level + 1);
				   }	  
			}
	}