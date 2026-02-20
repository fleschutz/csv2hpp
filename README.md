csv2hpp
=======
**This useful utility converts databases from CSV file format into C/C++ header files (even BIG ones). Afterward, include the header files in your software projects and immediately work on structured, well-formed datasets (and skip CSV file delivering, loading, parsing, converting, etc.).**

👣 Steps
---------
1. **Export** or download the database in CSV file format, e.g. to: [POIs.csv](examples/POIs.csv)
2. **Edit** the CSV file and add datatype hints to the header line, e.g.: `Location (string), Latitude (double), Longitude (double)`
3. **Convert** by executing: `csv2hpp POIs.csv POI > POIs.hpp`.
4. **Add** the header file to your project (#include "[POIs.hpp](examples/POIs.hpp)") and immediately start to develop.

💡 Hints
--------
* Datatype hints are mapped to C/C++ datatypes as follows: `(int)` → `int`, `(float)` → `float`, `(string)` → `const char*`, `(skip)` skips the entire column. All supported datatype hints are listed in: [datatype_hints.csv](src/datatype_hints.csv)
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
