#!/usr/bin/env bash

. $(dirname "$0")/run.sh

print_header "RUN scan-build"
cd DoIt/build
check_log "scan-build --show-description --status-bugs -stats -o . make -j4" "Error"
cd ../..

print_header "RUN infer"
cd DoIt/build
check_log "infer run -- clang -c ../main.cpp -I ../database/" "Error"
cd ../..

print_header "SUCCESS"