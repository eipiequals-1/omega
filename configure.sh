#!/usr/bin/bash

echo "Configuring Project"

cmake -S . -B build/ -DBOX2D_BUILD_TESTBED=OFF -DBOX2D_BUILD_UNIT_TESTS=OFF -DBUILD_SHARED_LIBS=ON
