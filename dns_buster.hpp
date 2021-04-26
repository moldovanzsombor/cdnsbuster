void dns_buster
(
std::string target_domain, bool verbose, std::vector<std::string> wordlist, std::string tid,
std::vector<std::string> *dns_output, bool write_dns, std::vector<std::string> *addr_output, bool write_addr
)
{
	std::string testing_subdomain, result_address;
    struct addrinfo hints, *results;
    struct sockaddr_in *ip_address;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
	//std::mutex mtx;

	for(size_t i = 0; i < wordlist.size(); ++i)
	{
		testing_subdomain = wordlist[i] + "." +  target_domain;

		if(getaddrinfo(testing_subdomain.c_str(), "domain", &hints, &results) == 0)
		{
			ip_address = (struct sockaddr_in*) results -> ai_addr;
			result_address = inet_ntoa(ip_address -> sin_addr);

			//mtx.lock();
            std::cout << tid << color_green << "[+]" << nocolor << " Found:  " << text_bold << testing_subdomain << nocolor << " " << result_address << "\n";
			//mtx.unlock();

			if(write_dns)
            {
				//mtx.lock();
                dns_output -> emplace_back(testing_subdomain);
				//mtx.unlock();
            }
            if(write_addr)
            {
				//mtx.lock();
                addr_output -> emplace_back(result_address);
				//mtx.unlock();
            }
		}
		else if(verbose)
		{
			//mtx.lock();
			std::cout << tid << color_red << "[-]" << nocolor << " Missed: " << testing_subdomain << "\n";
			//mtx.unlock();
		}
	}
}
