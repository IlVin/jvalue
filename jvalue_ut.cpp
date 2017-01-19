#define BOOST_TEST_MODULE testJValue
#include <boost/test/unit_test.hpp>
#include "jvalue.h"
#include <string>


using namespace NJValue;

BOOST_AUTO_TEST_SUITE(testSuiteJValue)

    BOOST_AUTO_TEST_CASE( testJValueUndefined ) {
        {
            TJValue<JSON_UNDEFINED> j;
            BOOST_CHECK_EQUAL(j.IsUndefined(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsBool(), false);
        }
    }

    BOOST_AUTO_TEST_CASE( testJValueNull ) {
        {
            TJValue<JSON_NULL> j;
            BOOST_CHECK_EQUAL(j.IsNull(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsBool(), false);
        }
    }

    BOOST_AUTO_TEST_CASE( testJValueBool ) {
        {
            TJValue<JSON_BOOL> j = true;
            BOOST_CHECK_EQUAL(j.IsBool(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "true");
            BOOST_CHECK_EQUAL(j.AsInteger(), 1);
            BOOST_CHECK_EQUAL(j.AsDouble(), 1.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsBool(), true);
        }

        {
            TJValue<JSON_BOOL> j = false;
            BOOST_CHECK_EQUAL(j.IsBool(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "false");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsBool(), false);
        }
    }

    BOOST_AUTO_TEST_CASE( testJValueInteger ) {
        {
            TJValue<JSON_INTEGER> j = 5;
            BOOST_CHECK_EQUAL(j.IsInteger(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "5");
            BOOST_CHECK_EQUAL(j.AsInteger(), 5);
            BOOST_CHECK_EQUAL(j.AsDouble(), 5.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsInteger(), 5);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsInteger(), 5);
        }

        {
            TJValue<JSON_INTEGER> j = -15;
            BOOST_CHECK_EQUAL(j.IsInteger(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "-15");
            BOOST_CHECK_EQUAL(j.AsInteger(), -15);
            BOOST_CHECK_EQUAL(j.AsDouble(), -15.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsInteger(), -15);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsInteger(), -15);
        }

        {
            TJValue<JSON_INTEGER> j = 0;
            BOOST_CHECK_EQUAL(j.IsInteger(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "0");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsInteger(), 0);
        }

        // TODO Добавить тесты на диапазоны допустимых значений
    }

    BOOST_AUTO_TEST_CASE( testJValueDouble ) {
        {
            TJValue<JSON_DOUBLE> j = 5.0;
            BOOST_CHECK_EQUAL(j.IsDouble(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "5.000000");
            BOOST_CHECK_EQUAL(j.AsInteger(), 5);
            BOOST_CHECK_EQUAL(j.AsDouble(), 5.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsDouble(), 5.0);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsDouble(), 5.0);
        }

        {
            TJValue<JSON_DOUBLE> j = -15.6;
            BOOST_CHECK_EQUAL(j.IsDouble(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "-15.600000");
            BOOST_CHECK_EQUAL(j.AsInteger(), -15);
            BOOST_CHECK_EQUAL(j.AsDouble(), -15.6);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsDouble(), -15.6);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsDouble(), -15.6);
        }

        {
            TJValue<JSON_DOUBLE> j = 0.1;
            BOOST_CHECK_EQUAL(j.IsDouble(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "0.100000");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.1);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsDouble(), 0.1);
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsDouble(), 0.1);
        }

        // TODO Добавить тесты на диапазоны допустимых значений
    }

    BOOST_AUTO_TEST_CASE( testJValueString ) {
        {
            TJValue<JSON_STRING> j = "Hello!";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "Hello!");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "Hello!");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "Hello!");
        }

        {
            TJValue<JSON_STRING> j = "";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "");
        }

        {
            TJValue<JSON_STRING> j = "null";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "null");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "null");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "null");
        }

        {
            TJValue<JSON_STRING> j = "0";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "0");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "0");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "0");
        }

        {
            TJValue<JSON_STRING> j = "5";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "5");
            BOOST_CHECK_EQUAL(j.AsInteger(), 5);
            BOOST_CHECK_EQUAL(j.AsDouble(), 5.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "5");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "5");
        }

        {
            TJValue<JSON_STRING> j = "-25";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "-25");
            BOOST_CHECK_EQUAL(j.AsInteger(), -25);
            BOOST_CHECK_EQUAL(j.AsDouble(), -25.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "-25");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "-25");
        }

        {
            TJValue<JSON_STRING> j = "true";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "true");
            BOOST_CHECK_EQUAL(j.AsInteger(), 1);
            BOOST_CHECK_EQUAL(j.AsDouble(), 1.0);
            BOOST_CHECK_EQUAL(j.AsBool(), true);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "true");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "true");
        }

        {
            TJValue<JSON_STRING> j = "false";
            BOOST_CHECK_EQUAL(j.IsString(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "false");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            BOOST_CHECK_EQUAL(j.GetValue().AsString(), "false");
            BOOST_CHECK_EQUAL(j.GetValuePtr()->AsString(), "false");
        }
    }

    BOOST_AUTO_TEST_CASE( testJValueArray ) {
        {
            std::cout << "===> testJValueArray\n";
            TJValue<JSON_ARRAY> j;
            BOOST_CHECK_EQUAL(j.IsArray(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "0");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
        }

        {
            std::cout << "===> testJValueArray.CopyConstructor\n";
            TJValue<JSON_ARRAY> j;
            BOOST_CHECK_EQUAL(j.IsArray(), true);
            BOOST_CHECK_EQUAL(j.AsString(), "0");
            BOOST_CHECK_EQUAL(j.AsInteger(), 0);
            BOOST_CHECK_EQUAL(j.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(j.AsBool(), false);
            TJValue<JSON_ARRAY> i = j;
//            i.push_back("345");
            BOOST_CHECK_EQUAL(i.IsArray(), true);
            BOOST_CHECK_EQUAL(i.AsString(), "0");
            BOOST_CHECK_EQUAL(i.AsInteger(), 0);
            BOOST_CHECK_EQUAL(i.AsDouble(), 0.0);
            BOOST_CHECK_EQUAL(i.AsBool(), false);

            BOOST_CHECK_EQUAL(i.AsString(), j.AsString());
        }
        // TODO Добавить тесты на диапазоны допустимых значений
    }

BOOST_AUTO_TEST_SUITE_END()
