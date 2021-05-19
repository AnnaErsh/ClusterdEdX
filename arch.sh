#!/bin/sh
name=DANSS
rm -f $name.tgz
echo "Creating archive..."
tar -czf $name.tgz src include *.cc *.conf *.sh CMakeLists.txt
