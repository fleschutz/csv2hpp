csv2hpp
=======
This command-line tool converts databases in CSV file format (.CSV suffix) into header files to be included in C++ projects. This allows to immediately work on large, well-formed datasets without the need of loading, allocating, checking, converting, etc. Please perform the following steps for conversion:

1. Export your database in CSV file format or fetch .CSV files directly.
2. Adjust the CSV header line by adding the C++ datatype or SI literal in round brackets, e.g.: `NAME (string), AGE (int), DISTANCE (_km)`
3. Execute: `./csv2hpp input_file.csv > output_file.hpp`.
4. Include the .hpp file in your software project.

Hints
-----
* Datatype mapping: (string) -> 'const char*', (int) -> 'int', (long) -> 'long', (float) -> 'float', (double) -> 'double', (bool) -> 'bool', (_km) -> 'SI:length' and so on.
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.
