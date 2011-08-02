#!/bin/bash
list="MainServer MainClient SnakeServer GameFileServer1"
basepath=`pwd`
rm -f MainClient-build-desktop/Multi_Snake1
for name in $list
do
gnome-terminal -e ./$name --working-directory=$basepath/${name}-build-desktop
done
