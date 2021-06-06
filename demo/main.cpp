// Copyright 2020 Your Name <your_email>

#include <boost/program_options.hpp>

#include "Project.hpp"

namespace po = boost::program_options;
int main(int argc, char* argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()("help", ": выводим вспомогательное сообщение")(
      "threshold", po::value<float>(), ": параметр")(
      "filename", po::value<std::string>(), ": имя файла"
      );

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  std::string help_mes =
      R"(
Usage: builder [options]
Allowed options:
  --help                    : выводим вспомогательное сообщение
  --threshold               : параметр (по умолчанию 5)
  --filename                : имя файла (по умолчанию data.txt)
)";
  if (vm.count("help")) {
    std::cout << help_mes << std::endl;
    return 0;
  }
  float threshold = (vm.count("threshold")) ? vm["threshold"].as<float>() : 2;
  std::string filename = (vm.count("filename")) ? vm["filename"].as<std::string>() : "data.txt";

  Log& the_log = Log::getInstance();
  PageContainer page;
  StatSender stat(page);
  UsedMemory used_memory(page);

  std::ifstream in(filename);
  page.Load(in, threshold);

  the_log.Write(std::to_string(used_memory.used()));

  for (size_t i = 0; i < 5; ++i) {
    const auto& item = page.ByIndex(i);
    std::cout << item.name << ": " << item.score << std::endl;
    const auto& item2 = page.ById(std::to_string(i));
    std::cout << item2.name << ": " << item2.score << std::endl;
  }

  page.Reload(threshold);
  the_log.Write(std::to_string(used_memory.used()));

  return 0;
}
