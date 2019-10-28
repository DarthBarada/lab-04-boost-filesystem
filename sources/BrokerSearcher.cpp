#include "../include/BrokerSearcher.hpp"
#include "../include/Addons.hpp"
#include <iostream>
#include <iomanip>

void BrokerSearcher::print() 
	{
	     std::cout<<std::left<<std::setw(12)<<"____________"  <<"_"<<std::setw(11)<<"___________"<<"_"<<std::setw(9)<<"_________"<<"_"<<std::setw(12)<<"____________"<<"_\n"
			      <<std::setw(12)<<""             <<"|"<<std::setw(11)<<""         <<"|"<<std::setw(9)<<""       <<"|"<<std::setw(12)<<""          <<"|\n"
				  <<std::setw(12)<<"   broker"     <<"|"<<std::setw(11)<<"  account" <<"|"<<std::setw(9)<<"  files" <<"|"<<std::setw(12)<<"  lastdate" <<"|\n"
			      <<std::setw(12)<<"____________"  <<"|"<<std::setw(11)<<"___________"<<"|"<<std::setw(9)<<"_________"<<"|"<<std::setw(12)<<"____________"<<"|\n";
		for (auto index = database.begin();index!=database.end();++index) 
			{
				std::cout<<std::left<<std::setw(12)<<""                  <<"|"<<std::setw(11)<<""                   <<"|"<<std::setw(9)<<""                 <<"|"<<std::setw(12)<<""          <<"|\n"
					<<std::setw(12)<<index->second.broker<<"|"<<std::setw(11)<<index->second.account<<"|"<<std::setw(9)<<index->second.files<<"|"<<std::setw(12)<<index->second.lastdate<<"|\n";
			}
		 std::cout<<std::left<<std::setw(12)<<"____________"  <<"|"<<std::setw(10)<<"___________"<<"|"<<std::setw(8)<<"_________"<<"|"<<std::setw(12)<<"____________"<<"|\n";
	}

void BrokerSearcher::print_all_finance_files() 
	{
	    std::cout<<"All finance files:\n\n";
		for (auto index = NeededFiles.begin();index!=NeededFiles.end();++index) 
			{
				std::cout<<*index<<"\n";
			}
		std::cout<<"\n";
	}

void BrokerSearcher::search(const std::filesystem::path &path) 
	{
		for (const std::filesystem::directory_entry &EntryDir : std::filesystem::directory_iterator{path}) 
			{
				std::filesystem::path canon_view = std::filesystem::canonical(EntryDir);				

				if (std::filesystem::is_directory(canon_view)) 
					{
						NestedDirs.push(canon_view.stem().string());

						search(canon_view);
					} 
				else if (std::filesystem::is_regular_file(canon_view)) 
					{
					   found_regular_file(canon_view);
					}
			}

		if (!NestedDirs.empty()) 
			{
				NestedDirs.pop();
			}
	}

void BrokerSearcher::found_regular_file(const std::filesystem::path &path) 
	{
	    BrokerData temp;
        std::string name_of_file = path.filename().string();
		std::smatch result;
		/* Мы должны избегать файлов, которые не содержат .old и имя другого формата*/
		if (name_of_file.find(".old") != std::string::npos || !std::regex_match(name_of_file, result, ExampleOfBA)) 
			{
				return;
			}
		NeededFiles.push_back(NestedDirs.top() + " " + path.filename().string());
		
		// Заносим данные в буфферную информацию о брокере
		temp.broker = NestedDirs.top();
		temp.account = get_brocker_account(path.filename().string());
		temp.lastdate = get_brocker_date(path.filename().string());
		temp.files = 0;

		// Если в базе уже существует аккаунт у того же брокера, то
		auto account = database.find(temp.account);
		if ((account != database.end()) && (account->second.broker == temp.broker)) 
			{
			   if (std::stoll(account->second.lastdate)<std::stoll(temp.lastdate)) 
				   {
                      account->second.lastdate = temp.lastdate;
				   }
			   ++account->second.files;
			} 
	    else 
			{
                database.insert(std::make_pair(temp.account,temp));
			}
	}