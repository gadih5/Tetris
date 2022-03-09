#pragma once

#include <exception>
#include <string>

// This class helps control game flow
class GameOverException :
	public std::exception
{
public:
	explicit GameOverException(const std::string& name)
		: m_looser_name(name) {}

	virtual ~GameOverException() noexcept {}

	virtual std::string who_lost() const noexcept { return  m_looser_name; }

protected:
	std::string m_looser_name;
};

