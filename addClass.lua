local templates = {
	hpp =
[[#ifndef LUA_BROTLI_OBJECTS_{{CNAME}}_H
#define LUA_BROTLI_OBJECTS_{{CNAME}}_H

#include "common.hpp"

namespace luabrotli {
	class {{CLASS}} : public Object<{{ORIG_CLASS}}> {
	public:
		explicit {{CLASS}}(State * state) : Object<{{ORIG_CLASS}}>(state){
		}

		{{ORIG_CLASS}} * constructor(State & state, bool & managed);

		void destructor(State & state, {{ORIG_CLASS}} * object);
	};
};

#endif	
]],
	cpp =
[[#include "objects/{{CLASS}}.hpp"

namespace luabrotli {
	{{ORIG_CLASS}} * {{CLASS}}::constructor(State & state, bool & managed){
		return nullptr;
	}

	void {{CLASS}}::destructor(State & state, {{ORIG_CLASS}} * object){
		delete object;
	}

	void init{{CLASS}}(State * state, Module & module){
		INIT_OBJECT({{CLASS}});
	}
};
]]
}

local function putFile(name, className, template, path)
	local f = io.open(path, "w")
	if f then
		f:write((template:gsub("{{([^{}]+)}}", {
			CNAME = name:upper(),
			CLASS = name,
			ORIG_CLASS = className,
		})))
		f:close()
		return true
	else
		return false
	end
end

local genClassFile = function(name, orig_class_name)
	putFile(name, orig_class_name, templates.hpp, ('src/objects/%s.hpp'):format(name))
	putFile(name, orig_class_name, templates.cpp, ('src/objects/%s.cpp'):format(name))
end

if #arg>1 then
	genClassFile(tostring(arg[1]), tostring(arg[2]))
else
	print(("lua %s <name> <orig_class_name>"):format(arg[0]))
	return {
		genclassFile = genClassFile,
		putFile = putFile,
	}
end