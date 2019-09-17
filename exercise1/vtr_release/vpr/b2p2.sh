for present in 0.5 1 2 10
do
	echo "diffeq1.blif acc_fac $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml diffeq1.blif --route_chan_width 56 --acc_fac $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 0.5 1 2 10
do
	echo "sha.blif acc_fac $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --route_chan_width 54 --acc_fac $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 0.5 1 2 10
do
	echo "raygentop.blif acc_fac $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml raygentop.blif --route_chan_width 72 --acc_fac $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 0.5 1 2 10
do
	echo "or1200.blif acc_fac $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml or1200.blif --route_chan_width 78 --acc_fac $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done