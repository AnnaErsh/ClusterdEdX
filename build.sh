#!/bin/bash
cur=$(pwd)
cd ../build
cmake $cur
make
