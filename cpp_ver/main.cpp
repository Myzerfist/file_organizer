#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <algorithm>
#include <chrono>

namespace fs = std::filesystem;

std::map<std::string, std::vector<std::string>> folder_names = {
    {"Images", {"jpg", "jpeg", "png", "gif", "tiff", "bmp", "svg"}},
    {"Videos", {"mp4", "avi", "mov", "wmv", "mkv", "flv", "webm", "vob", "ogv", "ogg", "drc", "mng", "avi", "asf", "wmv", "rm", "rmvb", "mpg", "mpeg", "mpe", "mp4", "m4p", "m4v", "svi", "3gp", "3g2", "mxf", "roq", "nsv", "flv", "f4v", "f4p", "f4a", "f4b"}},
    {"Documents", {"txt", "pdf", "doc", "docx", "odt", "rtf", "tex", "wks", "wps", "wpd", "xls", "xlt", "xlw", "mdb", "fodt", "ods", "odp", "odg", "odf", "odb", "odc", "odm", "ott", "ots", "odp", "otp", "odg"}},
    {"Archives", {"zip", "rar", "7z", "tar", "gz", "bz2", "xz", "iso", "dmg", "pkg"}},
    {"Music", {"mp3", "m4a", "m4b", "aif", "aiff", "aifc", "ogg", "oga", "wav", "wma", "flac", "alac", "ape", "mpc", "tta", "ac3", "dts", "mka", "m3u", "wpl", "pls", "m3u", "m3u8"}},
    {"Executables", {"exe", "msi"}},
    {"Fonts", {"ttf", "otf", "ttc", "otc", "pfa", "pfb", "pfr", "pfm", "afm", "fnt", "fon", "otf", "sfd", "woff", "woff2", "eot", "font", "fnt", "fon"}},
    {"Code", {"py", "c", "cpp", "h", "hpp", "cs", "java", "js", "html", "htm", "xhtml", "css", "xml", "xsl", "xslt", "php", "jsp", "asp", "aspx", "sh", "bat", "cmd", "pl", "rb", "py", "lua", "coffee", "ts", "ts", "ts", "ts"}},
    {"Operating Systems", {"iso", "img"}}
};

std::string get_extension_folder(const std::string& extension) {
    for (const auto& [folder, extensions] : folder_names) {
        if (std::find(extensions.begin(), extensions.end(), extension) != extensions.end()) {
            return folder;
        }
    }
    return "Other";
}

void organize_to_folders(const std::string& folder_path) {
    auto start_time = std::chrono::steady_clock::now();

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string(); // Corrected here
            std::string extension = entry.path().extension().string();
            if (!extension.empty()) {
                std::string folder_name = get_extension_folder(extension.substr(1));
                fs::path folder_path_for_extension = fs::path(folder_path) / folder_name;
                fs::create_directory(folder_path_for_extension);
                fs::rename(entry.path(), folder_path_for_extension / filename);
            }
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    // Save execution time to a text file
    std::ofstream outfile("execution_time.txt");
    if (outfile.is_open()) {
        outfile << "Execution time: " << elapsed_time << " seconds" << std::endl;
        outfile.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

int main() {
    std::string folder_path;
    std::cout << "Enter folder path: ";
    std::getline(std::cin, folder_path);

    organize_to_folders(folder_path);

    std::cout << "Organizing completed." << std::endl;

    return 0;
}
