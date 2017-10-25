#pragma once

#include "MyLibrary.h"

#ifndef COLORS_H
#define COLORS_H

namespace color
{
	/*Klasa pobrana ze strony: https://www.dropbox.com/s/jsdxeoqmc8bezll/Colors.h?dl=0,
	gdy¿ standardowe SetConsoleTextAttribute nie dzia³a.*/
	class color
	{
		friend std::ostream& operator<<(std::ostream& stream, color& color);
	public:
		color(WORD chosenColor = 0x0007) : chosenColor(chosenColor)
		{
		}
	private:
		WORD chosenColor;
	};

	std::ostream& operator<<(std::ostream& stream, color& color)
	{
		static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, color.chosenColor);
		return stream;
	}

	color red(FOREGROUND_RED);
	color blue(FOREGROUND_BLUE);
	color green(FOREGROUND_GREEN);
	color yellow(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	color white(0x0007);
	color grey(0x0008);
	color seledin(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
#endif