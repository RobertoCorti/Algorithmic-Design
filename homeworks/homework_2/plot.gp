set terminal png size 1280,800 font 'Helvetica,16'
set output "plot_benchmark.png"
set title "benchmark"
set xlabel "N"
set ylabel "time"

pl "insertion_time.txt" using 1:2 w l t "time" 


