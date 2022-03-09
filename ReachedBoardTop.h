#pragma once
#include <exception>

// This class helps control game flow
class ReachedBoardTopException :
	public std::exception
{
public:
	explicit ReachedBoardTopException() {}

	virtual ~ReachedBoardTopException() noexcept {}
};

