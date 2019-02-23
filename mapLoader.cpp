#include <fstream>
#include <vector>
#include "tools.h"
#include "GameObjectPool.h"


char* parseName(char *line, char *& endPos)
{
	line += 1;
	auto c = strtok(line, "\"");
	endPos = line + strlen(line) + 1;
	return c;
}

void parseFloats(char *line, char *& endPos, float& a, float &b, float &c)
{
	sscanf(strtok(line, ","), "%f", &a);
	endPos = line + strlen(line) + 1;
	sscanf(strtok(0, ","), "%f", &b);
	endPos += strlen(endPos) + 1;
	sscanf(strtok(0, " \n"), "%f", &c);
	endPos += strlen(endPos) + 1;
}

void parseFloat(char *line, char *& endPos, float& a)
{
	sscanf(strtok(line, " \n"), "%f", &a);
	endPos = line + strlen(line) + 1;
}

void parseint(char *line, char *& endPos, int& a)
{
	sscanf(strtok(line, " \n"), "%d", &a);
	endPos = line + strlen(line) + 1;
}

int parseCommand(char *line, char *& endPos)
{
	while (line[0] == ' ')
	{
		line++;
	}

	strtok(line, " ");
	endPos = line + strlen(line) + 1;
	if (strcmp(line, "@simple") == 0)
	{
		return simple;
	}
	else
		if (strcmp(line, "@complex") == 0)
		{
			return complex;
		}
		else
			if (strcmp(line, "@phisical") == 0)
			{
				return phisical;
			}
			else
				if (strcmp(line, "@light") == 0)
				{
					return light;
				}
				else
					if (strcmp(line, "@position") == 0)
					{
						return position;
					}
					else
						if (strcmp(line, "@rotation") == 0)
						{
							return rotation;
						}
						else
							if (strcmp(line, "@strength") == 0)
							{
								return strength;
							}
							else
								if (strcmp(line, "@exponent") == 0)
								{
									return exponent;
								}
								else
									if (strcmp(line, "@id") == 0)
									{
										return id;
									}
								else
								{
									//elog("Parsing Error: ", line);
									return none;
								}
}

std::vector<generalObjectData> loadMapData(const char *f)
{
	std::vector<generalObjectData> data;
	data.reserve(50);

	std::ifstream file(f);
	char line[256];
	char parsed[200];
	while (file.getline(line, 256))
	{
		if (line[0] == '/')
		{
			continue;
		}

		generalObjectData object;
		char *current = line;
		bool nextLine = 0;
		while (!nextLine)
		{
			float x = 0, y = 0, z = 0;
			char *p;
			int n = parseCommand(current, p);
			current = p;
			switch (n)
			{
			case none:
				nextLine = 1;
				break;
			case simple:
				object.type = simple;
				object.name = parseName(current, p);
				current = p;
				break;
			case complex:
				object.type = complex;
				object.name = parseName(current, p);
				current = p;
				break;
			case phisical:
				object.type = phisical;
				object.name = parseName(current, p);
				current = p;
				break;
			case light:
				object.type = light;
				object.name = parseName(current, p);
				current = p;
				break;
			case position:

				parseFloats(current, p, x, y, z);
				current = p;
				object.position = { x,y,z };
				break;
			case rotation:
				parseFloats(current, p, x, y, z);
				current = p;
				object.rotation = { x,y,z };
				break;
			case strength:
				parseFloat(current, p, x);
				object.strength = x;
				break;
			case exponent:
				parseFloat(current, p, x);
				object.ambienceExponent = x;
				break;
			case ambience:
				parseFloats(current, p, x, y, z);
				current = p;
				object.ka = { x,y,z };
				break;
			case diffuse:
				parseFloats(current, p, x, y, z);
				current = p;
				object.kd = { x,y,z };
				break;
			case specular:
				parseFloats(current, p, x, y, z);
				current = p;
				object.ks = { x,y,z };
				break;
			case id:
				int i;
				parseint(current, p, i);
				current = p;
				object.id = i;
				break;
			default:
				nextLine = 1;
				break;
			}
		}
		data.emplace_back(object);
	}

	file.close();

	return std::move(data);
}
