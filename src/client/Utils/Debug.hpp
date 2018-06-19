/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Debug.hpp
*/

#ifndef Debug_HPP
#define Debug_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <algorithm>

# define ACTIVATE_DEBUG		true

# define DEBUG	Debug::getInstance().setInfos(__FILE__, __func__, __LINE__)
# define DEFAULT_DEBUG_MODE		(ACTIVATE_DEBUG ? ON : OFF) | SHOW_FILE | SHOW_FUNC | SHOW_LINE | ALLOW_ALL_FILES
# define DEFAULT_DEBUG_ALLOWED_FILES	{ "main.cpp" }
# define DEFAULT_DEBUG_FORBIDDEN_FILES	{ "AiBrain", "TcpBrain" }

class Debug
{
public:

	enum DebugMode
	{
		OFF = 0x0,
		ON = 0x1,
		ALLOW_ALL_FILES = 0x2,
		FORBID_ALL_FILES = 0x4,
		SHOW_FILE = 0x8,
		SHOW_FUNC = 0x10,
		SHOW_LINE = 0x20
	};

	class NullStream : public std::ostream
	{
	public:

		NullStream()
			:	std::ostream(&_nb)
		{}

	private:

		class NullBuffer : public std::streambuf
		{
		public:

			int	overflow(int c) override { return c; }

		}	_nb;

	};

	Debug();
	virtual ~Debug() = default;
	Debug(Debug const & rhs) = delete;
	Debug(Debug && rhs) = delete;
	Debug & operator=(Debug const & rhs) = delete;
	Debug & operator=(Debug && rhs) = delete;

	template <typename T>
	std::ostream & operator<<(T const & t)
	{
		static NullStream buf;
		if (!canDebug())
			return buf;
		return showInfos(std::cout) << t;
	}

	template <typename T>
	Debug & operator>>(T const & t)
	{
		static NullStream buf;
		if (canDebug())
			t();
		return *this;
	}

	static Debug & getInstance();

	Debug &	setInfos(
			std::string const & file,
			std::string const & func,
			size_t line
		) noexcept;

	Debug &	setDebugMode(DebugMode mode) noexcept;

private:

	bool			canDebug();
	bool			isAllowedFile(std::string const & file);
	bool			isForbiddenFile(std::string const & file);
	std::ostream &	showInfos(std::ostream & os);

	DebugMode				_debugMode;
	std::list<std::string>	_allowed;
	std::list<std::string>	_forbidden;
	std::string 			_currentFile;
	std::string 			_currentFunc;
	size_t					_currentLine;

};

#endif // !Debug_HPP
