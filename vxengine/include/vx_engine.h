/*
 * vxEngine.h
 *
 *  Created on: Dec 10, 2018
 *      Author: root
 */

#ifndef _VX_ENGINE_H_
#define _VX_ENGINE_H_

#include "vxParameter.h"

class CVxEngine {
public:
	virtual ~CVxEngine(){};
	virtual int Initialize(int paramCount, int defaultTargetAffinity, int defaultTargetInfo, bool enableScheduleGraph, bool disableVirtual, bool enableFullProfile, bool disableNodeFlushForCL, std::string discardCommandList) = 0;
	virtual void SetConfigOptions(bool verbose, bool discardCompareErrors, bool enableDumpProfile, bool enableDumpGDF, int waitKeyDelayInMilliSeconds)= 0;
	virtual void SetFrameCountOptions(bool enableMultiFrameProcessing, bool framesEofRequested, bool frameCountSpecified, int frameStart, int frameEnd)= 0;
	virtual int SetGraphOptimizerFlags(vx_uint32 graph_optimizer_flags)= 0;
	virtual void SetDumpDataConfig(std::string dumpDataConfig)= 0;
	virtual int SetParameter(int index, const char * param)= 0;
	virtual int Shell(int level, FILE * fp = nullptr)= 0;
	virtual int Run()= 0;
	virtual int BuildGraph(int level, char * graphScript)= 0;
	virtual int SetImportedData(vx_reference ref, const char * name, const char * params)= 0;
	virtual int Shutdown()= 0;
	virtual void DisableWaitForKeyPress()= 0;
};
#endif /* DEPS_AMDOVX_CORE_VXENGINE_INCLUDE_VX_ENGINE_H_ */
