/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_STOREWRITER
#define MAUDIO_STOREWRITER

#include "maudio/store/KeyValueStore.hpp"
#include "maudio/store/MultiStore.hpp"
#include "maudio/store/MultiLevelStore.hpp"
#include <string>
#include <iostream>

namespace maudio{

template<typename T>
class StoreWriter{
public:
	StoreWriter();
	~StoreWriter();

	void writeFile(const char *file, T *store);
	void writeStream(std::ostream &stream, T *store);

private:
	void writeLevel(std::ostream &stream, IMultiLevelStore *store, unsigned int indentLevel = 0);
	std::string printIndent(unsigned int indentLevel);
};

template<>
void StoreWriter<IKeyValueStore>::writeFile(const char *file, IKeyValueStore *store);
template<>
void StoreWriter<IKeyValueStore>::writeStream(std::ostream &stream, IKeyValueStore *store);
template<>
void StoreWriter<IMultiStore>::writeFile(const char *file, IMultiStore *store);
template<>
void StoreWriter<IMultiStore>::writeStream(std::ostream &stream, IMultiStore *store);
template<>
void StoreWriter<IMultiLevelStore>::writeFile(const char *file, IMultiLevelStore *store);
template<>
void StoreWriter<IMultiLevelStore>::writeStream(std::ostream &stream, IMultiLevelStore *store);

template<>
void StoreWriter<IMultiLevelStore>::writeLevel(std::ostream &stream, IMultiLevelStore *store, unsigned int indentLevel);
template<>
std::string StoreWriter<IMultiLevelStore>::printIndent(unsigned int indentLevel);


template<typename T>
StoreWriter<T>::StoreWriter(){
}

template<typename T>
StoreWriter<T>::~StoreWriter(){
}

} // maudio

#endif // MAUDIO_STOREWRITER




