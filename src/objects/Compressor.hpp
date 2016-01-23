#ifndef LUA_BROTLI_OBJECTS_COMPRESSOR_H
#define LUA_BROTLI_OBJECTS_COMPRESSOR_H

#include "common.hpp"

namespace luabrotli {
	class Compressor : public Object < BrotliCompressor > {
	public:
		explicit Compressor(State * state) : Object<BrotliCompressor>(state){
			LUTOK_PROPERTY("inputBlockSize", &Compressor::getInputBlockSize, &Compressor::nullMethod);
			LUTOK_PROPERTY("customDictionary", &Compressor::nullMethod, &Compressor::brotliSetCustomDictionary);

			LUTOK_METHOD("writeMetaBlock", &Compressor::writeMetaBlock);
			LUTOK_METHOD("writeMetadata", &Compressor::writeMetadata);
			LUTOK_METHOD("finishStream", &Compressor::finishStream);
			LUTOK_METHOD("copyInputToRingBuffer", &Compressor::copyInputToRingBuffer);
			LUTOK_METHOD("writeBrotliData", &Compressor::writeBrotliData);
		}

		BrotliCompressor * constructor(State & state, bool & managed);

		void destructor(State & state, BrotliCompressor * object);

		int getInputBlockSize(State & state, BrotliCompressor * object);
		int brotliSetCustomDictionary(State & state, BrotliCompressor * object);

		int writeMetaBlock(State & state, BrotliCompressor * object);
		int writeMetadata(State & state, BrotliCompressor * object);
		int finishStream(State & state, BrotliCompressor * object);
		int copyInputToRingBuffer(State & state, BrotliCompressor * object);
		int writeBrotliData(State & state, BrotliCompressor * object);

	};
};

#endif	
