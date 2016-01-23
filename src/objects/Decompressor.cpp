#include "objects/Decompressor.hpp"

namespace luabrotli {
	BrotliState * Decompressor::constructor(State & state, bool & managed){
		BrotliState * object = BrotliCreateState(0, 0, nullptr);
		return object;
	}

	void Decompressor::destructor(State & state, BrotliState * object){
		BrotliDestroyState(object);
	}

	int Decompressor::brotliSetCustomDictionary(State & state, BrotliState * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			std::string dictionary = stack->toLString(1);
			BrotliSetCustomDictionary(dictionary.size(), reinterpret_cast<const uint8_t*>(dictionary.c_str()), object);
		}
		return 0;
	}
	/*
		WARNING! NOT TESTED!!!
	*/
	int Decompressor::decompressStream(State & state, BrotliState * object){
		Stack * stack = state.stack;

		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TNUMBER>(2)){
			std::string inputBuffer = stack->toLString(1);

			size_t outputBufferSize = stack->to<int>(2);
			uint8_t * outputBuffer = new uint8_t[outputBufferSize];

			size_t available_in = inputBuffer.size();
			const uint8_t * next_in = reinterpret_cast<const uint8_t*>(inputBuffer.c_str());
			size_t available_out = outputBufferSize;
			uint8_t * next_out = outputBuffer;
			size_t total_out = 0;

			int result = BrotliDecompressStream(&available_in, &next_in, &available_out, &next_out, &total_out, object);
			if (result == BROTLI_RESULT_SUCCESS){
				stack->pushLString(std::string(reinterpret_cast<const char*>(next_in), available_in), available_in);
				stack->pushLString(std::string(reinterpret_cast<const char*>(outputBuffer), available_out), available_out);
				stack->push<int>(total_out);
				delete[] outputBuffer;
				return 3;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				delete[] outputBuffer;
				return 2;
			}
		}
		return 0;
	}

	void initDecompressor(State * state, Module & module){
		INIT_OBJECT(Decompressor);
	}
};
