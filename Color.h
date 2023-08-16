#ifndef COLOR_H
#define COLOR_H
namespace Goat2d
{
namespace core
{
	typedef unsigned short ushort;
	struct Color
	{
		ushort r, g, b, a;
		Color()
		{
			r = 0;
			g = 0;
			b = 0;
			a = 0;
		}
		Color(ushort r, ushort g, ushort b, ushort a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
		Color(const Color& color)
		{
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;
		}
		~Color(){}

		Color operator=(const Color& _color)
		{
			return Color(_color);
		}
};
};
};
#endif