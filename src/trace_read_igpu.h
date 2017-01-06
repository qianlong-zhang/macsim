#ifndef _TRACE_READ_IGPU_H
#define _TRACE_READ_IGPU_H

#include "trace_read_cpu.h"

class igpu_decoder_c : public cpu_decoder_c
{
  public:
    igpu_decoder_c(macsim_c* simBase, ofstream* dprint_output)
      : cpu_decoder_c(simBase, dprint_output) 
    {
      m_trace_size = sizeof(trace_info_igpu_s) - sizeof(uint64_t);
    }

  private:
    void init_pin_convert();
    inst_info_s* convert_pinuop_to_t_uop(void *pi, trace_uop_s **trace_uop, 
        int core_id, int sim_thread_id);
    void convert_dyn_uop(inst_info_s *info, void *pi, trace_uop_s *trace_uop, 
        Addr rep_offset, int core_id);
    inst_info_s* get_inst_info(thread_s *thread_trace_info, int core_id, int sim_thread_id);
    void dprint_inst(void *t_info, int core_id, int thread_id);
};

typedef enum IGPU_OPCODE_ENUM_ {
  IGPU_INS_INVALID = 0,
  IGPU_INS_3DNOW,
  IGPU_INS_AES,
  IGPU_INS_AVX,
  IGPU_INS_AVX2,
  IGPU_INS_AVX2GATHER,
  IGPU_INS_BDW,
  IGPU_INS_BINARY,
  IGPU_INS_BITBYTE,
  IGPU_INS_BMI1,
  IGPU_INS_BMI2,
  IGPU_INS_BROADCAST,
  IGPU_INS_CALL,
  IGPU_INS_CMOV,
  IGPU_INS_COND_BR,
  IGPU_INS_CONVERT,
  IGPU_INS_DATAXFER,
  IGPU_INS_DECIMAL,
  IGPU_INS_FCMOV,
  IGPU_INS_FLAGOP,
  IGPU_INS_FMA4,
  IGPU_INS_INTERRUPT,
  IGPU_INS_IO,
  IGPU_INS_IOSTRINGOP,
  IGPU_INS_LOGICAL,
  IGPU_INS_LZCNT,
  IGPU_INS_MISC,
  IGPU_INS_MMX,
  IGPU_INS_NOP,
  IGPU_INS_PCLMULQDQ,
  IGPU_INS_POP,
  IGPU_INS_PREFETCH,
  IGPU_INS_PUSH,
  IGPU_INS_RDRAND,
  IGPU_INS_RDSEED,
  IGPU_INS_RDWRFSGS,
  IGPU_INS_RET,
  IGPU_INS_ROTATE,
  IGPU_INS_SEGOP,
  IGPU_INS_SEMAPHORE,
  IGPU_INS_SHIFT,
  IGPU_INS_SSE,
  IGPU_INS_STRINGOP,
  IGPU_INS_STTNI,
  IGPU_INS_SYSCALL,
  IGPU_INS_SYSRET,
  IGPU_INS_SYSTEM,
  IGPU_INS_TBM,
  IGPU_INS_UNCOND_BR,
  IGPU_INS_VFMA,
  IGPU_INS_VTX,
  IGPU_INS_WIDENOP,
  IGPU_INS_X87_ALU,
  IGPU_INS_XOP,
  IGPU_INS_XSAVE,
  IGPU_INS_XSAVEOPT,
	IGPU_INS_TR_MUL,            
  IGPU_INS_TR_DIV,
  IGPU_INS_TR_FMUL,                                
  IGPU_INS_TR_FDIV,                                
  IGPU_INS_TR_NOP,                                 
  IGPU_INS_PREFETCH_NTA,
  IGPU_INS_PREFETCH_T0,                            
  IGPU_INS_PREFETCH_T1,                                    
  IGPU_INS_PREFETCH_T2,                           
  IGPU_INS_GPU_EN,                                 
  IGPU_INS_CPU_MEM_EXT_OP, // To denote that the op is a continuation of the same parent op but has more mem accesses.
  IGPU_INS_LAST, // To mark the end of the list of instructions
} IGPU_OPCODE;

static const char* igpu_opcode_names[IGPU_INS_ENDING] =  {
  "IGPU_INS_INVALID",
  "IGPU_INS_3DNOW",
  "IGPU_INS_AES",
  "IGPU_INS_AVX",
  "IGPU_INS_AVX2",
  "IGPU_INS_AVX2GATHER",
  "IGPU_INS_BDW",
  "IGPU_INS_BINARY",
  "IGPU_INS_BITBYTE",
  "IGPU_INS_BMI1",
  "IGPU_INS_BMI2",
  "IGPU_INS_BROADCAST",
  "IGPU_INS_CALL",
  "IGPU_INS_CMOV",
  "IGPU_INS_COND_BR",
  "IGPU_INS_CONVERT",
  "IGPU_INS_DATAXFER",
  "IGPU_INS_DECIMAL",
  "IGPU_INS_FCMOV",
  "IGPU_INS_FLAGOP",
  "IGPU_INS_FMA4",
  "IGPU_INS_INTERRUPT",
  "IGPU_INS_IO",
  "IGPU_INS_IOSTRINGOP",
  "IGPU_INS_LOGICAL",
  "IGPU_INS_LZCNT",
  "IGPU_INS_MISC",
  "IGPU_INS_MMX",
  "IGPU_INS_NOP",
  "IGPU_INS_PCLMULQDQ",
  "IGPU_INS_POP",
  "IGPU_INS_PREFETCH",
  "IGPU_INS_PUSH",
  "IGPU_INS_RDRAND",
  "IGPU_INS_RDSEED",
  "IGPU_INS_RDWRFSGS",
  "IGPU_INS_RET",
  "IGPU_INS_ROTATE",
  "IGPU_INS_SEGOP",
  "IGPU_INS_SEMAPHORE",
  "IGPU_INS_SHIFT",
  "IGPU_INS_SSE",
  "IGPU_INS_STRINGOP",
  "IGPU_INS_STTNI",
  "IGPU_INS_SYSCALL",
  "IGPU_INS_SYSRET",
  "IGPU_INS_SYSTEM",
  "IGPU_INS_TBM",
  "IGPU_INS_UNCOND_BR",
  "IGPU_INS_VFMA",
  "IGPU_INS_VTX",
  "IGPU_INS_WIDENOP",
  "IGPU_INS_X87_ALU",
  "IGPU_INS_XOP",
  "IGPU_INS_XSAVE",
  "IGPU_INS_XSAVEOPT",
  "IGPU_INS_TR_MUL",
  "IGPU_INS_TR_DIV",
  "IGPU_INS_TR_FMUL",
  "IGPU_INS_TR_FDIV",
  "IGPU_INS_TR_NOP",
  "IGPU_INS_PREFETCH_NTA",
  "IGPU_INS_PREFETCH_T0",
  "IGPU_INS_PREFETCH_T1",
  "IGPU_INS_PREFETCH_T2",
  "IGPU_INS_GPU_EN",
  "IGPU_INS_CPU_MEM_EXT_OP"
};

#endif
