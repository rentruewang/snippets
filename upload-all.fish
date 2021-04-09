set bot "🤖 R3nTru3W4n9"
set today (date --iso-8601=date)

set shortmsg "$bot commits on $today"
set longmsg "$bot: Beep Boop, I'm a bot. I haven't really written all this code by myself. The short commit message is a little bit confusing. @r3ntru3w4n9 is the one who writes the code, and runs me periodically or when he/she/it sees fits. If you feels rather strongly for @r3ntru3w4n9 writing a more professional message or clairfy things or you just want to fix things, please reach out to him or comment on the part where you don't like. He/She/It is going to get a notification everytime you do so. And hopefully he/she/it listens to your suggestion! Beep Boop, message over!"

argparse 'c/clean' 'p/pull' 'C/commit-only' -- $argv

if set -q _flag_clean
    printf "Code cleaning enabled\n"
end

if set -q _flag_pull
    printf "Pulling file enabled\n"
end

if set -q _flag_commit_only
    printf "Commit only\n"
end

function upload
    pwd
    if not git -C . rev-parse 2> /dev/null
        printf "Not a git repo\n"
        return
    end

    if set -q _flag_commit_only
        git commit -m $shortmsg -m $longmsg
        git push
        return
    end
    
    if set -q _flag_clean
        git clean -f -d -X
    end
    if set -q _flag_pull
        git pull
    end
    git add .
    git commit -m $shortmsg
    git push
    echo \n
end

upload 2> /dev/null
