#include <stdio.h>
#include <string>
#include <cstring>

std::string nextCell(FILE* file)
{
	std::string result = "";

	// skip optional space/tab
	auto nextChar = fgetc(file);
	while (nextChar == ' ' || nextChar == '\t')
	{
		nextChar = fgetc(file);
	}

	if (feof(file) || nextChar == '\n' || nextChar == '\r')
		return ""; // end of line reached

	if (nextChar == '\"')
	{
		for (nextChar = fgetc(file); nextChar != '\"'; nextChar = fgetc(file))
		{
			result += nextChar;
		}
		nextChar = fgetc(file);
		if (nextChar != ',')
			ungetc(nextChar, file);
		return result;
	}

	while (nextChar != ',' && nextChar != '\n' && nextChar != '\r')
	{
		result += nextChar;
		nextChar = fgetc(file);
	}
	if (nextChar == '\n' || nextChar == '\r')
		ungetc(nextChar, file);
	return result;
}

std::string nameOfCell(std::string cell)
{
	auto ptr = cell.c_str();
	std::string result = "";

	while (*ptr != '\0' && *ptr != ' ')
		result += *ptr++;

	return result;
}

std::string typeOfCell(std::string cell)
{
	if (auto ptr = strchr(cell.c_str(), '('))
	{
		std::string result = "";
		for (ptr++; *ptr != ')'; )
		{
			result += *ptr++;
		}
		return result;
	}
	return "std::string";
}

void printValue(std::string type, std::string value)
{
	if (type == "std::string")
		printf("\"%s\", ", value.c_str());
	else
		printf("%s, ", value.c_str());
}

int readCSVHeader(FILE* file)
{
	std::string types[256];

	printf("#pragma once\n\n#include <array>\n#include <string>\n\nstruct csv_data_entry{\n");
	int i = 0;
	for (auto cell = nextCell(file); cell != ""; cell = nextCell(file), i++)
	{
		auto name = nameOfCell(cell);
		auto type = typeOfCell(cell);
		printf("    %s %s,\n", type.c_str(), name.c_str());
		types[i] = type;
	}
	printf("};\n\nconst std::array csv_data{\n");

	while (!feof(file))
	{
		printf("    csv_data_entry{");
		i = 0;
		for (auto cell = nextCell(file); cell != ""; cell = nextCell(file), i++)
		{
			printValue(types[i], cell);
		}
		printf("},\n");
	}

	printf("};\n");
	return 0;
}

int convertFile(const char* filename)
{
	if (auto file = fopen(filename, "rw"))
	{
		readCSVHeader(file);
		fclose(file);
		return 0;
	}
	fprintf(stderr, "Can't open CSV file: %s\n", filename);
	return 1;
}


int main(int argc, char **argv)
{
	if (argc == 2)
		return convertFile(argv[1]);

	fprintf(stderr, "csv2hpp <filename>\n");
	return 0;
}
