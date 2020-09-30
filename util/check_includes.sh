#!/bin/sh

INCLUDE_BINARY="check_includes"

find include -name include -exec "${INCLUDE_BINARY}" '{}' \; || exit
