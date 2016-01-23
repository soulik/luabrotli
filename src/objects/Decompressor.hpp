#ifndef LUA_BROTLI_OBJECTS_DECOMPRESSOR_H
#define LUA_BROTLI_OBJECTS_DECOMPRESSOR_H

#include "common.hpp"

namespace luabrotli {
	class Decompressor : public Object<BrotliState> {
	public:
		explicit Decompressor(State * state) : Object<BrotliState>(state){
			LUTOK_PROPERTY("customDictionary", &Decompressor::nullMethod, &Decompressor::brotliSetCustomDictionary);
			LUTOK_METHOD("decompressStream", &Decompressor::decompressStream);
		}

		BrotliState * constructor(State & state, bool & managed);

		void destructor(State & state, BrotliState * object);

		int brotliSetCustomDictionary(State & state, BrotliState * object);
		int decompressStream(State & state, BrotliState * object);
	};
};

#endif	
