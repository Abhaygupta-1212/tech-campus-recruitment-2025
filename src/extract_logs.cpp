#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void extract_logs(const std::string &log_file, const std::string &target_date) {
    std::string output_dir = "output";
    std::string output_file = output_dir + "/output_" + target_date + ".txt";

    if (!fs::exists(output_dir)) {
        fs::create_directory(output_dir);
    }

    std::ifstream infile(log_file);
    std::ofstream outfile(output_file);

    if (!infile.is_open()) {
        std::cerr << "❌ Error: Could not open log file: " << log_file << std::endl;
        return;
    }

    if (!outfile.is_open()) {
        std::cerr << "❌ Error: Could not create output file: " << output_file << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    while (std::getline(infile, line)) {
        // Check if the first 10 characters (YYYY-MM-DD) match the target date
        if (line.substr(0, 10) == target_date) {
            outfile << line << '\n';
            found = true;
        }
    }

    infile.close();
    outfile.close();

    if (!found) {
        std::cerr << "⚠️ Warning: No logs found for " << target_date << std::endl;
    } else {
        std::cout << "✅ Logs for " << target_date << " extracted to " << output_file << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "❌ Usage: ./extract_logs <YYYY-MM-DD>" << std::endl;
        return 1;
    }

    std::string log_file = "logs_2024.log";  // Updated file name
    std::string target_date = argv[1];

    extract_logs(log_file, target_date);

    return 0;
}
