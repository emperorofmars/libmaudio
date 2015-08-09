/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/String.hpp"

namespace maudio{

String::String(const char *str){
	*this = str;
	return;
}

String::String(std::string &str){
	*this = str;
	return;
}

String::String(String &str){
	*this = str;
	return;
}

String::String(){
	return;
}

String::~String(){
	clear();
	return;
}

void String::operator=(const char *str){
	clear();
	if(!str) return;
	mData = (char *)str;
	mSize = strlen(mData);
	return;
}

void String::operator=(std::string &str){
	clear();
	strcpy(mData, str.c_str());
	mSize = strlen(mData);
	return;
}

void String::operator=(String &str){
	clear();
	if(!str) return;
	strcpy(mData, str.c_str());
	mSize = strlen(mData);
	return;
}

String String::operator+(const char *str){
	char *tmp = new char[mSize + strlen(str) + 1];
	strcpy(tmp, mData);
	strcpy(tmp + mSize, str);
	String ret(tmp);
	return ret;
}

String String::operator+(std::string &str){
	char *tmp = new char[mSize + str.size() + 1];
	strcpy(tmp, mData);
	strcpy(tmp + mSize, str.c_str());
	String ret(tmp);
	return ret;
}

String String::operator+(String &str){
	char *tmp = new char[mSize + str.size() + 1];
	strcpy(tmp, mData);
	strcpy(tmp + mSize, str.c_str());
	String ret(tmp);
	return ret;
}

char String::operator[](unsigned int i){
	if(i > mSize) return '\0';
	return mData[i];
}

String::operator bool(){
	if(!mData) return false;
	return true;
}

unsigned int String::size(){
	return mSize;
}

const char *String::c_str(){
	return mData;
}

void String::clear(){
	if(mData != NULL) delete mData;
	mData = NULL;
	mSize = 0;
	return;
}

std::ostream& operator<<(std::ostream &out, String &str){
	out << str.mData;
	return out;
}


} // maudio



