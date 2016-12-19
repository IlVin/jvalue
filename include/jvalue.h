#pragma once

#include <vector>
#include <map>
#include <string>
#include <deque>

namespace NJValue {

    class IJValue;

    enum EJValueType { JUNDEFINED, JNULL, JBOOL, JINTEGER, JDOUBLE, JSTRING, JARRAY, JMAP };

    class IJValue;

    using bool_t = bool;
    using string_t = std::string;
    using integer_t = long;
    using double_t = double;
    using array_t = std::deque<IJValue>;
    using map_t = std::map<string_t, IJValue>;

    class JSON_UNDEFINED {
        public:
        EJValueType GetType() const;

        inline operator string_t() const { return ""; }
        inline operator bool_t() const { return false; }
        inline operator integer_t() const { return 0; }
        inline operator double_t() const { return 0.0; }
    };

    class JSON_NULL {
        public:

        EJValueType GetType() const;

        inline operator string_t() const { return ""; }
        inline operator bool_t() const { return false; }
        inline operator integer_t() const { return 0; }
        inline operator double_t() const { return 0.0; }
    };

    class JSON_STRING {
        string_t value;
        public:

        JSON_STRING(string_t value = "") : value(value) { }
        JSON_STRING(const JSON_STRING& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return value; }
        inline operator bool_t() const {
            return (value == "" || value == "null" || value == "0" || value == "false")
                ? false
                : true;
        }
        inline operator integer_t() const {
            try {
                return (value == "" || value == "null" || value =="false")
                    ? 0
                    : ( value == "true" )
                        ? 1
                        : std::stol(value);
            } catch (std::invalid_argument) {
                return 0;
            }
        }
        inline operator double_t() const {
            try {
                return (value == "" || value == "null" || value =="false")
                    ? 0.0
                    : ( value =="true" )
                        ? 1.0
                        : std::stod(value);
            } catch (std::invalid_argument) {
                return 0.0;
            }
        }
    };

    class JSON_BOOL {
        bool_t value;
        public:

        JSON_BOOL(bool_t value = false) : value(value) { }
        JSON_BOOL(const JSON_BOOL& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return value ? "true" : "false"; }
        inline operator bool_t() const { return value; }
        inline operator integer_t() const { return value ? 1 : 0; }
        inline operator double_t() const { return value ? 1.0 : 0.0; }
    };

    class JSON_INTEGER {
        integer_t value;
        public:

        JSON_INTEGER(integer_t value = 0) : value(value) { }
        JSON_INTEGER(const JSON_INTEGER& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return std::to_string(value); }
        inline operator bool_t() const { return value == 0 ? false : true; }
        inline operator integer_t() const { return value; }
        inline operator double_t() const { return (double_t)value; }
    };

    class JSON_DOUBLE {
        double_t value;
        public:

        JSON_DOUBLE(double_t value = 0.0) : value(value) { }
        JSON_DOUBLE(const JSON_DOUBLE& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return std::to_string(value); }
        inline operator bool_t() const { return (value >= 0.0 && value < 1.0) ? false : true; }
        inline operator integer_t() const { return (integer_t)value; }
        inline operator double_t() const { return value; }
    };

    class JSON_ARRAY : public std::deque<IJValue> {
        public:

        EJValueType GetType() const;

        inline operator string_t() const { return "ARRAY"; }
        inline operator bool_t() const { return size() == 0 ? false : true; }
        inline operator integer_t() const { return size(); }
        inline operator double_t() const { return (double_t)size(); }
    };

    class IJValue {
    public:
        virtual bool IsUndefined() const { return GetType() == JUNDEFINED; }
        virtual bool IsNull() const { return GetType() == JNULL; }
        virtual bool IsBool() const { return GetType() == JBOOL; }
        virtual bool IsInteger() const { return GetType() == JINTEGER; }
        virtual bool IsDouble() const { return GetType() == JDOUBLE; }
        virtual bool IsString() const { return GetType() == JSTRING; }
        virtual bool IsArray() const { return GetType() == JARRAY; }
        virtual bool IsMap() const { return GetType() == JMAP; }

        virtual EJValueType GetType() const { return JUNDEFINED; }
        virtual string_t AsString() const { return ""; };
        virtual bool_t AsBool() const { return false; };
        virtual integer_t AsInteger() const { return 0; };
        virtual double_t AsDouble() const { return 0; };

        virtual JSON_ARRAY ToArray() const {
            JSON_ARRAY a;
            a.push_back(*this);
            return a;
        }

        virtual ~IJValue() {
        }
    };

    template<class T>
    class TJValue : public IJValue {
        T val;

    public:

        TJValue() {
        }

        TJValue(const T& value) : val(value) {
        }

        TJValue(const integer_t& value) : val(T(JSON_INTEGER(value))) {
        }

        TJValue(const int& value) : val(T(JSON_INTEGER((integer_t)value))) {
        }

        TJValue(const double_t& value) : val(T(JSON_DOUBLE(value))) {
        }

        TJValue(const string_t& value) : val(T(JSON_STRING(value))) {
        }

        TJValue(const char* value) : val(T(JSON_STRING(string_t(value)))) {
        }

        TJValue(const bool_t& value) : val(T(JSON_BOOL(value))) {
        }

        virtual ~TJValue() {
        }

        virtual EJValueType GetType() const {
            return val.GetType();
        }

        virtual const T& GetValue() const {
            return val;
        }

        virtual string_t AsString() const {
            return (string_t)val;
        }

        virtual bool_t AsBool() const {
            return (bool_t)val;
        }

        virtual integer_t AsInteger() const {
            return (integer_t)val;
        }

        virtual double_t AsDouble() const {
            return (double_t)val;
        }

    };

}
