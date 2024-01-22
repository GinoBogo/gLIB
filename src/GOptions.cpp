////////////////////////////////////////////////////////////////////////////////
/// \file      GOptions.cpp
/// \version   0.2
/// \date      November 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GOptions.hpp"

#include <filesystem> // exists, file_size, is_directory, is_regular_file, path
#include <fmt/core.h> // format
#include <fstream>    // ifstream, ofstream
#include <regex>      // regex, regex_match, sregex_token_iterator

auto split = [](const std::string& data, const std::string& regex) {
    std::vector<std::string> tokens;

    std::regex                 re{regex};
    std::sregex_token_iterator next{data.begin(), data.end(), re, -1};
    std::sregex_token_iterator last;

    while (next != last) {
        tokens.push_back(next->str());
        ++next;
    }

    auto filter = [](const std::string s) {
        return (s.size() == 0);
    };
    auto junks{std::remove_if(tokens.begin(), tokens.end(), filter)};
    tokens.erase(junks, tokens.end());
    return tokens;
};

auto join = [](const std::vector<std::string>& data, const std::string& delimiter) {
    std::stringstream result;

    auto size{data.size() - 1};
    for (decltype(size) i{0}; i <= size; ++i) {
        result << data[i];
        if (i != size) {
            result << delimiter;
        }
    }
    return result.str();
};

template <typename T> auto expand_and_check(const std::string& value, T& type) {
    if (std::is_signed_v<T>) {
        auto n1{std::strtoll(value.c_str(), 0, 10)};
        auto n2{static_cast<T>(n1)};
        auto n3{static_cast<long long>(n2)};
        if (n1 == n3 && errno != ERANGE) {
            type = n2;
            return true;
        }
    }
    else {
        auto n1{std::strtoull(value.c_str(), 0, 10)};
        auto n2{static_cast<T>(n1)};
        auto n3{static_cast<unsigned long long>(n2)};
        if (n1 == n3 && errno != ERANGE) {
            type = n2;
            return true;
        }
    }
    return false;
}

template <typename T> auto string_to_type(const std::string& value, bool& is_valid) {
    T type{};
    is_valid = false;

    if constexpr (std::is_same_v<T, bool>) {
        if (value == "0" || value == "false" || value == "FALSE") {
            type     = false;
            is_valid = true;
        }
        else if (value == "1" || value == "true" || value == "TRUE") {
            type     = true;
            is_valid = true;
        }
        return type;
    }

    static auto integers{std::regex("^((-?)|(\\+?))\\d+(u?l?l?)$")};

    if (std::regex_match(value, integers)) {

        if constexpr (std::is_same_v<T, char>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, unsigned char>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, short>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, unsigned short>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, int>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, unsigned int>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, long>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, unsigned long>) {
            is_valid = expand_and_check<T>(value, type);
            return type;
        }

        if constexpr (std::is_same_v<T, long long>) {
            type     = std::stoll(value);
            is_valid = true;
            return type;
        }

        if constexpr (std::is_same_v<T, unsigned long long>) {
            type     = std::strtoull(value.c_str(), 0, 10);
            is_valid = true;
            return type;
        }
    }

    static auto decimals{
        std::regex("^((-?)|(\\+?))((\\d+\\.\\d*)|(\\d*\\.\\d+))(((e)|(E))((-?)|(\\+?))0?\\d+|)$")};

    if (std::regex_match(value, decimals)) {

        if constexpr (std::is_same_v<T, float>) {
            try {
                type     = std::stof(value);
                is_valid = true;
            }
            catch (const std::invalid_argument&) {
            }
            catch (const std::out_of_range&) {
            };
            return type;
        }

        if constexpr (std::is_same_v<T, double>) {
            try {
                type     = std::stod(value);
                is_valid = true;
            }
            catch (const std::invalid_argument&) {
            }
            catch (const std::out_of_range&) {
            };
            return type;
        }

        if constexpr (std::is_same_v<T, long double>) {
            try {
                type     = std::stold(value);
                is_valid = true;
            }
            catch (const std::invalid_argument&) {
            }
            catch (const std::out_of_range&) {
            };
            return type;
        }
    }

    if constexpr (std::is_same_v<T, std::string>) {
        try {
            if constexpr (!std::is_arithmetic_v<T>) {
                type     = value;
                is_valid = true;
            }
        }
        catch (const std::invalid_argument&) {
        };
        return type;
    }

    return type;
}

GOptions::Pairs GOptions::ToPairs() {
    Pairs pairs{};

    for (auto it{this->begin()}; it != this->end(); ++it) {
        const auto& label{it->first};
        const auto& value{it->second};

        if (value.type() == typeid(bool)) {
            Pair pair{label, (std::any_cast<bool>(value)) ? "true" : "false"};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(char)) {
            Pair pair{label, std::to_string(std::any_cast<char>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(unsigned char)) {
            Pair pair{label, std::to_string(std::any_cast<unsigned char>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(short)) {
            Pair pair{label, std::to_string(std::any_cast<short>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(unsigned short)) {
            Pair pair{label, std::to_string(std::any_cast<unsigned short>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(int)) {
            Pair pair{label, std::to_string(std::any_cast<int>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(unsigned int)) {
            Pair pair{label, std::to_string(std::any_cast<unsigned int>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(long)) {
            Pair pair{label, std::to_string(std::any_cast<long>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(unsigned long)) {
            Pair pair{label, std::to_string(std::any_cast<unsigned long>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(long long)) {
            Pair pair{label, std::to_string(std::any_cast<long long>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(unsigned long long)) {
            Pair pair{label, std::to_string(std::any_cast<unsigned long long>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(float)) {
            Pair pair{label, std::to_string(std::any_cast<float>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(double)) {
            Pair pair{label, std::to_string(std::any_cast<double>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(long double)) {
            Pair pair{label, std::to_string(std::any_cast<long double>(value))};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(std::string)) {
            Pair pair{label, std::any_cast<std::string>(value)};
            pairs.push_back(pair);
            continue;
        }
        if (value.type() == typeid(const char*)) {
            Pair pair{label, std::string(std::any_cast<const char*>(value))};
            pairs.push_back(pair);
            continue;
        }
    }

    return pairs;
}

GOptions::Sections GOptions::ToSections() {
    Sections sections{};

    auto pairs{ToPairs()};
    for (auto it{pairs.begin()}; it != pairs.end(); ++it) {
        auto tokens{split(it->label, "[. \\t]")};
        auto tokens_size{tokens.size()};
        if (tokens_size >= 1U) {
            auto                     index(static_cast<ssize_t>(tokens_size - 1));
            std::vector<std::string> upper(tokens.begin(), tokens.begin() + index);
            std::vector<std::string> lower(tokens.begin() + index, tokens.end());

            const auto title{join(upper, ".")};
            const auto label{join(lower, ".")};
            const auto _pair{Pair(label, it->value)};

            auto found{std::find_if(sections.begin(), sections.end(), [title](const Section s) {
                return (s.title == title);
            })};
            if (found == sections.end()) {
                auto _section{Section(title)};
                _section.pairs.push_back(_pair);
                sections.push_back(_section);
            }
            else {
                found->pairs.push_back(_pair);
            }
        }
    }

    return sections;
}

bool GOptions::Read(const std::string& filename) {
    const auto filepath{std::filesystem::path(filename)};

    if (std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath)) {
        auto bytes{std::filesystem::file_size(filepath)};
        if (bytes > 0) {
            Sections sections;

            std::ifstream stream(filename);
            std::string   line;
            while (std::getline(stream, line)) {
                auto check_1{line.find("[")};
                auto check_2{line.rfind("]")};
                if (check_1 < check_2) {
                    auto tokens{split(line, "[\\[\\] \\t]")};
                    auto title{tokens[0]};

                    auto filter = [title](const Section s) {
                        return (s.title == title);
                    };
                    auto found{std::find_if(sections.begin(), sections.end(), filter)};
                    if (found == sections.end()) {
                        auto section{Section(title)};
                        sections.push_back(section);
                    }
                }
                else {
                    auto tokens{split(line, "[= \\t]")};
                    if (tokens.size() == 2) {
                        auto pair{Pair(tokens[0], tokens[1])};
                        auto last{--sections.end()};
                        last->pairs.push_back(pair);
                    }
                }
            }
            stream.close();

            for (const auto& item : sections) {
                for (const auto& pair : item.pairs) {
                    bool     is_valid;
                    std::any value;

                    value = string_to_type<bool>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<char>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<unsigned char>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<short>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<unsigned short>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<int>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<unsigned int>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<long>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<unsigned long>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<long long>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<unsigned long long>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<float>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<double>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<long double>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }
                    value = string_to_type<std::string>(pair.value, is_valid);
                    if (is_valid) {
                        goto jmp_insert_or_assign;
                    }

jmp_insert_or_assign:
                    if (is_valid) {
                        auto label{fmt::format("{}.{}", item.title, pair.label)};
                        this->insert_or_assign(label, value);
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool GOptions::Write(const std::string& filename) {
    const auto filepath{std::filesystem::path(filename)};

    if (!std::filesystem::is_directory(filepath)) {
        auto stream{std::ofstream(filename)};
        auto sections{ToSections()};

        for (const auto& section : sections) {
            stream << fmt::format("[{}]", section.title) << std::endl;
            for (const auto& pair : section.pairs) {
                stream << fmt::format("{} = {}", pair.label, pair.value) << std::endl;
            }
            stream << std::endl;
        }
        stream.close();
        return true;
    }

    return false;
}

GOptions& GOptions::operator+=(const GOptions& options) {
    if (this != &options) {
        for (const auto& pair : options) {
            this->insert_or_assign(pair.first, pair.second);
        }
    }
    return *this;
}
