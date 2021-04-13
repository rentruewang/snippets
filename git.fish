#! /usr/bin/env fish

# Functions

function add
    git add $argv
end

# Clean the directory
function clean
    git clean -f -d -X $argv
end

# Commit message
function commit
    git commit -m $shortmsg -m $longmsg $argv
end

# Pull code from GitHub
function pull
    git pull $argv
end

# Push code to GitHub
function push
    git push $argv
end

# Bot messages
set bot "🤖 R3nTru3W4n9"
set today (date --iso-8601=date)
set shortmsg "$bot commits on $today"
set longmsg "Beep Boop, I'm a bot. I haven't really written all this code by myself. The short commit message is a little bit confusing. @r3ntru3w4n9 is the one who writes the code, and runs me periodically or when he/she/it sees fits.
If you feel rather strongly for @r3ntru3w4n9 writing a more professional message or clairfy things or you just want to fix things, please reach out to him/her/it or comment on the part where you don't like. He/She/It is going to get a notification everytime you do so. And hopefully he/she/it listens to your suggestions! Beep Boop, message over!
I am a bot, and this action is performed automatically. The source code can be found at https://github.com/r3ntru3w4n9/tmp/git.fish
"

# Define the arguments to parse.
# Allow only the long arguments for clarity
set -l add_opts (fish_opt -s a -l add --long-only)
set -l clean_opts (fish_opt -s x -l clean --long-only)
set -l commit_opts (fish_opt -s c -l commit --long-only)
set -l pull_opts (fish_opt -s d -l pull --long-only)
set -l push_opts (fish_opt -s u -l push --long-only)

# Main function starts here
argparse $add_opts $clean_opts $commit_opts $pull_opts $push_opts -- $argv

# Ifs
if set -q _flag_clean
    echo "Cleaning ingored files"
    clean
end

if set -q _flag_pull
    echo "Pulling files from remote server"
    pull origin master
end

if set -q _flag_add
    echo "Adding files to git"
    add . -A
end

if set -q _flag_commit
    echo "Committing files"
    commit
end

if set -q _flag_push
    echo "Pusing to remote server"
    push
end
