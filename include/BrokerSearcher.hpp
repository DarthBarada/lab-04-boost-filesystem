#pragma once
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <string>

#include <unordered_map>
#include <vector>
#include <stack>

class BrokerData 
	{
 public:
		std::string broker;
        size_t account = 0;
		size_t files = 0;
		std::string lastdate;
	};

class BrokerSearcher 
	{
		 public:
          
          std::unordered_map<size_t,BrokerData> database;                                                            // База данных брокеров
		  std::vector<std::string>NeededFiles;                                                                       // БД всех обнаруженных финансовых файлов
		  std::stack<std::string> NestedDirs;                                                                        // Стек из вложенных директорий
          const boost::regex ExampleOfBA{R"((\w+)_(\d{8})_([12]\d{3}(0[1-9]|1[0-2])(0[1-9]|[12]\d|3[01])).txt)"};      // Регулярное выражение

		  BrokerSearcher() 
			  { 
				  search("."); 
			  }
		  BrokerSearcher(const boost::filesystem::path &path) 
			  { 
				  search(path);
				  print_all_finance_files();
		  		  print();
			  }

		  void print();
		  void print_all_finance_files();
                  void search(const boost::filesystem::path &path);
                  void found_regular_file(const boost::filesystem::path &path);
                  ~BrokerSearcher() 
					  {
						database.clear();
						NeededFiles.clear();
						while (!NestedDirs.empty()) 
							{
							  NestedDirs.pop();
							}
					}
	};