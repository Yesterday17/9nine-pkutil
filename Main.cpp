

#include <windows.h>
#include "tp_stub.h"
#include <lmcons.h>

// 检查 ProductKey 的函数
//---------------------------------------------------------------------------
class tProductKeyCheckFunction : public tTJSDispatch
{
	tjs_error TJS_INTF_METHOD FuncCall(
		tjs_uint32 flag, const tjs_char* membername, tjs_uint32* hint,
		tTJSVariant* result,
		tjs_int numparams, tTJSVariant** param, iTJSDispatch2* objthis);
} *ProductKeyCheckFunction;
//---------------------------------------------------------------------------
tjs_error TJS_INTF_METHOD tProductKeyCheckFunction::FuncCall(
	tjs_uint32 flag, const tjs_char* membername, tjs_uint32* hint,
	tTJSVariant* result,
	tjs_int numparams, tTJSVariant** param, iTJSDispatch2* objthis)
{
	if (membername) return TJS_E_MEMBERNOTFOUND;

	tTJSVariant pkeyconf;
	TVPExecuteStorage("pkeyconf.tjs", &pkeyconf, true);

	tTJSVariant tagResult;
	auto conf = pkeyconf.AsObject();
	conf->PropGet(0, TJS_W("tag"), nullptr, &tagResult, nullptr);
	tTVInteger tag = tagResult.AsInteger();

	iTJSDispatch2* array = TJSCreateArrayObject();
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 0, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 1, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 2, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 3, &value, array);
	}
	{
		tTJSVariant value(tag & 0xff);
		array->PropSetByNum(0, 4, &value, array);
	}
	{
		tTJSVariant value((tag & 0xff00) >> 8);
		array->PropSetByNum(0, 5, &value, array);
	}
	{
		tTJSVariant value((tag & 0xff0000) >> 16);
		array->PropSetByNum(0, 6, &value, array);
	}
	{
		tTJSVariant value((tag & 0xff000000) >> 24);
		array->PropSetByNum(0, 7, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 8, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 9, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 10, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 11, &value, array);
	}
	{
		tTJSVariant value(0);
		array->PropSetByNum(0, 12, &value, array);
	}

	*result = tTJSVariant(array, array);
	array->Release();
	return TJS_S_OK;
}


// GetUserDefaultLCID
// GetSystemDefaultLCID
//---------------------------------------------------------------------------
class tGetDefaultLCIDFunction : public tTJSDispatch
{
	tjs_error TJS_INTF_METHOD FuncCall(
		tjs_uint32 flag, const tjs_char* membername, tjs_uint32* hint,
		tTJSVariant* result,
		tjs_int numparams, tTJSVariant** param, iTJSDispatch2* objthis);
} *GetDefaultLCIDFunction;

tjs_error TJS_INTF_METHOD tGetDefaultLCIDFunction::FuncCall(
	tjs_uint32 flag, const tjs_char* membername, tjs_uint32* hint,
	tTJSVariant* result,
	tjs_int numparams, tTJSVariant** param, iTJSDispatch2* objthis)
{
	if (membername) return TJS_E_MEMBERNOTFOUND;
	*result = 0x0411;
	return TJS_S_OK;
}





//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved) {
	return 1;
}


//---------------------------------------------------------------------------
static tjs_int GlobalRefCountAtInit = 0;
extern "C" __declspec(dllexport) HRESULT _stdcall V2Link(iTVPFunctionExporter * exporter)
{
	TVPInitImportStub(exporter);
	iTJSDispatch2* global = TVPGetScriptDispatch();
	tTJSVariant val;

	ProductKeyCheckFunction = new tProductKeyCheckFunction();
	val = tTJSVariant(ProductKeyCheckFunction);
	ProductKeyCheckFunction->Release();
	global->PropSet(TJS_MEMBERENSURE, TJS_W("ProductKeyCheck"), nullptr, &val, global);

	GetDefaultLCIDFunction = new tGetDefaultLCIDFunction();
	val = tTJSVariant(GetDefaultLCIDFunction);
	GetDefaultLCIDFunction->Release();
	global->PropSet(TJS_MEMBERENSURE, TJS_W("GetUserDefaultLCID"), nullptr, &val, global);
	global->PropSet(TJS_MEMBERENSURE, TJS_W("GetSystemDefaultLCID"), nullptr, &val, global);

	global->Release();
	val.Clear();
	GlobalRefCountAtInit = TVPPluginGlobalRefCount;
	return TJS_S_OK;
}

extern "C" __declspec(dllexport) HRESULT _stdcall V2Unlink()
{
	if (TVPPluginGlobalRefCount > GlobalRefCountAtInit) return TJS_E_FAIL;

	iTJSDispatch2* global = TVPGetScriptDispatch();

	if (global)
	{
		global->DeleteMember(0, TJS_W("ProductKeyCheck"), nullptr, global);
		global->DeleteMember(0, TJS_W("GetUserDefaultLCID"), nullptr, global);
		global->DeleteMember(0, TJS_W("GetSystemDefaultLCID"), nullptr, global);
	}

	if (global) global->Release();

	TVPUninitImportStub();

	return TJS_S_OK;
}
