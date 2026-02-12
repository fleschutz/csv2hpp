// DO NOT EDIT! File converted from supported_hints.csv on 2026-02-12 by csv2hpp 0.4
//              (see https://github.com/fleschutz/csv2hpp for details)
// USAGE: #include "supported_hints.hpp" ... for (auto& supported_hint : dataset::supported_hints) { ...
#pragma once

namespace dataset { 

struct supported_hint_data {
	const char* HINT;                       // CSV column  1 (string)
	const char* DECLARATION;                // CSV column  2 (string)
	const char* TYPE;                       // CSV column  3 (string)
};

const supported_hint_data supported_hints[] { // NOTE: 00=empty or unknown field
{"bool","bool %s;","BOOL"},
{"byte","unsigned char %s;","CARD"},
{"char[4]","char %s[4];","TEXT"},
{"char[8]","char %s[8];","TEXT"},
{"char[12]","char %s[12];","TEXT"},
{"char[16]","char %s[16];","TEXT"},
{"char[32]","char %s[32];","TEXT"},
{"char[64]","char %s[64];","TEXT"},
{"char[128]","char %s[128];","TEXT"},
{"double","double %s;","FLOAT"},
{"float","float %s;","FLOAT"},
{"int","int %s;","CARD"},
{"long double","long double %s;","CARD"},
{"short","short %s;","CARD"},
{"string","const char* %s;","TEXT"},
{"std::string","std::string %s;","TEXT"},
{"text","const char* %s;","TEXT"},
{"unsigned int","unsigned int %s;","CARD"},
{"unsigned short","unsigned short %s;","CARD"},
{"unsigned long","unsigned long %s;","CARD"},
{"unsigned long long","unsigned long long %s;","CARD"},
{"int8_t","int8_t %s;","CARD"},
{"int16_t","int16_t %s;","CARD"},
{"int32_t","int32_t %s;","CARD"},
{"int64_t","int64_t %s;","CARD"},
{"int128_t","int128_t %s;","CARD"},
{"uint8_t","uint8_t %s;","CARD"},
{"uint16_t","uint16_t %s;","CARD"},
{"uint32_t","uint32_t %s;","CARD"},
{"uint64_t","uint64_t %s;","CARD"},
{"uint128_t","uint128_t %s;","CARD"},
{"_nm","SI::length %s;","SI"},
{"_mm","SI::length %s;","SI"},
{"_cm","SI::length %s;","SI"},
{"_m","SI::length %s;","SI"},
{"_km","SI::length %s;","SI"},
{"_au","SI::length %s;","SI"},
{"_pc","SI::length %s;","SI"},
{"_Da","SI::mass %s;","SI"},
{"_mg","SI::mass %s;","SI"},
{"_g","SI::mass %s;","SI"},
{"_kg","SI::mass %s;","SI"},
{"_t","SI::mass %s;","SI"},
{"_ms","SI::time %s;","SI"},
{"_s","SI::time %s;","SI"},
{"_min","SI::time %s;","SI"},
{"_h","SI::time %s;","SI"},
{"_days","SI::time %s;","SI"},
{"_K","SI::temperature %s;","SI"},
{"_degC","SI::temperature %s;","SI"},
{"_degF","SI::temperature %s;","SI"},
{"_bar","SI::pressure %s;","SI"},
{"_mbar","SI::pressure %s;","SI"},
{"_Hz","SI::frequency %s;","SI"},
{"_mHz","SI::frequency %s;","SI"},
{"_kHz","SI::frequency %s;","SI"},
{"_MHz","SI::frequency %s;","SI"},
{"_GHz","SI::frequency %s;","SI"},
{"_THz","SI::frequency %s;","SI"},
}; // (3 columns x 59 rows = 177 cells)

} // namespace dataset

