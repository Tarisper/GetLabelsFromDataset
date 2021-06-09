#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

typedef struct Label {
  string name;
  int count;
};

int main(int argc, char* argv[]) {
  if (argc == 1) {
    cerr << "The path to the directory with files is not specified" << endl;
    return 0;
  }
  string path = argv[1];
  vector<Label> labels;
  for (auto& p : fs::recursive_directory_iterator(path)) {
    if (p.path().extension() == ".json") {
      cout << p << endl;
      std::string source, content;
      try {
        std::ifstream in(p);
        if (in.is_open()) {
          while (getline(in, source)) {
            content = content + source;
          }
        }
        in.close();
        json j = json::parse(content);
        for (size_t i = 0; i < j["shapes"].size(); i++) {
          string name = j["shapes"][i]["label"].get<string>();
          auto it = find_if(begin(labels), end(labels),
                            [=](Label const& f) { return (f.name == name); });
          if (it == labels.end()) {
            Label _label = {};
            _label.name = name;
            _label.count = 1;
            labels.push_back(_label);
          } else
            it->count++;
        }
      } catch (const json::exception& e) {
        cerr << "Parsing error: " << e.what();
        return false;
      }
    }
  }
  for (auto v : labels) {
    cout << v.name << " = " << v.count << endl;
  }
}