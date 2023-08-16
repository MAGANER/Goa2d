#ifndef ERROR_LOGGER_H
#define ERROR_LOGGER_H
#include"SDL.h"
#include<string>
#include<iostream>
#include<fstream>
namespace Goat2d
{
namespace core 
{
	static void print_error(const std::string& additional_info)
	{
		std::cout << additional_info << SDL_GetError();
	}
	static void write_error(const std::string& additional_info)
	{
		std::time_t t = std::time(0);
		auto log_file_name = std::string(std::ctime(&t));

		std::ofstream f(log_file_name);
		f << additional_info << SDL_GetError()<<std::endl;
	}
};
};
#endif //ERROR_LOGGER_H
