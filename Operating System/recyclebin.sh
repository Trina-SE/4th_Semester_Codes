#!/bin/bash

if [ $# -lt 1 ]; then
    echo "This is not the input format. The format is: $0 <command> [filename]"
    exit 1
fi

RECYCLE_BIN_DIR="./recycle_bin"

mkdir -p "$RECYCLE_BIN_DIR"

command="$1"
shift
filenames=("$@")

case "$command" in
    remv|remove)
        if [ ${#filenames[@]} -eq 0 ]; then
            echo "This is not the input format. The format is: $0 $command <filename>"
        else
            for f in "${filenames[@]}"; do
                mv "$f" "$RECYCLE_BIN_DIR"
                echo "Moved '$f' to the recycle bin."
            done
        fi
        ;;
    restore)
        if [ ${#filenames[@]} -eq 0 ]; then
            echo "This is not the input format. The format is: $0 restore <filename>"
        else
            for f in "${filenames[@]}"; do
                mv "$RECYCLE_BIN_DIR/$f" .
                echo "Restored '$f' from the recycle bin."
            done
        fi
        ;;
    remvp)
        if [ ${#filenames[@]} -eq 0 ]; then
            echo "This is not the input format. The format is: $0 remvp <filename>"
        else
            for f in "${filenames[@]}"; do
                rm "$RECYCLE_BIN_DIR/$f"
                echo "Permanently removed '$f' from the recycle bin."
            done
        fi
        ;;
    schedule)
        if [ ${#filenames[@]} -lt 2 ]; then
            echo "This is not the input format. The format is: $0 schedule <filename> <time_in_minutes>"
        else
            filename="${filenames[0]}"
            time_in_seconds="${filenames[1]}"
            ( sleep "$((time_in_seconds))" && ./recyclebin.sh remv "$filename" ) &
            echo "Scheduled removal: '$filename' will be moved to the recycle bin in $time_in_seconds seconds."
        fi
        ;;
    *)
        echo "Command NOT Found !: $command"
        ;;
esac

