#include "jvalue.h"
#include <iostream>

namespace NJValue {

    EJValueType JSON_UNDEFINED::GetType() const {
            return JUNDEFINED;
        }

//    JSON_STRING JSON_UNDEFINED::ToString() const {
//        return JSON_STRING("");
//    }

//  JSON_BOOL JSON_UNDEFINED::ToBool() const {
//      return JSON_BOOL(false);
//  }

//    JSON_INTEGER JSON_UNDEFINED::ToInteger() const {
//        return JSON_INTEGER(0);
//    }

//  JSON_DOUBLE JSON_UNDEFINED::ToDouble() const {
//      return JSON_DOUBLE(0.0);
//  }

/*
    JSON_MAP JSON_UNDEFINED::ToMap() const {
        JSON_MAP m;
        m['0'] = this;
        return m;
    }
*/

    EJValueType JSON_NULL::GetType() const {
        return JNULL;
    }

//    JSON_STRING JSON_NULL::ToString() const {
//        return JSON_STRING("");
//    }

//  JSON_BOOL JSON_NULL::ToBool() const {
//      return JSON_BOOL(false);
//  }

//    JSON_INTEGER JSON_NULL::ToInteger() const {
//        return JSON_INTEGER(0);
//    }

//  JSON_DOUBLE JSON_NULL::ToDouble() const {
//      return JSON_DOUBLE(0.0);
//  }



    EJValueType JSON_INTEGER::GetType() const {
        return JINTEGER;
    }

//    JSON_STRING JSON_INTEGER::ToString() const {
//        std::cout << "JSON_STRING JSON_INTEGER::ToString() : value = " << value << "\n";
//        return JSON_STRING(std::to_string(value));
//    }

//  JSON_BOOL JSON_INTEGER::ToBool() const {
//      return JSON_BOOL(value == 0 ? false : true);
//  }

//    JSON_INTEGER JSON_INTEGER::ToInteger() const {
//        return JSON_INTEGER(value);
//    }

//  JSON_DOUBLE JSON_INTEGER::ToDouble() const {
//      return JSON_DOUBLE((double)value);
//  }


    EJValueType JSON_STRING::GetType() const {
        return JSTRING;
    }

    EJValueType JSON_ARRAY::GetType() const {
        return JARRAY;
    }

//    JSON_STRING JSON_ARRAY::ToString() const {
//        return JSON_STRING("ARRAY");
//    }

//  JSON_BOOL JSON_ARRAY::ToBool() const {
//      return JSON_BOOL(size() == 0 ? false : true);
//  }

//    JSON_INTEGER JSON_ARRAY::ToInteger() const {
//        return size();
//    }

//  JSON_DOUBLE JSON_ARRAY::ToDouble() const {
//      return JSON_DOUBLE((double)size());
//  }


}
