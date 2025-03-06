open_project basic_arith_proj
set_top basic_arith
add_files basic_arith.cpp
add_files basic_arith.h
add_files -tb result_basic_arith_ref.dat
add_files -tb basic_arith_test.cpp

open_solution "solution1"
set_part {xcvu9p-flga2104-1-i}
create_clock -period 25 -name default

#source "./fir_proj/solution1/directives.tcl"

csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog
#
#Exit Vivada HLS
exit
