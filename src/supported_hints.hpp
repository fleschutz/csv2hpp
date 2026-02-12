// DO NOT EDIT! File converted from supported_hints.csv on 2026-02-12 by csv2hpp 0.4
//              (see https://github.com/fleschutz/csv2hpp for details)
// USAGE: #include "supported_hints.hpp" ... for (auto& supported_hint : dataset::supported_hints) { ...
#pragma once

namespace dataset { 

struct supported_hint_data {
	const char* HINT;                         // CSV column  1 (string)
	const char* DECLARATION;                         // CSV column  2 (string)
	bool NUMBER_EXPECTED;                                // CSV column  3 (bool)
};

const supported_hint_data supported_hints[] { // NOTE: 00=empty or unknown field
{"bool","bool %s;",false},
{"byte","unsigned char %s;",true},
{"char[4]","char %s[4];",false},
{"char[8]","char %s[8];",false},
{"char[12]","char %s[12];",false},
{"char[16]","char %s[16];",false},
{"char[32]","char %s[32];",false},
{"char[64]","char %s[64];",false},
{"char[128]","char %s[128];",false},
{"double","double %s;",true},
{"float","float %s;",true},
{"int","int %s;",true},
{"long double","long double %s;",true},
{"short","short %s;",true},
{"string","const char* %s;",false},
{"std::string","std::string %s;",false},
{"text","const char* %s;",false},
{"unsigned int","unsigned int %s;",true},
{"unsigned short","unsigned short %s;",true},
{"unsigned long","unsigned long %s;",true},
{"unsigned long long","unsigned long long %s;",true},
{"int8_t","int8_t %s;",true},
{"int16_t","int16_t %s;",true},
{"int32_t","int32_t %s;",true},
{"int64_t","int64_t %s;",true},
{"int128_t","int128_t %s;",true},
{"uint8_t","uint8_t %s;",true},
{"uint16_t","uint16_t %s;",true},
{"uint32_t","uint32_t %s;",true},
{"uint64_t","uint64_t %s;",true},
{"uint128_t","uint128_t %s;",true},
{"_nm","SI::length %s;",true},
{"_mm","SI::length %s;",true},
{"_cm","SI::length %s;",true},
{"_m","SI::length %s;",true},
{"_km","SI::length %s;",true},
{"_au","SI::length %s;",true},
{"_pc","SI::length %s;",true},
{"_Da","SI::mass %s;",true},
{"_mg","SI::mass %s;",true},
{"_g","SI::mass %s;",true},
{"_kg","SI::mass %s;",true},
{"_t","SI::mass %s;",true},
{"_ms","SI::time %s;",true},
{"_s","SI::time %s;",true},
{"_min","SI::time %s;",true},
{"_h","SI::time %s;",true},
{"_days","SI::time %s;",true},
{"_K","SI::temperature %s;",true},
{"_degC","SI::temperature %s;",true},
{"_degF","SI::temperature %s;",true},
{"_bar","SI::pressure %s;",true},
{"_mbar","SI::pressure %s;",true},
{"_Hz","SI::frequency %s;",true},
{"_mHz","SI::frequency %s;",true},
{"_kHz","SI::frequency %s;",true},
{"_MHz","SI::frequency %s;",true},
{"_GHz","SI::frequency %s;",true},
{"_THz","SI::frequency %s;",true},
}; // (3 columns x 59 rows = 177 cells)

} // namespace dataset

