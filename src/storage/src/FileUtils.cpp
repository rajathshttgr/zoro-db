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

IndexUpdateResult FileUtils::updateIndexFile(
    const std::string& path,
    uint32_t id,
    uint64_t offset,
    uint32_t length,
    uint8_t flag_delete // 0 = activate, 1 = delete
) {
    struct Record {
        uint32_t id;
        uint64_t offset;
        uint32_t length;
        uint8_t  flag;
    };

    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);

    // Create file if it does not exist
    if (!file) {
        file.open(path, std::ios::binary | std::ios::out);
        file.close();
        file.open(path, std::ios::binary | std::ios::in | std::ios::out);
    }

    Record rec;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (rec.id != id)
            continue;

        // DELETE 
        if (flag_delete) {
            if (rec.flag == 1)
                return IndexUpdateResult::NoOp; // already deleted

            rec.flag = 1;
            file.seekp(-static_cast<std::streamoff>(sizeof(rec)), std::ios::cur);
            file.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
            file.flush();
            return IndexUpdateResult::Deleted;
        }

        // UPSERT
        bool was_deleted = (rec.flag == 1);

        rec.offset = offset;
        rec.length = length;
        rec.flag   = 0;

        file.seekp(-static_cast<std::streamoff>(sizeof(rec)), std::ios::cur);
        file.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
        file.flush();

        return was_deleted
            ? IndexUpdateResult::Inserted   // revival
            : IndexUpdateResult::Updated;
    }

    // NOT FOUND
    if (flag_delete)
        return IndexUpdateResult::NoOp;

    // INSERT NEW
    Record new_rec{ id, offset, length, 0 };
    file.clear();
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char*>(&new_rec), sizeof(new_rec));
    file.flush();

    return IndexUpdateResult::Inserted;
}


bool FileUtils::findPayloadIndex(
    const std::string& idx_path,
    uint32_t id,
    uint64_t& out_offset,
    uint32_t& out_length
) {
    struct Record {
        uint32_t id;
        uint64_t offset;
        uint32_t length;
        uint8_t  flag;
    };

    std::ifstream file(idx_path, std::ios::binary);
    if (!file.is_open())
        return false;

    Record rec;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (rec.id != id)
            continue;

        // last-write-wins
        if (rec.flag == 1) {
            found = false; // tombstone overrides
        } else {
            out_offset = rec.offset;
            out_length = rec.length;
            found = true;
        }
    }

    return found;
}


std::string FileUtils::readBinaryData(
    const std::string& path,
    uint64_t offset,
    uint32_t length
) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open payload file");
    }

    file.seekg(offset);

    std::string buffer(length, '\0');
    file.read(buffer.data(), length);

    if (!file) {
        throw std::runtime_error("Failed to read payload data");
    }

    return buffer;
}

// This function collects ID's  of active payload points 

bool FileUtils::ListActivePointIds(const std::string &idx_file_path, std::vector<uint32_t> &out_ids, int limit)
{
    // Payload index file records format [id][offset][length][flag]
    struct Record {
        uint32_t id;
        uint64_t offset;
        uint32_t length;
        uint8_t  flag;
    };

    // make sure limit is not less than 1
    if (limit <= 0)
        return true;

    // open index file
    std::ifstream file(idx_file_path, std::ios::binary);
    if (!file.is_open())
        return false;

    Record rec;

    // Read until EOF 
    while (limit > 0 && file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {

        // flag == 0 is active
        if(rec.flag==0){
            out_ids.push_back(rec.id);
            --limit;
        }
    }

    // limit not reached but file records limit reached
    return true;
}

}