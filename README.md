csv2hpp
=======
**This utilty converts databases from CSV file format (.csv suffix) into C/C++ header files. Afterward, software projects can #include them and immediately work on structured, well-formed datasets (skipping data delivering, loading, allocating, checking, converting, etc.).**

👣 Steps
---------
1. **Export** your database in CSV file format, or directly download the .csv file.
2. **Add** datatype hints in round brackets to the CSV header line, e.g.: `Name (string), Age (int), Distance (_km)`
3. **Execute:** `./csv2hpp database.csv my_object_name > headerfile.hpp`.
4. **Add:** `#include "headerfile.hpp"` to your source code and start developing.

💡 Hints
--------
* Datatype hint to C/C++ datatype mapping is: `(string) -> const char*`, `(int) -> int`, `(long) -> long`, `(float) -> float`, `(double) -> double`, `(byte) -> unsigned char`, `(bool) -> bool`, `(skip) -> skips entire column`, `(_km) -> SI:length` and so on.
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.

🎉 Example
-----------
Using database [planets.csv](src/planets.csv) and executing the command-line: `./csv2hpp planets.csv planet > planets.hpp` results in the header file: [planets.hpp](src/planets.hpp).

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
