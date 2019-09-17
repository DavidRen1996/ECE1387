for present in 0.5 2 5 8
do
	echo "diffeq1.blif pres_fac_mult $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml diffeq1.blif --route_chan_width 56 --pres_fac_mult $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 0.5 2 5 8
do
	echo "sha.blif pres_fac_mult $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --route_chan_width 54 --pres_fac_mult $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 0.5 2 5 8
do
	echo "raygentop.blif pres_fac_mult $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml raygentop.blif --route_chan_width 72 --pres_fac_mult $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
for present in 0.5 2 5 8
do
	echo "or1200.blif pres_fac_mult $present" >> B2result.txt
	./vpr k6_frac_N10_mem32K_40nm.xml or1200.blif --route_chan_width 78 --pres_fac_mult $present --nodisp
	grep "Final critical path" vpr_stdout.log >> B2result.txt
done
