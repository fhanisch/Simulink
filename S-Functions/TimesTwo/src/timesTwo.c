#define _CRT_SECURE_NO_WARNINGS
#define NDEBUG
//#define MATLAB_MEX_FILE
#define SL_INTERNAL
#define S_FUNCTION_NAME  TimesTwo
#define S_FUNCTION_LEVEL 2

#include <stdio.h>
#include "tmwtypes.h"
#include "simstruc.h"

static void mdlInitializeSizes(SimStruct *S)
{
	//printf("ModelName: %s\n", ssGetModelName(S));
	ssSetNumSFcnParams(S, 0);
	S->sizes.in.numInputPorts = 1; //ssSetNumInputPorts(S, 1);
	ssSetInputPortWidth(S, 0, 1);
	ssSetInputPortDirectFeedThrough(S, 0, 1);
	S->sizes.out.numOutputPorts = 1; //ssSetNumOutputPorts(S,1);
	ssSetOutputPortWidth(S, 0, 1);
	ssSetNumSampleTimes(S, 1);
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
	ssSetSampleTime(S, 0, 0.001);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
	//printf("u = %f\n", *uPtrs);
	real_T *y = ssGetOutputPortRealSignal(S,0);
	*y = 2.0 * *(real_T*)uPtrs;
}

static void mdlTerminate(SimStruct *S)
{
}

//#include "simulink.c"

int main(int argc, char *argv[])
{
	const char *modelName = "TimesTwo";
	//printf("S-Function Test\n");
	SimStruct S;
	S.modelName = modelName;
	time_T sampleTime;
	time_T offsetTime;
	S.stInfo.sampleTimes = &sampleTime;
	S.stInfo.offsetTimes = &offsetTime;
	real_T u = 1.75;
	real_T y;
	struct _ssPortInputs input;
	input.signal.ptrs = (InputPtrsType)&u;
	S.portInfo.inputs = &input;
	struct _ssPortOutputs output;
	output.signalVect = &y;
	S.portInfo.outputs = &output;
	mdlInitializeSizes(&S);
	mdlInitializeSampleTimes(&S);
	mdlOutputs(&S,0);
	//printf("y = %f\n", y);

	return 0;
}