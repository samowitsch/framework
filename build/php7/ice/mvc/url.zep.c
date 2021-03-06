
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * This component allows to create URLs.
 *
 * @package     Ice/Mvc
 * @category    Component
 * @author      Ice Team
 * @copyright   (c) 2014-2018 Ice Team
 * @license     http://iceframework.org/license
 */
ZEPHIR_INIT_CLASS(Ice_Mvc_Url) {

	ZEPHIR_REGISTER_CLASS(Ice\\Mvc, Url, ice, mvc_url, ice_mvc_url_method_entry, 0);

	zend_declare_property_string(ice_mvc_url_ce, SL("baseUri"), "/", ZEND_ACC_PROTECTED);

	zend_declare_property_string(ice_mvc_url_ce, SL("staticUri"), "/", ZEND_ACC_PROTECTED);

	return SUCCESS;

}

PHP_METHOD(Ice_Mvc_Url, getBaseUri) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "baseUri");

}

PHP_METHOD(Ice_Mvc_Url, setBaseUri) {

	zval *baseUri, baseUri_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&baseUri_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &baseUri);



	zephir_update_property_zval(this_ptr, SL("baseUri"), baseUri);
	RETURN_THISW();

}

PHP_METHOD(Ice_Mvc_Url, getStaticUri) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "staticUri");

}

PHP_METHOD(Ice_Mvc_Url, setStaticUri) {

	zval *staticUri, staticUri_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&staticUri_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &staticUri);



	zephir_update_property_zval(this_ptr, SL("staticUri"), staticUri);
	RETURN_THISW();

}

/**
 * Generates a URL for a static resource.
 *
 * @param string uri
 * @return string
 */
PHP_METHOD(Ice_Mvc_Url, getStatic) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *uri_param = NULL, _0;
	zval uri;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &uri_param);

	if (!uri_param) {
		ZEPHIR_INIT_VAR(&uri);
		ZVAL_STRING(&uri, "");
	} else {
		zephir_get_strval(&uri, uri_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getstaticuri", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &_0, &uri);
	RETURN_MM();

}

/**
 * Generates a URL.
 *
 * @param string uri
 * @param array|object args Optional arguments to be appended to the query string
 * @param bool local
 * @return string
 */
PHP_METHOD(Ice_Mvc_Url, get) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool local, _0$$3, _1$$3, _6$$8, _7$$10, _9$$12;
	zval *uri = NULL, uri_sub, *args = NULL, args_sub, *local_param = NULL, _GET, __$null, baseUri, queryString, _2$$4, _3$$4, _4$$4, _5$$4, _8$$11, _10$$13, _11$$13, _12$$14, _13$$15;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_sub);
	ZVAL_UNDEF(&args_sub);
	ZVAL_UNDEF(&_GET);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&baseUri);
	ZVAL_UNDEF(&queryString);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_10$$13);
	ZVAL_UNDEF(&_11$$13);
	ZVAL_UNDEF(&_12$$14);
	ZVAL_UNDEF(&_13$$15);

	ZEPHIR_MM_GROW();
	zephir_get_global(&_GET, SL("_GET"));
	zephir_fetch_params(1, 0, 3, &uri, &args, &local_param);

	if (!uri) {
		uri = &uri_sub;
		ZEPHIR_CPY_WRT(uri, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(uri);
	}
	if (!args) {
		args = &args_sub;
		args = &__$null;
	}
	if (!local_param) {
		local = 1;
	} else {
		local = zephir_get_boolval(local_param);
	}


	if (!(local)) {
		_0$$3 = Z_TYPE_P(uri) == IS_STRING;
		if (_0$$3) {
			_1$$3 = zephir_memnstr_str(uri, SL("//"), "ice/mvc/url.zep", 45);
			if (!(_1$$3)) {
				_1$$3 = zephir_memnstr_str(uri, SL(":"), "ice/mvc/url.zep", 45);
			}
			_0$$3 = _1$$3;
		}
		if (_0$$3) {
			ZEPHIR_INIT_VAR(&_2$$4);
			ZEPHIR_INIT_VAR(&_3$$4);
			ZVAL_STRING(&_3$$4, "#^((//)|([a-z0-9]+://)|([a-z0-9]+:))#i");
			ZEPHIR_INIT_VAR(&_4$$4);
			ZEPHIR_INIT_VAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "#^((//)|([a-z0-9]+://)|([a-z0-9]+:))#i");
			zephir_preg_match(&_4$$4, &_5$$4, uri, &_2$$4, 0, 0 , 0 );
			if (zephir_is_true(&_4$$4)) {
				local = 0;
			} else {
				local = 1;
			}
		} else {
			local = 1;
		}
	}
	ZEPHIR_CALL_METHOD(&baseUri, this_ptr, "getbaseuri", NULL, 0);
	zephir_check_call_status();
	if (local) {
		_6$$8 = ZEPHIR_IS_FALSE_IDENTICAL(uri);
		if (_6$$8) {
			_6$$8 = zephir_array_isset_string(&_GET, SL("_url"));
		}
		if (_6$$8) {
			ZEPHIR_OBS_NVAR(uri);
			zephir_array_fetch_string(uri, &_GET, SL("_url"), PH_NOISY, "ice/mvc/url.zep", 61);
		} else {
			_7$$10 = !(zephir_start_with_str(uri, SL("#")));
			if (_7$$10) {
				_7$$10 = !(zephir_start_with_str(uri, SL("?")));
			}
			if (_7$$10) {
				ZEPHIR_INIT_VAR(&_8$$11);
				ZEPHIR_CONCAT_VV(&_8$$11, &baseUri, uri);
				ZEPHIR_CPY_WRT(uri, &_8$$11);
			}
		}
	}
	if (zephir_is_true(args)) {
		ZEPHIR_CALL_FUNCTION(&queryString, "http_build_query", NULL, 18, args);
		zephir_check_call_status();
		_9$$12 = Z_TYPE_P(&queryString) == IS_STRING;
		if (_9$$12) {
			_9$$12 = ((zephir_fast_strlen_ev(&queryString)) ? 1 : 0);
		}
		if (_9$$12) {
			ZEPHIR_INIT_VAR(&_10$$13);
			ZVAL_STRING(&_10$$13, "?");
			ZEPHIR_INIT_VAR(&_11$$13);
			zephir_fast_strpos(&_11$$13, &queryString, &_10$$13, 0 );
			if (!ZEPHIR_IS_FALSE_IDENTICAL(&_11$$13)) {
				ZEPHIR_INIT_VAR(&_12$$14);
				ZEPHIR_CONCAT_SV(&_12$$14, "&", &queryString);
				zephir_concat_self(uri, &_12$$14);
			} else {
				ZEPHIR_INIT_VAR(&_13$$15);
				ZEPHIR_CONCAT_SV(&_13$$15, "?", &queryString);
				zephir_concat_self(uri, &_13$$15);
			}
		}
	}
	RETVAL_ZVAL(uri, 1, 0);
	RETURN_MM();

}

