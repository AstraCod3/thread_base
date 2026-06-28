#!/bin/sh

export tbt_script_path=$(cd "$(dirname "$0")" && pwd)
export tbt_build_path="$tbt_script_path/../build"
export tbt_bin_path="$tbt_script_path/../bin"
export tbt_deps_path="$tbt_script_path/../deps"
export tbt_log_path="$tbt_script_path/../log"

export tbt_bin_file_testbasethread="$tbt_build_path/test_basethread"

cd "$tbt_script_path/.." 
