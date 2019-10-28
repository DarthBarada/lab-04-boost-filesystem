// Copyright 2018 Your Name <your_email>

#include "../include/BrokerSearcher.hpp"

int main(int argc, char *argv[]) 
	{ 
		 std::filesystem::path path = ".";
		  if (argc > 1) 
			  {
				path = argv[1];
			  }
		return 0; 
	}