--[[brainf.lua
A brainf*** program language interpreter written in Lua
    along with an implement of class system
    for Lua 5.1/5.2/5.3
    by Iweidieng Iep on 2019-7-24
]]

unpack = unpack or table.unpack;

-- OOP utility

-- Functions for member names
function isIdentifier(str)
    return type(str) == 'string' and str:match('^[_%a][_%w]*$');
end
function isMetatableEvent(str)
    return type(str) == 'string' and str:match('^__.+[^_]+$');
end
function isSpecialMethod(str)
    return type(str) == 'string' and str:match('^__.+__$');
end

-- garbage collection
function makeWeakTable(tbl, mode)
    if tbl ~= nil and type(tbl) ~= 'table' then tbl, mode = nil, mode; end
    local res = tbl or {};
    setmetatable(res, {__mode = mode or 'v'});
    return res;
end

-- The formal basic class of all primitive types
primitive = 'primitive';
primitive_types = {
    ['nil']=true, boolean=true, number=true, string=string,
    ['function']=true, userdata=true, thread=true, table=true,};

-- The class of all the classes
class = {
    __name__ = 'class',
    __call = function (cls, ...) return cls.__new__(...); end,
    __super_cache__ = makeWeakTable{},
    __deriveds__ = makeWeakTable{},
};

-- Query functions for class information

inspector = {};

function typeof(obj)
    local meta = getmetatable(obj);
    if meta and meta.__class__ == class then
        if type(obj) ~= 'table' or obj.__class__ == meta then
            return meta;
        end
    end
    return type(obj);
end

function isprimitivetype(class)
    return primitive_types[class] or false;
end
function isprimitive(obj)
    return isprimitivetype(typeof(obj));
end

function issubclass(class_, classinfo)
    if class_ == classinfo then return true; end
    if isprimitivetype(class_) and classinfo == primitive then return true; end
    if typeof(class_) == class then
        for idx, cls in pairs(rawget(class_, '__bases__') or {}) do
            if issubclass(cls, classinfo) then return true; end
        end
    end
    return false;
end

function isinstance(obj, classinfo)
    if type(obj) == classinfo then return true; end
    if isprimitive(obj) and classinfo == primitive then return true; end
    if not isprimitive(obj) then
        return issubclass(typeof(obj), classinfo);
    end
    return false;
end

-- The special methods / metamethods of `class`

function class.__index_super__(cls, key)
    local res = rawget(cls, '__super_cache__')[key];
    if res ~= nil then return res; end
    for i, v in ipairs(rawget(cls, '__bases__')) do
        res = rawget(class, '__index__')(v, key);
        if res ~= nil then
            rawget(cls, '__super_cache__')[key] = res;
            return res;
        end
    end
end
function class.__index__(cls, key, obj)
    -- Member lookup of the class
    local res;
    local index = rawget(cls, '__index__');
    if index ~= nil then
        if type(index) == 'function' then
            res = index(obj or cls, key);
        else res = index[key]; end
        if res ~= nil then return res; end
    end
    res = rawget(cls, key);
    if res ~= nil then return res; end
    return rawget(class, '__index_super__')(cls, key);
end
class.__index = class.__index__;
function class:__super__(cls)
    if cls ~= nil and (self == cls or not issubclass(self, cls)) then
        error(inspector.info(cls)
            .. ' is not super class of ' .. inspector.info(self), 2);
    end
    local res = {};
    setmetatable(res, {
        __index = cls == nil and function (self_, key)
            return rawget(class, '__index_super__')(self, key);
        end or function (self_, key)
            return rawget(class, '__index__')(cls, key);
        end,
    });
    return res;
end
function class.__update_super_cache__(cls, key, value_prev, value)
    local cls_value_prev = rawget(cls, '__super_cache__')[key];
    if cls_value_prev and cls_value_prev == value_prev then
        rawget(cls, '__super_cache__')[key] = value;
    end
    for k, v in pairs(rawget(cls, '__deriveds__')) do
        rawget(class, '__update_super_cache__')(v, key, value_prev, value);
    end
end
function class.__newindex(cls, key, value)
    local value_prev = rawget(cls, key)
        or rawget(class, '__index_super__')(cls, key);
    rawset(cls, key, value);
    rawget(class, '__update_super_cache__')(cls, key, value_prev, value);
end
class.__class__ = class;
setmetatable(class, class);

function defBasicClass(class_def)
    rawset(class_def, '__class__', class);
    rawset(class_def, '__index__', rawget(class_def, '__index'));
    if rawget(class_def, '__bases__') == nil then
        rawset(class_def, '__bases__', {});
    end
    rawset(class_def, '__deriveds__', makeWeakTable{});
    rawset(class_def, '__super_cache__', makeWeakTable'v');
    -- Inherit metamethods from super classes
    for i, cls in ipairs(rawget(class_def, '__bases__')) do
        for k, v in pairs(cls) do
            if isMetatableEvent(k) then
                rawset(class_def, k, v);
            end
        end
        table.insert(rawget(cls, '__deriveds__'), class_def);
    end
    -- Member lookup of the instance
    function class_def:__index(key)
        return rawget(class, '__index__')(class_def, key, self);
    end
    function class_def:__super__(cls)
        return rawget(class, '__super__')(class_def, cls);
    end
    function class_def.__cast__(obj)
        rawset(obj, '__class__', class_def);
        setmetatable(obj, class_def);
        return obj;
    end
    function class_def.__new__(...)
        local function noop(...) end;
        local obj = rawget(class_def, '__cast__'){};
        local kwargs = ({...})[#{...}];
        if type(kwargs) == 'table' then
            (class_def:__index('__initfields__') or noop)(obj, kwargs);
        end
        (class_def:__index('__init__') or noop)(obj, ...);
        if type(kwargs) == 'table' then
            (class_def:__index('__checkfields__') or noop)(obj, kwargs);
        end
        return obj;
    end
    setmetatable(class_def, class);
    return class_def;
end

-- Inspect functions

function inspectStr(str, kwargs)
    local inline = kwargs and kwargs.inline;
    if type(str) ~= 'string' then return inspect(str); end
    local res = ('%q'):format(str);
    if inline then return res:gsub('\\\n', [[\n]]):gsub('\t', [[\t]]); end
    return res;
end
inspector.inspectStr = inspectStr;

function info(obj, show_type)
    show_type = (show_type == nil) and true or nil;
    if type(obj) == 'string' then
        return 'string(len = '..#obj..')';
    end
    if show_type and
            not isprimitive(obj) and rawget(typeof(obj), '__name__') then
        local res = {};
        res[1] = rawget(typeof(obj), '__name__');
        if typeof(obj) == class and rawget(obj, '__name__') then
            res[2] = (res[1] and ' ' or '')
                ..inspect(rawget(obj, '__name__'));
        end
        res[3] = (res[2] and ' ' or '') .. '(' .. tostring(obj) .. ')';
        return res[1] .. (res[2] or '') .. res[3];
    end
    return tostring(obj);
end
inspector.info = info;

local function inspect_key(key)
    return isIdentifier(key) and key
            or (type(key) == 'string') and inspectStr(key) or info(key);
end
local function inspect_value(key, value, kwargs)
    kwargs = kwargs or {};
    return ((kwargs.ignore and kwargs.ignore[key] == true)
            or (kwargs.ignore_v and kwargs.ignore_v[value] == true))
                and info(value, kwargs.show_type) or inspect(value, kwargs);
end
function inspect(obj, kwargs)
    kwargs = kwargs or {};
    local sep, fmt = kwargs.sep or ', ', kwargs.fmt;
    kwargs.sep = ', ';
    kwargs.ignore_v = kwargs.ignore_v or makeWeakTable'k';
    if obj ~= nil then kwargs.ignore_v[obj] = true; end
    if type(obj) == 'table' then
        local res_total = {};
        local res = {};
        local len = 0;
        local function fmt_kv(k, v, v_only)
            return ((type(fmt) == 'function') and fmt(k, v, v_only) or fmt)
                or (v_only and '%s'
                    or isIdentifier(k) and '%s = %s' or '[%s] = %s');
        end
        local function res_append(k, v, v_only)
            res[#res+1] = fmt_kv(k, v, v_only):format(
                select(v_only and 2 or 1, inspect_key(k),
                inspect_value(k, v, kwargs)));
            kwargs.ignore_v[v] = true;
        end
        if kwargs.ordered then
            for k, v in pairs(obj) do
                if type(k) == 'number' and k > len then len = k; end
            end
            for k = 1, len, 1 do res_append(k, obj[k], true); end
        end
        for k, v in pairs(obj) do
            if len and type(k) == 'number' and k > 0 and k <= len then
            elseif len and type(k) == 'number' and k == len + 1 then
                len = k;
                res_append(k, obj[k], true);
            else
                len = nil;
                if k ~= '__name__'
                      and not (not kwargs.detail and isSpecialMethod(k)) then
                    res_append(k, obj[k]);
                end
            end
        end
        if showtype and
              not isprimitive(obj) and rawget(typeof(obj), '__name__') then
            res_total[1] = rawget(typeof(obj), '__name__');
        end
        if rawget(obj, '__name__') then
            res_total[2] = (res_total[1] and ' ' or '')
                    .. inspect(rawget(obj, '__name__'));
        end
        res_total[3] = (res_total[2] and ' ' or '')
                .. '{'..table.concat(res, sep)..'}';
        return (res_total[1] or '') .. (res_total[2] or '') .. res_total[3];
    end
    return (type(obj) == 'string') and inspectStr(obj) or info(obj);
end
inspector.inspect = inspect;

-- The base class of all the other classes with default inheritance

Object = defBasicClass{
    __name__ = 'Object',
    info = info,
    inspect = inspect,
    __init__ = function (self, copy)
        if type(copy) == 'table' then
            for k, v in pairs(copy) do rawset(self, k, rawget(copy, k)); end
        end
    end,
    __required__ = {},
    __optional__ = {},
    __setfields__ = function (self, kwargs, fields, fields_ign, override)
        for k, v in pairs(kwargs) do
            if type(k) == 'string' then
                if fields and fields[k] ~= nil then
                    local key, value = k, fields[k];
                    if type(value) == 'table'
                          and isIdentifier(next(value)) then
                        key, value = next(value);
                    end
                    local res = {value:match(v)};
                    if #res ~= 0 and (override ~= false
                            or rawget(self, key) == nil) then
                        rawset(self, key, res[1]);
                    end
                elseif fields_ign and fields_ign[k] ~= nil then
                elseif not fields and rawget(self, k) ~= nil then
                    rawset(self, k, v);
                else
                    error('Invalid keyword parameter: '..inspect(k)..'\n'
                        .. 'Valid arguments: '
                        .. ((fields or fields_ign)
                            and inspect{fields, fields_ign}
                            or inspect(self)));
                end
            end
        end
        return self;
    end,
    __setrequired__ = function (self, kwargs)
        local fields = self.__class__:__index('__required__') or {};
        local fields_ign = self.__class__:__index('__optional__') or {};
        return self:__setfields__(kwargs, fields, fields_ign);
    end,
    __checkrequired__ = function (self, kwargs)
        local fields = self.__class__:__index('__required__') or {};
        for k, v in pairs(fields) do
            local key, value = k, v;
            if type(v) == 'table' and isIdentifier(next(v)) then
                key, value = next(v);
            end
            if kwargs[k] == nil and rawget(self, key) == nil then
                error('Missing required keyword parameter: '..inspect(k), 2);
            end
        end
        return self;
    end,
    __setoptional__ = function (self, kwargs)
        local fields_ign = self.__class__:__index('__required__') or {};
        local fields = self.__class__:__index('__optional__') or {};
        return self:__setfields__(kwargs, fields, fields_ign, false);
    end,
    __checkoptional__ = function (self)
        local fields = self.__class__:__index('__optional__') or {};
        for k, v in pairs(fields) do
            local key, value = k, v;
            if type(v) == 'table' and isIdentifier(next(v)) then
                key, value = next(v);
            end
            if rawget(self, key) == nil then self[key] = value:default(); end
        end
        return self;
    end,
    __initfields__ = function (self, kwargs)
        return self:__setrequired__(kwargs):__setoptional__(kwargs)
                :__checkoptional__();
    end,
    __checkfields__ = function (self, kwargs)
        return self:__checkrequired__(kwargs);
    end,
};
rawset(class, '__bases__', {Object});

-- Class definition functions

--[=[
    @name class
    @param obj: A non-primitive object
    @usage class(obj) => typeof(obj)

    @name class & localclass (use `class` here for example)
    @params (`a...` means 0 or more `a`s)
        name: A non-table object
        bases...: Tables of class `class` or `false`s
        def: A primitive table
    @returns A new class with `__name__`
            set to either `name` (if given) or `def.__name__`
            which inherits from `bases...`,
                `Object` (if `bases...` is empty),
                or nothing (if `false` appears in `bases...`)
    @syntax (`[a]` means `a` is optional)
        class[(name)](bases...)([def])
        class([name,] bases...)(def)
        class(name, base1, bases...)()
        class[(name)](bases..., def)
        class([name,] bases..., def)
]=]

local function def_class_base(global, first, ...)
    local name = (type(first) ~= 'table') and first or nil;
    local res = {};
    res.func = coroutine.wrap(function (...)
        local args, last_arg, def;
        local function parse_def(def_)
            def = (type(def_) == 'table' and isprimitive(def_))
                    and def_ or nil;
        end
        local function parse_args(...)
            args = {...};
            last_arg = args[#args];
            parse_def(last_arg);
        end
        parse_args(...);

        -- class(name)
        if name ~= nil and #args == 0 and def == nil then
            parse_args(coroutine.yield(res.func));
        end

        local bases = {};
        for i = 1, #args, 1 do
            if typeof(args[i]) == class then
                bases[#bases+1] = args[i];
            elseif args[i] == false then
                bases = nil;
                break;
            end
        end

        if def == nil then
            parse_def(coroutine.yield(res.func));
            if def == nil then
                error('Argument for parameter `def` '..inspect(def)
                    ..' is not a primitive table', 2);
            end
        end

        if name ~= nil then rawset(def, '__name__', name); end
        if bases == nil then
            rawset(def, '__bases__', {});
        else
            rawset(def, '__bases__', (#bases ~= 0) and bases or {Object});
        end
        local res_class = defBasicClass(def);
        name = rawget(res_class, '__name__');
        if global and isIdentifier(name) then
            _G[name] = res_class;
            _G['to'..name] = rawget(res_class, '__cast__');
        end
        return res_class;
    end);
    if name == nil then return res.func(first, ...); end
    return res.func(...);
end

function class.__new__(first, ...)
    -- class(obj) => typeof(obj)
    if #{...} == 0 and not isprimitive(first)
            and (type(first) ~= 'table' or typeof(first) ~= class) then
        return typeof(first);
    end
    return def_class_base(true, first, ...);
end
function localclass(...) return def_class_base(false, ...); end

-- Utility classes

class 'Table' (table);

class 'Set'(Table) {
    __init__ = function (self, array)
        for k, v in pairs(array) do self[v] = true; end
    end,
    __index = function (self, key) return rawget(self, key) or false; end,
    __mode = 'k',
};

class 'Ro'(Table) {
    __newindex = function (self, key, value)
        error(self:inspect{ordered=true}..' is read-only', 2);
    end,
};

class 'Enum'(Ro) {
    default = function (self) return rawget(self, 1); end,
    match = function (self, value)
        for k, v in pairs(self) do
            if v == value then return value; end
        end
        if value == nil then return; end
        error(inspect(value)..' is not a value in '
              ..self:inspect{ordered=true}, 2);
    end,
};

class 'TypeEnum'(Enum) {
    default = function (self) return self[1]; end,
    match = function (self, value)
        return self:__super__().match(self,
                (type(value) == 'table') and value.__class__ or type(value))
            and value;
    end,
};

-- Class system functionality checks

assert(typeof{} == 'table');
assert(typeof(TypeEnum) == class);
assert(typeof(class) == class);
assert(typeof(TypeEnum{} == TypeEnum));
assert(typeof(class{}) == class);

assert(isprimitivetype'table');
assert(not isprimitivetype'non_primitive_type');
assert(not isprimitivetype(primitive));

assert(isprimitive{});
assert(not isprimitive(TypeEnum{}));
assert(not isprimitive(class{}));

assert(issubclass(typeof{}, primitive));
assert(issubclass(typeof{}, typeof{}));
assert(issubclass(TypeEnum, Object));
assert(issubclass(TypeEnum, Enum));
assert(issubclass(TypeEnum, TypeEnum));
assert(issubclass(class(Enum, TypeEnum){}, TypeEnum));
assert(issubclass(class, Object));

assert(isinstance({}, primitive));
assert(isinstance({}, 'table'));
assert(isinstance(class, class));
assert(isinstance(class, Object));
assert(isinstance(TypeEnum, class));

do
    local X = localclass 'X'{};
    local Y = localclass 'Y'(X){};
    local Z = localclass 'Z'(X, Y){};
    local z = Z();

    local _class_member = Z.__name__;
    X.__name__ = 'XType';
    assert(Z.__name__ == 'Z');
    assert(Z:__super__().__name__ == X.__name__);
    assert(z:__super__().__name__ == X.__name__);
    assert(z:__super__(X).__name__ == X.__name__);
    assert(z:__super__(Y).__name__ == Y.__name__);
    assert(Y.__name__ == 'Y');

    local _nonexist_member = Z.nonexist;
    X.nonexist = {};
    Y.nonexist = {};
    assert(Y.nonexist ~= X.nonexist);
    assert(Z.nonexist == X.nonexist);
    assert(Z:__super__().nonexist == X.nonexist);
    assert(z:__super__().nonexist == X.nonexist);
    assert(z:__super__(X).nonexist == X.nonexist);
    assert(z:__super__(Y).nonexist == Y.nonexist);

    local _invoke_super_cache = Y.__init__;
    function X:__init__(...) end
    assert(Y.__init__ == X.__init__);
    assert(Z.__init__ == X.__init__);
    assert(Z:__super__().__init__ == X.__init__);
    assert(z:__super__().__init__ == X.__init__);
end

do
    collectgarbage();
    local _check_class_gc = rawget(Object, '__deriveds__');
    local _last_subclass_of_object = _check_class_gc[#_check_class_gc];
    assert(_last_subclass_of_object == Table);
end

-- IO

bf_io = class{
    __init__ = function (self)
        self.state = 1;
    end,
    STATE = {
        {
            read = function (self, len)
                return io.read(len);
            end,
            write = function (self, ch)
                if ch == 0x80 then
                    self.STATE = 1;
                    return;
                end
                io.write(toChar(ch, true));
            end,
        },
        {
        },
    },
    getState = function (self, state)
        return self.STATE[self.state];
    end,
    read = function (self, len)
        return self:getState().read(self, len);
    end,
    write = function (self, ch)
        self:getState().write(self, ch);
    end,
}();

--[=[Call
    0x80 reg ''
    0x80 reg '[' 'obj' 0x0 ['field' 0x0]... 0x80
    0x80 reg '(' 0x0 ['arg' 0x0]... 0x80

    bbs.rect(4, 2, 'title')
    nil, boolean, number, string, thread, and table
    reg[i] = (nil) nil => 0x80 i 0x80
    reg[i] = (boolean) v => 0x80 i 'b' v 0x80
    reg[i] = (number) v => 0x80 i 'n' v 0x80
    reg[i] = (string) str => 0x80 i 's' str 0x80
    reg[i]
    0x80 0 'n' 4 0x80
    0x80 1 'n' 2 0x80
    0x80 2 ''
    0x80 2 '[' 'bbs' 0x0 'rect' 0x0 0x80
    0x80
]=]

local function is_printable(ch)
    if type(ch) == 'string' then ch = string.byte(ch); end
    return (ch >= 0x80 and ch < 0x100)
             or ((ch > 0) and string.char(ch)
                    :match('[%p%w ' .. (inline and '' or '\n\t') .. ']'));
end
function toChar(ch, escape)
    local inline = type(escape) == 'table' and escape.inline;
    if escape and not is_printable(ch) then
        return ([[\x%02X]]):format(ch);
    else
        local res = string.char(ch);
        if inline then return ({['\n']=[[\n]], ['\t']=[[\t]]})[res] or res; end
        return res;
    end
end

function getLine() return io.read('*l'); end
function getInput(len) return bf_io:read(len); end
function doOutput(ch) bf_io:write(ch); end

-- Program Interpreter

class 'Bf' {
    __required__ = {
        prog_str = {_prog = toTypeEnum{'string'}};
    },
    __optional__ = {
        input = {_input = toTypeEnum{'', 'string'}};
        loop_limit = toTypeEnum{1e5, 'number'},
        eof_value = toEnum{nil, 0, -1},
        end_of_prog = toEnum{nil, '!'},

        show_progress = toTypeEnum{false, 'boolean'};
        step = toTypeEnum{false, 'boolean'};
        show_char = toTypeEnum{false, 'boolean'};
    },
    __init__ = function (self, prog_str, kwargs)
        if type(prog_str) == 'table' then
            prog_str, kwargs = self._prog, prog_str;
        end
        if prog_str and self.end_of_prog then
            local prog_end = self.end_of_prog
                    and prog_str:find(self.end_of_prog);
            self._prog = prog_str:sub(0, (prog_end or 0) - 1);
            self._input = prog_end and prog_str:sub(prog_end+1);
        else
            self._prog = prog_str;
        end
        self._input_pos = 0;
        self._cur = 1;
        self._line_n = 1;
        self._line_p = 1;
        self._data = Object();
        self._pd = 1;
        self._cur_hist = Table();
        self._loop_cache = {};
        self._line_pos = {};

        self.show_progress = self.show_progress or self.step;
    end,

    eval = function (self)
        local succ, err = pcall(self._eval, self);
        if not succ then print(err); end
        return self;
    end,
    dumpProg = function (self, detail)
        return self:_dumpProg(self._cur, self._line_n, detail);
    end,
    dumpData = function (self, detail)
        detail = detail or self.show_char;
        local data = self:getData();
        return '<'.. self._pd .. ': ' .. data .. '>'
            .. (detail and ' "'..toChar(data, {inline=true})..'"' or '') .. ': '
            .. self._data:inspect{sep=' ', show_type=false,
                fmt = function (k, v, v_only)
                    return ((k == self._pd) and '<%s>' or '[%s]')
                        :format(v_only and '%s%s' or '%s %s%s')
                        :format(select(v_only and 2 or 1,
                            k, v, detail
                                and ' "'..toChar(v, {inline=true})..'"' or ''));
                end};
    end,
    dumpState = function (self, detail)
        return self:inspect{sep=',\n',
                ignore = detail and Set{}
                    or Set{'_prog', '_data', '_loop_cache', '_line_pos'}};
    end,
    peekCur = function (self, throw)
        return unpack(self:_refTopCur(throw));
    end,
    getOp = function (self, cur)
        local cur, end_ = cur or self._cur, nil;
        local op = self._prog:sub(cur, cur);
        for i = cur+1, #self._prog, 1 do
            if self._prog:sub(i, i) ~= op then
                end_ = i-1;
                break;
            end
        end
        return self._prog:sub(cur, end_);
    end,
    getData = function (self, pd)
        pd = pd or self._pd;
        return self._data[pd] or 0;
    end,

    _eval = function (self)
        local op_list = self._OP;
        while self._cur <= #self._prog do
            local op = self:getOp();
            local func = op_list[op:sub(1, 1)];
            if func then
                if self.show_progress then print(self:dumpProg()); end
                func(self, #op);
                if self.show_progress then print(self:dumpData()); end
                if self.step then getLine(); end
            end
            self._cur = self._cur + #op;
        end
        self:_assertCurHistNull();
    end,
    _assertCurHist = function (self)
        if #self._cur_hist == 0 then self:_error"Unexpected ']'"; end
    end,
    _assertCurHistNull = function (self)
        if #self._cur_hist ~= 0 then
            self:_error("Unbalanced '['", self:peekCur());
        end
    end,
    _pushCur = function (self, cur, line_n, loop_c)
        self._cur_hist:insert{
            cur or self._cur, line_n or self._line_n, loop_c or 1,};
    end,
    _refTopCur = function (self, throw)
        if throw then self:_assertCurHist(); end
        return self._cur_hist[#self._cur_hist];
    end,
    _popCur = function (self)
        self:_assertCurHist();
        return unpack(self._cur_hist:remove());
    end,
    _getInputFromSelf = function (self, rep)
        local input_pos = self._input_pos;
        local input_end = self._input and #self._input or 0;
        input_pos = input_pos + rep;
        if input_pos <= input_end then
            self._input_pos = input_pos;
            return self._input:sub(input_pos, input_pos):byte();
        end
        self._input_pos = input_end;
        return self.eof_value, input_pos - input_end;
    end,
    _getInputFromGlobal = function (self, rep)
        local input = getInput(rep);
        return input and input:sub(-1):byte() or self.eof_value;
    end,
    _getInput = function (self, rep)
        local res, len = self:_getInputFromSelf(rep);
        if res then return res; end
        self._getInput = self._getInputFromGlobal;
        return self:_getInput(len);
    end,
    _error = function (self, msg, cur, line_n)
        error(msg .. ' at '
              .. self:_dumpProg(cur or self._cur, line_n or self._line_n), 2);
    end,
    _getProgLine = function (self, line_pos_k, detail)
        local end_ = self._prog:find('\n', line_pos_k);
        local prog = self._prog:sub(0, (end_ or 0) - 1);
        return detail and prog or prog:sub(line_pos_k),
              prog:sub(line_pos_k),
              (detail and end_) and self._prog:sub(end_) or '';
    end,
    _dumpProg = function (self, cur, line_n, detail)
        cur = cur or self._cur;
        line_n = line_n or self._line_n;
        local line_pos_k = (line_n == self._line_n)
                and self._line_p or self._line_pos[line_n];
        local prog_line, prog_cur, prog_after =
              self:_getProgLine(line_pos_k, detail);
        local op = self:getOp(cur);
        return ('%d(%d:%d)'):format(cur, line_n, 1 + cur - line_pos_k)
                .. ': ' .. (#op==1 and '' or #op..' * ')
                .. inspectStr(op:sub(0, 1), {inline=true}) .. "\n"
                .. prog_line .. '\n'
                .. prog_cur:gsub('%S', ' '):sub(1, cur - line_pos_k)
                .. '^' .. ('~'):rep(#op-1)
                .. prog_after;
    end,
    _OP = {
        ['>'] = function (self, rep)
            self._pd = self._pd + rep;
        end,
        ['<'] = function (self, rep)
            self._pd = self._pd - rep;
        end,
        ['+'] = function (self, rep)
            self._data[self._pd] = self:getData() + rep;
        end,
        ['-'] = function (self, rep)
            self._data[self._pd] = self:getData() - rep;
        end,
        ['.'] = function (self, rep)
            local data = self._data[self._pd] or 0;
            self._data[self._pd] = data or 0;
            for i = 1, rep, 1 do doOutput(data); end
        end,
        [','] = function (self, rep)
            local input = self:_getInput(rep);
            if input then self._data[self._pd] = input; end
        end,
        ['['] = function (self, rep)
            local cur_n = self._cur;
            if self:getData() == 0 then
                local cache = self._loop_cache[cur_n];
                local cur, n = unpack(cache or {});
                if cur == nil then
                    local _, pos_n;
                    _, cur = self._prog:find('%b[]', cur_n);
                    if cur == nil then
                        self:_error("Unbalanced '['", cur_n);
                    end
                    n, pos = self._line_n, cur_n + 1;
                    while true do
                        pos_n = self._prog:find('\n', pos);
                        if pos_n ~= nil and pos_n < cur then
                            n = n + 1;
                            pos = pos_n + 1;
                        else break; end
                    end
                    self._loop_cache[cur_n] = {cur, n};
                    self._loop_cache[cur] = {cur_n, self._line_n};
                end
                cur_n, self._line_n = cur, n;
                cur_n = cur_n + 1;
            else
                self._line_pos[self._line_n] = self._line_p;
                for i = 1, rep, 1 do
                    self:_pushCur(cur_n);
                    cur_n = cur_n + 1;
                end
            end
            self._cur = cur_n - rep;
        end,
        [']'] = function (self, rep)
            local cur_n = self._cur;
            if self:getData() ~= 0 then
                local cur, line_n, loop_c = self:peekCur(true);
                self._loop_cache[cur_n] = {cur, line_n};
                self._loop_cache[cur] = {cur_n, self._line_n};
                if (loop_c > self.loop_limit) then
                    self:_error('Loop limit '
                        .. '(' .. self.loop_limit .. ') exceeded',
                    cur_n);
                end
                cur_n = cur;
                self._line_n = line_n;
                self:_refTopCur()[3] = loop_c+1;
                cur_n = cur_n + 1;
            elseif #self._cur_hist == rep then
                self._cur_hist = Table{};
                self._loop_cache = {};
                self._line_pos = {};
                cur_n = cur_n + rep;
            else
                for i = 1, rep, 1 do
                    local cur, line_n, _ = self:_popCur();
                    self._loop_cache[cur_n] = {cur, line_n};
                    self._loop_cache[cur] = {cur_n, self._line_n};
                    cur_n = cur_n + 1;
                end
            end
            self._cur = cur_n - rep;
        end,
        ['#'] = function (self, rep) print(self:dumpState(rep>1)); end,
        ['\n'] = function (self, rep)
            self._line_n = self._line_n + rep;
            self._line_p = self._cur + rep;
        end,
    },
};

program = Bf{prog_str=io.read('*a') or [=[
    ++++ [->+++<]>+
    [->++++<]> .--.
]=], loop_limit=1e5, end_of_prog='!'};

program:eval();
