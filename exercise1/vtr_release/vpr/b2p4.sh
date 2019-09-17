for present in 2 5 8 15
do
	echo "diffeq1.blif bb_factor $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml diffeq1.blif --route_chan_width 56 --bb_factor $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 2 5 8 15
do
	echo "sha.blif bb_factor $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --route_chan_width 54 --bb_factor $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 2 5 8 15
do
	echo "raygentop.blif bb_factor $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml raygentop.blif --route_chan_width 72 --bb_factor $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 2 5 8 15
do
	echo "or1200.blif bb_factor $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml or1200.blif --route_chan_width 78 --bb_factor $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
