#pragma once

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <deque>

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

    class JSON_UNDEFINED {

        public:

        EJValueType GetType() const;

        inline operator string_t() const { return ""; }
        inline operator bool_t() const { return false; }
        inline operator integer_t() const { return 0; }
        inline operator double_t() const { return 0.0; }

        operator array_t() const;
    };

    class JSON_NULL {

        public:

        EJValueType GetType() const;

        inline operator string_t() const { return ""; }
        inline operator bool_t() const { return false; }
        inline operator integer_t() const { return 0; }
        inline operator double_t() const { return 0.0; }

        operator array_t() const;
    };

    class JSON_STRING {

        string_t value;

        public:

        explicit inline JSON_STRING(const string_t & value = "") : value(value) { }
        explicit inline JSON_STRING(const JSON_STRING & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const {
            return value;
        }

        inline operator bool_t() const {
            return (value.empty() || value == "0" || value == "false")
                ? false
                : true;
        }

        inline operator integer_t() const {
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

        inline operator double_t() const {
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

        operator array_t() const;
    };

    class JSON_BOOL {

        bool_t value;

        public:

        explicit inline JSON_BOOL(const bool_t & value = false) : value(value) { }
        explicit inline JSON_BOOL(const JSON_BOOL & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return value ? "true" : "false"; }
        inline operator bool_t() const { return value; }
        inline operator integer_t() const { return value ? 1 : 0; }
        inline operator double_t() const { return value ? 1.0 : 0.0; }

        operator array_t() const;
    };

    class JSON_INTEGER {

        integer_t value;

        public:

        explicit inline JSON_INTEGER(const integer_t & value = 0) : value(value) { }
        explicit inline JSON_INTEGER(const JSON_INTEGER & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return std::to_string(value); }
        inline operator bool_t() const { return value == 0 ? false : true; }
        inline operator integer_t() const { return value; }
        inline operator double_t() const { return (double_t)value; }

        operator array_t() const;
    };

    class JSON_DOUBLE {

        double_t value;

        public:

        explicit inline JSON_DOUBLE(const double_t & value = 0.0) : value(value) { }
        explicit inline JSON_DOUBLE(const JSON_DOUBLE & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return std::to_string(value); }
        inline operator bool_t() const { return (value >= 0.0 && value < 1.0) ? false : true; }
        inline operator integer_t() const { return (integer_t)value; }
        inline operator double_t() const { return value; }

        operator array_t() const;
    };

    class JSON_ARRAY {

        char buffer[20];
        array_t value;

        public:
        explicit inline JSON_ARRAY() { }
        explicit inline JSON_ARRAY(const array_t & value) : value(value) { }
        explicit inline JSON_ARRAY(const JSON_ARRAY & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const {
            snprintf((char*)buffer, 20, "ARRAY(0x%zx)", (size_t)this);
            return string_t(buffer);
        }
        inline operator bool_t() const { return value.size() == 0 ? false : true; }
        inline operator integer_t() const { return value.size(); }
        inline operator double_t() const { return (double_t)value.size(); }

        operator array_t() const;
    };

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
            return (string_t)value;
        }

        virtual bool_t AsBool() const {
            return (bool_t)value;
        }

        virtual integer_t AsInteger() const {
            return (integer_t)value;
        }

        virtual double_t AsDouble() const {
            return (double_t)value;
        }

        const TJValue<JSON_ARRAY> & AsArray();

    };

    template<>
    inline const TJValue<JSON_ARRAY> & TJValue<JSON_ARRAY>::AsArray() {
        return *this;
    }
/*
    template<>
    inline TJValue<JSON_ARRAY> TJValue<JSON_MAP>::AsArray() {
        return TJArray();
    }
*/
    /*
    TJValue<JSON_ARRAY> g;
    template<class T>
    inline const TJValue<JSON_ARRAY> & TJValue<T>::AsArray() {
        TJValue<JSON_ARRAY>  array; // = new TJValue<JSON_ARRAY>();
        (array.GetValue()).push_back(*this);
        return array;
    }

    */

    inline JSON_ARRAY::operator array_t() const {
        return value;
    }

    inline JSON_UNDEFINED::operator array_t() const {
        return array_t();
    }

    inline JSON_NULL::operator array_t() const {
        array_t a;
        a.push_back(new TJValue<JSON_NULL>());
        return a;
    }

    inline JSON_INTEGER::operator array_t() const {
        array_t a;
        a.push_back(new TJValue<JSON_INTEGER>(value));
        return a;
    }

    inline JSON_STRING::operator array_t() const {
        array_t a;
        a.push_back(new TJValue<JSON_STRING>(value));
        return a;
    }

    inline JSON_DOUBLE::operator array_t() const {
        array_t a;
        a.push_back(new TJValue<JSON_DOUBLE>(value));
        return a;
    }

    inline JSON_BOOL::operator array_t() const {
        array_t a;
        a.push_back(new TJValue<JSON_BOOL>(value));
        return a;
    }

    inline EJValueType JSON_UNDEFINED::GetType() const { return JUNDEFINED; }
    inline EJValueType JSON_NULL::GetType() const { return JNULL; }
    inline EJValueType JSON_INTEGER::GetType() const { return JINTEGER; }
    inline EJValueType JSON_STRING::GetType() const { return JSTRING; }
    inline EJValueType JSON_DOUBLE::GetType() const { return JDOUBLE; }
    inline EJValueType JSON_BOOL::GetType() const { return JBOOL; }
    inline EJValueType JSON_ARRAY::GetType() const { return JARRAY; }
}
