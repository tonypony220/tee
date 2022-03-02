#pragma once
#include <vector>

template <typename char_type, typename traits = std::char_traits<char_type> >
class basic_teebuf : public std::basic_streambuf<char_type, traits>
{
 public:
    typedef typename traits::int_type int_type;
	typedef typename std::vector< std::basic_streambuf<char_type, traits> * > ptrs;
	typedef typename std::basic_streambuf<char_type, traits> * ptr;
	typedef typename ptrs::iterator buf_it;

	basic_teebuf(std::vector<std::shared_ptr<std::ofstream> > & streams) {
		typedef typename std::vector<std::shared_ptr<std::ofstream> >::iterator stream_it;
		for (stream_it it = streams.begin(); it != streams.end(); it++)
			bufs.push_back((*it)->rdbuf());
		bufs.push_back(std::cout.rdbuf());  // this is hardcoded solution
	}
 private:

	virtual int sync() {
		bool flag = false;

		for (buf_it it = bufs.begin(); it != bufs.end(); it++) {
			if ( (*it)->pubsync() == 0 )
				flag = true;
		}
		return flag ? 0 : -1;
	}

	virtual int_type overflow(int_type c) {
        int_type const eof = traits::eof();

        if (traits::eq_int_type(c, eof))
            return traits::not_eof(c);

		bool flag = false;

		char_type const ch = traits::to_char_type(c);
		for (buf_it it = bufs.begin(); it != bufs.end(); it++) {
			int_type const r = (*it)->sputc(ch);
			if ( traits::eq_int_type(r, eof) )
				flag = true;
		}
		return flag ? eof : c;
    }

 private:
	ptrs bufs;

};

typedef basic_teebuf<char> teebuf;

class teestream : public std::ostream {
 public:

	teestream(std::vector<std::shared_ptr<std::ofstream> > & streams)
			: std::ostream(&tbuf)
			, tbuf(streams) {}
 private:
	teebuf tbuf;
};
