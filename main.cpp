#pragma GCC optimize("03")
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>
//#include <mutex>
#include <arpa/inet.h>
#include <netdb.h>

#include "colors.h"
#include "usage.hpp"
#include "dns_buster.hpp"
#include "cbuster_addons.hpp"

const auto program_start = std::chrono::system_clock::now();
const std::vector<std::string> cbuster_options = {
	"-w", "--wordlist",
	"-d", "--domain",
	"-t", "--threads",
	"-v", "--verbose",
	"-c", "--skip-check",
	"-s", "--skip-banner",
	"-p", "--print-tid",
	"-T", "--skip-time"
	"-W", "--wait",
	"-o", "--out-dns",
	"-O", "--out-addr",
	"-h", "--help",
	"-hh"
};

int main(int argc, char* argv[])
{
	bool verbose = false, check_args = true, print_banner = true, print_tid = false, write_dns = false, write_addr = false, print_time = true;
	int thread_count = 0xA, wait_time = 0;
	std::string argv_i, wordlist_address = "", target_domain = "", dns_output_file_name = "Nothing", addr_output_file_name = "Nothing", wl_line;

	std::vector<std::string> dns_output;
	dns_output.reserve(0xFFFF);
	std::vector<std::string> addr_output;
	addr_output.reserve(0xFFFF);

	std::vector<std::string> wl_lines;
	wl_lines.reserve(0xFFFFFF);

	std::vector<std::thread> cbuster_threads;
	cbuster_threads.reserve(0x50);

	std::vector<std::vector<std::string>> wordlists;
	wordlists.resize(0xFFFFFF);

	if(argc == 1 || ((std::string)argv[1] == "-h") || ((std::string)argv[1] == "--help"))
	{
		print_usage();
	}
	else if((std::string)argv[0x1] == "-hh")
	{
		print_advanced_usage();
	}
	for(size_t i = 1; i < argc; ++i)
	{
		argv_i = argv[i];

		if(argv_i == "-w" || argv_i == "--wordlist")
		{
			if(argc >= i + 2)
			{
				wordlist_address = argv[i + 1];
			}
			else
			{
				std::cout << "Must specify wordlist path [-w /dir/wordlist.txt]\n";
				print_usage();
			}
			++i;
		}
		else if(argv_i == "-d" || argv_i == "--domain")
		{
			if(argc >= i + 2)
			{
				target_domain = argv[i + 1];
			}
			else
			{
				std::cout << "Must specify target domain [-d example.com]\n";
				print_usage();
			}
			++i;
		}
		else if(argv_i == "-t" || argv_i == "--threads")
		{
			if(argc >= i + 2)
			{
				if(atoi(argv[i + 1]) > 100)
				{
					thread_count = 100;
				}
				else
				{
					thread_count = atoi(argv[i + 1]);
				}
			}
			else
			{
				std::cout << "Must add thread count [-t 10]\n";
				print_usage();
			}
			++i;
		}
		else if(argv_i == "-v" || argv_i == "--verbose")
		{
			verbose = true;
		}
		else if(argv_i == "-c" || argv_i == "--skip-check")
		{
			check_args = false;
		}
		else if(argv_i == "-s" || argv_i == "--skip-banner")
		{
			print_banner = false;
		}
		else if(argv_i == "-p" || argv_i == "--print-tid")
		{
			print_tid = true;
		}
		else if(argv_i == "-T" || argv_i == "--skip_time")
		{
			print_time = false;
		}
		else if(argv_i == "-W" || argv_i == "--wait")
		{
			if(argc >= i + 2)
			{
				if(atoi(argv[i + 1]) < 0)
				{
					wait_time *= atoi(argv[i + 1]) - 1;
				}
				else
				{
					wait_time = atoi(argv[i + 1]);
				}
			}
			else
			{
				std::cout << "Must specify time to wait [-w 9000]\n";
				print_usage();
			}
			++i;
		}
		else if(argv_i == "-o" || argv_i == "--out-dns")
		{
			write_dns = true;
			if(argc >= i + 2)
			{
				if(!elem_in_vect(argv[i + 1], cbuster_options))
				{
					dns_output_file_name = argv[i + 1];
					++i;
				}
				else
				{
					dns_output_file_name = "cbustersubdomainfinds.txt";
				}
			}
			else
			{
				dns_output_file_name = "cbustersubdomainfinds.txt";
			}
		}
		else if(argv_i == "-O" || argv_i == "--out-addr")
		{
			write_addr = true;
			if(argc >= i + 2)
			{
				if(!elem_in_vect(argv[i + 1], cbuster_options))
				{
					addr_output_file_name = argv[i + 1];
					++i;
				}
				else
				{
					addr_output_file_name = "cbusteraddressfinds.txt";
				}
			}
			else
			{
				addr_output_file_name = "cbusteraddressfinds.txt";
			}
		}
		else
		{
			std::cout << "Unknown option: " << argv[i] << "\n";
			print_usage();
		}
	}
	if(wordlist_address == "" || target_domain == "")
	{
		std::cout << "Missing arguments \n";
		print_usage();
	}

	std::ifstream wordlist_path (wordlist_address);

	while(wordlist_path >> wl_line)
	{
		wl_lines.emplace_back(wl_line);
	}

	if(thread_count > wl_lines.size())
	{
		thread_count = wl_lines.size();
	}

	for(size_t j = 0; j < thread_count; ++j)
	{
		for(size_t i = j; i < wl_lines.size(); i += thread_count)
		{
			wordlists[j].emplace_back(wl_lines[i]);
		}
	}

	auto cbuster_start = std::chrono::system_clock::now();
	auto current_time = std::chrono::system_clock::to_time_t(cbuster_start);

	if(print_banner)
	{
		cbuster_banner();
	}
	if(print_time)
	{
		std::cout << "Start time: " << ctime(&current_time) << "\n";
	}
	if(check_args)
	{
		std::cout <<
		  "Wordlist path:             " << wordlist_address <<
		"\nDomain target:             " << target_domain <<
		"\nVerbose output:            " << verbose <<
		"\nAddress output filename:   " << dns_output_file_name <<
		"\nSubdomain output filename: " << addr_output_file_name <<
		"\nThreads:                   " << thread_count << "\n\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

	for(size_t i = 0; i < thread_count; ++i)
	{
		if(print_tid)
		{
			cbuster_threads.emplace_back(
				std::thread(dns_buster, target_domain, verbose, wordlists[i], " ("+std::to_string(i)+") " + (i >= 10 ? "" : " ") , &dns_output, write_dns, &addr_output, write_addr)
			);
		}
		else
		{
			cbuster_threads.emplace_back(
				std::thread(dns_buster, target_domain, verbose, wordlists[i], "", &dns_output, write_dns, &addr_output, write_addr)
			);
		}
	}

	for(std::thread & current_thread : cbuster_threads)
	{
		current_thread.join();
	}

	if(write_dns)
	{
		std::ofstream dns_output_file(dns_output_file_name);
		if(verbose)
		{
			std::cout << "\nWriting to file: " << dns_output_file_name << "\n";
		}

		for(auto &output_line : dns_output)
		{
			dns_output_file << output_line << "\n";
		}
	}
	if(write_addr)
	{
		std::ofstream addr_output_file(addr_output_file_name);
		if(verbose)
		{
			std::cout << "\nWriting to file: " << addr_output_file_name << "\n";
		}

		for(auto &output_line : addr_output)
		{
			addr_output_file << output_line << "\n";
		}
	}

	if(print_time)
	{
		auto program_end = std::chrono::system_clock::now();
		std::chrono::duration<double> cbuster_elapsed_time = program_end - cbuster_start, total_execution_time = program_end - program_start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(program_end);

		std::cout << "\nFinished program at: " << std::ctime(&end_time) <<
		"cbuster elapsed time: " << cbuster_elapsed_time.count() << "\n" <<
		"Total program execution time: " << total_execution_time.count() << "\n\n";
	}

	return 0;
}
