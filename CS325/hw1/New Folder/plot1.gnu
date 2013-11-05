set title "Enumeration Times vs. Array Size"
set xrange[100:10000]
set yrange[0.0001:10]
set logscale y
set logscale x
set logscale xy
set xlabel "Array Size"
set ylabel "Runtime (seconds)"
set term post eps
#set term png
set output "./graph.eps"
plot "./plotting.txt" using 1:2 title 'Enum1' with lines lt rgb "blue", "./plotting.txt" u 1:3 t 'Enum2' w lines lt rgb "red"
pause -1
