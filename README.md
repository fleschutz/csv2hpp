csv2hpp 0.2
===========
**This utility converts databases from CSV file format into C/C++ header files. Afterward, #include them in your software projects and immediately work on structured, well-formed datasets (skipping CSV file delivering, loading, parsing, converting, etc.).**

👣 Steps
---------
1. **Export** your database in CSV file format.
2. **Edit** the CSV file and add datatype hints to the header line only, e.g.: `Name (string), Age (int), Weight (_kg)`
3. **Execute:** `csv2hpp database.csv my_object_name > headerfile.hpp`.
4. **Add:** `#include "headerfile.hpp"` to your source code and start developing.

💡 Hints
--------
* Datatype hints are mapped to C/C++ datatypes as follows: `(string) -> const char*`, `(int) -> int`, `(long) -> long`, `(float) -> float`, `(double) -> double`, `(byte) -> unsigned char`, `(bool) -> bool`, `(skip)` skips the entire column, `(_km) -> SI:length` and so on.
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.

🎉 Example
-----------
Using [planets.csv](src/planets.csv) and executing: `csv2hpp planets.csv planet > planets.hpp` results in the header file: [planets.hpp](src/planets.hpp).

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
