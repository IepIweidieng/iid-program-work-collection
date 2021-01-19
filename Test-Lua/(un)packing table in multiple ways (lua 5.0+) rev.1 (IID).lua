-- For Lua 5.0+

function print_r(arr, dep, indLv)
	local str, dep, indLv, indStr = "("..type(arr)..")", dep or -1, indLv or 0, "#";

	if type(arr) ~= "table" or dep == 0 then return str.." "..tostring(arr); end

	for i=1, indLv do indStr = "  "..indStr; end
	str = str..":";
	for i, v in pairs(arr) do str = str.."\n"..indStr..i..": "..print_r(v, (dep - 1), (indLv + 1)); end
	return str;
end


imp={};

function imp.getn(tbl)
	return type(tbl) == "table" and
		(function() local n=0; for i, v in pairs(tbl) do n = math.max(tonumber(i) or 0, n); end return n; end)() or
		0;
end

do
	local function _body_r(intlAT, intlExp, getnA, aT)
		return "return function(var, ...)\
			local function _intl(res, i, "..intlAT..")\
				res[i] = "..intlExp..";\
				if imp.getn"..getnA.." == 0 then\
					res.n = i;\
					return res;\
				end\
				return _intl(res, i+1, "..aT..");\
			end\
\
			if imp.getn"..getnA.." == 0 then return var == nil and {n=0} or {var; n=1}; end\
			return _intl({var; n=2}, 2, "..aT..");\
		end;";
	end

	local _ldStr = loadstring or load;
	imp.pack = _ldStr("return {n = imp.getn{...}; ...};") or (function(...) return arg; end);
	imp.pack_c = table.pack or imp.pack;
	imp.pack_r = (_ldStr(_body_r("var, ...", "var", "{...}", "...")) or
		_ldStr(_body_r("arg", "table.remove(arg, 1)", "(arg)", "arg")))();
end

imp.unpack_c = table.unpack or function(tbl)
	tbl.n = imp.getn(tbl);
	return unpack(tbl);
end

function imp.unpack_r(tbl)
	local n = imp.getn(tbl);
	local function _intl(i, tbl)
		if i==n then return tbl[i]; end
		return tbl[i], _intl(i+1, tbl);
	end

	if n==0 then return; end
	if n==1 then return tbl[1]; end
	return tbl[1], _intl(2, tbl);
end


sable = {"A", "", {math.exp(1)}, nil, false, true, 42};

do
	local function _fPr(tbl, un)
		for i, k in pairs(tbl) do
			print((un and "un" or "").."pack"..k..": "..print_r(imp["pack"..(un and "_c" or k)](imp["unpack"..(un and k or "_c")](sable))).."\n");
		end
	end;
	_fPr{"", "_c", "_r"};
	_fPr({"_c", "_r"}, true);
end