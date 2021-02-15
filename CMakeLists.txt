cmake_minimum_required(VERSION 3.17)
project(DIT632 C)

set(CMAKE_C_STANDARD 11)

# WORK PACKAGE 2
set(ex1 wp_2/exerc_2_1/exerc_2_1.c)
set(ex2 wp_2/exerc_2_2/exerc_2_2.c)
set(ex3 wp_2/exerc_2_3/exerc_2_3.c)
set(ex4 wp_2/exerc_2_4/exerc_2_4.c)
set(ex5 wp_2/exerc_2_5/exerc_2_5.c)
set(ex6 wp_2/exerc_2_6/exerc_2_6.c)
set(ex7 wp_2/exerc_2_7/exerc_2_7.c)
set(ex8 wp_2/exerc_2_8/exerc_2_8.c)

# WORK PACKAGE 3
set(exerc_3_1 wp_3/exerc_3_1/exerc_3_1.c)
set(exerc_3_2 wp_3/exerc_3_2/exerc_3_2.c)
set(exerc_3_3 wp_3/exerc_3_3/exerc_3_3.c)
set(exerc_3_4 wp_3/exerc_3_4/exerc_3_4.c)
set(personalNumberValidator wp_3/exerc_3_4/personalNumberValidator.c)



# WORK PACKAGE 2
add_executable("ex1" ${ex1})
add_executable("ex2" ${ex2})
add_executable("ex3" ${ex3})
add_executable("ex4" ${ex4})
add_executable("ex5" ${ex5})
add_executable("ex6" ${ex6})
add_executable("ex7" ${ex7})
add_executable("ex8" ${ex8})

# WORK PACKAGE 3
add_executable("exerc_3_1" ${exerc_3_1})
add_executable("exerc_3_2" ${exerc_3_2})
add_executable("exerc_3_3" ${exerc_3_3})
add_executable("exerc_3_4" ${exerc_3_4} ${personalNumberValidator})

# WORK PACKAGE 4
set(code wp_4/exerc_4_1/code.c wp_4/exerc_4_3/exerc_4_3.c)
set(exerc_4_3 wp_4/exerc_4_3/exerc_4_3.c)


add_executable("code" ${code})
add_executable("exerc_4_3" ${exerc_4_3})