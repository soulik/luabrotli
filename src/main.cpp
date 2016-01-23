/*
	luabrotli - Lua binding for brotli library

	Copyright 2016 Mário Kašuba

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "common.hpp"
#include "init_classes.hpp"

using namespace luabrotli;

int compress(State & state){
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

	if (stack->is<LUA_TSTRING>(2) && stack->is<LUA_TNUMBER>(3)){
		std::string inputBuffer = stack->toLString(2);

		size_t outputBufferSize = stack->to<int>(3);
		uint8_t * outputBuffer = new uint8_t[outputBufferSize];

		int result = BrotliCompressBuffer(params, inputBuffer.size(), reinterpret_cast<const uint8_t*>(inputBuffer.c_str()), &outputBufferSize, outputBuffer);
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

int decompress(State & state){
	Stack * stack = state.stack;
	if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TNUMBER>(2)){
		std::string inputBuffer = stack->toLString(1);

		size_t outputBufferSize = stack->to<int>(2);
		uint8_t * outputBuffer = new uint8_t[outputBufferSize];

		int result = BrotliDecompressBuffer(inputBuffer.size(), reinterpret_cast<const uint8_t*>(inputBuffer.c_str()), &outputBufferSize, outputBuffer);
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

int decompressedSize(State & state){
	Stack * stack = state.stack;
	if (stack->is<LUA_TSTRING>(1)){
		std::string inputBuffer = stack->toLString(1);
		size_t decodedSize = 0;

		int result = BrotliDecompressedSize(inputBuffer.size(), reinterpret_cast<const uint8_t*>(inputBuffer.c_str()), &decodedSize);
		if (result == BROTLI_RESULT_SUCCESS){
			stack->push<int>(decodedSize);
		}
		else{
			stack->push<bool>(false);
		}
		return 1;
	}
	return 0;
}

extern "C" LUABROTLI_DLL_EXPORTED int luaopen_luabrotli(lua_State * L){
	State * state = new State(L);
	Stack * stack = state->stack;
	Module luabrotli_module;

	stack->newTable();
	
	initConstants(state, luabrotli_module);
	initCompressor(state, luabrotli_module);
	initDecompressor(state, luabrotli_module);

	luabrotli_module["compress"] = compress;
	luabrotli_module["decompress"] = decompress;
	luabrotli_module["decompressedSize"] = decompressedSize;

	state->registerLib(luabrotli_module);
	return 1;
}

