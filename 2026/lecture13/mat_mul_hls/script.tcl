open_project mat_mul.cpp

set_top mat_mul

add_files src/mat_mul.cpp
add_files src/mat_mul.h
add_files -tb src/mat_mul_tb.cpp

open_solution "solution1"

set_part xcvu13p-fsga2577-2-e
create_clock -period 25

# Optional: add directives here (or keep in code)
# set_directive_pipeline "rgb2gray"
# set_directive_unroll "filter3x3/loop1"

csim_design
csynth_design
#cosim_design

#export_design -format ip_catalog

exit
