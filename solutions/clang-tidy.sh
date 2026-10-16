#!/bin/bash

# check problem number
if [ -z "$1" ]; then
    echo "Use example: ./clang-tidy.sh 02.01"
    exit 1
fi

TARGET_FILE="$1/main.cpp"

if [ ! -f "$TARGET_FILE" ]; then
    echo "$TARGET_FILE not found"
    exit 1
fi

FIX_FLAG=""
if [ "$2" == "--fix" ] || [ "$2" == "-f" ]; then
    echo "Fix mode enabled."
    FIX_FLAG="--fix"
fi

echo "call clang-tidy $TARGET_FILE..."

clang-tidy "$TARGET_FILE" \
  -checks="-*,bugprone-*,modernize-*,performance-*" \
  --header-filter="^$(pwd)/" \
  $FIX_FLAG \
  -- \
  -std=c++23 \
  -stdlib=libc++ \
  -Wall \
  -Wextra \
  -Wno-unknown-warning-option
