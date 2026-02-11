// DO NOT EDIT! File converted from hints.csv on 2026-02-08 by csv2hpp 0.4
//              (see https://github.com/fleschutz/csv2hpp for details)
// USAGE: #include "hints.hpp" ... for (auto& hint : dataset::hints) { ...
#pragma once

namespace dataset { 

struct hint_data {
	const char* HINT;                        // CSV column  1 (string)
	const char* DECLARATION;                 // CSV column  2 (string)
	bool NUMBER_EXPECTED;                    // CSV column  3 (bool)
};

const hint_data hints[] { // NOTE: 00=empty or unknown field
{"char[4]","char %s[4]",false},
{"char[8]","char %s[8]",false},
{"char[12]","char %s[12]",false},
{"char[16]","char %s[16]",false},
{"char[32]","char %s[32]",false},
{"char[64]","char %s[64]",false},
{"char[128]","char %s[128]",false},
{"double","double %s",true},
{"float","float %s",true},
{"int","int %s",true},
{"long double","long double %s",true},
{"short","short %s",true},
{"string","const char* %s",false},
{"std::string","std::string %s",false},
{"unsigned int","unsigned int %s",true},
{"unsigned short","unsigned short %s",true},
{"unsigned long","unsigned long %s",true},
{"unsigned long long","unsigned long long %s",true},
}; // (3 columns x 19 rows = 57 cells)

} // namespace dataset

