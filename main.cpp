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

int main(int argc, const char** argv)
{
	std::vector<std::shared_ptr<std::ofstream> > streams;
//	teebuf::ptrs bufs;
//	std::vector< std::basic_streambuf<char> * > bufs;

			//    std::ofstream log( argv[1] );
   	std::string a(argv[1]);
   	bool append = a == "-a";
   	int i = 0;
   	append && i++;
   	while (++i < argc) {
		std::shared_ptr<std::ofstream> out(new std::ofstream);
//		std::ofstream out;
   		if (!open_file(argv[i], *out, append))
   			return 1;
		streams.push_back(out);
//		std::cout << sizeof(*bufs[0]) << std::endl;
//		teebuf::ptr p = (*out).rdbuf();
//		bufs.push_back(p);

   	}
//	bufs.push_back(std::cout.rdbuf());
//	std::shared_ptr<std::ofstream> out(new std::ofstream);
//   	redirecter r(*out, std::cout );
//	streams.push_back(std::move(std::cout));
//	streams.push_back(out);

    teestream tee(streams);
//	teestream tee(std::cout, log);
	tee << std::cin.rdbuf();
//	r.a & 1;
//	sleep(100);
    return 0;
}
