#! /usr/bin/env luajit

local function fact(n)
    if n == 0 then
        return 1
    else
        return n * fact(n - 1)
    end
end

print(fact(5))

local function do_something() for i in 1, 1000 do if 1 == 0 then break end end end

-- Testing user input
-- print("please enter a number")

-- local read_type = "*number"

-- I don't know why reading number looks like this.
-- local num = io.read(read_type)
-- print(fact(num))
-- print(c)

local x = "string"
print(x)
x = 3
print(x)

local str = [[
	what is this thing?
	this syntax looks cool.
]]

print(str)

print(tonumber("aviwpec"))
print(tonumber("321"))
print(3)

local arr = {}
print(arr[0], arr[1], arr[2])

local function modify(arr)
    arr[0] = 1
    arr[2] = 3
end

modify(arr)

print(arr)
print(arr[0], arr[1], arr[2])

repeat
    local val = 3
    print(val)
until val ~= nil
print(val)

for i = 1, 10 do print(i) end
