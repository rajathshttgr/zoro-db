#include "config.hpp"
#include <filesystem>
#include <yaml-cpp/yaml.h>

Config Config::load(const std::string& filename){
    YAML::Node config = YAML::LoadFile(filename);

    auto configPath = std::filesystem::canonical(filename);
    auto base = configPath.parent_path();

    Config cfg;

    cfg.storage.storage_path = (base / config["storage"]["storage_path"].as<std::string>()).string();
    cfg.storage.snapshot_path = (base / config["storage"]["snapshot_path"].as<std::string>()).string();

    cfg.log_level=config["logging"]["level"].as<std::string>();
    cfg.http_port=config["network"]["http_port"].as<int>();

    return cfg;
}