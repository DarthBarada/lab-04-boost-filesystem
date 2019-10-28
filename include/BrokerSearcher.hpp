#pragma once
#include <filesystem>
#include <forward_list>
#include <string>

struct BrokerData 
	{
		struct FileData 
			{
				std::string broker;
				size_t account;
			};
	};

class BrokerSearcher 
	{
		 public:
		  BrokerSearcher() { search("."); }
		  BrokerSearcher(const std::filesystem::path &path) { search(path);}
		  void search(const std::filesystem::path &path,int level = 1);
		 // ~BrokerSearcher() = default;
		  //void search(const std::filesystem::path &path);
	};