set title "Change Required vs Time"
set xrange[0.1:5000]
set yrange[0.000001:0.015415]
set logscale y
set logscale x
set logscale xy
set xlabel "Change"
set ylabel "Execution Time"
set term post eps
#set term png
set output "./graph2-log.eps"

plot "./hw3.txt" using 1:2 title 'changegreedy' with line lt rgb "blue", "./hw3.txt" using 1:3 title 'changedp' with lines lt rgb "red"
pause -1
