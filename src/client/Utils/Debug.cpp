/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Debug.cpp
*/

#include "Debug.hpp"

Debug::Debug()
	:	_debugMode((DebugMode)(DEFAULT_DEBUG_MODE))
	,	_allowed(DEFAULT_DEBUG_ALLOWED_FILES)
	,	_forbidden(DEFAULT_DEBUG_FORBIDDEN_FILES)
{}

Debug & Debug::getInstance()
{
	static Debug instance;
	return instance;
}

bool	Debug::canDebug()
{
	if (!(_debugMode & ON))
		return false;
	bool allowFile = isAllowedFile(_currentFile);
	bool forbidFile = isForbiddenFile(_currentFile);
	return allowFile && !forbidFile;
}

bool	Debug::isAllowedFile(std::string const & file)
{
	if (_debugMode & ALLOW_ALL_FILES)
		return true;
	return std::find_if(_allowed.begin(), _allowed.end(),
		[file](std::string const & s)
		{
			return file.find(s) != std::string::npos;
		}
	) != _allowed.end();
}

bool	Debug::isForbiddenFile(std::string const & file)
{
	if (_debugMode & FORBID_ALL_FILES)
		return true;
	return std::find_if(_forbidden.begin(), _forbidden.end(),
		[file](std::string const & s)
		{
			return file.find(s) != std::string::npos;
		}
	) != _forbidden.end();
}

Debug &	Debug::setInfos(
	std::string const & file,
	std::string const & func,
	size_t line
) noexcept
{
	_currentFile = file;
	_currentFunc = func;
	_currentLine = line;
	return *this;
}

Debug &	Debug::setDebugMode(DebugMode mode) noexcept
{
	_debugMode = mode;
	return *this;
}

std::ostream &	Debug::showInfos(std::ostream & os)
{
	if (_debugMode & (SHOW_FILE | SHOW_FUNC | SHOW_LINE))
	{
		os	<< "[";
		if (_debugMode & SHOW_FILE)
			os << _currentFile;
		if (_debugMode & SHOW_LINE)
			os << ":" << _currentLine;
		if (_debugMode & SHOW_FUNC)
			os << " - " << _currentFunc;
		os << "]: ";
	}
	return os;
}