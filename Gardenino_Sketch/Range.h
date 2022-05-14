#pragma once

template <typename T>
struct Range
{
	Range(T start, T end)
	{
		Start = start;
		End = end;
	}

	T Start;
	T End;
};