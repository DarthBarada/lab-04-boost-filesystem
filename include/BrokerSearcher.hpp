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
		  BrokerSearcher() { BrokerSearcher("."); }
		  BrokerSearcher(const std::filesystem::path &path);
		  ~BrokerSearcher() = default;
		  void search(const std::filesystem::path &path);
	};