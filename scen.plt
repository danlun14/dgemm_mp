set terminal png size 1000, 450 font 'Verdana, 10'
set output 'dgemm_MPI.png' 
set title "dgemm_MPI"
set xlabel 'Number of processes'
set ylabel 'Speedup(relative to 8)'

set key left top

set grid lc rgb  '#555555' lw 1 lt 4
set grid lc rgb '#555555' lw 1 lt 4

set xtics 8
set ytics 1

set xrange [16:64]
set yrange [1:8]

plot 'mpi2500.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'dgemm MPI n = 2500', \
 'linearRel8.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Linear speedup'

set output 'dgemm.png' 
set title "dgemm"
set xlabel 'Number of threads'
set ylabel 'Speedup'

set key left top

set grid lc rgb  '#555555' lw 1 lt 4
set grid lc rgb '#555555' lw 1 lt 4

set xtics 1
set ytics 1

set xrange [2:6]
set yrange [1:8]

plot 'pom1000_2500_5000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'dgemm n=1000 openmp', \
'pom1000_2500_5000.txt' using 1:3 with linespoints lw 1 lt rgb 'blue' title 'dgemm n=2500 openmp', \
'pom1000_2500_5000.txt' using 1:4 with linespoints lw 1 lt rgb 'green' title 'dgemm n=5000 openmp', \
'pt1000_2500_5000.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'dgemm n=1000 pthreads', \
'pt1000_2500_5000.txt' using 1:3 with linespoints lw 1 lt rgb '#03034521' title 'dgemm n=2500 pthreads', \
'pt1000_2500_5000.txt' using 1:4 with linespoints lw 1 lt rgb 'yellow' title 'dgemm n=5000 pthreads', \
 'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Linear speedup'