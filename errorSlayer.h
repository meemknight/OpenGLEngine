#pragma once
/*
	Luca's Error Handling library for C++: Error Slayer
	Macro params:
	ErrorSlayerUnityBuild     - removes extern specifier
	ErrorSlayerNoTS           - removes thread_local specifier
	ErrorSlayerErrorTypeCheck - includes type checks for the error enum
*/

//Modify this enum, recommend you keep None otherwise you will need to modify the macros
#define ErrorSlayerErrorTypeCheck

#ifdef ErrorSlayerNoTS 
#define error_slayer_thread_local 
#else 
#define error_slayer_thread_local thread_local
#endif

namespace ErrorSlayer
{
	enum class Error
	{
		None = 0,
		IOFail, //Feel free to remove this one
	};

#ifdef ErrorySlayerUnityBuild
	error_slayer_thread_local bool  errorEncountered;
	error_slayer_thread_local Error errorTag;
#else
	extern error_slayer_thread_local bool  errorEncountered;
	extern error_slayer_thread_local Error errorTag;
#endif
};

#define ignoreError ; ErrorSlayer::errorEncountered = false; ErrorSlayer::errorTag = ErrorSlayer::Error::None;

#define assertNoError ; assert(!ErrorSlayer::errorEncountered);

#define handleError(code) ; if (ErrorSlayer::errorEncountered) { code; ErrorSlayer::errorEncountered = false; ErrorSlayer::errorTag = ErrorSlayer::Error::None; }

#define propagateErrorWith(returnVal) ; if (ErrorSlayer::errorEncountered) { return returnVal; }
#define propagateError ; if (ErrorSlayer::errorEncountered) { return; }

#define ErrorSlyerMakeErrorState() namespace ErrorSlayer { error_slayer_thread_local bool errorEncountered; error_slayer_thread_local Error errorTag; }

#ifdef ErrorySlayerErrorTypeCheck
namespace ErrorSlayer
{
	//Basically std::is_same but I didn't want to have a dependency on the stdlib
	template<class A, class B> struct MetaTypeEquals
	{
		constexpr static auto result = false;
	};

	template<class A> struct MetaTypeEquals<A, A>
	{
		constexpr static auto result = true;
	};

	template<class A, class B> constexpr auto typeEquals = MetaTypeEquals<A, B>::result;
};

#define returnErrorWith(returnVal, error) static_assert(ErrorSlayer::typeEquals<decltype(ErrorSlayer::Error:: error), ErrorSlayer::Error>, "Any error must be of type Error from ErrorHandling.cpp."); ErrorSlayer::errorEncountered = true; ErrorSlayer::errorTag = ErrorSlayer::Error:: error; return returnVal;
#define returnError(error) static_assert(ErrorSlayer::typeEquals<decltype(ErrorSlayer::Error:: error), ErrorSlayer::Error>, "Any error must be of type Error from ErrorHandling.cpp."); ErrorSlayer::errorEncountered = true; ErrorSlayer::errorTag = ErrorSlayer::Error:: error; return;

#else 

#define returnErrorWith(returnVal, error) ErrorSlayer::errorEncountered = true; ErrorSlayer::errorTag = ErrorSlayer::Error:: error; return returnVal;
#define returnError(error) ErrorSlayer::errorEncountered = true; ErrorSlayer::errorTag = ErrorSlayer::Error:: error; return;

#endif