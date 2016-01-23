#include "objects/Compressor.hpp"

namespace luabrotli {
	BrotliCompressor * Compressor::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		BrotliParams params;
		if (stack->is<LUA_TTABLE>(1)){
			//Compression mode.
			stack->getField("mode", 1);
			if (stack->is<LUA_TNUMBER>(-1)){
				params.mode = static_cast<BrotliParams::Mode>(stack->to<int>(-1));
			}
			stack->pop();

			//Compression quality. Range is 0 to 11.
			stack->getField("quality", 1);
			if (stack->is<LUA_TNUMBER>(-1)){
				params.quality = stack->to<int>(-1);
			}
			stack->pop();

			//Base 2 logarithm of the sliding window size. Range is 10 to 24.
			stack->getField("lgwin", 1);
			if (stack->is<LUA_TNUMBER>(-1)){
				params.lgwin = stack->to<int>(-1);
			}
			stack->pop();

			//Base 2 logarithm of the maximum input block size. Range is 16 to 24.
			stack->getField("lgblock", 1);
			if (stack->is<LUA_TNUMBER>(-1)){
				params.lgblock = stack->to<int>(-1);
			}
			stack->pop();

			//Dictionary.
			stack->getField("enable_dictionary", 1);
			if (stack->is<LUA_TBOOLEAN>(-1)){
				params.enable_dictionary = stack->to<bool>(-1);
			}
			stack->pop();

			//Transforms.
			stack->getField("enable_transforms", 1);
			if (stack->is<LUA_TBOOLEAN>(-1)){
				params.enable_transforms = stack->to<bool>(-1);
			}
			stack->pop();

			//Greedy block split.
			stack->getField("greedy_block_split", 1);
			if (stack->is<LUA_TBOOLEAN>(-1)){
				params.greedy_block_split = stack->to<bool>(-1);
			}
			stack->pop();

			//Context modeling.
			stack->getField("enable_context_modeling", 1);
			if (stack->is<LUA_TBOOLEAN>(-1)){
				params.enable_context_modeling = stack->to<bool>(-1);
			}
			stack->pop();
		}

		return new BrotliCompressor(params);
	}

	void Compressor::destructor(State & state, BrotliCompressor * object){
		delete object;
	}

	int Compressor::getInputBlockSize(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;
		stack->push<int>(object->input_block_size());
		return 1;
	}

	int Compressor::brotliSetCustomDictionary(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			std::string dictionary = stack->toLString(1);
			object->BrotliSetCustomDictionary(dictionary.size(), reinterpret_cast<const uint8_t*>(dictionary.c_str()));
		}
		return 0;
	}

	int Compressor::writeMetaBlock(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TBOOLEAN>(2) && stack->is<LUA_TNUMBER>(3)){
			std::string inputBuffer = stack->toLString(1);

			bool isLast = stack->to<bool>(2);

			size_t outputBufferSize = stack->to<int>(3);
			uint8_t * outputBuffer = new uint8_t[outputBufferSize];

			int result = object->WriteMetaBlock(inputBuffer.size(), reinterpret_cast<const uint8_t*>(inputBuffer.c_str()), isLast, &outputBufferSize, outputBuffer);
			if (result == BROTLI_RESULT_SUCCESS){
				stack->pushLString(std::string(reinterpret_cast<const char*>(outputBuffer), outputBufferSize), outputBufferSize);
			}
			else{
				stack->push<bool>(false);
			}
			delete[] outputBuffer;
			return 1;
		}
		return 0;
	}
	int Compressor::writeMetadata(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;

		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TBOOLEAN>(2) && stack->is<LUA_TNUMBER>(3)){
			std::string inputBuffer = stack->toLString(1);

			bool isLast = stack->to<bool>(2);

			size_t outputBufferSize = stack->to<int>(3);
			uint8_t * outputBuffer = new uint8_t[outputBufferSize];

			int result = object->WriteMetadata(inputBuffer.size(), reinterpret_cast<const uint8_t*>(inputBuffer.c_str()), isLast, &outputBufferSize, outputBuffer);
			if (result == BROTLI_RESULT_SUCCESS){
				stack->pushLString(std::string(reinterpret_cast<const char*>(outputBuffer), outputBufferSize), outputBufferSize);
			}
			else{
				stack->push<bool>(false);
			}
			delete[] outputBuffer;
			return 1;
		}
		return 0;
	}
	int Compressor::finishStream(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;

		if (stack->is<LUA_TNUMBER>(1)){
			size_t outputBufferSize = stack->to<int>(1);
			uint8_t * outputBuffer = new uint8_t[outputBufferSize];

			int result = object->FinishStream(&outputBufferSize, outputBuffer);
			if (result == BROTLI_RESULT_SUCCESS){
				stack->pushLString(std::string(reinterpret_cast<const char*>(outputBuffer), outputBufferSize), outputBufferSize);
			}
			else{
				stack->push<bool>(false);
			}
			delete[] outputBuffer;
			return 1;
		}
		return 0;
	}
	int Compressor::copyInputToRingBuffer(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;

		if (stack->is<LUA_TSTRING>(1)){
			std::string inputBuffer = stack->toLString(1);

			object->CopyInputToRingBuffer(inputBuffer.size(), reinterpret_cast<const uint8_t*>(inputBuffer.c_str()));
		}
		return 0;
	}
	int Compressor::writeBrotliData(State & state, BrotliCompressor * object){
		Stack * stack = state.stack;

		if (stack->is<LUA_TBOOLEAN>(1) && stack->is<LUA_TBOOLEAN>(2) && stack->is<LUA_TNUMBER>(3)){
			size_t outputBufferSize = stack->to<int>(1);
			uint8_t * outputBuffer = nullptr;

			bool isLast = stack->to<bool>(1);
			bool forceFlush = stack->to<bool>(2);

			int result = object->WriteBrotliData(isLast, forceFlush, &outputBufferSize, &outputBuffer);
			if (result){
				stack->pushLString(std::string(reinterpret_cast<const char*>(outputBuffer), outputBufferSize), outputBufferSize);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}


	void initCompressor(State * state, Module & module){
		INIT_OBJECT(Compressor);
	}
};
