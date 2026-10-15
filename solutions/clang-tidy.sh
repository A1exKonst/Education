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

echo "call $TARGET_FILE clang-tidy..."

clang-tidy "$TARGET_FILE" \
  -checks="-*,bugprone-*,modernize-*,performance-*" \
  --header-filter="^$(pwd)/" \
  -- \
  -std=c++23 \
  -stdlib=libc++ \
  -Wall \
  -Wextra \
  -Wno-unknown-warning-option
