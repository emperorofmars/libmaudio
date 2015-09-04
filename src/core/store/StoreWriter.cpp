/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/StoreWriter.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

namespace maudio{

template<>
void StoreWriter<IKeyValueStore>::writeFile(const char *file, IKeyValueStore *store){
	if(!store) throw MaudioException("nvalid tore");
	std::ofstream ofile(file);
	if(!ofile.is_open()) throw MaudioException("couldn't open file!");
	
	writeStream(ofile, store);
	
	ofile.flush();
	return;
}

template<>
void StoreWriter<IKeyValueStore>::writeStream(std::ostream &stream, IKeyValueStore *store){
	if(!store) throw MaudioException("invalid store");
	if(!stream.good()) throw MaudioException("invalid stream");
	
	stream << "|IKeyValueStore" << std::endl;
	
	for(unsigned int i = 0; i < store->getSize(); i++){
		const char *key = store->getKey(i);
		const char *value = store->get(i);
		if(!key || !value) continue;
		stream << key  << " " << value << std::endl;
	}
	return;
}

template<>
void StoreWriter<IMultiStore>::writeFile(const char *file, IMultiStore *store){
	if(!store) throw MaudioException("nvalid tore");
	std::ofstream ofile(file);
	if(!ofile.is_open()) throw MaudioException("couldn't open file!");
	
	writeStream(ofile, store);
	
	ofile.flush();
	return;
}

template<>
void StoreWriter<IMultiStore>::writeStream(std::ostream &stream, IMultiStore *store){
	if(!store) throw MaudioException("invalid store");
	if(!stream.good()) throw MaudioException("invalid stream");
	
	stream << "|IMultiStore" << std::endl;
	
	for(unsigned int i = 0; i < store->getSize(); i++){
		const char *key = store->getKey(i);
		const char *value = store->get(i);
		if(!key || !value) continue;
		stream << key  << " " << value << std::endl;
	}
	return;
}

template<>
void StoreWriter<IMultiLevelStore>::writeFile(const char *file, IMultiLevelStore *store){
	if(!store) throw MaudioException("nvalid tore");
	std::ofstream ofile(file);
	if(!ofile.is_open()) throw MaudioException("couldn't open file!");
	
	writeStream(ofile, store);
	
	ofile.flush();
	return;
}

template<>
void StoreWriter<IMultiLevelStore>::writeStream(std::ostream &stream, IMultiLevelStore *store){
	if(!store) throw MaudioException("invalid store");
	if(!stream.good()) throw MaudioException("invalid stream");
	
	stream << "|IMultiLevelStore" << std::endl;
	
	writeLevel(stream, store);
	
	return;
}

template<>
void StoreWriter<IMultiLevelStore>::writeLevel(std::ostream &stream, IMultiLevelStore *store, unsigned int indentLevel){
	
	for(unsigned int i = 0; i < store->getSize(); i++){
		const char *key = store->getKey(i);
		const char *value = store->get(i);
		if(!key || !value) continue;
		stream << printIndent(indentLevel) << key  << " " << value << std::endl;
	}
	
	for(unsigned int i = 0; i < store->getNumLevels(); i++){
		stream << printIndent(indentLevel) << "!level " << store->getLevelKey(i) << std::endl;
		writeLevel(stream, store->getLevel(i), indentLevel + 1);
		stream << printIndent(indentLevel) << "!end" << std::endl;
	}
	return;
}

template<>
std::string StoreWriter<IMultiLevelStore>::printIndent(unsigned int indentLevel){
	std::string ret;
	for(unsigned int ind = 0; ind < indentLevel; ind++){
		ret += '\t';
	}
	return ret;
}

} // maudio



