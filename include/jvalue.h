#pragma once

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <deque>
#include <iostream>

namespace NJValue {

    class IJValue;

    enum EJValueType { JUNDEFINED, JNULL, JBOOL, JINTEGER, JDOUBLE, JSTRING, JARRAY, JMAP };

    class IJValue;

    using bool_t = bool;
    using string_t = std::string;
    using integer_t = long;
    using double_t = double;
    using array_t = std::deque<IJValue *>;
    using map_t = std::map<string_t, IJValue *>;

    class JSON_UNDEFINED;
    class JSON_NULL;
    class JSON_BOOL;
    class JSON_INTEGER;
    class JSON_DOUBLE;
    class JSON_STRING;
    class JSON_ARRAY;

    class JSON_UNDEFINED {

        public:

        inline JSON_UNDEFINED() { std::cout << "JSON_UNDEFINED()\n"; }
        inline JSON_UNDEFINED(const JSON_UNDEFINED & val) { std::cout << "JSON_UNDEFINED(const JSON_UNDEFINED & val)\n"; }
        inline JSON_UNDEFINED(const JSON_NULL & val) { std::cout << "JSON_UNDEFINED(const JSON_NULL & val)\n"; }
        inline JSON_UNDEFINED(const JSON_BOOL & val) { std::cout << "JSON_UNDEFINED(const JSON_BOOL & val)\n"; }
        inline JSON_UNDEFINED(const JSON_INTEGER & val) { std::cout << "JSON_UNDEFINED(const JSON_INTEGER & val)\n"; }
        inline JSON_UNDEFINED(const JSON_DOUBLE & val) { std::cout << "JSON_UNDEFINED(const JSON_DOUBLE & val)\n"; }
        inline JSON_UNDEFINED(const JSON_STRING & val) { std::cout << "JSON_UNDEFINED(const JSON_STRING & val)\n"; }
        inline JSON_UNDEFINED(const JSON_ARRAY & val) { std::cout << "JSON_UNDEFINED(const JSON_ARRAY & val)\n"; }
        inline ~JSON_UNDEFINED() { std::cout << "~JSON_UNDEFINED()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const { return ""; }
        inline bool_t AsBool() const { return false; }
        inline integer_t AsInteger() const { return 0; }
        inline double_t AsDouble() const { return 0.0; }
        inline array_t AsArray() const { return array_t(); }

    };

    class JSON_NULL {

        public:

        inline JSON_NULL() { std::cout << "JSON_NULL()\n"; }
        inline JSON_NULL(const JSON_UNDEFINED & val) { std::cout << "JSON_NULL(const JSON_UNDEFINED & val)\n"; }
        inline JSON_NULL(const JSON_NULL & val) { std::cout << "JSON_NULL(const JSON_NULL & val)\n"; }
        inline JSON_NULL(const JSON_BOOL & val) { std::cout << "JSON_NULL(const JSON_BOOL & val)\n"; }
        inline JSON_NULL(const JSON_INTEGER & val) { std::cout << "JSON_NULL(const JSON_INTEGER & val)\n"; }
        inline JSON_NULL(const JSON_DOUBLE & val) { std::cout << "JSON_NULL(const JSON_DOUBLE & val)\n"; }
        inline JSON_NULL(const JSON_STRING & val) { std::cout << "JSON_NULL(const JSON_STRING & val)\n"; }
        inline JSON_NULL(const JSON_ARRAY & val) { std::cout << "JSON_NULL(const JSON_ARRAY & val)\n"; }
        inline ~JSON_NULL () { std::cout << "~JSON_NULL()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const { return ""; }
        inline bool_t AsBool() const { return false; }
        inline integer_t AsInteger() const { return 0; }
        inline double_t AsDouble() const { return 0.0; }
        inline array_t AsArray() const { return array_t(); }

    };

    class JSON_BOOL {

        bool_t value;

        public:

        inline JSON_BOOL(const bool_t & val = false) : value(val) { std::cout << "JSON_BOOL(const bool_t & val)\n"; }
        inline JSON_BOOL(const JSON_UNDEFINED & val);
        inline JSON_BOOL(const JSON_NULL & val);
        inline JSON_BOOL(const JSON_BOOL & val);
        inline JSON_BOOL(const JSON_INTEGER & val);
        inline JSON_BOOL(const JSON_DOUBLE & val);
        inline JSON_BOOL(const JSON_STRING & val);
        inline JSON_BOOL(const JSON_ARRAY & val);
        inline ~JSON_BOOL () { std::cout << "~JSON_BOOL()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const { return value ? string_t("true") : string_t("false"); }
        inline bool_t AsBool() const { return value; }
        inline integer_t AsInteger() const { return value ? 1 : 0; }
        inline double_t AsDouble() const { return value ? 1.0 : 0.0; }
        inline array_t AsArray() const { return array_t(); }

    };

    class JSON_INTEGER {

        integer_t value;

        public:

        inline JSON_INTEGER(const integer_t & val = 0) : value(val) { std::cout << "JSON_INTEGER()\n"; }
        inline JSON_INTEGER(const JSON_UNDEFINED & val);
        inline JSON_INTEGER(const JSON_NULL & val);
        inline JSON_INTEGER(const JSON_BOOL & val);
        inline JSON_INTEGER(const JSON_INTEGER & val);
        inline JSON_INTEGER(const JSON_DOUBLE & val);
        inline JSON_INTEGER(const JSON_STRING & val);
        inline JSON_INTEGER(const JSON_ARRAY & val);
        inline ~JSON_INTEGER () { std::cout << "~JSON_INTEGER()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const { return std::to_string(value); }
        inline bool_t AsBool() const { return value == 0 ? false : true; }
        inline integer_t AsInteger() const { return value; }
        inline double_t AsDouble() const { return static_cast<double_t>(value); }
        inline array_t AsArray() const { return array_t(); }

    };

    class JSON_DOUBLE {

        double_t value;

        public:

        inline JSON_DOUBLE(const double_t & val = 0.0) : value(val) { std::cout << "JSON_DOUBLE()\n"; }
        inline JSON_DOUBLE(const JSON_UNDEFINED & val);
        inline JSON_DOUBLE(const JSON_NULL & val);
        inline JSON_DOUBLE(const JSON_BOOL & val);
        inline JSON_DOUBLE(const JSON_INTEGER & val);
        inline JSON_DOUBLE(const JSON_DOUBLE & val);
        inline JSON_DOUBLE(const JSON_STRING & val);
        inline JSON_DOUBLE(const JSON_ARRAY & val);
        inline ~JSON_DOUBLE () { std::cout << "~JSON_DOUBLE()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const { return std::to_string(value); }
        inline bool_t AsBool() const { return (value >= 0.0 && value < 1.0) ? false : true; }
        inline integer_t AsInteger() const { return (integer_t)value; }
        inline double_t AsDouble() const { return value; }
        inline array_t AsArray() const { return array_t(); }

    };

    class JSON_STRING {

        string_t value;

        public:

        inline JSON_STRING(const string_t & val = "") : value(val) { std::cout << "JSON_STRING()\n"; }
        inline JSON_STRING(const JSON_UNDEFINED & val);
        inline JSON_STRING(const JSON_NULL & val);
        inline JSON_STRING(const JSON_BOOL & val);
        inline JSON_STRING(const JSON_INTEGER & val);
        inline JSON_STRING(const JSON_DOUBLE & val);
        inline JSON_STRING(const JSON_STRING & val);
        inline JSON_STRING(const JSON_ARRAY & val);
        inline ~JSON_STRING () { std::cout << "~JSON_STRING()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const {
            return value;
        }

        inline bool_t AsBool() const {
            return (value.empty() || value == "0" || value == "false")
                ? false
                : true;
        }

        inline integer_t AsInteger() const {
            try {
                return (value.empty() || value =="false")
                    ? 0
                    : ( value == "true" )
                        ? 1
                        : std::stol(value);
            } catch (std::invalid_argument) {
                return 0;
            }
        }

        inline double_t AsDouble() const {
            try {
                return (value.empty() || value =="false")
                    ? 0.0
                    : ( value =="true" )
                        ? 1.0
                        : std::stod(value);
            } catch (std::invalid_argument) {
                return 0.0;
            }
        }

        inline array_t AsArray() const { return array_t(); }
    };


    class JSON_ARRAY {

        array_t value;

        public:
        inline JSON_ARRAY() { std::cout << "JSON_ARRAY()\n"; }
        inline JSON_ARRAY(const array_t & val) : value(val) { std::cout << "JSON_ARRAY(const array_t & val)\n"; }
        inline JSON_ARRAY(const JSON_UNDEFINED & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_UNDEFINED & val)\n"; }
        inline JSON_ARRAY(const JSON_NULL & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_NULL & val)\n"; }
        inline JSON_ARRAY(const JSON_BOOL & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_BOOL & val)\n"; }
        inline JSON_ARRAY(const JSON_INTEGER & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_INTEGER & val)\n"; }
        inline JSON_ARRAY(const JSON_DOUBLE & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_DOUBLE & val)\n"; }
        inline JSON_ARRAY(const JSON_STRING & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_STRING & val)\n"; }
        inline JSON_ARRAY(const JSON_ARRAY & val) : value(val.AsArray()) { std::cout << "JSON_ARRAY(const JSON_ARRAY & val)\n"; }
        inline ~JSON_ARRAY () { std::cout << "~JSON_ARRAY()\n"; }

        EJValueType GetType() const;

        inline string_t AsString() const { return std::to_string(value.size()); }
        inline bool_t AsBool() const { return value.size() == 0 ? false : true; }
        inline integer_t AsInteger() const { return value.size(); }
        inline double_t AsDouble() const { return (double_t)value.size(); }
        inline array_t AsArray() const { return value; }
    };

    // BOOL
    inline JSON_BOOL::JSON_BOOL(const JSON_UNDEFINED & val) {
       value = val.AsBool();
       std::cout << "JSON_BOOL(const JSON_UNDEFINED & val)\n";
    }
    inline JSON_BOOL::JSON_BOOL(const JSON_NULL & val) {
       value = val.AsBool();
       std::cout << "JSON_BOOL(const JSON_NULL & val)\n";
    }
    inline JSON_BOOL::JSON_BOOL(const JSON_BOOL & val) {
        value = val.AsBool();
        std::cout << "JSON_BOOL(const JSON_BOOL & val)\n";
    }
    inline JSON_BOOL::JSON_BOOL(const JSON_INTEGER & val) {
        value = val.AsBool();
        std::cout << "JSON_BOOL(const JSON_INTEGER & val)\n";
    }
    inline JSON_BOOL::JSON_BOOL(const JSON_DOUBLE & val) {
        value = val.AsBool();
        std::cout << "JSON_BOOL(const JSON_DOUBLE & val)\n";
    }
    inline JSON_BOOL::JSON_BOOL(const JSON_STRING & val) {
        value = val.AsBool();
        std::cout << "JSON_BOOL(const JSON_STRING & val)\n";
    }
    inline JSON_BOOL::JSON_BOOL(const JSON_ARRAY & val) {
        value = val.AsBool();
        std::cout << "JSON_BOOL(const JSON_ARRAY & val)\n";
    }

    // INTEGER
    inline JSON_INTEGER::JSON_INTEGER(const JSON_UNDEFINED & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_UNDEFINED & val)\n";
    }
    inline JSON_INTEGER::JSON_INTEGER(const JSON_NULL & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_NULL & val)\n";
    }
    inline JSON_INTEGER::JSON_INTEGER(const JSON_BOOL & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_BOOL & val)\n";
    }
    inline JSON_INTEGER::JSON_INTEGER(const JSON_INTEGER & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_INTEGER & val)\n";
    }
    inline JSON_INTEGER::JSON_INTEGER(const JSON_DOUBLE & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_DOUBLE & val)\n";
    }
    inline JSON_INTEGER::JSON_INTEGER(const JSON_STRING & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_STRING & val)\n";
    }
    inline JSON_INTEGER::JSON_INTEGER(const JSON_ARRAY & val) {
        value = val.AsInteger();
        std::cout << "JSON_INTEGER(const JSON_ARRAY & val)\n";
    }

    // DOUBLE
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_UNDEFINED & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_UNDEFINED & val)\n";
    }
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_NULL & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_NULL & val)\n";
    }
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_BOOL & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_BOOL & val)\n";
    }
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_INTEGER & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_INTEGER & val)\n";
    }
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_DOUBLE & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_DOUBLE & val)\n";
    }
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_STRING & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_STRING & val)\n";
    }
    inline JSON_DOUBLE::JSON_DOUBLE(const JSON_ARRAY & val) {
        value = val.AsDouble();
        std::cout << "JSON_DOUBLE(const JSON_ARRAY & val)\n";
    }

    // STRING
    inline JSON_STRING::JSON_STRING(const JSON_UNDEFINED & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_UNDEFINED & val)\n";
    }
    inline JSON_STRING::JSON_STRING(const JSON_NULL & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_NULL & val)\n";
    }
    inline JSON_STRING::JSON_STRING(const JSON_BOOL & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_BOOL & val)\n";
    }
    inline JSON_STRING::JSON_STRING(const JSON_INTEGER & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_INTEGER & val)\n";
    }
    inline JSON_STRING::JSON_STRING(const JSON_DOUBLE & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_DOUBLE & val)\n";
    }
    inline JSON_STRING::JSON_STRING(const JSON_STRING & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_STRING & val)\n";
    }
    inline JSON_STRING::JSON_STRING(const JSON_ARRAY & val) {
        value = val.AsString();
        std::cout << "JSON_STRING(const JSON_ARRAY & val)\n";
    }

    class IJValue {

    protected:

        IJValue() { }

    public:
        inline bool IsUndefined() const { return GetType() == JUNDEFINED; }
        inline bool IsNull() const { return GetType() == JNULL; }
        inline bool IsBool() const { return GetType() == JBOOL; }
        inline bool IsInteger() const { return GetType() == JINTEGER; }
        inline bool IsDouble() const { return GetType() == JDOUBLE; }
        inline bool IsString() const { return GetType() == JSTRING; }
        inline bool IsArray() const { return GetType() == JARRAY; }
        inline bool IsMap() const { return GetType() == JMAP; }

        virtual EJValueType GetType() const = 0;
        virtual string_t AsString() const = 0;
        virtual bool_t AsBool() const = 0;
        virtual integer_t AsInteger() const = 0;
        virtual double_t AsDouble() const = 0;

//        virtual IJValue * GetValue() const = 0;

        virtual ~IJValue() {
        }
    };

    template<class T>
    class TJValue : public IJValue {

        T value;

    public:

        TJValue() {
        }

        TJValue(const T & val) : value(val) {
        }

        TJValue(const integer_t & val) : value(T(JSON_INTEGER(val))) {
        }

        TJValue(const int & val) : value(T(JSON_INTEGER((integer_t)val))) {
        }

        TJValue(const double_t & val) : value(T(JSON_DOUBLE(val))) {
        }

        TJValue(const string_t & val) : value(T(JSON_STRING(val))) {
        }

        TJValue(const char * val) : value(T(JSON_STRING(string_t(val)))) {
        }

        TJValue(const bool_t & val) : value(T(JSON_BOOL(val))) {
        }

        TJValue(const array_t & val) : value(T(JSON_ARRAY(val))) {
        }

        virtual ~TJValue() {
        }

        virtual EJValueType GetType() const {
            return value.GetType();
        }

        virtual string_t AsString() const {
            return value.AsString();
        }

        virtual bool_t AsBool() const {
            return value.AsBool();
        }

        virtual integer_t AsInteger() const {
            return value.AsInteger();
        }

        virtual double_t AsDouble() const {
            return value.AsDouble();
        }

//        virtual array_t AsArray() const {
//            return static_cast<array_t>(value);
//        };

    };

    inline EJValueType JSON_UNDEFINED::GetType() const { return JUNDEFINED; }
    inline EJValueType JSON_NULL::GetType() const { return JNULL; }
    inline EJValueType JSON_INTEGER::GetType() const { return JINTEGER; }
    inline EJValueType JSON_STRING::GetType() const { return JSTRING; }
    inline EJValueType JSON_DOUBLE::GetType() const { return JDOUBLE; }
    inline EJValueType JSON_BOOL::GetType() const { return JBOOL; }
    inline EJValueType JSON_ARRAY::GetType() const { return JARRAY; }
}
