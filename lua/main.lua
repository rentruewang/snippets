#! /usr/bin/env luajit

local function fact(n)
    if n == 0 then
        return 1
    else
        return n * fact(n - 1)
    end
end

local function doSth() for i = 1, 1000 do if 1 == 0 then break end end end

doSth()
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

-- string or table contructor can omit the parenthesis
print "hello"
print(type {})

array = {1, 2, 3, 4, 5}
local sum = 0
for _, val in ipairs(array) do sum = sum + val end
print(sum)

local function multipleResult() return 1, 2, 3, 4 end

-- tuples cannot be enclosed in parenthesis
-- local function multipleResult2()
--     return (1,2,3,4)    
-- end

local x = multipleResult()
print(x)

local a, b, c, d, e = multipleResult()
print(a, b, c, d, e)

print(multipleResult())

local function foo0() end
local function foo1() return 'a' end
local function foo2() return 'a', 'b' end

print({foo0()})
print({foo1()})
print({foo2()})

print({foo0(), foo1()})
print({foo0(), foo1(), foo2()})
local tab = {foo2()}
print(tab[1])

local function letsSee()
    local var = 0
    local function mod() var = 1 end

    print("var=", var)
    mod()
    print("var=", var)

    var = {0}
    local function change() var = {1} end
    print("var=", var[1])
    change()
    print("var=", var[1])
    -- Will have no effect because lua pass references by value
    local function changeRef(v) v = {2} end
    changeRef(var)
    print("var=", var[1])

end

letsSee()
