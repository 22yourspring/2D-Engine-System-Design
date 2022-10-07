#pragma once

#include "struct.h"

#define SINGLE(_type)		public:\
								 static _type* GetInst()\
								 {\
									static _type Inst;\
					 				return &Inst;\
								 }\
							private:\
								_type();\
								~_type();

#define	__DECLARE_SINGLECAST_DELEGATE_Param()		public:	__FUNCTION		__function;		ENABLE_FUNC		__enable

#define __AddDynamic_SINGLECAST_SET_CALLBACK_0PARAM(__caller, __SourceFunction)									__caller->__function.pFuncPtr_0Param = __SourceFunction;\
																												__caller->__enable = ENABLE_FUNC::NULL_PARAM

#define __AddDynamic_SINGLECAST_SET_CALLBACK_1PARAM(__caller, __SourceFunction, _param1)						__caller->__function.pFuncPtr_1Param = __SourceFunction;\
																												__caller->__function.param1 = _param1;\
																												__caller->__enable = ENABLE_FUNC::ONE_PARAM

#define __AddDynamic_SINGLECAST_SET_CALLBACK_2PARAM(__caller, __SourceFunction, _param1, _param2)				__caller->__function.pFuncPtr_2Param = __SourceFunction;\
																												__caller->__function.param1 = _param1;\
																												__caller->__function.param2 = _param2;\
																												__caller->__enable = ENABLE_FUNC::TWO_PARAM

#define __AddDynamic_SINGLECAST_SET_CALLBACK_3PARAM(__caller, __SourceFunction, _param1, _param2, _param3)		__caller->__function.pFuncPtr_3Param = __SourceFunction;\
																												__caller->__function.param1 = _param1;\
																												__caller->__function.param2 = _param2;\
																												__caller->__function.param3 = _param3;\
																												__caller->__enable = ENABLE_FUNC::THREE_PARAM

#define	__FUNCTION_SINGLECAST_0PARAM()				if (__function.pFuncPtr_0Param) __function.pFuncPtr_0Param()
#define	__FUNCTION_SINGLECAST_1PARAM()				if (__function.pFuncPtr_1Param) __function.pFuncPtr_1Param(__function.param1)
#define	__FUNCTION_SINGLECAST_2PARAM()				if (__function.pFuncPtr_2Param) __function.pFuncPtr_2Param(__function.param1, __function.param2)
#define	__FUNCTION_SINGLECAST_3PARAM()				if (__function.pFuncPtr_3Param) __function.pFuncPtr_3Param(__function.param1, __function.param2, __function.param3)

#define __DELEGATE_SINGLECAST()						switch (__enable)\
													{\
													case ENABLE_FUNC::NULL_PARAM:\
														__FUNCTION_SINGLECAST_0PARAM(__function);\
														break;\
													case ENABLE_FUNC::ONE_PARAM:\
														__FUNCTION_SINGLECAST_1PARAM(__function);\
														break;\
													case ENABLE_FUNC::TWO_PARAM:\
														__FUNCTION_SINGLECAST_2PARAM(__function);\
														break;\
													case ENABLE_FUNC::THREE_PARAM:\
														__FUNCTION_SINGLECAST_3PARAM(__function);\
														break;\
													}


#define	__DECLARE_MULTICAST_DELEGATE_Param()		public:	vector<__FUNCTION>	__vecFunction;		vector<ENABLE_FUNC>		__vecEnable

#define __AddDynamic_MULTICAST_SET_CALLBACK_0PARAM(__caller, __SourceFunction)								__FUNCTION __function;\
																											__function.pFuncPtr_0Param = __SourceFunction;\
																											__caller->__vecFunction.push_back(__function);\
																											ENABLE_FUNC __enable = ENABLE_FUNC::NULL_PARAM;\
																											__caller->__vecEnable.push_back(__enable)
					
#define __AddDynamic_MULTICAST_SET_CALLBACK_1PARAM(__caller, __SourceFunction, _param1)						__FUNCTION __function;\
																											__function.pFuncPtr_1Param = __SourceFunction;\
																											__function.param1 = _param1;\
																											__caller->__vecFunction.push_back(__function);\
																											ENABLE_FUNC __enable = ENABLE_FUNC::ONE_PARAM;\
																											__caller->__vecEnable.push_back(__enable)

					
#define __AddDynamic_MULTICAST_SET_CALLBACK_2PARAM(__caller, __SourceFunction, _param1, _param2)			__FUNCTION __function;\
																											__function.pFuncPtr_1Param = __SourceFunction;\
																											__function.param1 = _param1;\
																											__function.param2 = _param2;\
																											__caller->__vecFunction.push_back(__function);\
																											ENABLE_FUNC __enable = ENABLE_FUNC::ONE_PARAM;\
																											__caller->__vecEnable.push_back(__enable)

					
#define __AddDynamic_MULTICAST_SET_CALLBACK_3PARAM(__caller, __SourceFunction, _param1, _param2, _param3)	__FUNCTION __function;\
																											__function.pFuncPtr_1Param = __SourceFunction;\
																											__function.param1 = _param1;\
																											__function.param2 = _param2;\
																											__function.param3 = _param3;\
																											__caller->__vecFunction.push_back(__function);\
																											ENABLE_FUNC __enable = ENABLE_FUNC::ONE_PARAM;\
																											__caller->__vecEnable.push_back(__enable)


#define	__FUNCTION_MULTICAST_0PARAM()				if (__vecFunction[i].pFuncPtr_0Param) __vecFunction[i].pFuncPtr_0Param()
#define	__FUNCTION_MULTICAST_1PARAM()				if (__vecFunction[i].pFuncPtr_1Param) __vecFunction[i].pFuncPtr_1Param(__vecFunction[i].param1)
#define	__FUNCTION_MULTICAST_2PARAM()				if (__vecFunction[i].pFuncPtr_2Param) __vecFunction[i].pFuncPtr_2Param(__vecFunction[i].param1, __vecFunction[i].param2)
#define	__FUNCTION_MULTICAST_3PARAM()				if (__vecFunction[i].pFuncPtr_3Param) __vecFunction[i].pFuncPtr_3Param(__vecFunction[i].param1, __vecFunction[i].param2, __vecFunction[i].param3)

#define __DELEGATE_MULTICAST()						for (size_t i = 0; i < __vecFunction.size(); i++)\
													{\
														switch (__vecEnable[i])\
														{\
														case ENABLE_FUNC::NULL_PARAM:\
															__FUNCTION_MULTICAST_0PARAM();\
															break;\
														case ENABLE_FUNC::ONE_PARAM:\
															__FUNCTION_MULTICAST_1PARAM();\
															break;\
														case ENABLE_FUNC::TWO_PARAM:\
															__FUNCTION_MULTICAST_2PARAM();\
															break;\
														case ENABLE_FUNC::THREE_PARAM:\
															__FUNCTION_MULTICAST_3PARAM();\
															break;\
														}\
													}\


#define CLONE(_type)	virtual _type* Clone() override { return new _type(*this); }
#define __OBJECT_CLONE(_type)	_type->Clone()

#define __DELTATIME CTimeManager::GetInst()->GetDT()

#define __KEY_CONFIRM(_key, _State) CKeyManager::GetInst()->GetKeyState(_key) == _State
#define __KEY_TAP(_key) __KEY_CONFIRM(_key, KEY_STATE::TAP)
#define __KEY_HOLD(_key) __KEY_CONFIRM(_key, KEY_STATE::HOLD)
#define __KEY_AWAY(_key) __KEY_CONFIRM(_key, KEY_STATE::AWAY)
#define __KEY_NONE(_key) __KEY_CONFIRM(_key, KEY_STATE::NONE)


#define __MOUSE_POS CKeyManager::GetInst()->GetMousePos()

#define PI	3.14159265358979323846264f

#define PATH_LIMIT	255

#define TILE_SIZE	16

enum class GROUP_TYPE
{
	DEFAULT,

	TILE,

	PLAYER,
	ENEMY,

	PROJECTILE_PLAYER,
	PROJECTILE_ENEMY,

	EFFECT,

	UI = 31,

	COUNT = 32,
};

enum class SCENE_TYPE
{
	ENTRY,

	EDITOR,

	STAGE1,
	STAGE2,

	COUNT,
};

enum class COMPONENT_TYPE
{
	COLLIDER,
	ANIMATOR,

	COUNT
};

enum class BRUSH_TYPE
{
	HOLLOW,

	COUNT
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	
	COUNT
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_SUBSTITUTE,

	COUNT
};

enum class ENABLE_FUNC
{
	NULL_PARAM,
	ONE_PARAM,
	TWO_PARAM,
	THREE_PARAM,

	DISABLE,
};

enum class FUNCTION_REGISTER_BUTTON
{
	LBUTTON,
	RBUTTON,
};