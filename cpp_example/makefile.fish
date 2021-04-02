#! env fish

set binary main

argparse 'c/clean' -- $argv

# It performs cleaning regardless of what is called
rm -f $binary

if set -q _flag_clean
	exit 0
end

g++ *.cpp -o $binary
