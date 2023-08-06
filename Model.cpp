#include "Model.h"

#include "Log.h"

#include <string>
#include <fstream>
#include <sstream>
#include <queue>

void Model::loadOBJ(const char* path) {
	gl_data_.clear();

	std::vector<float> verts;
	std::vector<float> tex_cs;
	std::vector<float> norms;

	std::string line;
	std::ifstream file(path);

	while (std::getline(file, line)) {

		// Set up a string stream from which to extract words
		std::stringstream stream;
		stream << line;

		// Extract first word from stream
		std::string start;
		stream >> start;

		if (start == "#") {
			// Comment - skip this line
			continue;
		}

		if (start == "v") {
			std::string element = "";
			// For each element of the vertex, push it onto the vertices vector
			for (int i = 0; i < 3; i++) {
				stream >> element;
				verts.push_back(std::stof(element));
				element = "";
			}
		}

		if (start == "vt") {
			std::string element = "";
			// For each element of the vertex, push it onto the vertices vector
			for (int i = 0; i < 2; i++) {
				stream >> element;
				tex_cs.push_back(std::stof(element));
				element = "";
			}
		}

		if (start == "vn") {
			std::string element = "";
			// For each element of the vertex, push it onto the vertices vector
			for (int i = 0; i < 3; i++) {
				stream >> element;
				norms.push_back(std::stof(element));
				element = "";
			}
		}

		if (start == "f") {
			std::string points[3];

			stream >> points[0];
			stream >> points[1];
			stream >> points[2];

			// For each point
			for (int i = 0; i < 3; i++) {
				std::stringstream point_stream(points[i]);

				std::string segment; // String variable for each individual segment (v, vt or vn)
				std::vector<std::string> segments; // Vector to store all segments (v, vt then vn)

				while (std::getline(point_stream, segment, '/')) {
					segments.push_back(segment); // Split the string by / character and add them to segments vector
				}

				gl_data_.push_back(verts[(std::stoi(segments[0]) - 1) * 3 + 0]);
				gl_data_.push_back(verts[(std::stoi(segments[0]) - 1) * 3 + 1]);
				gl_data_.push_back(verts[(std::stoi(segments[0]) - 1) * 3 + 2]);

				gl_data_.push_back(tex_cs[(std::stoi(segments[1]) - 1) * 2]);
				gl_data_.push_back(tex_cs[(std::stoi(segments[1]) - 1) * 2 + 1]);

				gl_data_.push_back(norms[(std::stoi(segments[2]) - 1) * 3]);
				gl_data_.push_back(norms[(std::stoi(segments[2]) - 1) * 3 + 1]);
				gl_data_.push_back(norms[(std::stoi(segments[2]) - 1) * 3 + 2]);

				index_.push_back(index_.size());
			}
		}
	}
}

void Model::save(const char* name) {
	std::ofstream outfile;

	std::string filename(name);
	filename.append(".tmd");

	outfile.open(filename, 'w');//std::ios_base::app
	outfile << "# '" << name << "' teapot framework model file\n";
	outfile << "# " << getIndexSize() << " vertices\n";
	outfile << "# " << "v1 v2 v3 t1 t2 n1 n2 n3\n";

	outfile << "# start\n";
	for (int i = 0; i < gl_data_.size(); i++) {
		outfile << gl_data_[i] << " ";
		if (!((i + 1) % 8)) {
			outfile << "\n";
		}
	}
	outfile << "# end";

	outfile.close();
}

void Model::open(const char* name) {
	gl_data_.clear();

	std::string line;

	std::string filename(name);
	filename.append(".tmd");
	std::ifstream infile(filename);

	while (std::getline(infile, line)) {
		if (line[0] == '#' || line.length() < 1) {
			continue;
		}
		else {
			std::stringstream line_stream(line);
			std::string element = "";
			for (int i = 0; i < 8; i++) {
				try {
					line_stream >> element;
					gl_data_.push_back(std::stof(element));
					element = "";
				} catch (...) {
					Log::error("Invalid teapot model data file provided");
					gl_data_.clear();
					return;
				}
			}

			index_.push_back(index_.size());
		}
	}
}
