set title "Change Required vs Number of Coins"
set xrange[1990:2310]
set yrange[35:65]
#set logscale y
#set logscale x
#set logscale xy
set xlabel "Change"
set ylabel "Number of Coins"
set term post eps
#set term png
set output "./graph2.eps"

plot "./plotting2.txt" using 1:2 title 'changegreedy' with line lt rgb "blue", "./plotting2.txt" using 1:3 title 'changedp' with lines lt rgb "red"
pause -1
