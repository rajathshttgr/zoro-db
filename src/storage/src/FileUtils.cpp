#include "FileUtils.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace fs=std::filesystem;

namespace zoro::storage{

bool FileUtils::Exists(const std::string& path){
    return fs::exists(path);
}

bool FileUtils::CreateFileIfNotExists(const std::string& path) {
    try {
        fs::path filePath(path);

        if (filePath.has_parent_path()) {
            fs::create_directories(filePath.parent_path());
        }

        if (!fs::exists(filePath)) {
            std::ofstream ofs(filePath);
            if (!ofs) {
                return false;
            }
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool FileUtils::WriteText(const std::string& path, const std::string& content){
    std::ofstream out(path);
    if(!out) return false;
    out<<content;
    return true;
}

bool FileUtils::WriteBinary(const std::string& path, const char* data, size_t size)
{
    std::ofstream ofs(path, std::ios::binary | std::ios::app);
    if (!ofs) return false;

    ofs.write(data, size);
    return ofs.good();
}

std::string FileUtils::ReadText(const std::string& path){
    std::ifstream in(path);

    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
   
}

uint64_t FileUtils::appendBinaryData(const std::string& path,const char* data, uint64_t size_bytes){
    std::ofstream out(path, std::ios::binary | std::ios::app);

    if (!out) {
        throw std::runtime_error("Failed to open file");
    }

    // get offset 
    uint64_t offset = out.tellp();

    out.write(reinterpret_cast<const char*>(data), size_bytes);

    if (!out) {
        throw std::runtime_error("Write failed");
    }

    out.flush();

    return offset;
}


bool FileUtils::updateIndexFile(
    const std::string& path,
    uint32_t id,
    uint64_t offset,
    uint32_t length,
    uint8_t flag
) {
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);

    // If file doesn't exist, create it
    if (!file) {
        file.open(path, std::ios::binary | std::ios::out);
        file.close();
        file.open(path, std::ios::binary | std::ios::in | std::ios::out);
    }

    const std::streamoff record_size =
        sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t) + sizeof(uint8_t);

    uint32_t existing_id;
    uint64_t existing_offset;
    uint32_t existing_length;
    uint8_t existing_flag;

    while (file.read(reinterpret_cast<char*>(&existing_id), sizeof(existing_id))) {

        std::streampos record_pos = file.tellg() - record_size;

        file.read(reinterpret_cast<char*>(&existing_offset), sizeof(existing_offset));
        file.read(reinterpret_cast<char*>(&existing_length), sizeof(existing_length));
        file.read(reinterpret_cast<char*>(&existing_flag), sizeof(existing_flag));

        if (existing_id == id) {
            // overwrite in place
            file.seekp(record_pos);

            file.write(reinterpret_cast<const char*>(&id), sizeof(id));
            file.write(reinterpret_cast<const char*>(&offset), sizeof(offset));
            file.write(reinterpret_cast<const char*>(&length), sizeof(length));
            file.write(reinterpret_cast<const char*>(&flag), sizeof(flag));

            file.flush();
            return true;
        }
    }

    // not found → append
    file.clear();
    file.seekp(0, std::ios::end);

    file.write(reinterpret_cast<const char*>(&id), sizeof(id));
    file.write(reinterpret_cast<const char*>(&offset), sizeof(offset));
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(reinterpret_cast<const char*>(&flag), sizeof(flag));

    file.flush();
    return true;
}


}