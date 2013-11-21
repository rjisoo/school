set title "Best Linear Regression"
set xrange[0:12]
set yrange[0:20]
#set logscale y
#set logscale x
#set logscale xy
set xlabel "X"
set ylabel "Y"
set grid
set term post eps
set term png
set output "./graph2.eps"

f(x) = m*x + b

fit f(x) "./data.txt" using 1:2 via m,b

plot f(x), "./data.txt" using 1:2
pause -1
