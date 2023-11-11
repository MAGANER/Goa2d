/*!
\file
\brief Class to compute elapsed time
\author Maganer
\version 0.2
\date 02.09.2023
*/


#ifndef TIMER_H
#define TIMER_H
#include<chrono>
namespace Goat2d
{
namespace core
{


	/*!
	\brief Class to compute elapsed time
	\author MAGANER
	\date 10.09.2023
	*/
	class Timer
	{
		//! time point of computation start
		std::chrono::time_point<std::chrono::steady_clock> start_point;

		//! time point of computation finish
		std::chrono::time_point<std::chrono::steady_clock> end_point;
	public:
		//! creates timer
		Timer() {}


		//! delete timer
		~Timer() {}


		//!  set time point of computation start.
		void start();


		//! compute the difference between end point and start point.
		double get_elapsed_ticks();
	private:
		//! set time point of computation finish.
		void stop();
	};
};
};
#endif //TIMER_H