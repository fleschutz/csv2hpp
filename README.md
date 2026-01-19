csv2hpp
=======
This tool converts databases in CSV file format (.CSV suffix) into C++ header files for C++ projects. Please perform the following steps for conversion:

1. Export your database in CSV file format or fetch .CSV files directly.
2. Adjust the CSV header line by adding the C++ datatype or SI literal in round brackets. For example: NAME (string), AGE (int), DISTANCE (_km)
3. Execute: `./csv2hpp input_file.csv > output_file.hpp`.
4. Include the .hpp file in your software project.

Hints
-----
* (string) is mapped to: 'const char*', (int) is mapped to: 'int', (float) is mapped to: 'float', (double) is mapped to: 'double', (_km) is mapped to: SI:length
* Empty CSV cells are mapped to "" for strings and to 00 for everything else.
* Supports really HUGE .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers).
