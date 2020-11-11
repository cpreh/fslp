#!/usr/bin/env bash

set -e -u

update_cmake \
	"CMakeLists.txt" \
	FSLP_FILES \
	include
