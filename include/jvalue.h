#pragma once

#include <vector>
#include <map>
#include <string>
#include <deque>

namespace NJValue {

    class IJValue;

    enum EJValueType { JUNDEFINED, JNULL, JBOOL, JINTEGER, JDOUBLE, JSTRING, JARRAY, JMAP };

    class JSON_UNDEFINED;
    class JSON_NULL;
    class JSON_INTEGER;
//    class JSON_DOUBLE;
    class JSON_STRING;
    class JSON_BOOL;
    class JSON_ARRAY;
//    class JSON_MAP;

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

//        TJValue(const double& value) : val(T(JSON_DOUBLE(value))) {
//        }

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
/*
    class IJValue {
    protected:

    public:

        virtual bool IsUnknown() const { return this->GetType() == UNKNOWN; }
        virtual bool IsNull() const { return this->GetType() == UNDEFINED; }
        virtual bool IsBool() const { return this->GetType() == BOOL; }
        virtual bool IsInteger() const { return this->GetType() == INTEGER; }
        virtual bool IsDouble() const { return this->GetType() == DOUBLE; }
        virtual bool IsString() const { return this->GetType() == STRING; }
        virtual bool IsArray() const { return this->GetType() == ARRAY; }
        virtual bool IsMap() const { return this->GetType() == MAP; }

        virtual EJValueType GetType() const { return UNKNOWN; }
        virtual JSON_STRING ToString() const { return ""; };
        virtual JSON_BOOL ToBool() const { return false; };
        virtual JSON_INTEGER ToInteger() const { return 0; };
        virtual JSON_DOUBLE ToDouble() const { return 0; };

        virtual ~IJValue() {
        }

        operator JSON_STRING() {
            return ToString();
        }

        operator JSON_INTEGER() {
            return ToInteger();
        }

        operator JSON_DOUBLE() {
            return ToDouble();
        }

        operator JSON_BOOL() {
            return ToBool();
        }

    };

    template<class T>
    class TJValue: public IJValue {
        T val;

        const JSON_BOOL bool_t = true;
        const JSON_BOOL bool_f = false;

    protected:
        EJValueType GetType(const TJValue<JSON_UNKNOWN> * o) const { return UNKNOWN; }
        EJValueType GetType(const TJValue<JSON_UNDEFINED> * o) const { return UNDEFINED; }
        EJValueType GetType(const TJValue<JSON_BOOL> * o) const { return BOOL; }
        EJValueType GetType(const TJValue<JSON_INTEGER> * o) const { return INTEGER; }
        EJValueType GetType(const TJValue<JSON_DOUBLE> * o) const { return DOUBLE; }
        EJValueType GetType(const TJValue<JSON_STRING> * o) const { return STRING; }
        EJValueType GetType(const TJValue<JSON_ARRAY> * o) const { return ARRAY; }
        EJValueType GetType(const TJValue<JSON_MAP> * o) const { return MAP; }

        JSON_STRING ToString(const TJValue<JSON_UNKNOWN> * o) const { return "UNKNOWN"; }
        JSON_STRING ToString(const TJValue<JSON_UNDEFINED> * o) const { return "null"; }
        JSON_STRING ToString(const TJValue<JSON_BOOL> * o) const { return o->val ? "true" : "false"; }
        JSON_STRING ToString(const TJValue<JSON_INTEGER> * o) const { return std::to_string(o->val); }
        JSON_STRING ToString(const TJValue<JSON_DOUBLE> * o) const { return std::to_string(o->val); }
        JSON_STRING ToString(const TJValue<JSON_STRING> * o) const { return o->val; }
        JSON_STRING ToString(const TJValue<JSON_ARRAY> * o) const { return "ARRAY[" + std::to_string((size_t)&(o->val)) + "]"; }
        JSON_STRING ToString(const TJValue<JSON_MAP> * o) const { return "MAP{" + std::to_string((size_t)&(o->val)) + "}"; }

        const JSON_BOOL& ToBool(const TJValue<JSON_UNKNOWN> * o) const { return bool_f; }
        const JSON_BOOL& ToBool(const TJValue<JSON_UNDEFINED> * o) const { return bool_f; }
        const JSON_BOOL& ToBool(const TJValue<JSON_BOOL> * o) const { return o->val ? bool_t : bool_f; }
        const JSON_BOOL& ToBool(const TJValue<JSON_INTEGER> * o) const { return o->val == 0 ? bool_f : bool_t; }
        const JSON_BOOL& ToBool(const TJValue<JSON_DOUBLE> * o) const { return o->val == 0 ? bool_f : bool_t; }
        const JSON_BOOL& ToBool(const TJValue<JSON_STRING> * o) const { return o->val == "" || o->val == "false" || o->val == "null" || o->val == "0" ? bool_f : bool_t; }
        const JSON_BOOL& ToBool(const TJValue<JSON_ARRAY> * o) const { return bool_t; }
        const JSON_BOOL& ToBool(const TJValue<JSON_MAP> * o) const { return bool_t; }

        JSON_INTEGER ToInteger(const TJValue<JSON_UNKNOWN> * o) const { return 0; }
        JSON_INTEGER ToInteger(const TJValue<JSON_UNDEFINED> * o) const { return 0; }
        JSON_INTEGER ToInteger(const TJValue<JSON_BOOL> * o) const { return o->val ? 1 : 0; }
        JSON_INTEGER ToInteger(const TJValue<JSON_INTEGER> * o) const { return o->val; }
        JSON_INTEGER ToInteger(const TJValue<JSON_DOUBLE> * o) const { return (JSON_INTEGER)o->val; }
        JSON_INTEGER ToInteger(const TJValue<JSON_STRING> * o) const { return o->val == "" || o->val == "false" || o->val == "null" ? 0 : std::stoi(o->val); }
        JSON_INTEGER ToInteger(const TJValue<JSON_ARRAY> * o) const { return 0; }
        JSON_INTEGER ToInteger(const TJValue<JSON_MAP> * o) const { return 0; }

        JSON_DOUBLE ToDouble(const TJValue<JSON_UNKNOWN> * o) const { return 0; }
        JSON_DOUBLE ToDouble(const TJValue<JSON_UNDEFINED> * o) const { return 0; }
        JSON_DOUBLE ToDouble(const TJValue<JSON_BOOL> * o) const { return o->val ? 1 : 0; }
        JSON_DOUBLE ToDouble(const TJValue<JSON_INTEGER> * o) const { return (JSON_DOUBLE)o->val; }
        JSON_DOUBLE ToDouble(const TJValue<JSON_DOUBLE> * o) const { return o->val; }
        JSON_DOUBLE ToDouble(const TJValue<JSON_STRING> * o) const { return o->val == "" || o->val == "false" || o->val == "null" ? 0 : std::stod(o->val); }
        JSON_DOUBLE ToDouble(const TJValue<JSON_ARRAY> * o) const { return 0; }
        JSON_DOUBLE ToDouble(const TJValue<JSON_MAP> * o) const { return 0; }

    public:

        TJValue(const T& value)
            : val(value)
        {
        }

        virtual ~TJValue() {
        }

        virtual EJValueType GetType() const {
            return GetType(this);
        }

        virtual const T& GetValue() const {
            return val;
        }

        virtual JSON_STRING ToString() const {
            return ToString(this);
        }

        virtual JSON_BOOL ToBool() const {
            return ToBool(this);
        }

        virtual JSON_INTEGER ToInteger() const {
            return ToInteger(this);
        }

        virtual JSON_DOUBLE ToDouble() const {
            return ToDouble(this);
        }

    };
*/
/*
    using TJValuePtr = TJValue*;
    using TJArrayContainer = std::vector<TJValuePtr>;
    using TJMapContainer = std::map<std::string, TJValuePtr>;
    const std::string nullValue = "null";
    const std::string trueValue = "true";
    const std::string falseValue = "false";


        virtual std::string ToString() {
            return "[ ]";
        }

        virtual int ToInteger() const {
            return (int)val.size();
        }



    class TJMap: public TJValue {
        TJMapContainer val;

    public:
        virtual bool IsMap() const {
            return true;
        }

        TJMapContainer GetValue() {
            return val;
        }

        virtual std::string ToString() {
            return "{ }";
        }

        virtual int ToInteger() const {
            return (int)val.size();
        }

        virtual double ToDouble() const {
            return (double)val.size();
        }

        virtual bool ToBool() const {
            return val.size() != 0;
        }
    };
*/

}
