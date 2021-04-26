void print_usage()
{
	std::cout << color_cyan <<
	"      ____  _   _ ____  _               _\n"
	"  ___|  _ \\| \\ | / ___|| |__  _   _ ___| |_ ___ _ __\n"
	" / __| | | |  \\| \\___ \\| '_ \\| | | / __| __/ _ \\ '__|\n"
	"| (__| |_| | |\\  |___) | |_) | |_| \\__ \\ ||  __/ |\n"
	" \\___|____/|_| \\_|____/|_.__/ \\__,_|___/\\__\\___|_|\n"
	<< nocolor <<
	"cbuster  *[-w </dir/wordlist>] *[-d <something.com>]\n"
	" -w --wordlist <path>       # ** Path to wordlist \n"
	" -d --domain <domain>       # ** Set target \n"
	" -t --threads <threads>     # + Set number of threads (default = 10, max = 100)\n"
	" -v --verbose               # + Prints unsuccesfull tries\n"
	" -h --help                  # This usage screen\n"
	" -hh                        # Advanced options\n\n";
	exit(0x0);
}

void print_advanced_usage()
{
	std::cout << color_magenta <<
    "      ____  _   _ ____  _               _\n"
    "  ___|  _ \\| \\ | / ___|| |__  _   _ ___| |_ ___ _ __\n"
    " / __| | | |  \\| \\___ \\| '_ \\| | | / __| __/ _ \\ '__|\n"
    "| (__| |_| | |\\  |___) | |_) | |_| \\__ \\ ||  __/ |\n"
    " \\___|____/|_| \\_|____/|_.__/ \\__,_|___/\\__\\___|_|\n"
    << nocolor <<
	"cbuster  *[-w </dir/wordlist>] *[-d <something.com>]\n"
	" -w --wordlist <path>       # ** Path to wordlist \n"
	" -d --domain <domain>       # ** Set target \n"
	" -t --threads <threads>     # + Set number of threads (default = 10, max = 100)\n"
	" -v --verbose               # + Prints unsuccesfull tries\n"
	" -c --skip-check            # Skips argument check\n"
	" -s --skip-banner           # Skips banner\n"
	" -p --print-tid             # Prints thread number on each threads output\n"
	" -T --skip-time             # Skips printing start/end time and execution time\n"
	" -W --wait <miliseconds>    # Waits an amount before running cbuster\n"
	" -o --out-dns <filename>    # Output succesful finds into a file (default: \"cbustersudbdomainfinds.txt\")\n"
	" -O --out-addr <filename>   # Output found IP addresses into a file (default: \"cbusteraddressfinds.txt\")\n"
	" -h --help                  # Default usage screen\n"
	" -hh                        # This usage screen\n\n";
	exit(0x0);
}


void cbuster_banner()
{
	std::cout << color_blue <<
	"      ____  _   _ ____  _               _\n"
	"  ___|  _ \\| \\ | / ___|| |__  _   _ ___| |_ ___ _ __\n"
	" / __| | | |  \\| \\___ \\| '_ \\| | | / __| __/ _ \\ '__|\n"
	"| (__| |_| | |\\  |___) | |_) | |_| \\__ \\ ||  __/ |\n"
	" \\___|____/|_| \\_|____/|_.__/ \\__,_|___/\\__\\___|_|\n"
    << nocolor;
}
