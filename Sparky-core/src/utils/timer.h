#pragma once

#include <Windows.h>

namespace sparky {

	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Freq;
	public:
		Timer()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			m_Freq = 1.0 / freq.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Freq);
		}

	};

}