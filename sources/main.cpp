// Copyright 2019 Your Name <DarthBarada@gmail.com>

#include "../include/BrokerSearcher.hpp"

int main(int argc, char *argv[]) 
	{ 
		std::filesystem::path path = ".";
		/*if (argc > 1) 
			{
                  path = argv[1];
			}*/
                BrokerSearcher a{path};
		system("pause");
		return 0; 
	}