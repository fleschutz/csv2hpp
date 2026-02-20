// DO NOT EDIT! File converted from supported_hints.csv on 2026-02-20 by csv2hpp 0.5
//              (see https://github.com/fleschutz/csv2hpp for details)
// USAGE: #include "supported_hints.hpp" ... for (auto& supported_hint : dataset::supported_hints) { ...
#pragma once

namespace dataset { 

struct supported_hint_data {
	const char* HINT;                  // from column  1 
	const char* DECLARATION;           // from column  2 
	const char* TYPE;                  // from column  3 
	const char* DESCRIPTION;           // from column  4 
};

const supported_hint_data supported_hints[] { // NOTE: 00=empty or unknown field
{"","const char* %s;","TEXT","C/C++ datatype to hold a string when no datatype hint is given"},
{"(bool)","bool %s;","BOOL","C/C++ datatype to hold either true or false"},
{"(byte)","unsigned char %s;","CARD","C/C++ datatype to hold one byte"},
{"(char[4])","char %s[4];","TEXT","C/C++ datatype to hold 3 characters maximum"},
{"(char[8])","char %s[8];","TEXT","C/C++ datatype to hold 7 characters maximum"},
{"(char[12])","char %s[12];","TEXT","C/C++ datatype to hold 11 characters maximum"},
{"(char[16])","char %s[16];","TEXT","C/C++ datatype to hold 15 characters maximum"},
{"(char[32])","char %s[32];","TEXT","C/C++ datatype to hold 31 characters maximum"},
{"(char[64])","char %s[64];","TEXT","C/C++ datatype to hold 63 characters maximum"},
{"(char[128])","char %s[128];","TEXT","C/C++ datatype to hold 127 characters maximum"},
{"(double)","double %s;","FLOAT","C/C++ datatype for floating point values (mostly 64-bit)"},
{"(float)","float %s;","FLOAT","C/C++ datatype for floating point values (mostly 32-bit)"},
{"(int)","int %s;","CARD","C/C++ datatype for integer values (mostly 32-bit)"},
{"(long double)","long double %s;","CARD","C/C++ datatype for big floating values (mostly 64/128-bit)"},
{"(short)","short %s;","CARD","C/C++ datatype for short integer values (mostly 16-bit)"},
{"(string)","const char* %s;","TEXT","C/C++ datatype to hold a string"},
{"(text)","const char* %s;","TEXT","C/C++ datatype to hold a string"},
{"(std::string)","std::string %s;","TEXT","C++ datatype to hold a string"},
{"(unsigned int)","unsigned int %s;","CARD","C/C++ datatype for unsigned integer values (mostly 32-bit)"},
{"(unsigned short)","unsigned short %s;","CARD","C/C++ datatype for unsigned short integer values (mostly 16-bit)"},
{"(unsigned long)","unsigned long %s;","CARD","C/C++ datatype for unsigned long integer values (mostly 64-bit)"},
{"(unsigned long long)","unsigned long long %s;","CARD","C/C++ datatype for big unsigned integers (mostly 64/128-bit)"},
{"(int8_t)","int8_t %s;","CARD","C/C++ datatype to hold an 8-bit signed integer"},
{"(int16_t)","int16_t %s;","CARD","C/C++ datatype to hold a 16-bit signed integer"},
{"(int32_t)","int32_t %s;","CARD","C/C++ datatype to hold a 32-bit signed integer"},
{"(int64_t)","int64_t %s;","CARD","C/C++ datatype to hold a 64-bit signed integer"},
{"(int128_t)","int128_t %s;","CARD","C/C++ datatype to hold a 128-bit signed integer"},
{"(uint8_t)","uint8_t %s;","CARD","C/C++ datatype to hold an 8-bit unsigned integer"},
{"(uint16_t)","uint16_t %s;","CARD","C/C++ datatype to hold a 16-bit unsigned integer"},
{"(uint32_t)","uint32_t %s;","CARD","C/C++ datatype to hold a 32-bit unsigned integer"},
{"(uint64_t)","uint64_t %s;","CARD","C/C++ datatype to hold a 64-bit unsigned integer"},
{"(uint128_t)","uint128_t %s;","CARD","C/C++ datatype to hold a 128-bit unsigned integer"},
{"(_nm)","SI::length %s;","_nm","Length in nanometers (using SI lib)"},
{"(_mm)","SI::length %s;","_mm","Length in millimeters (using SI lib)"},
{"(_cm)","SI::length %s;","_cm","Length in centimeters (using SI lib)"},
{"(_m)","SI::length %s;","_m","Length in meters (using SI lib)"},
{"(_km)","SI::length %s;","_km","Length in kilometers (using SI lib)"},
{"(_au)","SI::length %s;","_au","Length in Astronomical Units (using SI lib)"},
{"(_pc)","SI::length %s;","_pc","Length in Parsec (using SI lib)"},
{"(_Da)","SI::mass %s;","_Da","Mass in Daltons (using SI lib)"},
{"(_mg)","SI::mass %s;","_mg","Mass in milligrams (using SI lib)"},
{"(_g)","SI::mass %s;","_g","Mass in grams (using SI lib)"},
{"(_kg)","SI::mass %s;","_kg","Mass in kilograms (using SI lib)"},
{"(_t)","SI::mass %s;","_t","Mass in metric tons (using SI lib)"},
{"(_ms)","SI::time %s;","_ms","Time in milliseconds (using SI lib)"},
{"(_s)","SI::time %s;","_s","Time in seconds (using SI lib)"},
{"(_min)","SI::time %s;","_min","Time in minutes (using SI lib)"},
{"(_h)","SI::time %s;","_h","Time in hours (using SI lib)"},
{"(_days)","SI::time %s;","_days","Time in days (using SI lib)"},
{"(_K)","SI::temperature %s;","_K","Temperature in Kelvins (using SI lib)"},
{"(_degC)","SI::temperature %s;","_degC","Temperature in °Celsius (using SI lib)"},
{"(_degF)","SI::temperature %s;","_degF","Temperature in °Fahrenheit (using SI lib)"},
{"(_bar)","SI::pressure %s;","_bar","Pressure in bar (using SI lib)"},
{"(_mbar)","SI::pressure %s;","_mbar","Pressure in millibars (using SI lib)"},
{"(_Hz)","SI::frequency %s;","_Hz","Frequency in Hz (using SI lib)"},
{"(_mHz)","SI::frequency %s;","_mHz","Frequency in millihertz (using SI lib)"},
{"(_kHz)","SI::frequency %s;","_kHz","Frequency in kilohertz (using SI lib)"},
{"(_MHz)","SI::frequency %s;","_MHz","Frequency in megahertz (using SI lib)"},
{"(_GHz)","SI::frequency %s;","_GHz","Frequency in gigahertz (using SI lib)"},
{"(_THz)","SI::frequency %s;","_THz","Frequency in terahertz (using SI lib)"},
{"(_m_per_s)","SI::velocity %s;","_m_per_s","Velocity in meter per second (using SI lib)"},
{"(_km_per_h)","SI::velocity %s;","_km_per_h","Velocity in kilometer per hour (using SI lib)"},
{"(_kg_per_m³)","SI::density %s;","_kg_per_m³","Density in kilograms per square meter (using SI lib)"},
{"(_m_per_s²)","SI::acceleration %s;","_m_per_s²","Acceleration in meter per square second (using SI lib)"},
}; // (4 columns x 64 rows = 256 cells)

} // namespace dataset

