csv2hpp
=======
This tool converts databases in CSV format (.CSV suffix) into C++ header files for C++ projects. Please perform the following steps for conversion:

1. Copy the .CSV file, e.g. input_file.csv
2. Adjust the CSV header line by adding the C++ datatype or SI literal. For example: "NAME (string), AGE (int), DISTANCE (_km)
3. Execute: `./csv2hpp input_file.csv > output_file.hpp`.
4. Include the .hpp file in your software project.

Hints
-----
* (string) is mapped to: 'const char*', (int) is mapped to: 'int', (double) is mapped to: 'double', (_km) is mapped to: SI:length
* Empty CSV cells are mapped to "" for strings and to 00 for everything else.
* Supports really HUGE .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers).
