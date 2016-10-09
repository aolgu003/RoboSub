#ifndef __c2_auv_6dof_sim_h__
#define __c2_auv_6dof_sim_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_auv_6dof_simInstanceStruct
#define typedef_SFc2_auv_6dof_simInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_auv_6dof_sim;
  const mxArray *c2_aircraftHandle;
  boolean_T c2_aircraftHandle_not_empty;
  real_T (*c2_u)[13];
} SFc2_auv_6dof_simInstanceStruct;

#endif                                 /*typedef_SFc2_auv_6dof_simInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_auv_6dof_sim_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_auv_6dof_sim_get_check_sum(mxArray *plhs[]);
extern void c2_auv_6dof_sim_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
