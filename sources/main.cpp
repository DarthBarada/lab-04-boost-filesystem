// Copyright 2019 Your Name <DarthBarada@gmail.com>

#include "BrokerSearcher.hpp"

int main(int argc, char *argv[]) 
	{ 
		boost::filesystem::path path = boost::filesystem::canonical(".");
		if (argc > 1) 
			{
                  path = argv[1];
			}
        BrokerSearcher a{path};
        system("pause");
		return 0; 
	}