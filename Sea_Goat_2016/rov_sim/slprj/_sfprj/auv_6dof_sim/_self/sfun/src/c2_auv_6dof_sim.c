/* Include files */

#include "auv_6dof_sim_sfun.h"
#include "c2_auv_6dof_sim.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "auv_6dof_sim_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[23] = { "pn", "pe", "pd", "ux", "vx",
  "wx", "phi", "theta", "psi", "p", "q", "r", "t", "field_width", "V", "F",
  "patchcolors", "XYZ", "R", "nargin", "nargout", "u", "aircraftHandle" };

static const char * c2_b_debug_family_names[10] = { "patchcolors", "F", "V",
  "myred", "mygreen", "myblue", "myyellow", "mycyan", "nargin", "nargout" };

static const char * c2_c_debug_family_names[10] = { "R_roll", "R_pitch", "R_yaw",
  "R", "nargin", "nargout", "XYZ", "phi", "theta", "psi" };

static const char * c2_d_debug_family_names[10] = { "R_roll", "R_pitch", "R_yaw",
  "R", "nargin", "nargout", "XYZ", "phi", "theta", "psi" };

static const char * c2_e_debug_family_names[12] = { "V", "F", "patchcolors",
  "XYZ", "R", "mode", "nargin", "nargout", "phi", "theta", "psi", "handle" };

/* Function Declarations */
static void initialize_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void initialize_params_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void enable_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void disable_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_auv_6dof_sim
  (SFc2_auv_6dof_simInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_auv_6dof_sim
  (SFc2_auv_6dof_simInstanceStruct *chartInstance);
static void set_sim_state_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void sf_gateway_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void mdl_start_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void initSimStructsc2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);
static void c2_spacecraftVFC(SFc2_auv_6dof_simInstanceStruct *chartInstance);
static const mxArray *c2_drawSpacecraftBody(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, real_T c2_phi, real_T c2_theta, real_T c2_psi, const mxArray
  *c2_handle);
static void c2_rotate(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
                      c2_XYZ[48], real_T c2_phi, real_T c2_theta, real_T c2_psi,
                      real_T c2_b_XYZ[48]);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static boolean_T c2_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_isempty, const char_T *c2_identifier);
static boolean_T c2_b_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[48]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[33]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_f_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[44]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[48]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_h_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y[6]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_b_rotate(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
  c2_XYZ[48], real_T c2_phi, real_T c2_theta, real_T c2_psi, real_T c2_b_XYZ[48]);
static real_T c2_cos(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T c2_x);
static real_T c2_sin(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T c2_x);
static void c2_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance);
static void c2_b_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance);
static void c2_c_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance);
static void c2_d_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_j_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_k_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_aircraftHandle, const char_T
  *c2_identifier, boolean_T *c2_svPtr);
static const mxArray *c2_l_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  boolean_T *c2_svPtr);
static uint8_T c2_m_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_auv_6dof_sim, const char_T
  *c2_identifier);
static uint8_T c2_n_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_cos(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
                     *c2_x);
static void c2_b_sin(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
                     *c2_x);
static void init_dsm_address_info(SFc2_auv_6dof_simInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_auv_6dof_simInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_auv_6dof_sim(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_aircraftHandle = NULL;
  chartInstance->c2_aircraftHandle_not_empty = false;
  chartInstance->c2_is_active_c2_auv_6dof_sim = 0U;
}

static void initialize_params_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_auv_6dof_sim
  (SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_auv_6dof_sim
  (SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  const mxArray *c2_b_u;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_b_u = sf_mex_dup(chartInstance->c2_aircraftHandle);
  c2_b_y = NULL;
  if (!chartInstance->c2_aircraftHandle_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_duplicatearraysafe(&c2_b_u), false);
  }

  sf_mex_destroy(&c2_b_u);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_auv_6dof_sim;
  c2_c_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_b_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_b_u = sf_mex_dup(c2_st);
  sf_mex_assign(&chartInstance->c2_aircraftHandle, c2_k_emlrt_marshallIn
                (chartInstance, sf_mex_dup(sf_mex_getcell("aircraftHandle",
    c2_b_u, 0)), "aircraftHandle", &chartInstance->c2_aircraftHandle_not_empty),
                true);
  chartInstance->c2_is_active_c2_auv_6dof_sim = c2_m_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c2_auv_6dof_sim",
       c2_b_u, 1)), "is_active_c2_auv_6dof_sim");
  sf_mex_destroy(&c2_b_u);
  c2_update_debugger_state_c2_auv_6dof_sim(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c2_aircraftHandle);
}

static void sf_gateway_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  int32_T c2_i0;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i0 = 0; c2_i0 < 13; c2_i0++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_u)[c2_i0], 0U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_auv_6dof_sim(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_auv_6dof_simMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  int32_T c2_i1;
  uint32_T c2_debug_family_var_map[23];
  real_T c2_b_u[13];
  real_T c2_pn;
  real_T c2_pe;
  real_T c2_pd;
  real_T c2_ux;
  real_T c2_vx;
  real_T c2_wx;
  real_T c2_phi;
  real_T c2_theta;
  real_T c2_psi;
  real_T c2_p;
  real_T c2_q;
  real_T c2_r;
  real_T c2_t;
  real_T c2_field_width;
  real_T c2_V[48];
  real_T c2_F[44];
  real_T c2_patchcolors[33];
  real_T c2_XYZ[48];
  real_T c2_R[9];
  real_T c2_b_V[48];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 0.0;
  int32_T c2_i2;
  real_T c2_c_u;
  const mxArray *c2_y = NULL;
  static real_T c2_dv0[48] = { 2.0, 0.2, 0.2, 0.2, 0.2, -4.0, -3.0, -4.0, 0.0,
    -1.0, 0.0, -1.0, -3.0, -3.0, -4.0, -4.0, 0.0, 0.2, -0.2, -0.2, 0.2, 0.0, 0.0,
    0.0, 3.0, 3.0, -3.0, -3.0, 1.0, -1.0, 1.0, -1.0, 0.0, 0.2, 0.2, -0.2, -0.2,
    0.0, 0.0, -0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i3;
  int32_T c2_i4;
  static real_T c2_b_F[44] = { 1.0, 3.0, 1.0, 1.0, 3.0, 4.0, 5.0, 2.0, 7.0, 9.0,
    13.0, 3.0, 1.0, 5.0, 5.0, 6.0, 6.0, 6.0, 6.0, 6.0, 10.0, 15.0, 4.0, 2.0, 2.0,
    4.0, 4.0, 5.0, 2.0, 3.0, 8.0, 12.0, 16.0, 1.0, 3.0, 1.0, 1.0, 3.0, 4.0, 5.0,
    2.0, 7.0, 11.0, 14.0 };

  static real_T c2_b_patchcolors[33] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0 };

  int32_T c2_i5;
  real_T c2_dv1[48];
  real_T c2_dv2[48];
  static real_T c2_dv3[48] = { 2.0, 0.0, 0.0, 0.2, 0.2, 0.2, 0.2, -0.2, 0.2, 0.2,
    -0.2, -0.2, 0.2, 0.2, -0.2, -4.0, 0.0, 0.0, -3.0, 0.0, 0.0, -4.0, 0.0, -0.3,
    0.0, 3.0, 0.0, -1.0, 3.0, 0.0, 0.0, -3.0, 0.0, -1.0, -3.0, 0.0, -3.0, 1.0,
    0.0, -3.0, -1.0, 0.0, -4.0, 1.0, 0.0, -4.0, -1.0, 0.0 };

  int32_T c2_i6;
  int32_T c2_i7;
  static real_T c2_a[9] = { 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 };

  int32_T c2_i8;
  int32_T c2_i9;
  real_T c2_b[48];
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  real_T c2_C[48];
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  const mxArray *c2_b_y = NULL;
  static char_T c2_d_u[8] = { 'V', 'e', 'r', 't', 'i', 'c', 'e', 's' };

  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  const mxArray *c2_c_y = NULL;
  int32_T c2_i20;
  real_T c2_e_u[48];
  int32_T c2_i21;
  const mxArray *c2_d_y = NULL;
  static char_T c2_f_u[5] = { 'F', 'a', 'c', 'e', 's' };

  int32_T c2_i22;
  const mxArray *c2_e_y = NULL;
  real_T c2_g_u[44];
  const mxArray *c2_f_y = NULL;
  static char_T c2_h_u[15] = { 'F', 'a', 'c', 'e', 'V', 'e', 'r', 't', 'e', 'x',
    'C', 'D', 'a', 't', 'a' };

  int32_T c2_i23;
  const mxArray *c2_g_y = NULL;
  real_T c2_i_u[33];
  const mxArray *c2_h_y = NULL;
  static char_T c2_j_u[9] = { 'F', 'a', 'c', 'e', 'C', 'o', 'l', 'o', 'r' };

  const mxArray *c2_i_y = NULL;
  static char_T c2_k_u[4] = { 'f', 'l', 'a', 't' };

  const mxArray *c2_j_y = NULL;
  static char_T c2_l_u[9] = { 'E', 'r', 'a', 's', 'e', 'M', 'o', 'd', 'e' };

  const mxArray *c2_k_y = NULL;
  static char_T c2_m_u[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i1 = 0; c2_i1 < 13; c2_i1++) {
    c2_b_u[c2_i1] = (*chartInstance->c2_u)[c2_i1];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 24U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_pn, 0U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_pe, 1U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_pd, 2U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ux, 3U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_vx, 4U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_wx, 5U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi, 6U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_theta, 7U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_psi, 8U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_p, 9U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_q, 10U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_r, 11U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_t, 12U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_field_width, 13U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_V, MAX_uint32_T, c2_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_F, 15U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_patchcolors, 16U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_XYZ, 17U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_R, 18U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_V, MAX_uint32_T, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 19U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 20U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_u, 21U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&chartInstance->c2_aircraftHandle, 22U,
    c2_sf_marshallOut);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  c2_pn = c2_b_u[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_pe = c2_b_u[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_pd = c2_b_u[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_ux = c2_b_u[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_vx = c2_b_u[4];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_wx = c2_b_u[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_phi = c2_b_u[6];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  c2_theta = c2_b_u[7];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  c2_psi = c2_b_u[8];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_p = c2_b_u[9];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  c2_q = c2_b_u[10];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_r = c2_b_u[11];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
  c2_t = c2_b_u[12];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  c2_field_width = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_aircraftHandle_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
    c2_spacecraftVFC(chartInstance);
    for (c2_i2 = 0; c2_i2 < 48; c2_i2++) {
      c2_V[c2_i2] = c2_dv0[c2_i2];
    }

    _SFD_SYMBOL_SWITCH(14U, 14U);
    for (c2_i3 = 0; c2_i3 < 44; c2_i3++) {
      c2_F[c2_i3] = c2_b_F[c2_i3];
    }

    for (c2_i4 = 0; c2_i4 < 33; c2_i4++) {
      c2_patchcolors[c2_i4] = c2_b_patchcolors[c2_i4];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
    for (c2_i5 = 0; c2_i5 < 48; c2_i5++) {
      c2_dv1[c2_i5] = c2_dv3[c2_i5];
    }

    c2_b_rotate(chartInstance, c2_dv1, c2_phi, c2_theta, c2_psi, c2_dv2);
    for (c2_i6 = 0; c2_i6 < 48; c2_i6++) {
      c2_XYZ[c2_i6] = c2_dv2[c2_i6];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
    for (c2_i7 = 0; c2_i7 < 9; c2_i7++) {
      c2_R[c2_i7] = c2_a[c2_i7];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
    for (c2_i8 = 0; c2_i8 < 48; c2_i8++) {
      c2_b[c2_i8] = c2_XYZ[c2_i8];
    }

    for (c2_i9 = 0; c2_i9 < 48; c2_i9++) {
      c2_b_V[c2_i9] = 0.0;
    }

    for (c2_i10 = 0; c2_i10 < 48; c2_i10++) {
      c2_b_V[c2_i10] = 0.0;
    }

    for (c2_i11 = 0; c2_i11 < 48; c2_i11++) {
      c2_C[c2_i11] = c2_b_V[c2_i11];
    }

    for (c2_i12 = 0; c2_i12 < 48; c2_i12++) {
      c2_b_V[c2_i12] = c2_C[c2_i12];
    }

    for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
      c2_i14 = 0;
      for (c2_i15 = 0; c2_i15 < 16; c2_i15++) {
        c2_b_V[c2_i14 + c2_i13] = 0.0;
        c2_i18 = 0;
        for (c2_i19 = 0; c2_i19 < 3; c2_i19++) {
          c2_b_V[c2_i14 + c2_i13] += c2_a[c2_i18 + c2_i13] * c2_b[c2_i19 +
            c2_i14];
          c2_i18 += 3;
        }

        c2_i14 += 3;
      }
    }

    _SFD_SYMBOL_SWITCH(14U, 19U);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 10, 0U, 1U, 0U, 2, 1, 8),
                  false);
    c2_i16 = 0;
    for (c2_i17 = 0; c2_i17 < 3; c2_i17++) {
      c2_i20 = 0;
      for (c2_i21 = 0; c2_i21 < 16; c2_i21++) {
        c2_e_u[c2_i21 + c2_i16] = c2_b_V[c2_i20 + c2_i17];
        c2_i20 += 3;
      }

      c2_i16 += 16;
    }

    c2_c_y = NULL;
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 16, 3),
                  false);
    c2_d_y = NULL;
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_f_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    for (c2_i22 = 0; c2_i22 < 44; c2_i22++) {
      c2_g_u[c2_i22] = c2_F[c2_i22];
    }

    c2_e_y = NULL;
    sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_g_u, 0, 0U, 1U, 0U, 2, 11, 4),
                  false);
    c2_f_y = NULL;
    sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_h_u, 10, 0U, 1U, 0U, 2, 1, 15),
                  false);
    for (c2_i23 = 0; c2_i23 < 33; c2_i23++) {
      c2_i_u[c2_i23] = c2_patchcolors[c2_i23];
    }

    c2_g_y = NULL;
    sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 2, 11, 3),
                  false);
    c2_h_y = NULL;
    sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_j_u, 10, 0U, 1U, 0U, 2, 1, 9),
                  false);
    c2_i_y = NULL;
    sf_mex_assign(&c2_i_y, sf_mex_create("y", c2_k_u, 10, 0U, 1U, 0U, 2, 1, 4),
                  false);
    c2_j_y = NULL;
    sf_mex_assign(&c2_j_y, sf_mex_create("y", c2_l_u, 10, 0U, 1U, 0U, 2, 1, 9),
                  false);
    c2_k_y = NULL;
    sf_mex_assign(&c2_k_y, sf_mex_create("y", c2_m_u, 10, 0U, 1U, 0U, 2, 1, 6),
                  false);
    sf_mex_assign(&chartInstance->c2_aircraftHandle, sf_mex_call_debug
                  (sfGlobalDebugInstanceStruct, "patch", 1U, 10U, 14, c2_b_y, 14,
                   c2_c_y, 14, c2_d_y, 14, c2_e_y, 14, c2_f_y, 14, c2_g_y, 14,
                   c2_h_y, 14, c2_i_y, 14, c2_j_y, 14, c2_k_y), true);
    chartInstance->c2_aircraftHandle_not_empty = true;
    chartInstance->c2_aircraftHandle_not_empty = !c2_emlrt_marshallIn
      (chartInstance, sf_mex_call_debug(sfGlobalDebugInstanceStruct, "isempty",
        1U, 1U, 14, sf_mex_dup(chartInstance->c2_aircraftHandle)), "isempty");
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 0, c2_t, 0.0, -1, 0U, c2_t ==
        0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
    c2_c_u = 1.0;
    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "figure", 0U, 1U, 14, c2_y);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "clf", 0U, 0U);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
    sf_mex_assign(&chartInstance->c2_aircraftHandle, c2_drawSpacecraftBody
                  (chartInstance, c2_phi, c2_theta, c2_psi, sf_mex_dup
                   (chartInstance->c2_aircraftHandle)), true);
    chartInstance->c2_aircraftHandle_not_empty = !c2_emlrt_marshallIn
      (chartInstance, sf_mex_call_debug(sfGlobalDebugInstanceStruct, "isempty",
        1U, 1U, 14, sf_mex_dup(chartInstance->c2_aircraftHandle)), "isempty");
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
    sf_mex_assign(&chartInstance->c2_aircraftHandle, c2_drawSpacecraftBody
                  (chartInstance, c2_phi, c2_theta, c2_psi, sf_mex_dup
                   (chartInstance->c2_aircraftHandle)), true);
    chartInstance->c2_aircraftHandle_not_empty = !c2_emlrt_marshallIn
      (chartInstance, sf_mex_call_debug(sfGlobalDebugInstanceStruct, "isempty",
        1U, 1U, 14, sf_mex_dup(chartInstance->c2_aircraftHandle)), "isempty");
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -49);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_auv_6dof_sim(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_spacecraftVFC(SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  uint32_T c2_debug_family_var_map[10];
  real_T c2_patchcolors[33];
  real_T c2_F[44];
  real_T c2_V[48];
  real_T c2_myred[3];
  real_T c2_mygreen[3];
  real_T c2_myblue[3];
  real_T c2_myyellow[3];
  real_T c2_mycyan[3];
  real_T c2_nargin = 0.0;
  real_T c2_nargout = 3.0;
  int32_T c2_i24;
  static real_T c2_dv4[48] = { 2.0, 0.2, 0.2, 0.2, 0.2, -4.0, -3.0, -4.0, 0.0,
    -1.0, 0.0, -1.0, -3.0, -3.0, -4.0, -4.0, 0.0, 0.2, -0.2, -0.2, 0.2, 0.0, 0.0,
    0.0, 3.0, 3.0, -3.0, -3.0, 1.0, -1.0, 1.0, -1.0, 0.0, 0.2, 0.2, -0.2, -0.2,
    0.0, 0.0, -0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i25;
  static real_T c2_dv5[44] = { 1.0, 3.0, 1.0, 1.0, 3.0, 4.0, 5.0, 2.0, 7.0, 9.0,
    13.0, 3.0, 1.0, 5.0, 5.0, 6.0, 6.0, 6.0, 6.0, 6.0, 10.0, 15.0, 4.0, 2.0, 2.0,
    4.0, 4.0, 5.0, 2.0, 3.0, 8.0, 12.0, 16.0, 1.0, 3.0, 1.0, 1.0, 3.0, 4.0, 5.0,
    2.0, 7.0, 11.0, 14.0 };

  int32_T c2_i26;
  static real_T c2_dv6[3] = { 1.0, 0.0, 0.0 };

  int32_T c2_i27;
  static real_T c2_dv7[3] = { 0.0, 1.0, 0.0 };

  int32_T c2_i28;
  static real_T c2_dv8[3] = { 0.0, 0.0, 1.0 };

  int32_T c2_i29;
  static real_T c2_dv9[3] = { 1.0, 1.0, 0.0 };

  int32_T c2_i30;
  static real_T c2_dv10[3] = { 0.0, 1.0, 1.0 };

  int32_T c2_i31;
  static real_T c2_dv11[33] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0 };

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_patchcolors, 0U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_F, 1U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_V, 2U, c2_h_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_myred, 3U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_mygreen, 4U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_myblue, 5U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_myyellow, 6U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_mycyan, 7U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 8U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 9U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 5);
  for (c2_i24 = 0; c2_i24 < 48; c2_i24++) {
    c2_V[c2_i24] = c2_dv4[c2_i24];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 24);
  for (c2_i25 = 0; c2_i25 < 44; c2_i25++) {
    c2_F[c2_i25] = c2_dv5[c2_i25];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 39);
  for (c2_i26 = 0; c2_i26 < 3; c2_i26++) {
    c2_myred[c2_i26] = c2_dv6[c2_i26];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 40);
  for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
    c2_mygreen[c2_i27] = c2_dv7[c2_i27];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 41);
  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    c2_myblue[c2_i28] = c2_dv8[c2_i28];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 42);
  for (c2_i29 = 0; c2_i29 < 3; c2_i29++) {
    c2_myyellow[c2_i29] = c2_dv9[c2_i29];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 43);
  for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
    c2_mycyan[c2_i30] = c2_dv10[c2_i30];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 45);
  for (c2_i31 = 0; c2_i31 < 33; c2_i31++) {
    c2_patchcolors[c2_i31] = c2_dv11[c2_i31];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -45);
  _SFD_SYMBOL_SCOPE_POP();
}

static const mxArray *c2_drawSpacecraftBody(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, real_T c2_phi, real_T c2_theta, real_T c2_psi, const mxArray
  *c2_handle)
{
  const mxArray *c2_b_handle;
  uint32_T c2_debug_family_var_map[12];
  real_T c2_V[48];
  real_T c2_F[44];
  real_T c2_patchcolors[33];
  real_T c2_XYZ[48];
  real_T c2_R[9];
  real_T c2_b_V[48];
  char_T c2_mode[6];
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i32;
  static char_T c2_cv0[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  int32_T c2_i33;
  static real_T c2_dv12[48] = { 2.0, 0.2, 0.2, 0.2, 0.2, -4.0, -3.0, -4.0, 0.0,
    -1.0, 0.0, -1.0, -3.0, -3.0, -4.0, -4.0, 0.0, 0.2, -0.2, -0.2, 0.2, 0.0, 0.0,
    0.0, 3.0, 3.0, -3.0, -3.0, 1.0, -1.0, 1.0, -1.0, 0.0, 0.2, 0.2, -0.2, -0.2,
    0.0, 0.0, -0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i34;
  int32_T c2_i35;
  static real_T c2_b_F[44] = { 1.0, 3.0, 1.0, 1.0, 3.0, 4.0, 5.0, 2.0, 7.0, 9.0,
    13.0, 3.0, 1.0, 5.0, 5.0, 6.0, 6.0, 6.0, 6.0, 6.0, 10.0, 15.0, 4.0, 2.0, 2.0,
    4.0, 4.0, 5.0, 2.0, 3.0, 8.0, 12.0, 16.0, 1.0, 3.0, 1.0, 1.0, 3.0, 4.0, 5.0,
    2.0, 7.0, 11.0, 14.0 };

  static real_T c2_b_patchcolors[33] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0 };

  int32_T c2_i36;
  real_T c2_dv13[48];
  real_T c2_dv14[48];
  static real_T c2_dv15[48] = { 2.0, 0.0, 0.0, 0.2, 0.2, 0.2, 0.2, -0.2, 0.2,
    0.2, -0.2, -0.2, 0.2, 0.2, -0.2, -4.0, 0.0, 0.0, -3.0, 0.0, 0.0, -4.0, 0.0,
    -0.3, 0.0, 3.0, 0.0, -1.0, 3.0, 0.0, 0.0, -3.0, 0.0, -1.0, -3.0, 0.0, -3.0,
    1.0, 0.0, -3.0, -1.0, 0.0, -4.0, 1.0, 0.0, -4.0, -1.0, 0.0 };

  int32_T c2_i37;
  int32_T c2_i38;
  static real_T c2_a[9] = { 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 };

  int32_T c2_i39;
  int32_T c2_i40;
  real_T c2_b[48];
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  real_T c2_C[48];
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  const mxArray *c2_y = NULL;
  static char_T c2_b_u[8] = { 'V', 'e', 'r', 't', 'i', 'c', 'e', 's' };

  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i51;
  real_T c2_c_u[48];
  int32_T c2_i52;
  const mxArray *c2_c_y = NULL;
  static char_T c2_d_u[5] = { 'F', 'a', 'c', 'e', 's' };

  int32_T c2_i53;
  const mxArray *c2_d_y = NULL;
  real_T c2_e_u[44];
  const mxArray *c2_e_y = NULL;
  static char_T c2_f_u[14] = { 'C', 'a', 'm', 'e', 'r', 'a', 'P', 'o', 's', 'i',
    't', 'i', 'o', 'n' };

  int32_T c2_i54;
  const mxArray *c2_f_y = NULL;
  c2_b_handle = NULL;
  c2_b_handle = NULL;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 14U, c2_e_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_V, MAX_uint32_T, c2_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_F, 1U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_patchcolors, 2U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_XYZ, 3U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_R, 4U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_V, MAX_uint32_T, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_mode, 5U, c2_k_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 6U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 7U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi, 8U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_theta, 9U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_psi, 10U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_handle, 11U, c2_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_handle, MAX_uint32_T, c2_j_sf_marshallOut);
  for (c2_i32 = 0; c2_i32 < 6; c2_i32++) {
    c2_mode[c2_i32] = c2_cv0[c2_i32];
  }

  sf_mex_assign(&c2_b_handle, sf_mex_dup(c2_handle), false);
  _SFD_SYMBOL_SWITCH(11U, 13U);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 4);
  c2_spacecraftVFC(chartInstance);
  for (c2_i33 = 0; c2_i33 < 48; c2_i33++) {
    c2_V[c2_i33] = c2_dv12[c2_i33];
  }

  _SFD_SYMBOL_SWITCH(0U, 0U);
  for (c2_i34 = 0; c2_i34 < 44; c2_i34++) {
    c2_F[c2_i34] = c2_b_F[c2_i34];
  }

  for (c2_i35 = 0; c2_i35 < 33; c2_i35++) {
    c2_patchcolors[c2_i35] = c2_b_patchcolors[c2_i35];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 6);
  for (c2_i36 = 0; c2_i36 < 48; c2_i36++) {
    c2_dv13[c2_i36] = c2_dv15[c2_i36];
  }

  c2_rotate(chartInstance, c2_dv13, c2_phi, c2_theta, c2_psi, c2_dv14);
  for (c2_i37 = 0; c2_i37 < 48; c2_i37++) {
    c2_XYZ[c2_i37] = c2_dv14[c2_i37];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 10);
  for (c2_i38 = 0; c2_i38 < 9; c2_i38++) {
    c2_R[c2_i38] = c2_a[c2_i38];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 16);
  for (c2_i39 = 0; c2_i39 < 48; c2_i39++) {
    c2_b[c2_i39] = c2_XYZ[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 48; c2_i40++) {
    c2_b_V[c2_i40] = 0.0;
  }

  for (c2_i41 = 0; c2_i41 < 48; c2_i41++) {
    c2_b_V[c2_i41] = 0.0;
  }

  for (c2_i42 = 0; c2_i42 < 48; c2_i42++) {
    c2_C[c2_i42] = c2_b_V[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 48; c2_i43++) {
    c2_b_V[c2_i43] = c2_C[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 3; c2_i44++) {
    c2_i45 = 0;
    for (c2_i46 = 0; c2_i46 < 16; c2_i46++) {
      c2_b_V[c2_i45 + c2_i44] = 0.0;
      c2_i49 = 0;
      for (c2_i50 = 0; c2_i50 < 3; c2_i50++) {
        c2_b_V[c2_i45 + c2_i44] += c2_a[c2_i49 + c2_i44] * c2_b[c2_i50 + c2_i45];
        c2_i49 += 3;
      }

      c2_i45 += 3;
    }
  }

  _SFD_SYMBOL_SWITCH(0U, 5U);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 23);
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 8),
                false);
  c2_i47 = 0;
  for (c2_i48 = 0; c2_i48 < 3; c2_i48++) {
    c2_i51 = 0;
    for (c2_i52 = 0; c2_i52 < 16; c2_i52++) {
      c2_c_u[c2_i52 + c2_i47] = c2_b_V[c2_i51 + c2_i48];
      c2_i51 += 3;
    }

    c2_i47 += 16;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 16, 3),
                false);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_d_u, 10, 0U, 1U, 0U, 2, 1, 5),
                false);
  for (c2_i53 = 0; c2_i53 < 44; c2_i53++) {
    c2_e_u[c2_i53] = c2_F[c2_i53];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 11, 4),
                false);
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_f_u, 10, 0U, 1U, 0U, 2, 1, 14),
                false);
  for (c2_i54 = 0; c2_i54 < 48; c2_i54++) {
    c2_b[c2_i54] = c2_XYZ[c2_i54];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_b, 0, 0U, 1U, 0U, 2, 3, 16),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "set", 0U, 7U, 14, sf_mex_dup
                    (c2_b_handle), 14, c2_y, 14, c2_b_y, 14, c2_c_y, 14, c2_d_y,
                    14, c2_e_y, 14, c2_f_y);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, -23);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c2_handle);
  return c2_b_handle;
}

static void c2_rotate(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
                      c2_XYZ[48], real_T c2_phi, real_T c2_theta, real_T c2_psi,
                      real_T c2_b_XYZ[48])
{
  uint32_T c2_debug_family_var_map[10];
  real_T c2_R_roll[9];
  real_T c2_R_pitch[9];
  real_T c2_R_yaw[9];
  real_T c2_R[9];
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i55;
  real_T c2_d0;
  real_T c2_d1;
  real_T c2_d2;
  real_T c2_d3;
  int32_T c2_i56;
  int32_T c2_i57;
  static real_T c2_dv16[3] = { 1.0, 0.0, 0.0 };

  real_T c2_d4;
  real_T c2_d5;
  real_T c2_d6;
  real_T c2_d7;
  int32_T c2_i58;
  int32_T c2_i59;
  static real_T c2_dv17[3] = { 0.0, 1.0, 0.0 };

  real_T c2_d8;
  real_T c2_d9;
  real_T c2_d10;
  real_T c2_d11;
  int32_T c2_i60;
  int32_T c2_i61;
  static real_T c2_dv18[3] = { 0.0, 0.0, 1.0 };

  int32_T c2_i62;
  int32_T c2_i63;
  real_T c2_a[9];
  int32_T c2_i64;
  real_T c2_b[9];
  int32_T c2_i65;
  int32_T c2_i66;
  int32_T c2_i67;
  int32_T c2_i68;
  real_T c2_y[9];
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  int32_T c2_i72;
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  real_T c2_b_b[48];
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  real_T c2_C[48];
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 11U, c2_d_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R_roll, 0U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R_pitch, 1U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R_yaw, 2U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R, 3U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_XYZ, 6U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi, 7U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_theta, 8U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_psi, 9U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_XYZ, MAX_uint32_T,
    c2_d_sf_marshallOut, c2_b_sf_marshallIn);
  for (c2_i55 = 0; c2_i55 < 48; c2_i55++) {
    c2_b_XYZ[c2_i55] = c2_XYZ[c2_i55];
  }

  _SFD_SYMBOL_SWITCH(6U, 10U);
  CV_SCRIPT_FCN(1, 1);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 27);
  c2_d0 = c2_phi;
  c2_b_cos(chartInstance, &c2_d0);
  c2_d1 = c2_phi;
  c2_b_sin(chartInstance, &c2_d1);
  c2_d2 = c2_phi;
  c2_b_sin(chartInstance, &c2_d2);
  c2_d3 = c2_phi;
  c2_b_cos(chartInstance, &c2_d3);
  c2_i56 = 0;
  for (c2_i57 = 0; c2_i57 < 3; c2_i57++) {
    c2_R_roll[c2_i56] = c2_dv16[c2_i57];
    c2_i56 += 3;
  }

  c2_R_roll[1] = 0.0;
  c2_R_roll[4] = c2_d0;
  c2_R_roll[7] = -c2_d1;
  c2_R_roll[2] = 0.0;
  c2_R_roll[5] = c2_d2;
  c2_R_roll[8] = c2_d3;
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 31);
  c2_d4 = c2_theta;
  c2_b_cos(chartInstance, &c2_d4);
  c2_d5 = c2_theta;
  c2_b_sin(chartInstance, &c2_d5);
  c2_d6 = c2_theta;
  c2_b_sin(chartInstance, &c2_d6);
  c2_d7 = c2_theta;
  c2_b_cos(chartInstance, &c2_d7);
  c2_R_pitch[0] = c2_d4;
  c2_R_pitch[3] = 0.0;
  c2_R_pitch[6] = c2_d5;
  c2_i58 = 0;
  for (c2_i59 = 0; c2_i59 < 3; c2_i59++) {
    c2_R_pitch[c2_i58 + 1] = c2_dv17[c2_i59];
    c2_i58 += 3;
  }

  c2_R_pitch[2] = -c2_d6;
  c2_R_pitch[5] = 0.0;
  c2_R_pitch[8] = c2_d7;
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 36);
  c2_d8 = c2_psi;
  c2_b_cos(chartInstance, &c2_d8);
  c2_d9 = c2_psi;
  c2_b_sin(chartInstance, &c2_d9);
  c2_d10 = c2_psi;
  c2_b_sin(chartInstance, &c2_d10);
  c2_d11 = c2_psi;
  c2_b_cos(chartInstance, &c2_d11);
  c2_R_yaw[0] = c2_d8;
  c2_R_yaw[3] = -c2_d9;
  c2_R_yaw[6] = 0.0;
  c2_R_yaw[1] = c2_d10;
  c2_R_yaw[4] = c2_d11;
  c2_R_yaw[7] = 0.0;
  c2_i60 = 0;
  for (c2_i61 = 0; c2_i61 < 3; c2_i61++) {
    c2_R_yaw[c2_i60 + 2] = c2_dv18[c2_i61];
    c2_i60 += 3;
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 41);
  for (c2_i62 = 0; c2_i62 < 9; c2_i62++) {
    c2_a[c2_i62] = c2_R_roll[c2_i62];
  }

  for (c2_i63 = 0; c2_i63 < 9; c2_i63++) {
    c2_b[c2_i63] = c2_R_pitch[c2_i63];
  }

  for (c2_i64 = 0; c2_i64 < 3; c2_i64++) {
    c2_i66 = 0;
    for (c2_i67 = 0; c2_i67 < 3; c2_i67++) {
      c2_y[c2_i66 + c2_i64] = 0.0;
      c2_i69 = 0;
      for (c2_i71 = 0; c2_i71 < 3; c2_i71++) {
        c2_y[c2_i66 + c2_i64] += c2_a[c2_i69 + c2_i64] * c2_b[c2_i71 + c2_i66];
        c2_i69 += 3;
      }

      c2_i66 += 3;
    }
  }

  for (c2_i65 = 0; c2_i65 < 9; c2_i65++) {
    c2_b[c2_i65] = c2_R_yaw[c2_i65];
  }

  for (c2_i68 = 0; c2_i68 < 9; c2_i68++) {
    c2_R[c2_i68] = 0.0;
  }

  for (c2_i70 = 0; c2_i70 < 9; c2_i70++) {
    c2_R[c2_i70] = 0.0;
  }

  for (c2_i72 = 0; c2_i72 < 9; c2_i72++) {
    c2_a[c2_i72] = c2_R[c2_i72];
  }

  for (c2_i73 = 0; c2_i73 < 9; c2_i73++) {
    c2_R[c2_i73] = c2_a[c2_i73];
  }

  for (c2_i74 = 0; c2_i74 < 3; c2_i74++) {
    c2_i75 = 0;
    for (c2_i77 = 0; c2_i77 < 3; c2_i77++) {
      c2_R[c2_i75 + c2_i74] = 0.0;
      c2_i79 = 0;
      for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
        c2_R[c2_i75 + c2_i74] += c2_y[c2_i79 + c2_i74] * c2_b[c2_i80 + c2_i75];
        c2_i79 += 3;
      }

      c2_i75 += 3;
    }
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 43);
  for (c2_i76 = 0; c2_i76 < 9; c2_i76++) {
    c2_a[c2_i76] = c2_R[c2_i76];
  }

  for (c2_i78 = 0; c2_i78 < 48; c2_i78++) {
    c2_b_b[c2_i78] = c2_b_XYZ[c2_i78];
  }

  for (c2_i81 = 0; c2_i81 < 48; c2_i81++) {
    c2_b_XYZ[c2_i81] = 0.0;
  }

  for (c2_i82 = 0; c2_i82 < 48; c2_i82++) {
    c2_b_XYZ[c2_i82] = 0.0;
  }

  for (c2_i83 = 0; c2_i83 < 48; c2_i83++) {
    c2_C[c2_i83] = c2_b_XYZ[c2_i83];
  }

  for (c2_i84 = 0; c2_i84 < 48; c2_i84++) {
    c2_b_XYZ[c2_i84] = c2_C[c2_i84];
  }

  for (c2_i85 = 0; c2_i85 < 3; c2_i85++) {
    c2_i86 = 0;
    for (c2_i87 = 0; c2_i87 < 16; c2_i87++) {
      c2_b_XYZ[c2_i86 + c2_i85] = 0.0;
      c2_i88 = 0;
      for (c2_i89 = 0; c2_i89 < 3; c2_i89++) {
        c2_b_XYZ[c2_i86 + c2_i85] += c2_a[c2_i88 + c2_i85] * c2_b_b[c2_i89 +
          c2_i86];
        c2_i88 += 3;
      }

      c2_i86 += 3;
    }
  }

  _SFD_SYMBOL_SWITCH(6U, 10U);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, -43);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 0U,
    sf_debug_get_script_id(
    "/home/andrew/Projects/RoboSub/Sea_Goat_2016/rov_sim/spacecraftVFC.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 1U,
    sf_debug_get_script_id(
    "/home/andrew/Projects/RoboSub/Sea_Goat_2016/rov_sim/drawSpacecraftBody.m"));
}

static boolean_T c2_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_isempty, const char_T *c2_identifier)
{
  boolean_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_isempty), &c2_thisId);
  sf_mex_destroy(&c2_isempty);
  return c2_y;
}

static boolean_T c2_b_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_b0, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b0;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  const mxArray *c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = sf_mex_dup(*(const mxArray **)c2_inData);
  c2_y = NULL;
  if (!chartInstance->c2_aircraftHandle_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_b_u), false);
  }

  sf_mex_destroy(&c2_b_u);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i90;
  const mxArray *c2_y = NULL;
  real_T c2_b_u[13];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i90 = 0; c2_i90 < 13; c2_i90++) {
    c2_b_u[c2_i90] = (*(real_T (*)[13])c2_inData)[c2_i90];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 13), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d12;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_d12, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d12;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i91;
  int32_T c2_i92;
  const mxArray *c2_y = NULL;
  int32_T c2_i93;
  real_T c2_b_u[48];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i91 = 0;
  for (c2_i92 = 0; c2_i92 < 16; c2_i92++) {
    for (c2_i93 = 0; c2_i93 < 3; c2_i93++) {
      c2_b_u[c2_i93 + c2_i91] = (*(real_T (*)[48])c2_inData)[c2_i93 + c2_i91];
    }

    c2_i91 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 3, 16),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[48])
{
  real_T c2_dv19[48];
  int32_T c2_i94;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv19, 1, 0, 0U, 1, 0U, 2, 3,
                16);
  for (c2_i94 = 0; c2_i94 < 48; c2_i94++) {
    c2_y[c2_i94] = c2_dv19[c2_i94];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[48];
  int32_T c2_i95;
  int32_T c2_i96;
  int32_T c2_i97;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_V = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_V);
  c2_i95 = 0;
  for (c2_i96 = 0; c2_i96 < 16; c2_i96++) {
    for (c2_i97 = 0; c2_i97 < 3; c2_i97++) {
      (*(real_T (*)[48])c2_outData)[c2_i97 + c2_i95] = c2_y[c2_i97 + c2_i95];
    }

    c2_i95 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i98;
  int32_T c2_i99;
  const mxArray *c2_y = NULL;
  int32_T c2_i100;
  real_T c2_b_u[9];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i98 = 0;
  for (c2_i99 = 0; c2_i99 < 3; c2_i99++) {
    for (c2_i100 = 0; c2_i100 < 3; c2_i100++) {
      c2_b_u[c2_i100 + c2_i98] = (*(real_T (*)[9])c2_inData)[c2_i100 + c2_i98];
    }

    c2_i98 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i101;
  int32_T c2_i102;
  const mxArray *c2_y = NULL;
  int32_T c2_i103;
  real_T c2_b_u[33];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i101 = 0;
  for (c2_i102 = 0; c2_i102 < 3; c2_i102++) {
    for (c2_i103 = 0; c2_i103 < 11; c2_i103++) {
      c2_b_u[c2_i103 + c2_i101] = (*(real_T (*)[33])c2_inData)[c2_i103 + c2_i101];
    }

    c2_i101 += 11;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 11, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[33])
{
  real_T c2_dv20[33];
  int32_T c2_i104;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv20, 1, 0, 0U, 1, 0U, 2, 11,
                3);
  for (c2_i104 = 0; c2_i104 < 33; c2_i104++) {
    c2_y[c2_i104] = c2_dv20[c2_i104];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_patchcolors;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[33];
  int32_T c2_i105;
  int32_T c2_i106;
  int32_T c2_i107;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_patchcolors = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_patchcolors), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_patchcolors);
  c2_i105 = 0;
  for (c2_i106 = 0; c2_i106 < 3; c2_i106++) {
    for (c2_i107 = 0; c2_i107 < 11; c2_i107++) {
      (*(real_T (*)[33])c2_outData)[c2_i107 + c2_i105] = c2_y[c2_i107 + c2_i105];
    }

    c2_i105 += 11;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i108;
  int32_T c2_i109;
  const mxArray *c2_y = NULL;
  int32_T c2_i110;
  real_T c2_b_u[44];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i108 = 0;
  for (c2_i109 = 0; c2_i109 < 4; c2_i109++) {
    for (c2_i110 = 0; c2_i110 < 11; c2_i110++) {
      c2_b_u[c2_i110 + c2_i108] = (*(real_T (*)[44])c2_inData)[c2_i110 + c2_i108];
    }

    c2_i108 += 11;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 11, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_f_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[44])
{
  real_T c2_dv21[44];
  int32_T c2_i111;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv21, 1, 0, 0U, 1, 0U, 2, 11,
                4);
  for (c2_i111 = 0; c2_i111 < 44; c2_i111++) {
    c2_y[c2_i111] = c2_dv21[c2_i111];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_F;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[44];
  int32_T c2_i112;
  int32_T c2_i113;
  int32_T c2_i114;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_F = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_F), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_F);
  c2_i112 = 0;
  for (c2_i113 = 0; c2_i113 < 4; c2_i113++) {
    for (c2_i114 = 0; c2_i114 < 11; c2_i114++) {
      (*(real_T (*)[44])c2_outData)[c2_i114 + c2_i112] = c2_y[c2_i114 + c2_i112];
    }

    c2_i112 += 11;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i115;
  int32_T c2_i116;
  const mxArray *c2_y = NULL;
  int32_T c2_i117;
  real_T c2_b_u[48];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i115 = 0;
  for (c2_i116 = 0; c2_i116 < 3; c2_i116++) {
    for (c2_i117 = 0; c2_i117 < 16; c2_i117++) {
      c2_b_u[c2_i117 + c2_i115] = (*(real_T (*)[48])c2_inData)[c2_i117 + c2_i115];
    }

    c2_i115 += 16;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 16, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i118;
  const mxArray *c2_y = NULL;
  real_T c2_b_u[3];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i118 = 0; c2_i118 < 3; c2_i118++) {
    c2_b_u[c2_i118] = (*(real_T (*)[3])c2_inData)[c2_i118];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[48])
{
  real_T c2_dv22[48];
  int32_T c2_i119;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv22, 1, 0, 0U, 1, 0U, 2, 16,
                3);
  for (c2_i119 = 0; c2_i119 < 48; c2_i119++) {
    c2_y[c2_i119] = c2_dv22[c2_i119];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[48];
  int32_T c2_i120;
  int32_T c2_i121;
  int32_T c2_i122;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_V = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_V);
  c2_i120 = 0;
  for (c2_i121 = 0; c2_i121 < 3; c2_i121++) {
    for (c2_i122 = 0; c2_i122 < 16; c2_i122++) {
      (*(real_T (*)[48])c2_outData)[c2_i122 + c2_i120] = c2_y[c2_i122 + c2_i120];
    }

    c2_i120 += 16;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_h_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9])
{
  real_T c2_dv23[9];
  int32_T c2_i123;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv23, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c2_i123 = 0; c2_i123 < 9; c2_i123++) {
    c2_y[c2_i123] = c2_dv23[c2_i123];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_R;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i124;
  int32_T c2_i125;
  int32_T c2_i126;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_R = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_R), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_R);
  c2_i124 = 0;
  for (c2_i125 = 0; c2_i125 < 3; c2_i125++) {
    for (c2_i126 = 0; c2_i126 < 3; c2_i126++) {
      (*(real_T (*)[9])c2_outData)[c2_i126 + c2_i124] = c2_y[c2_i126 + c2_i124];
    }

    c2_i124 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  const mxArray *c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = sf_mex_dup(*(const mxArray **)c2_inData);
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_b_u), false);
  sf_mex_destroy(&c2_b_u);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i127;
  const mxArray *c2_y = NULL;
  char_T c2_b_u[6];
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i127 = 0; c2_i127 < 6; c2_i127++) {
    c2_b_u[c2_i127] = (*(char_T (*)[6])c2_inData)[c2_i127];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 6),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y[6])
{
  char_T c2_cv1[6];
  int32_T c2_i128;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                6);
  for (c2_i128 = 0; c2_i128 < 6; c2_i128++) {
    c2_y[c2_i128] = c2_cv1[c2_i128];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_mode;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  char_T c2_y[6];
  int32_T c2_i129;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mode = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_mode), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_mode);
  for (c2_i129 = 0; c2_i129 < 6; c2_i129++) {
    (*(char_T (*)[6])c2_outData)[c2_i129] = c2_y[c2_i129];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_auv_6dof_sim_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  const char * c2_data[4] = {
    "789c6360f4f46500023e20fec0c1c0c006a4811403130304b042f98c40cc0ca521e22c0cbc507e131027e7e795a456944024f3127353196020253f37332f31af"
    "24a4b22095a128b5383fa72c35052c939699931a92999bea938fc4f1c8047272dd90a4e01c9054514631dc64861c640e0480fc61c080f0070b9a3f6000e60f01",
    "247d0e78f481d4f3a2e903f18b0b129353938b12d34ac2dc9c29b4bf8280fd6e68fa40fc68d758fd8cfcdc54fdc4bc94a2d472fd80a2fcacd4e49262fda0fca4"
    "fce0d224fde0d4c478f7fcc4927823034333fda2fcb2f8e2cc5c7d1467ebe542ecb740b29f0d8bfd8c48f673c2fde360cdb7e7aa23f9fa11fe1f68fd1a48fa19",
    "b1e86740a2c9514f6ebaf0c0a30fa45e084d1f889f5294581e0c8f64a7fc944aece184cd3c3634f340fc94fcd2a49c5488fe0602fabdd1f483f864a6534c6f80"
    "122b167f101fdf07def21c1a4dafc4a86f60181cf1ec40c01da3e5f268b94c6e3a07003a84b867",
    "" };

  c2_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c2_data, 2304U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_b_rotate(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
  c2_XYZ[48], real_T c2_phi, real_T c2_theta, real_T c2_psi, real_T c2_b_XYZ[48])
{
  uint32_T c2_debug_family_var_map[10];
  real_T c2_R_roll[9];
  real_T c2_R_pitch[9];
  real_T c2_R_yaw[9];
  real_T c2_R[9];
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i130;
  real_T c2_d13;
  real_T c2_d14;
  real_T c2_d15;
  real_T c2_d16;
  int32_T c2_i131;
  int32_T c2_i132;
  static real_T c2_dv24[3] = { 1.0, 0.0, 0.0 };

  real_T c2_d17;
  real_T c2_d18;
  real_T c2_d19;
  real_T c2_d20;
  int32_T c2_i133;
  int32_T c2_i134;
  static real_T c2_dv25[3] = { 0.0, 1.0, 0.0 };

  real_T c2_d21;
  real_T c2_d22;
  real_T c2_d23;
  real_T c2_d24;
  int32_T c2_i135;
  int32_T c2_i136;
  static real_T c2_dv26[3] = { 0.0, 0.0, 1.0 };

  int32_T c2_i137;
  int32_T c2_i138;
  real_T c2_a[9];
  int32_T c2_i139;
  real_T c2_b[9];
  int32_T c2_i140;
  int32_T c2_i141;
  int32_T c2_i142;
  int32_T c2_i143;
  real_T c2_y[9];
  int32_T c2_i144;
  int32_T c2_i145;
  int32_T c2_i146;
  int32_T c2_i147;
  int32_T c2_i148;
  int32_T c2_i149;
  int32_T c2_i150;
  int32_T c2_i151;
  int32_T c2_i152;
  int32_T c2_i153;
  int32_T c2_i154;
  int32_T c2_i155;
  int32_T c2_i156;
  real_T c2_b_b[48];
  int32_T c2_i157;
  int32_T c2_i158;
  int32_T c2_i159;
  real_T c2_C[48];
  int32_T c2_i160;
  int32_T c2_i161;
  int32_T c2_i162;
  int32_T c2_i163;
  int32_T c2_i164;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 11U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R_roll, 0U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R_pitch, 1U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R_yaw, 2U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R, 3U, c2_e_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_XYZ, 6U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi, 7U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_theta, 8U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_psi, 9U, c2_c_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_XYZ, MAX_uint32_T,
    c2_d_sf_marshallOut, c2_b_sf_marshallIn);
  for (c2_i130 = 0; c2_i130 < 48; c2_i130++) {
    c2_b_XYZ[c2_i130] = c2_XYZ[c2_i130];
  }

  _SFD_SYMBOL_SWITCH(6U, 10U);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  c2_d13 = c2_phi;
  c2_b_cos(chartInstance, &c2_d13);
  c2_d14 = c2_phi;
  c2_b_sin(chartInstance, &c2_d14);
  c2_d15 = c2_phi;
  c2_b_sin(chartInstance, &c2_d15);
  c2_d16 = c2_phi;
  c2_b_cos(chartInstance, &c2_d16);
  c2_i131 = 0;
  for (c2_i132 = 0; c2_i132 < 3; c2_i132++) {
    c2_R_roll[c2_i131] = c2_dv24[c2_i132];
    c2_i131 += 3;
  }

  c2_R_roll[1] = 0.0;
  c2_R_roll[4] = c2_d13;
  c2_R_roll[7] = -c2_d14;
  c2_R_roll[2] = 0.0;
  c2_R_roll[5] = c2_d15;
  c2_R_roll[8] = c2_d16;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
  c2_d17 = c2_theta;
  c2_b_cos(chartInstance, &c2_d17);
  c2_d18 = c2_theta;
  c2_b_sin(chartInstance, &c2_d18);
  c2_d19 = c2_theta;
  c2_b_sin(chartInstance, &c2_d19);
  c2_d20 = c2_theta;
  c2_b_cos(chartInstance, &c2_d20);
  c2_R_pitch[0] = c2_d17;
  c2_R_pitch[3] = 0.0;
  c2_R_pitch[6] = c2_d18;
  c2_i133 = 0;
  for (c2_i134 = 0; c2_i134 < 3; c2_i134++) {
    c2_R_pitch[c2_i133 + 1] = c2_dv25[c2_i134];
    c2_i133 += 3;
  }

  c2_R_pitch[2] = -c2_d19;
  c2_R_pitch[5] = 0.0;
  c2_R_pitch[8] = c2_d20;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
  c2_d21 = c2_psi;
  c2_b_cos(chartInstance, &c2_d21);
  c2_d22 = c2_psi;
  c2_b_sin(chartInstance, &c2_d22);
  c2_d23 = c2_psi;
  c2_b_sin(chartInstance, &c2_d23);
  c2_d24 = c2_psi;
  c2_b_cos(chartInstance, &c2_d24);
  c2_R_yaw[0] = c2_d21;
  c2_R_yaw[3] = -c2_d22;
  c2_R_yaw[6] = 0.0;
  c2_R_yaw[1] = c2_d23;
  c2_R_yaw[4] = c2_d24;
  c2_R_yaw[7] = 0.0;
  c2_i135 = 0;
  for (c2_i136 = 0; c2_i136 < 3; c2_i136++) {
    c2_R_yaw[c2_i135 + 2] = c2_dv26[c2_i136];
    c2_i135 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 68);
  for (c2_i137 = 0; c2_i137 < 9; c2_i137++) {
    c2_a[c2_i137] = c2_R_roll[c2_i137];
  }

  for (c2_i138 = 0; c2_i138 < 9; c2_i138++) {
    c2_b[c2_i138] = c2_R_pitch[c2_i138];
  }

  for (c2_i139 = 0; c2_i139 < 3; c2_i139++) {
    c2_i141 = 0;
    for (c2_i142 = 0; c2_i142 < 3; c2_i142++) {
      c2_y[c2_i141 + c2_i139] = 0.0;
      c2_i144 = 0;
      for (c2_i146 = 0; c2_i146 < 3; c2_i146++) {
        c2_y[c2_i141 + c2_i139] += c2_a[c2_i144 + c2_i139] * c2_b[c2_i146 +
          c2_i141];
        c2_i144 += 3;
      }

      c2_i141 += 3;
    }
  }

  for (c2_i140 = 0; c2_i140 < 9; c2_i140++) {
    c2_b[c2_i140] = c2_R_yaw[c2_i140];
  }

  for (c2_i143 = 0; c2_i143 < 9; c2_i143++) {
    c2_R[c2_i143] = 0.0;
  }

  for (c2_i145 = 0; c2_i145 < 9; c2_i145++) {
    c2_R[c2_i145] = 0.0;
  }

  for (c2_i147 = 0; c2_i147 < 9; c2_i147++) {
    c2_a[c2_i147] = c2_R[c2_i147];
  }

  for (c2_i148 = 0; c2_i148 < 9; c2_i148++) {
    c2_R[c2_i148] = c2_a[c2_i148];
  }

  for (c2_i149 = 0; c2_i149 < 3; c2_i149++) {
    c2_i150 = 0;
    for (c2_i152 = 0; c2_i152 < 3; c2_i152++) {
      c2_R[c2_i150 + c2_i149] = 0.0;
      c2_i154 = 0;
      for (c2_i155 = 0; c2_i155 < 3; c2_i155++) {
        c2_R[c2_i150 + c2_i149] += c2_y[c2_i154 + c2_i149] * c2_b[c2_i155 +
          c2_i150];
        c2_i154 += 3;
      }

      c2_i150 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 70);
  for (c2_i151 = 0; c2_i151 < 9; c2_i151++) {
    c2_a[c2_i151] = c2_R[c2_i151];
  }

  for (c2_i153 = 0; c2_i153 < 48; c2_i153++) {
    c2_b_b[c2_i153] = c2_b_XYZ[c2_i153];
  }

  for (c2_i156 = 0; c2_i156 < 48; c2_i156++) {
    c2_b_XYZ[c2_i156] = 0.0;
  }

  for (c2_i157 = 0; c2_i157 < 48; c2_i157++) {
    c2_b_XYZ[c2_i157] = 0.0;
  }

  for (c2_i158 = 0; c2_i158 < 48; c2_i158++) {
    c2_C[c2_i158] = c2_b_XYZ[c2_i158];
  }

  for (c2_i159 = 0; c2_i159 < 48; c2_i159++) {
    c2_b_XYZ[c2_i159] = c2_C[c2_i159];
  }

  for (c2_i160 = 0; c2_i160 < 3; c2_i160++) {
    c2_i161 = 0;
    for (c2_i162 = 0; c2_i162 < 16; c2_i162++) {
      c2_b_XYZ[c2_i161 + c2_i160] = 0.0;
      c2_i163 = 0;
      for (c2_i164 = 0; c2_i164 < 3; c2_i164++) {
        c2_b_XYZ[c2_i161 + c2_i160] += c2_a[c2_i163 + c2_i160] * c2_b_b[c2_i164
          + c2_i161];
        c2_i163 += 3;
      }

      c2_i161 += 3;
    }
  }

  _SFD_SYMBOL_SWITCH(6U, 10U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -70);
  _SFD_SYMBOL_SCOPE_POP();
}

static real_T c2_cos(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_cos(chartInstance, &c2_b_x);
  return c2_b_x;
}

static real_T c2_sin(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_sin(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_c_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_d_scalarEg(SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_j_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i165;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_i165, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i165;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_k_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_aircraftHandle, const char_T
  *c2_identifier, boolean_T *c2_svPtr)
{
  const mxArray *c2_y = NULL;
  emlrtMsgIdentifier c2_thisId;
  c2_y = NULL;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  sf_mex_assign(&c2_y, c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_aircraftHandle), &c2_thisId, c2_svPtr), false);
  sf_mex_destroy(&c2_b_aircraftHandle);
  return c2_y;
}

static const mxArray *c2_l_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  boolean_T *c2_svPtr)
{
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  (void)c2_parentId;
  c2_y = NULL;
  if (mxIsEmpty(c2_b_u)) {
    *c2_svPtr = false;
  } else {
    *c2_svPtr = true;
    sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_b_u), false);
  }

  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static uint8_T c2_m_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_auv_6dof_sim, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_auv_6dof_sim), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_auv_6dof_sim);
  return c2_y;
}

static uint8_T c2_n_emlrt_marshallIn(SFc2_auv_6dof_simInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_b_cos(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
                     *c2_x)
{
  (void)chartInstance;
  *c2_x = muDoubleScalarCos(*c2_x);
}

static void c2_b_sin(SFc2_auv_6dof_simInstanceStruct *chartInstance, real_T
                     *c2_x)
{
  (void)chartInstance;
  *c2_x = muDoubleScalarSin(*c2_x);
}

static void init_dsm_address_info(SFc2_auv_6dof_simInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_auv_6dof_simInstanceStruct
  *chartInstance)
{
  chartInstance->c2_u = (real_T (*)[13])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_auv_6dof_sim_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3316454746U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1415323132U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(125718431U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(581175889U);
}

mxArray* sf_c2_auv_6dof_sim_get_post_codegen_info(void);
mxArray *sf_c2_auv_6dof_sim_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("c8QqcqdnIz4LCyCKVMTGrC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_auv_6dof_sim_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_auv_6dof_sim_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_auv_6dof_sim_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_auv_6dof_sim_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_auv_6dof_sim_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_auv_6dof_sim(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[4],M[0],T\"aircraftHandle\",S'l','i','p'{{M1x2[212 226],M[0],}}},{M[8],M[0],T\"is_active_c2_auv_6dof_sim\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_auv_6dof_sim_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_auv_6dof_simInstanceStruct *chartInstance =
      (SFc2_auv_6dof_simInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _auv_6dof_simMachineNumber_,
           2,
           1,
           1,
           0,
           1,
           0,
           0,
           0,
           0,
           2,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_auv_6dof_simMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_auv_6dof_simMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _auv_6dof_simMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,2,0,2,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,967);
        _SFD_CV_INIT_EML_FCN(0,1,"rotate",967,-1,1338);
        _SFD_CV_INIT_EML_IF(0,1,0,247,273,-1,685);
        _SFD_CV_INIT_EML_IF(0,1,1,687,694,850,965);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,690,694,-1,0);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"spacecraftVFC",0,-1,1054);
        _SFD_CV_INIT_SCRIPT(1,3,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"drawSpacecraftBody",0,-1,573);
        _SFD_CV_INIT_SCRIPT_FCN(1,1,"rotate",573,-1,1105);
        _SFD_CV_INIT_SCRIPT_FCN(1,2,"translate",1105,-1,1199);

        {
          unsigned int dimVector[1];
          dimVector[0]= 13U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _auv_6dof_simMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_auv_6dof_simInstanceStruct *chartInstance =
      (SFc2_auv_6dof_simInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_u);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sqh2v9DMwZOvAlFlOIIES3G";
}

static void sf_opaque_initialize_c2_auv_6dof_sim(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_auv_6dof_simInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*)
    chartInstanceVar);
  initialize_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_auv_6dof_sim(void *chartInstanceVar)
{
  enable_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_auv_6dof_sim(void *chartInstanceVar)
{
  disable_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_auv_6dof_sim(void *chartInstanceVar)
{
  sf_gateway_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_auv_6dof_sim(SimStruct* S)
{
  return get_sim_state_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_auv_6dof_sim(SimStruct* S, const mxArray *
  st)
{
  set_sim_state_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_auv_6dof_sim(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_auv_6dof_simInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_auv_6dof_sim_optimization_info();
    }

    finalize_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_auv_6dof_sim(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_auv_6dof_sim((SFc2_auv_6dof_simInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_auv_6dof_sim(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_auv_6dof_sim_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=0; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(535487484U));
  ssSetChecksum1(S,(1458865774U));
  ssSetChecksum2(S,(3031331123U));
  ssSetChecksum3(S,(826122590U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_auv_6dof_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_auv_6dof_sim(SimStruct *S)
{
  SFc2_auv_6dof_simInstanceStruct *chartInstance;
  chartInstance = (SFc2_auv_6dof_simInstanceStruct *)utMalloc(sizeof
    (SFc2_auv_6dof_simInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_auv_6dof_simInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_auv_6dof_sim;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_auv_6dof_sim;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_auv_6dof_sim;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_auv_6dof_sim;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_auv_6dof_sim;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_auv_6dof_sim;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_auv_6dof_sim;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_auv_6dof_sim;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_auv_6dof_sim;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_auv_6dof_sim;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_auv_6dof_sim;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_auv_6dof_sim(chartInstance);
}

void c2_auv_6dof_sim_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_auv_6dof_sim(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_auv_6dof_sim(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_auv_6dof_sim(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_auv_6dof_sim_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
