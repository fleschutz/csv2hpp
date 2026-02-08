// DO NOT EDIT! File converted from planets.csv on 2026-02-08 by csv2hpp 0.4.
//              See https://github.com/fleschutz/csv2hpp for details
//              Usage: #include "planets.hpp" ... for (auto& planet : planets) { ...
#pragma once
#include <SI/literals.h>
using namespace SI;

namespace dataset { 

struct planet_data {
	char name[16];                           // CSV column  1 (char[16])
	SI::mass mass;                           // CSV column  2 (_kg)
	SI::length diameter;                     // CSV column  3 (_km)
	SI::density density;                     // CSV column  4 (_kg_per_m³)
	SI::acceleration gravity;                // CSV column  5 (_m_per_s²)
	SI::velocity escape_velocity;            // CSV column  6 (_m_per_s)
	SI::time rotation_period;                // CSV column  7 (_h)
	SI::time length_of_day;                  // CSV column  8 (_h)
	SI::mass distance_from_sun;              // CSV column  9 (_kg)
	float perihelion;                        // CSV column 10 (float)
	float aphelion;                          // CSV column 11 (float)
	SI::time orbital_period;                 // CSV column 12 (_h)
	SI::velocity orbital_velocity;           // CSV column 13 (_m_per_s)
	float orbital_inclination;               // CSV column 14 (float)
	float orbital_eccentricity;              // CSV column 15 (float)
	float obliquity_to_orbit;                // CSV column 16 (float)
	SI::temperature mean_temperature;        // CSV column 17 (_degC)
	SI::pressure surface_pressure;           // CSV column 18 (_bar)
	int number_of_moons;                     // CSV column 19 (int)
	bool has_ring_system;                    // CSV column 20 (bool)
	bool has_global_magnetic_field;          // CSV column 21 (bool)
};

const planet_data planets[] { // NOTE: 00=empty or unknown field
{"Mercury",0.33_kg,4879_km,5427_kg_per_m³,3.7_m_per_s²,4.3_m_per_s,1407.6_h,4222.6_h,57.9_kg,46.f,69.8f,88._h,47.4_m_per_s,7.f,0.205f,0.034f,167_degC,0_bar,0,false,true},
{"Venus",4.87_kg,12104_km,5243_kg_per_m³,8.9_m_per_s²,10.4_m_per_s,-5832.5_h,2802._h,108.2_kg,107.5f,108.9f,224.7_h,35._m_per_s,3.4f,0.007f,177.4f,464_degC,92_bar,0,false,false},
{"Earth",5.97_kg,12756_km,5514_kg_per_m³,9.8_m_per_s²,11.2_m_per_s,23.9_h,24._h,149.6_kg,147.1f,152.1f,365.2_h,29.8_m_per_s,0.f,0.017f,23.4f,15_degC,1_bar,1,false,true},
{"Mars",0.642_kg,6792_km,3933_kg_per_m³,3.7_m_per_s²,5._m_per_s,24.6_h,24.7_h,227.9_kg,206.6f,249.2f,687._h,24.1_m_per_s,1.9f,0.094f,25.2f,-65_degC,0.01_bar,2,false,false},
{"Jupiter",1898_kg,142984_km,1326_kg_per_m³,23.1_m_per_s²,59.5_m_per_s,9.9_h,9.9_h,778.6_kg,740.5f,816.6f,4331_h,13.1_m_per_s,1.3f,0.049f,3.1f,-110_degC,00_bar,79,true,true},
{"Saturn",568_kg,120536_km,687_kg_per_m³,9._m_per_s²,35.5_m_per_s,10.7_h,10.7_h,1433.5_kg,1352.6f,1514.5f,10747_h,9.7_m_per_s,2.5f,0.057f,26.7f,-140_degC,00_bar,62,true,true},
{"Uranus",86.8_kg,51118_km,1271_kg_per_m³,8.7_m_per_s²,21.3_m_per_s,-17.2_h,17.2_h,2872.5_kg,2741.3f,3003.6f,30589_h,6.8_m_per_s,0.8f,0.046f,97.8f,-195_degC,00_bar,27,true,true},
{"Neptune",102_kg,49528_km,1638_kg_per_m³,11._m_per_s²,23.5_m_per_s,16.1_h,16.1_h,4495.1_kg,4444.5f,4545.7f,59800_h,5.4_m_per_s,1.8f,0.011f,28.3f,-200_degC,00_bar,14,true,true},
{"Pluto",0.0146_kg,2370_km,2095_kg_per_m³,0.7_m_per_s²,1.3_m_per_s,-153.3_h,153.3_h,5906.4_kg,4436.8f,7375.9f,90560_h,4.7_m_per_s,17.2f,0.244f,122.5f,-225_degC,0.00001_bar,5,false,false},
}; // (21 columns x 9 rows = 189 cells)

} // namespace dataset

