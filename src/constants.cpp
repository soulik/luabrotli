#include "common.hpp"
#include "constants.hpp"

namespace luabrotli {
	void initConstants(State * state, Module & module) {
		Stack * stack = state->stack;

		stack->setField<int>("RESULT_ERROR", BROTLI_RESULT_ERROR);
		stack->setField<int>("RESULT_SUCCESS", BROTLI_RESULT_SUCCESS);
		stack->setField<int>("RESULT_NEEDS_MORE_INPUT", BROTLI_RESULT_NEEDS_MORE_INPUT);
		stack->setField<int>("RESULT_NEEDS_MORE_OUTPUT", BROTLI_RESULT_NEEDS_MORE_OUTPUT);

		stack->push<const std::string &>("mode");
		stack->newTable();
		{
			stack->setField<int>("GENERIC", BrotliParams::MODE_GENERIC);
			stack->setField<int>("TEXT", BrotliParams::MODE_TEXT);
			stack->setField<int>("FONT", BrotliParams::MODE_FONT);
		}
		stack->setTable();
	}
}

