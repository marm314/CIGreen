#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file\n";
        return 1;
    }

    std::string input_filename = argv[1];

    std::ifstream input(input_filename);
    if (!input.is_open()) {
        std::cerr << "Error: cannot open input file: "
                  << input_filename << '\n';
        return 1;
    }

    // Separate filename and extension
    std::string base_name = input_filename;
    std::string extension;

    std::size_t dot = base_name.find_last_of('.');

    if (dot != std::string::npos) {
        extension = base_name.substr(dot);
        base_name = base_name.substr(0, dot);
    }

    std::string line;
    std::ofstream output;

    int vector_number = 0;
    bool inside_vector = false;

    while (std::getline(input, line)) {

        // Beginning of a CI vector
        if (!inside_vector &&
            line.find("Final CI vector") != std::string::npos) {

            ++vector_number;

            std::string output_filename =
                base_name + "_" +
                std::to_string(vector_number) +
                extension;

            output.open(output_filename);

            if (!output.is_open()) {
                std::cerr << "Error: cannot create "
                          << output_filename << '\n';
                return 1;
            }

            inside_vector = true;

            // Write the beginning of the vector
            output << line << '\n';

            continue;
        }

        // Write lines belonging to the current CI vector
        if (inside_vector) {

            output << line << '\n';

            // End of CI vector
            if (line.find("/EOF") != std::string::npos) {

                output.close();
                inside_vector = false;
            }
        }
    }

    // Check for an unfinished vector
    if (inside_vector) {
        output.close();

        std::cerr << "Warning: last CI vector has no /EOF marker.\n";
    }

    std::cout << "Extracted "
              << vector_number
              << " CI vectors.\n";

    return 0;
}
