#!/bin/sh
echo " "
echo "Start Clean ..."

. "$(dirname "$0")/env.sh" "$0"

export tbt_build_path="$tbt_script_path/../build"
export tbt_bin_path="$tbt_script_path/../bin"
export tbt_deps_path="$tbt_script_path/../deps"
export tbt_log_path="$tbt_script_path/../log"

if [ -d "$tbt_build_path" ]; then
    echo "remove directory: $tbt_build_path"
    rm -rf "$tbt_build_path"
fi

if [ -d "$tbt_bin_path" ]; then
    echo "remove directory: $tbt_bin_path"
    rm -rf "$tbt_bin_path"
fi

if [ -d "$tbt_deps_path" ]; then
    echo "remove directory: $tbt_deps_path"
    rm -rf "$tbt_deps_path"
fi

if [ -d "$tbt_log_path" ]; then
    echo "remove directory: $tbt_log_path"
    rm -rf "$tbt_log_path"
fi

echo " "
echo "... done!"
echo " "
