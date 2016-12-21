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
    using array_t = std::deque<IJValue>;
    using map_t = std::map<string_t, IJValue>;

    class JSON_UNDEFINED {

        public:

        EJValueType GetType() const;

        inline void Swap (JSON_UNDEFINED & j) { }
        inline JSON_UNDEFINED & operator = (JSON_UNDEFINED j) {
            this->Swap(j);
            return *this;
        }

        inline operator string_t() const { return ""; }
        inline operator bool_t() const { return false; }
        inline operator integer_t() const { return 0; }
        inline operator double_t() const { return 0.0; }

        inline void push_back(const IJValue & val) { };
        inline void push_front(const IJValue & val) { };
        inline void pop_back() { };
        inline void pop_front() { };
        inline size_t size() { return 1; };
    };

    class JSON_NULL : public JSON_UNDEFINED {

        public:

        EJValueType GetType() const;

        inline void Swap (JSON_NULL & j) { }
        inline JSON_NULL & operator = (JSON_NULL j) {
            this->Swap(j);
            return *this;
        }

        inline operator string_t() const { return ""; }
        inline operator bool_t() const { return false; }
        inline operator integer_t() const { return 0; }
        inline operator double_t() const { return 0.0; }
    };

    class JSON_STRING : public JSON_UNDEFINED {

        string_t value;

        public:

        explicit inline JSON_STRING(const string_t & value = "") : value(value) { }
        explicit inline JSON_STRING(const JSON_STRING & val) : value(val.value) { }

        EJValueType GetType() const;

        inline void Swap (JSON_STRING & str) {
            std::swap(value, str.value);
        }

        inline JSON_STRING & operator = (JSON_STRING str) {
            this->Swap(str);
            return *this;
        }

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

        inline size_t size() {
            return value.size();
        }
    };

    class JSON_BOOL : public JSON_UNDEFINED {

        bool_t value;

        public:

        explicit inline JSON_BOOL(const bool_t & value = false) : value(value) { }
        explicit inline JSON_BOOL(const JSON_BOOL & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return value ? "true" : "false"; }
        inline operator bool_t() const { return value; }
        inline operator integer_t() const { return value ? 1 : 0; }
        inline operator double_t() const { return value ? 1.0 : 0.0; }
    };

    class JSON_INTEGER : public JSON_UNDEFINED {

        integer_t value;

        public:

        explicit inline JSON_INTEGER(const integer_t & value = 0) : value(value) { }
        explicit inline JSON_INTEGER(const JSON_INTEGER & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return std::to_string(value); }
        inline operator bool_t() const { return value == 0 ? false : true; }
        inline operator integer_t() const { return value; }
        inline operator double_t() const { return (double_t)value; }
    };

    class JSON_DOUBLE : public JSON_UNDEFINED {

        double_t value;

        public:

        explicit inline JSON_DOUBLE(const double_t & value = 0.0) : value(value) { }
        explicit inline JSON_DOUBLE(const JSON_DOUBLE & val) : value(val.value) { }

        EJValueType GetType() const;

        inline operator string_t() const { return std::to_string(value); }
        inline operator bool_t() const { return (value >= 0.0 && value < 1.0) ? false : true; }
        inline operator integer_t() const { return (integer_t)value; }
        inline operator double_t() const { return value; }
    };

    class JSON_ARRAY : public std::deque<IJValue> {
        char buffer[20];
        public:

        EJValueType GetType() const;

        inline operator string_t() const {
            snprintf((char*)buffer, 20, "ARRAY(0x%x)", (size_t)this);
            return string_t(buffer);
        }
        inline operator bool_t() const { return size() == 0 ? false : true; }
        inline operator integer_t() const { return size(); }
        inline operator double_t() const { return (double_t)size(); }
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

        virtual EJValueType GetType() const { return JUNDEFINED; }
        virtual string_t AsString() const { return ""; };
        virtual bool_t AsBool() const { return false; };
        virtual integer_t AsInteger() const { return 0; };
        virtual double_t AsDouble() const { return 0; };

        virtual void push_back(const IJValue & val) { };
        virtual void push_front(const IJValue & val) { };
        virtual void pop_back() { };
        virtual void pop_front() { };
        virtual size_t size() { return 0; };

        virtual JSON_ARRAY AsArray() const {
            JSON_ARRAY a;
            a.push_back(*this);
            return a;
        }

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

        virtual ~TJValue() {
        }

        virtual EJValueType GetType() const {
            return value.GetType();
        }

        virtual const T & GetValue() const {
            return value;
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

        virtual void push_back(const IJValue & val) {
            value.push_back(val);
        };

        virtual void push_front(const IJValue & val) {
            value.push_front(val);
        };

        virtual void pop_back() {
            value.pop_back();
        };

        virtual void pop_front() {
            value.pop_front();
        };

        virtual size_t size() {
            return value.size();
        };

    };

    inline EJValueType JSON_UNDEFINED::GetType() const { return JUNDEFINED; }
    inline EJValueType JSON_NULL::GetType() const { return JNULL; }
    inline EJValueType JSON_INTEGER::GetType() const { return JINTEGER; }
    inline EJValueType JSON_STRING::GetType() const { return JSTRING; }
    inline EJValueType JSON_DOUBLE::GetType() const { return JDOUBLE; }
    inline EJValueType JSON_BOOL::GetType() const { return JBOOL; }
    inline EJValueType JSON_ARRAY::GetType() const { return JARRAY; }
}
