# Cpp-SudokuSolver
A program for solving sudoku stored in .sdm or .sdx format
Input and output file are passed as arguments in main function (example : "-i input.sdm -o output.txt". If one (or both) are not provided, program will read (or write) to console instead.
Alternatively, if a .sdx file is passed as input, with parameter "--check" ("--check input.sdx), programm will output 'YES" or 'NO', depends on if the sudoku can be solved by the given candidate numbers in .sdx file.
.sdm file example (each line represents 1 sudoku with zeroes as empty cells): 

016400000200009000400000062070230100100000003003087040960000005000800007000006820
049008605003007000000000030000400800060815020001009000010000000000600400804500390
760500000000060008000000403200400800080000030005001007809000000600010000000003041
316452978285679314497318562879234156142965783653187249968721495521843697734596821
000605000003020800045090270500000001062000540400000007098060450006040700000203000
409000705000010000006207800200000009003704200800000004002801500000060000905000406

.sdx file example (1 sudoku, 9x9 cells are separated by whitespaces, candidate numbers for each cells are provided, and if cell starts with 'u', that means its number is already set):

2 679 6789 1 46789 5 469 9 3

389 5 4 69 689 68 7 1 29

9 1 679 2 4679 3 4569 8 59

6 9 2 8 u1 7 3 59 4

3489 3479 3789 56 2456 46 u1 2579 2579

1 47 5 3 24 9 8 27 6

3459 2 39 7 3589 1 59 6 589

359 8 1 569 3569 6 2 4 579

7 369 369 4 35689 2 59 359 1
