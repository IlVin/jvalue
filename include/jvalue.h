#pragma once

#include <vector>
#include <map>
#include <string>
#include <deque>

namespace NJValue {

    class IJValue;
    template<class T>
    class TJValue;

    enum EJValueType { UNKNOWN, UNDEFINED, BOOL, INTEGER, DOUBLE, STRING, ARRAY, MAP };

    struct TUnknown {};
    struct TUndefined {};

    using JSON_UNKNOWN = TUnknown;
    using JSON_UNDEFINED = TUndefined;
    using JSON_INTEGER = int;
    using JSON_DOUBLE = double;
    using JSON_STRING = std::string;
    using JSON_BOOL = bool;
    using JSON_ARRAY = std::deque<IJValue>;
    using JSON_MAP = std::map<std::string, IJValue>;



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
