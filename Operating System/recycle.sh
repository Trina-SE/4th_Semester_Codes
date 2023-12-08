#! /bin/bash

RECYCLE_BIN_DIR="$HOME/recycle_bin"
current_path=$(pwd)
script_path=$(readlink -f "$0")
LOG="$RECYCLE_BIN_DIR/trash.log"

mkdir -p "$RECYCLE_BIN_DIR"

if [ ! -e "$LOG" ]; then
    touch "$LOG"
fi

remove() {
	for i in "${@:2}"; do
		file_path=$(readlink -f "$i")
		if [ "$file_path" != "$script_path" ]; then
			current_time=$(date +"%Y-%m-%d_%H-%M-%S")
			new_name="${i}_${current_time}"
			mv $i "${RECYCLE_BIN_DIR}/${new_name}"
			echo mv $i "${RECYCLE_BIN_DIR}${new_name}"
			echo "$file_path:${new_name}" >> "$LOG"
		fi
	done
	
}

restore() {
	for i in $RECYCLE_BIN_DIR/*; do
		if [ "$i" != "$LOG" ]; then
			file_name=$(basename "$i")
			file_record=$(grep "$file_name" "$LOG")
			file_real_path=$(echo $file_record | cut -d ":" -f 1)
			mv $i "$file_real_path"
			echo > $LOG
		fi
	done
}
remove_perm() {
	rm -r "$RECYCLE_BIN_DIR"/*
}
