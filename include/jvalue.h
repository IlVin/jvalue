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

        inline operator std::string() const { return ""; }
        inline operator bool() const { return false; }
        inline operator long() const { return 0; }
        inline operator double() const { return 0.0; }
    };

    class JSON_NULL {
        public:

        EJValueType GetType() const;

        inline operator std::string() const { return ""; }
        inline operator bool() const { return false; }
        inline operator long() const { return 0; }
        inline operator double() const { return 0.0; }
    };

    class JSON_STRING {
        std::string value;
        public:

        JSON_STRING(std::string value = "") : value(value) { }
        JSON_STRING(const JSON_STRING& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator std::string() const { return value; }
        inline operator bool() const {
            return (value == "" || value == "null" || value == "0" || value == "false")
                ? false
                : true;
        }
        inline operator long() const {
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
        inline operator double() const {
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
        bool value;
        public:

        JSON_BOOL(bool value = false) : value(value) { }
        JSON_BOOL(const JSON_BOOL& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator std::string() const { return value ? "true" : "false"; }
        inline operator bool() const { return value; }
        inline operator long() const { return value ? 1 : 0; }
        inline operator double() const { return value ? 1.0 : 0.0; }
    };

    class JSON_INTEGER {
        long value;
        public:

        JSON_INTEGER(long value = 0) : value(value) { }
        JSON_INTEGER(const JSON_INTEGER& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator std::string() const { return std::to_string(value); }
        inline operator bool() const { return value == 0 ? false : true; }
        inline operator long() const { return value; }
        inline operator double() const { return (double)value; }
    };

    class JSON_DOUBLE {
        double value;
        public:

        JSON_DOUBLE(double value = 0.0) : value(value) { }
        JSON_DOUBLE(const JSON_DOUBLE& val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator std::string() const { return std::to_string(value); }
        inline operator bool() const { return (value >= 0.0 && value < 1.0) ? false : true; }
        inline operator long() const { return (long)value; }
        inline operator double() const { return value; }
    };

    class JSON_ARRAY : public std::deque<IJValue> {
        public:

        EJValueType GetType() const;

        inline operator std::string() const { return "ARRAY"; }
        inline operator bool() const { return size() == 0 ? false : true; }
        inline operator long() const { return size(); }
        inline operator double() const { return (double)size(); }
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
        virtual std::string AsString() const { return ""; };
        virtual bool AsBool() const { return false; };
        virtual long AsInteger() const { return 0; };
        virtual double AsDouble() const { return 0; };

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

        TJValue(const long& value) : val(T(JSON_INTEGER(value))) {
        }

        TJValue(const int& value) : val(T(JSON_INTEGER(value))) {
        }

        TJValue(const double& value) : val(T(JSON_DOUBLE(value))) {
        }

        TJValue(const std::string& value) : val(T(JSON_STRING(value))) {
        }

        TJValue(const char* value) : val(T(JSON_STRING(std::string(value)))) {
        }

        TJValue(const bool& value) : val(T(JSON_BOOL(value))) {
        }

        virtual ~TJValue() {
        }

        virtual EJValueType GetType() const {
            return val.GetType();
        }

        virtual const T& GetValue() const {
            return val;
        }

        virtual std::string AsString() const {
            return (std::string)val;
        }

        virtual bool AsBool() const {
            return (bool)val;
        }

        virtual long AsInteger() const {
            return (long)val;
        }

        virtual double AsDouble() const {
            return (double)val;
        }

    };

}
