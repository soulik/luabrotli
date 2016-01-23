local brotli = require 'luabrotli'

function string.hex_dump(buf, options)
	local options = options or {}
	local first, last = options.first or 1, options.last or #buf
	local tabs = options.tabs or 0
	local tabsStr = ("\t"):rep(tabs)
	local prefix = options.prefix or ""
	local ti = table.insert
	local columns = 16
	local columnsHalf = columns/2
	local out = {}
	local function align(n) return math.ceil(n/columns) * columns end

	ti(out, ('%s%sLength: %dB\n'):format(prefix, tabsStr, #buf))

	for i=(align(first-columns)+1),align(math.min(last,#buf)) do
		if (i-1) % columns == 0 then
			ti(out,string.format('%s%08X  ', tabsStr, i-1))
		end
		
		table.insert(out, i > #buf and '   ' or string.format('%02X ', buf:byte(i)) )
		
		if i % columnsHalf == 0 then
			ti(out,' ')
		end
		
		if i % columns == 0 then
			ti(out,buf:sub(i-columns+1, i):gsub('%c','.')..'\n' )
		end
	end
	return table.concat(out)
end

local input = [[
Hello world!
Hello world?
]]

local out = assert(brotli.compress({}, input, 4096))

print(out:hex_dump())

local out2 = assert(brotli.decompress(out, brotli.decompressedSize(out)))

print(out2:hex_dump())
