#!/bin/bash

[ ! -d /var/lib/mystat ] && mkdir /var/lib/mystat
gnuplot /home/antoni/Documents/Lato_2020-2021/Linux/Lista_8/plotter.plt > /var/lib/mystat/cpu.png
