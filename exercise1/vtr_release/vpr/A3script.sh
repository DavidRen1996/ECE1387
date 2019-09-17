for file in diffeq1.blif sha.blif raygentop.blif or1200.blif
do
	for temp in 900 50 5 0.8 0.05
	do
		for seed in 2 20 45 90 150
		do
			#echo "$file -1.0 $temp $seed" >> A3result.txt
			./vpr --place --pack --place_algorithm bounding_box k6_frac_N10_mem32K_40nm.xml $file \
				--nodisp --seed $seed --init_t $temp
			grep "Placement cost: " vpr_stdout.log >> A3result.txt
			sed -i -- 's/Placement cost://' A3result.txt
			sed -i -- 's/bb_cost://' A3result.txt
			sed -i -- 's/td_cost://' A3result.txt
			sed -i -- 's/delay_cost://' A3result.txt
		done
	done
done
