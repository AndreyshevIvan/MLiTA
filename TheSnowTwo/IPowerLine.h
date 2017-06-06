#pragma once

class IPowerLine
{
public:
	virtual ~IPowerLine() = default;

	virtual long long GetSnowSum(size_t from, size_t to) const = 0;
	virtual void AddSnow(size_t from, size_t to, int snowCount) = 0;
};