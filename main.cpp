#include <fstream>
#include <iostream>
#include "tee.hpp"
#include <unistd.h>
bool open_file(const std::string& name,
			   std::ofstream & o,
			   bool append = false) {
	if (append)
		o.open(name, std::ios_base::app);
	else
		o.open(name);
	if (o.fail()) {
		std::cerr << "te: " << name << ": " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}

int main(int argc, const char** argv) {
	std::vector<std::shared_ptr<std::ofstream> > streams;
   	std::string a(argv[1]);
   	bool append = a == "-a";
   	int i = 0;
   	append && i++;
   	while (++i < argc) {
		std::shared_ptr<std::ofstream> out(new std::ofstream);
   		if (!open_file(argv[i], *out, append))
   			return 1;
		streams.push_back(out);
	   }
    teestream tee(streams);
	tee << std::cin.rdbuf();
    return 0;
}