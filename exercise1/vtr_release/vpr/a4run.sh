./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --place --pack --place_algorithm bounding_box --nodisp --seed 2 
grep "          0" vpr_stdout.log >> s4.txt
./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --place --pack --place_algorithm bounding_box --nodisp --seed 3 
grep "          0" vpr_stdout.log >> s4.txt
./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --place --pack --place_algorithm bounding_box --nodisp --seed 4 
grep "          0" vpr_stdout.log >> s4.txt
./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --place --pack --place_algorithm bounding_box --nodisp --seed 5 
grep "          0" vpr_stdout.log >> s4.txt
./vpr k6_frac_N10_mem32K_40nm.xml sha.blif --place --pack --place_algorithm bounding_box --nodisp --seed 6 
grep "          0" vpr_stdout.log >> s4.txt
