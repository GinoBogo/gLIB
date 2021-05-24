////////////////////////////////////////////////////////////////////////////////
/// \file      GOptions.hpp
/// \version   0.2
/// \date      November 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GOPTIONS_HPP
#define GOPTIONS_HPP

#include <any>
#include <list>
#include <map>
#include <string>

class GOptions : public std::map<std::string, std::any> {
    public:
    struct Pair {
        Pair(const std::string &_label, const std::string &_value) {
            label = _label;
            value = _value;
        };
        std::string label;
        std::string value;
    };

    typedef std::list<Pair> Pairs;

    struct Section {
        Section(const std::string &_title) {
            title = _title;
        };
        std::string title;
        Pairs       pairs;
    };

    typedef std::list<Section> Sections;

    template <typename T> void Insert(const std::string &label, const std::any &value);

    template <typename T> T Get(const std::string &label);

    Pairs ToPairs();

    Sections ToSections();

    bool Read(const std::string &filename);

    bool Write(const std::string &filename);

    GOptions &operator+=(const GOptions &options);
};

template <typename T> void GOptions::Insert(const std::string &label, const std::any &value) {
    if (value.type() == typeid(T)) {
        this->insert_or_assign(label, std::any_cast<T>(value));
    }
    else {
        if constexpr (std::is_same_v<T, std::string>) {
            if (value.type() == typeid(const char *)) {
                this->insert_or_assign(label, std::string(std::any_cast<const char *>(value)));
            }
        }
        else {
            if (value.type() == typeid(bool)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<bool>(value)));
            }
            else if (value.type() == typeid(char)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<char>(value)));
            }
            else if (value.type() == typeid(unsigned char)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<unsigned char>(value)));
            }
            else if (value.type() == typeid(short)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<short>(value)));
            }
            else if (value.type() == typeid(unsigned short)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<unsigned short>(value)));
            }
            else if (value.type() == typeid(int)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<int>(value)));
            }
            else if (value.type() == typeid(unsigned int)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<unsigned int>(value)));
            }
            else if (value.type() == typeid(long)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<long>(value)));
            }
            else if (value.type() == typeid(unsigned long)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<unsigned long>(value)));
            }
            else if (value.type() == typeid(long long)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<long long>(value)));
            }
            else if (value.type() == typeid(unsigned long long)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<unsigned long long>(value)));
            }
            else if (value.type() == typeid(float)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<float>(value)));
            }
            else if (value.type() == typeid(double)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<double>(value)));
            }
            else if (value.type() == typeid(long double)) {
                this->insert_or_assign(label, static_cast<T>(std::any_cast<long double>(value)));
            }
        }
    }
}

template <typename T> T GOptions::Get(const std::string &label) {
    T type{};

    auto found{this->find(label)};
    if (found != this->end()) {
        const auto &value{found->second};
        if (value.type() == typeid(T)) {
            type = std::any_cast<T>(value);
        }
        else {
            if constexpr (!std::is_same_v<T, std::string>) {
                if (value.type() == typeid(bool)) {
                    type = static_cast<T>(std::any_cast<bool>(value));
                }
                else if (value.type() == typeid(char)) {
                    type = static_cast<T>(std::any_cast<char>(value));
                }
                else if (value.type() == typeid(unsigned char)) {
                    type = static_cast<T>(std::any_cast<unsigned char>(value));
                }
                else if (value.type() == typeid(short)) {
                    type = static_cast<T>(std::any_cast<short>(value));
                }
                else if (value.type() == typeid(unsigned short)) {
                    type = static_cast<T>(std::any_cast<unsigned short>(value));
                }
                else if (value.type() == typeid(int)) {
                    type = static_cast<T>(std::any_cast<int>(value));
                }
                else if (value.type() == typeid(unsigned int)) {
                    type = static_cast<T>(std::any_cast<unsigned int>(value));
                }
                else if (value.type() == typeid(long)) {
                    type = static_cast<T>(std::any_cast<long>(value));
                }
                else if (value.type() == typeid(unsigned long)) {
                    type = static_cast<T>(std::any_cast<unsigned long>(value));
                }
                else if (value.type() == typeid(long long)) {
                    type = static_cast<T>(std::any_cast<long long>(value));
                }
                else if (value.type() == typeid(unsigned long long)) {
                    type = static_cast<T>(std::any_cast<unsigned long long>(value));
                }
                else if (value.type() == typeid(float)) {
                    type = static_cast<T>(std::any_cast<float>(value));
                }
                else if (value.type() == typeid(double)) {
                    type = static_cast<T>(std::any_cast<double>(value));
                }
                else if (value.type() == typeid(long double)) {
                    type = static_cast<T>(std::any_cast<long double>(value));
                }
            }
        }
    }
    return type;
}

#endif // GOPTIONS_HPP