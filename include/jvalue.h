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

    enum EJValueType { JUNDEFINED = 1, JNULL, JBOOL, JINTEGER, JDOUBLE, JSTRING, JARRAY, JMAP };


    using bool_t = bool;
    using string_t = std::string;
    using integer_t = long;
    using double_t = double;
    using array_t = std::deque<IJValue *>;
    using map_t = std::map<string_t, IJValue *>;

    class IJSON_VALUE;
    class JSON_UNDEFINED;
    class JSON_NULL;
    class JSON_BOOL;
    class JSON_INTEGER;
    class JSON_DOUBLE;
    class JSON_STRING;
    class JSON_ARRAY;

    class IJSON_VALUE {
        EJValueType type;

        public:
        inline IJSON_VALUE(EJValueType type): type(type) { }
        inline virtual ~IJSON_VALUE() { std::cout << "~IJSON_VALUE()\n"; }

        inline EJValueType GetType() const { return type; }

        inline virtual string_t AsString() const = 0;
        inline virtual bool_t AsBool() const = 0;
        inline virtual integer_t AsInteger() const = 0;
        inline virtual double_t AsDouble() const = 0;
        inline virtual array_t AsArray() const = 0;
    };

    class JSON_UNDEFINED: public IJSON_VALUE {

        public:
        inline JSON_UNDEFINED() : IJSON_VALUE(JUNDEFINED) { std::cout << "JSON_UNDEFINED()\n"; }
        inline JSON_UNDEFINED(const IJSON_VALUE & val) : IJSON_VALUE(JUNDEFINED) { std::cout << "JSON_UNDEFINED(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_UNDEFINED() { std::cout << "~JSON_UNDEFINED()\n"; }

        inline virtual string_t AsString() const { return ""; }
        inline virtual bool_t AsBool() const { return false; }
        inline virtual integer_t AsInteger() const { return 0; }
        inline virtual double_t AsDouble() const { return 0.0; }
        inline virtual array_t AsArray() const { return array_t(); }

    };

    class JSON_NULL: public IJSON_VALUE {

        public:
        inline JSON_NULL() : IJSON_VALUE(JNULL) { std::cout << "JSON_NULL()\n"; }
        inline JSON_NULL(const IJSON_VALUE & val) : IJSON_VALUE(JNULL) { std::cout << "JSON_NULL(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_NULL () { std::cout << "~JSON_NULL()\n"; }

        inline virtual string_t AsString() const { return ""; }
        inline virtual bool_t AsBool() const { return false; }
        inline virtual integer_t AsInteger() const { return 0; }
        inline virtual double_t AsDouble() const { return 0.0; }
        inline virtual array_t AsArray() const { return array_t(); }

    };

    class JSON_BOOL: public IJSON_VALUE {

        bool_t value;

        public:
        inline JSON_BOOL(const bool_t & val = false) : IJSON_VALUE(JBOOL), value(val) { std::cout << "JSON_BOOL(const bool_t & val)\n"; }
        inline JSON_BOOL(const IJSON_VALUE & val) : IJSON_VALUE(JBOOL), value(val.AsBool()) { std::cout << "JSON_BOOL(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_BOOL () { std::cout << "~JSON_BOOL()\n"; }

        inline virtual string_t AsString() const { return value ? string_t("true") : string_t("false"); }
        inline virtual bool_t AsBool() const { return value; }
        inline virtual integer_t AsInteger() const { return value ? 1 : 0; }
        inline virtual double_t AsDouble() const { return value ? 1.0 : 0.0; }
        inline virtual array_t AsArray() const { return array_t(); }

    };

    class JSON_INTEGER: public IJSON_VALUE {

        integer_t value;

        public:
        inline JSON_INTEGER(const integer_t & val = 0) : IJSON_VALUE(JINTEGER), value(val) { std::cout << "JSON_INTEGER()\n"; }
        inline JSON_INTEGER(const IJSON_VALUE & val) : IJSON_VALUE(JINTEGER), value(val.AsInteger()) { std::cout << "JSON_INTEGER(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_INTEGER () { std::cout << "~JSON_INTEGER()\n"; }

        inline virtual string_t AsString() const { return std::to_string(value); }
        inline virtual bool_t AsBool() const { return value == 0 ? false : true; }
        inline virtual integer_t AsInteger() const { return value; }
        inline virtual double_t AsDouble() const { return static_cast<double_t>(value); }
        inline virtual array_t AsArray() const { return array_t(); }

    };

    class JSON_DOUBLE: public IJSON_VALUE {

        double_t value;

        public:
        inline JSON_DOUBLE(const double_t & val = 0.0) : IJSON_VALUE(JDOUBLE), value(val) { std::cout << "JSON_DOUBLE()\n"; }
        inline JSON_DOUBLE(const IJSON_VALUE & val) : IJSON_VALUE(JDOUBLE), value(val.AsDouble()) { std::cout << "JSON_DOUBLE(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_DOUBLE () { std::cout << "~JSON_DOUBLE()\n"; }

        inline virtual string_t AsString() const { return std::to_string(value); }
        inline virtual bool_t AsBool() const { return (value >= 0.0 && value < 1.0) ? false : true; }
        inline virtual integer_t AsInteger() const { return (integer_t)value; }
        inline virtual double_t AsDouble() const { return value; }
        inline virtual array_t AsArray() const { return array_t(); }

    };

    class JSON_STRING: public IJSON_VALUE {

        string_t value;

        public:
        inline JSON_STRING(const string_t & val = "") : IJSON_VALUE(JSTRING), value(val) { std::cout << "JSON_STRING()\n"; }
        inline JSON_STRING(const IJSON_VALUE & val) : IJSON_VALUE(JSTRING), value(val.AsString()) { std::cout << "JSON_STRING(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_STRING () { std::cout << "~JSON_STRING()\n"; }

        inline virtual string_t AsString() const {
            return value;
        }

        inline virtual bool_t AsBool() const {
            return (value.empty() || value == "0" || value == "false")
                ? false
                : true;
        }

        inline virtual integer_t AsInteger() const {
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

        inline virtual double_t AsDouble() const {
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

        inline virtual array_t AsArray() const { return array_t(); }
    };


    class JSON_ARRAY: public IJSON_VALUE {

        array_t value;
        public:
        inline JSON_ARRAY() : IJSON_VALUE(JARRAY) { std::cout << "JSON_ARRAY()\n"; }
        inline JSON_ARRAY(const array_t & val) : IJSON_VALUE(JARRAY), value(val) { std::cout << "JSON_ARRAY(const array_t & val)\n"; }
        inline JSON_ARRAY(const IJSON_VALUE & val) : IJSON_VALUE(JARRAY), value(val.AsArray()) { std::cout << "JSON_ARRAY(const IJSON_VALUE & val)\n"; }
        inline virtual ~JSON_ARRAY () { std::cout << "~JSON_ARRAY()\n"; }

        inline virtual string_t AsString() const { return std::to_string(value.size()); }
        inline virtual bool_t AsBool() const { return value.size() == 0 ? false : true; }
        inline virtual integer_t AsInteger() const { return value.size(); }
        inline virtual double_t AsDouble() const { return static_cast<double_t>(value.size()); }
        inline virtual array_t AsArray() const { return value; }
    };



    class IJValue {

    protected:

        IJValue() { }

    public:
        inline bool IsUndefined() const { return GetValue().GetType() == JUNDEFINED; }
        inline bool IsNull() const { return GetValue().GetType() == JNULL; }
        inline bool IsBool() const { return GetValue().GetType() == JBOOL; }
        inline bool IsInteger() const { return GetValue().GetType() == JINTEGER; }
        inline bool IsDouble() const { return GetValue().GetType() == JDOUBLE; }
        inline bool IsString() const { return GetValue().GetType() == JSTRING; }
        inline bool IsArray() const { return GetValue().GetType() == JARRAY; }
        inline bool IsMap() const { return GetValue().GetType() == JMAP; }

        virtual const IJSON_VALUE & GetValue() const = 0;
        virtual IJSON_VALUE * GetValuePtr() = 0;

        inline string_t AsString() const { return GetValue().AsString(); };
        inline bool_t AsBool() const { return GetValue().AsBool(); };
        inline integer_t AsInteger() const { return GetValue().AsInteger(); };
        inline double_t AsDouble() const { return GetValue().AsDouble(); };
        inline array_t AsArray() const {
            if (IsArray()) {
                return GetValue().AsArray();
            } else {
                array_t a;
//                a.push_back(this);
                return a;
            }
        };

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

        TJValue(const int & val) : value(T(JSON_INTEGER(static_cast<integer_t>(val)))) {
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


        virtual inline const IJSON_VALUE & GetValue() const {
            return value;
        };

        virtual inline IJSON_VALUE * GetValuePtr() {
            return &value;
        };

/*
        virtual void push_back(const JSON_NULL & val) {
            if (IsArray()) {
                value.push_back(val);
            }
        };
        virtual void push_back(const JSON_BOOL & val) {
            if (IsArray()) {
                value.push_back(val);
            }
        };
        virtual void push_back(const JSON_INTEGER & val) {
            if (IsArray()) {
                value.push_back(val);
            }
        };
        virtual void push_back(const JSON_DOUBLE & val) {
            if (IsArray()) {
                value.push_back(val);
            }
        };
        virtual void push_back(const JSON_STRING & val) {
            if (IsArray()) {
                value.push_back(val);
            }
        };
        virtual void push_back(const JSON_ARRAY & val) {
            if (IsArray()) {
                value.push_back(val);
            }
        };
*/
    };


/* /////////////////////////////////////////////////////////////////////////// */


    // JSON_UNDEFINED


    // JSON_NULL


    // JSON_BOOL

    // JSON_INTEGER

    // JSON_DOUBLE

    // JSON_STRING

    // JSON_ARRAY
}
