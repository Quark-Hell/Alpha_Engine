#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <filesystem>

namespace Utility {
  class File {
  private:
    std::string sourceName;
    std::string sourcePath;
    std::string sourceType;

  public:
    std::vector<std::string> _sourceBuffer;
    std::vector<std::string> _generatedBuffer;

  public:
    File() = delete;
    File(std::string name, std::string path, std::string type);

    void PushBuffer();
    void PopBuffer();

    void LoadBuffer();

    [[nodiscard]] const std::string& GetSourceName() const;
    [[nodiscard]] const std::string& GetSourcePath() const;
    [[nodiscard]] const std::string& GetSourceType() const;

    ~File() = default;
  };
}


#endif //FILE_H
