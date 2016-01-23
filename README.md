luabrotli
=========

Lua binding for Brotli compression library

Dependencies
===========

* Lutok2 - https://github.com/soulik/lutok2
* Brotli - https://github.com/google/brotli
* Lua 5.x or LuaJIT 2.x - http://www.lua.org/ or http://luajit.org/
* cmake 3.x - http://www.cmake.org/

Usage
=====

Compression
-----------

```lua
local brotli = require 'luabrotli'

local input = [[
Lorem ipsum dolor sit amet...
]]

local outputBufferSize = 4096

-- Omitted parameters are set to defaults.
local parameters = {
	--[[
		brotli.mode.GENERIC 		-	Default compression mode.
		brotli.mode.TEXT			-	Compression mode for UTF-8 format text input.
		brotli.mode.FONT			-	Compression mode used in WOFF 2.0.
	--]]
	mode = brotli.mode.GENERIC,

	-- Compression quality: 0 (Worst) - 11 (Best)
	quality = 11,

	-- Base 2 logarithm of the sliding window size. Range is 10 to 24.
	lgwin = 11,

	-- Base 2 logarithm of the maximum input block size. Range is 16 to 24.
	lgblock = 11,

	enable_dictionary = true,
	enable_transforms = false,
	greedy_block_split = false,
	enable_context_modeling = true,
}
local out = assert(brotli.compress(parameters, input, outputBufferSize))
```

Decompression
-----------

```lua
local brotli = require 'luabrotli'

local input = [[
Lorem ipsum dolor sit amet...
]]

local outputBufferSize = 4096
local out = assert(brotli.compress({}, input, outputBufferSize))

local original = assert(brotli.decompress(out, brotli.decompressedSize(out)))
```

