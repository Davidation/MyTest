#!/bin/bash
export DEST="./.exvim.epoll"
export TOOLS="/home/brooklv/test/ExvimFull/vimfiles/tools/"
export TMP="${DEST}/_inherits"
export TARGET="${DEST}/inherits"
sh ${TOOLS}/shell/bash/update-inherits.sh
