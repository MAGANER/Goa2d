#include"Timer.h"
using namespace Goat2d::core;

void Timer::start()
{
	start_point = std::chrono::steady_clock::now();
}
void Timer::stop()
{
	end_point = std::chrono::steady_clock::now();
}
double Timer::get_elapsed_ticks()
{
	stop();
	const std::chrono::duration<double> diff = end_point - start_point;
	start();
	return diff.count();
}