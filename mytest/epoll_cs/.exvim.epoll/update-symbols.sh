#!/bin/bash
export DEST="./.exvim.epoll"
export TOOLS="/home/brooklv/test/ExvimFull/vimfiles/tools/"
export TMP="${DEST}/_symbols"
export TARGET="${DEST}/symbols"
sh ${TOOLS}/shell/bash/update-symbols.sh
