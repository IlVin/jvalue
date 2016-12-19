#include "jvalue.h"
#include <iostream>

namespace NJValue {

    EJValueType JSON_UNDEFINED::GetType() const {
            return JUNDEFINED;
        }

    EJValueType JSON_NULL::GetType() const {
        return JNULL;
    }

    EJValueType JSON_INTEGER::GetType() const {
        return JINTEGER;
    }

    EJValueType JSON_STRING::GetType() const {
        return JSTRING;
    }

    EJValueType JSON_BOOL::GetType() const {
        return JBOOL;
    }

    EJValueType JSON_ARRAY::GetType() const {
        return JARRAY;
    }

}
