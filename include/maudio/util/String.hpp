/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_MSTRING
#define MAUDIO_MSTRING

#include <cstring>
#include <string>
#include <ostream>

namespace maudio{

///String class that takes ownership of char * on assignment
class String{
public:
	String(const char *str);
	String(std::string &str);
	String(String &str);
	String();
	~String();

	void operator=(const char *str);
	void operator=(std::string &str);
	void operator=(String &str);

	String operator+(const char *str);
	String operator+(std::string &str);
	String operator+(String &str);

	char operator[](unsigned int i);

	operator bool();

	unsigned int size();
	const char *c_str();
	char *release();
	void clear();

	friend std::ostream& operator<<(std::ostream &out, String &str);

private:
	char *mData = NULL;
	unsigned int mSize = 0;
};

std::ostream& operator<<(std::ostream &out, String &str);

} // maudio

#endif // MAUDIO_MSTRING




