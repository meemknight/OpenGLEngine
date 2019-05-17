/////////////////////////////////////////////
//tools.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

///define FORCE_LOG
///to controll the behavour of the log or just 
///change from debug to releasee

///define ERRORS_ONLY
///to only display error messages


#pragma once
#include <iostream>
#include <Windows.h>
#include <sstream>

#define ERRORS_ONLY

#ifdef _DEBUG
#define FORCE_LOG
#endif

#ifdef ERRORS_ONLY
#undef FORCE_LOG

	

#endif // ERRORS_ONLY



#ifdef FORCE_LOG
inline void llog()
{
	std::cout << "\n";
}

template<class F, class ...T>
inline void llog(F f, T ...args)
{
	std::cout << f << " ";
	llog(args...);
}
#else
template<class F, class ...T>
inline void llog(F f, T ...args)
{

}
#endif

///warning log
#ifdef FORCE_LOG
inline void wlog()
{
	std::cout << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

template<class F, class ...T>
inline void wlog(F f, T ...args)
{	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << f << " ";
	wlog(args...);
}
#else
template<class F, class ...T>
inline void wlog(F f, T ...args)
{

}
#endif

///important log
#ifdef FORCE_LOG
inline void ilog()
{
	std::cout << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

template<class F, class ...T>
inline void ilog(F f, T ...args)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	std::cout << f << " ";
	ilog(args...);
}
#else
template<class F, class ...T>
inline void ilog(F f, T ...args)
{

}
#endif

///good log
#ifdef FORCE_LOG
inline void glog()
{
	std::cout << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

template<class F, class ...T>
inline void glog(F f, T ...args)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << f << " ";
	glog(args...);
}
#else
template<class F, class ...T>
inline void glog(F f, T ...args)
{

}
#endif

///error log
#ifdef FORCE_LOG
inline void elog()
{
	std::cout << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

template<class F, class ...T>
inline void elog(F f, T ...args)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << f << " ";
	elog(args...);
}
#else

#ifdef ERRORS_ONLY

inline void elog(std::stringstream &&stream)
{
	OutputDebugString(stream.str().c_str());

	int rezult = MessageBox(0, stream.str().c_str(), "error, abort game ?", MB_YESNO | MB_ICONERROR);

	if (rezult == IDYES) 
	{
		exit(0);
	}

}

template<class F, class ...T>
inline void elog(std::stringstream &&stream, F &&f, T &&...args)
{
	stream << std::forward<F>(f) << " ";

	elog(std::move(stream), args...);
}

template<class F, class ...T>
inline void elog(F &&f, T &&...args)
{
	std::stringstream stream;

	stream << std::forward<F>(f) << " ";

	elog(std::move(stream), args...);
}



#else
template<class F, class ...T>
inline void elog(F f, T ...args)
{

}
#endif

#endif


/*

#ifdef _DEBUG 

#define log std::cout

#else // _DEBUG


struct _log
{
}log;

template<class T>
const _log& operator<<(const _log &l,const T &other) {}

#endif // RELEASE

*/

/*
#ifndef _DEBUG
static struct __RemoveCout
{
	__RemoveCout() { std::cout.rdbuf(nullptr); }
}_RemoveCout;
#endif // !_DEBUG
*/

/*
struct _Log {}log;
template<typename T>
_Log operator<<(_Log logger, const T &val) {
#ifdef _DEBUG
	std::cout << val;
#endif
	return logger;
}
*/