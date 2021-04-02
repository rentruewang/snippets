#! env fish

argparse 'b/build' 'c/clean' 'f/files=+' -- $argv

set binary main.exe
set compiler clang++
set compflags -std=c++2a #-stdlib=libc++ -fimplicit-modules -fimplicit-module-maps
set objflags -Xclang -emit-module-interface
set linkerflags -fprebuilt-module-path=.

if set -q _flag_clean
    rm -f $binary
end

if set -q _flag_build
    for file in $_flag_files
        $compiler $compflags $objflags -c "$file".cpp -o "$file".pcm
    end
end

$compiler $compflags $linkerflags (fd -e cpp) -o $binary
