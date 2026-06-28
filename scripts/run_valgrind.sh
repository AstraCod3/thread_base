#!/bin/bash

# Include the common environment file for paths
. "$(dirname "$0")/env.sh" "$0"

echo ""
echo "Start Running with Valgrind"
echo ""

log_postfix="$(date +"%Y%m%d_%H%M%S").log"

check_memory_leask() {
    tbt_bin_file_testbasethread="$1"
    log_file="$tbt_log_path/$tbt_bin_file_testbasethread".memory_leak."$log_postfix"
    # cms_valg_memleak="valgrind --error-limit=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$log_file ./$tbt_bin_file_testbasethread"
    cms_valg_memleak="valgrind --error-limit=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$tbt_bin_file_testbasethread > $log_file 2>&1"
    echo "Valgrind Test Memory Leak"
    echo " > $cms_valg_memleak"
    eval "$cms_valg_memleak"
    #eval "$cms_valg_memleak" > $log_file 2>&1
    echo ""
}

check_race_condition_drd() {
    tbt_bin_file_testbasethread="$1"
    log_file="$tbt_log_path/$tbt_bin_file_testbasethread.drd.$log_postfix"
    # cmd_valg_drd="valgrind --error-limit=no --tool=drd -s --log-file="$log_file" ./"$tbt_bin_file_testbasethread""
    cmd_valg_drd="valgrind --error-limit=no --tool=drd -s ./$tbt_bin_file_testbasethread > $log_file 2>&1"
    echo "Valgrind Test drd run"
    echo " > $cmd_valg_drd"
    echo ""
    eval $cmd_valg_drd
}

check_race_condition_helgrind() { 
    tbt_bin_file_testbasethread="$1"
    log_file="$tbt_log_path/$tbt_bin_file_testbasethread".helgrind."$log_postfix"
    echo ""
    # cmd_valg_helgrind="valgrind --error-limit=no --tool=helgrind --history-level=approx --log-file="$log_file" -s ./"$tbt_bin_file_testbasethread""
    cmd_valg_helgrind="valgrind --error-limit=no --tool=helgrind --history-level=approx -s ./$tbt_bin_file_testbasethread > $log_file 2>&1"
    echo "Valgrind Test helgrind"
    echo " > $cmd_valg_helgrind"
    eval "$cmd_valg_helgrind"
}

if [ ! -d "$tbt_bin_path" ]; then
    echo " ERROR! : folder "$tbt_bin_path" is no exist run \"./test_build.sh\" before"
    echo ""
    exit
fi


if [ ! -d "$tbt_log_path" ]; then
    mkdir -v "$tbt_log_path"
fi
echo ""


cd "$tbt_bin_path"
for filename in $(ls -1); do
    check_memory_leask "$filename"
    check_race_condition_drd "$filename"
    check_race_condition_helgrind "$filename"
done

cd ..
echo " "
echo "... done!"
echo " "
