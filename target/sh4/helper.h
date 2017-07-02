DEF_HELPER_1(ldtlb, void, env)
DEF_HELPER_1(raise_illegal_instruction, noreturn, env)
DEF_HELPER_1(raise_slot_illegal_instruction, noreturn, env)
DEF_HELPER_1(raise_fpu_disable, noreturn, env)
DEF_HELPER_1(raise_slot_fpu_disable, noreturn, env)
DEF_HELPER_1(debug, noreturn, env)
DEF_HELPER_1(sleep, noreturn, env)
DEF_HELPER_2(trapa, noreturn, env, i32)

DEF_HELPER_3(movcal, void, env, i32, i32)
DEF_HELPER_1(discard_movcal_backup, void, env)
DEF_HELPER_2(ocbi, void, env, i32)

DEF_HELPER_3(macl, void, env, i32, i32)
DEF_HELPER_3(macw, void, env, i32, i32)

DEF_HELPER_2(ld_fpscr, void, env, i32)

DEF_HELPER_FLAGS_3(fadd_FT, TCG_CALL_NO_WG, f32, env, f32, f32)
DEF_HELPER_FLAGS_3(fadd_DT, TCG_CALL_NO_WG, f64, env, f64, f64)
DEF_HELPER_FLAGS_2(fcnvsd_FT_DT, TCG_CALL_NO_WG, f64, env, f32)
DEF_HELPER_FLAGS_2(fcnvds_DT_FT, TCG_CALL_NO_WG, f32, env, f64)

DEF_HELPER_FLAGS_3(fcmp_eq_FT, TCG_CALL_NO_WG, i32, env, f32, f32)
DEF_HELPER_FLAGS_3(fcmp_eq_DT, TCG_CALL_NO_WG, i32, env, f64, f64)
DEF_HELPER_FLAGS_3(fcmp_gt_FT, TCG_CALL_NO_WG, i32, env, f32, f32)
DEF_HELPER_FLAGS_3(fcmp_gt_DT, TCG_CALL_NO_WG, i32, env, f64, f64)
DEF_HELPER_FLAGS_3(fdiv_FT, TCG_CALL_NO_WG, f32, env, f32, f32)
DEF_HELPER_FLAGS_3(fdiv_DT, TCG_CALL_NO_WG, f64, env, f64, f64)
DEF_HELPER_FLAGS_2(float_FT, TCG_CALL_NO_WG, f32, env, i32)
DEF_HELPER_FLAGS_2(float_DT, TCG_CALL_NO_WG, f64, env, i32)
DEF_HELPER_FLAGS_4(fmac_FT, TCG_CALL_NO_WG, f32, env, f32, f32, f32)
DEF_HELPER_FLAGS_3(fmul_FT, TCG_CALL_NO_WG, f32, env, f32, f32)
DEF_HELPER_FLAGS_3(fmul_DT, TCG_CALL_NO_WG, f64, env, f64, f64)
DEF_HELPER_FLAGS_3(fsub_FT, TCG_CALL_NO_WG, f32, env, f32, f32)
DEF_HELPER_FLAGS_3(fsub_DT, TCG_CALL_NO_WG, f64, env, f64, f64)
DEF_HELPER_FLAGS_2(fsqrt_FT, TCG_CALL_NO_WG, f32, env, f32)
DEF_HELPER_FLAGS_2(fsqrt_DT, TCG_CALL_NO_WG, f64, env, f64)
DEF_HELPER_FLAGS_2(ftrc_FT, TCG_CALL_NO_WG, i32, env, f32)
DEF_HELPER_FLAGS_2(ftrc_DT, TCG_CALL_NO_WG, i32, env, f64)
DEF_HELPER_3(fipr, void, env, i32, i32)
DEF_HELPER_2(ftrv, void, env, i32)
