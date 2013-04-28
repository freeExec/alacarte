#include "utils/time_win.hpp"
int gettimeofday(struct timeval* tp, void *)
	{
	boost::date_time::winapi::FILETIME ft;
	//FILETIME ft;
 
	//::GetSystemTimeAsFileTime( &ft );  // never fails
	boost::date_time::winapi::get_system_time_as_file_time(ft);
	long long t = (static_cast<long long>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
	# if !defined( BOOST_MSVC ) || BOOST_MSVC > 1300 // > VC++ 7.0
	t -= 116444736000000000LL;
	# else
	t -= 116444736000000000;
	# endif
	t /= 10;  // microseconds
	tp->tv_sec = static_cast<long>( t / 1000000UL);
	tp->tv_usec = static_cast<long>( t % 1000000UL);
	return 0;
	}
