from helper import *

Add("1,2,3", Word("1,2"))
Add("1,2,3,4", Word("1,2", ["1,2,3"]))
Add("1,2,3,4,5", Word("mmm", ["1,2,3,4"]))
print(All())
