./vpr k6_frac_N10_mem32K_40nm.xml diffeq1.blif --route_chan_width 56 --nodisp 
grep "Final critical path" vpr_stdout.log >> B3result.txt
./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --route_chan_width 54 --nodisp 
grep "Final critical path" vpr_stdout.log >> B3result.txt
./vpr k6_frac_N10_mem32K_40nm.xml raygentop.blif --route_chan_width 72 --nodisp 
grep "Final critical path" vpr_stdout.log >> B3result.txt
./vpr k6_frac_N10_mem32K_40nm.xml or1200.blif --route_chan_width 78 --nodisp 
grep "Final critical path" vpr_stdout.log >> B3result.txt