reset
set title "Average CPU usage by mystat daemon"
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S"
set format x "%d-%m %H:%M"
# set xrange [time(0)-1*60*60:time(0)]
set term png
set bmargin at screen 0.27
set xtics rotate by 90 offset 0,-4.5
plot '/var/log/mystat.log' using 1:5 with lines t "Avg CPU usage"
