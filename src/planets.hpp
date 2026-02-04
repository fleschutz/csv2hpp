// DO NOT EDIT! Data source is planets.csv (converted by github.com/fleschutz/csv2hpp 0.3 on 2026-02-04)
#pragma once
#include <SI/literals.h>
using namespace SI;

namespace dataset { 

struct planet_data {
	const char* name;                         // column  1 (string) in CSV file
	SI::mass mass;                            // column  2 (_kg) in CSV file
	SI::length diameter;                      // column  3 (_km) in CSV file
	SI::density density;                      // column  4 (_kg_per_m³) in CSV file
	SI::acceleration gravity;                 // column  5 (_m_per_s²) in CSV file
	SI::velocity escape_velocity;             // column  6 (_m_per_s) in CSV file
	SI::time rotation_period;                 // column  7 (_h) in CSV file
	SI::time length_of_day;                   // column  8 (_h) in CSV file
	SI::mass distance_from_sun;               // column  9 (_kg) in CSV file
	float perihelion;                         // column 10 (float) in CSV file
	float aphelion;                           // column 11 (float) in CSV file
	SI::time orbital_period;                  // column 12 (_h) in CSV file
	SI::velocity orbital_velocity;            // column 13 (_m_per_s) in CSV file
	float orbital_inclination;                // column 14 (float) in CSV file
	float orbital_eccentricity;               // column 15 (float) in CSV file
	float obliquity_to_orbit;                 // column 16 (float) in CSV file
	SI::temperature mean_temperature;         // column 17 (_degC) in CSV file
	SI::pressure surface_pressure;            // column 18 (_bar) in CSV file
	int number_of_moons;                      // column 19 (int) in CSV file
	bool has_ring_system;                     // column 20 (bool) in CSV file
	bool has_global_magnetic_field;           // column 21 (bool) in CSV file
};

const planet_data planets[] { // NOTE: 00=empty or unknown field
{"Mercury",0.33_kg,4879_km,5427_kg_per_m³,3.7_m_per_s²,4.3_m_per_s,1407.6_h,4222.6_h,57.9_kg,46.,69.8,88._h,47.4_m_per_s,7.,0.205,0.034,167_degC,0_bar,0,false,true},
{"Venus",4.87_kg,12104_km,5243_kg_per_m³,8.9_m_per_s²,10.4_m_per_s,-5832.5_h,2802._h,108.2_kg,107.5,108.9,224.7_h,35._m_per_s,3.4,0.007,177.4,464_degC,92_bar,0,false,false},
{"Earth",5.97_kg,12756_km,5514_kg_per_m³,9.8_m_per_s²,11.2_m_per_s,23.9_h,24._h,149.6_kg,147.1,152.1,365.2_h,29.8_m_per_s,0.,0.017,23.4,15_degC,1_bar,1,false,true},
{"Mars",0.642_kg,6792_km,3933_kg_per_m³,3.7_m_per_s²,5._m_per_s,24.6_h,24.7_h,227.9_kg,206.6,249.2,687._h,24.1_m_per_s,1.9,0.094,25.2,-65_degC,0.01_bar,2,false,false},
{"Jupiter",1898_kg,142984_km,1326_kg_per_m³,23.1_m_per_s²,59.5_m_per_s,9.9_h,9.9_h,778.6_kg,740.5,816.6,4331_h,13.1_m_per_s,1.3,0.049,3.1,-110_degC,00_bar,79,true,true},
{"Saturn",568_kg,120536_km,687_kg_per_m³,9._m_per_s²,35.5_m_per_s,10.7_h,10.7_h,1433.5_kg,1352.6,1514.5,10747_h,9.7_m_per_s,2.5,0.057,26.7,-140_degC,00_bar,62,true,true},
{"Uranus",86.8_kg,51118_km,1271_kg_per_m³,8.7_m_per_s²,21.3_m_per_s,-17.2_h,17.2_h,2872.5_kg,2741.3,3003.6,30589_h,6.8_m_per_s,0.8,0.046,97.8,-195_degC,00_bar,27,true,true},
{"Neptune",102_kg,49528_km,1638_kg_per_m³,11._m_per_s²,23.5_m_per_s,16.1_h,16.1_h,4495.1_kg,4444.5,4545.7,59800_h,5.4_m_per_s,1.8,0.011,28.3,-200_degC,00_bar,14,true,true},
{"Pluto",0.0146_kg,2370_km,2095_kg_per_m³,0.7_m_per_s²,1.3_m_per_s,-153.3_h,153.3_h,5906.4_kg,4436.8,7375.9,90560_h,4.7_m_per_s,17.2,0.244,122.5,-225_degC,0.00001_bar,5,false,false},
}; // (21 columns x 9 rows = 189 cells)

} // namespace dataset

