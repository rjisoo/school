set title "Enumeration Times vs. Array Size"
set xrange[100:10000]
set yrange[0.00001:0.05]
#set logscale y
#set logscale x
#set logscale xy
set xlabel "Array Size"
set ylabel "Runtime (seconds)"
set term post eps
#set term png
set output "./graph2.eps"
plot "./plotting.txt" using 1:2 title 'Alg1' with lines lt rgb "blue", "./plotting.txt" using 1:3 title 'Alg2' with lines lt rgb "red", "./plotting.txt" u 1:4 t 'Alg3' w lines lt rgb "green", "./plotting.txt" u 1:5 t 'Alg4' w lines lt rgb "black"
pause -1
