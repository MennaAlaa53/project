#include <iostream>
#include <filesystem>
#include <map>
using namespace std;
namespace fs = std::filesystem;

void organize_files(const fs::path& folder_path) {
    map<string, string> extension_to_folder = {
        {".png", "imgs"}, {".jpg", "imgs"}, {".gif", "imgs"},
        {".pdf", "docs"}, {".md", "docs"}, {".doc", "docs"},
        {".txt", "writings"},
        {".exe", "programs"}, {".msi", "programs"},
        {".mp3", "multimedia"}, {".mp4", "multimedia"}, {".wav", "multimedia"}
    };
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            string extension = entry.path().extension().string();
            string folder_name = "others";
            if (extension_to_folder.find(extension) != extension_to_folder.end()) {
                folder_name = extension_to_folder[extension];
            }
            fs::path target_folder = folder_path / folder_name;
            fs::create_directory(target_folder);
            fs::rename(entry.path(), target_folder / entry.path().filename());
        }
    }
    cout << "The folder has organized successfully!" << endl;
    system(("explorer " + folder_path.string()).c_str());
}
int main() {
    string path;
    cout << "Please, enter the folder path that you want to organize it: ";
    cin >> path;
    organize_files(path);

    return 0;
}