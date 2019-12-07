#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0_level_9_3 /EPS /Fh
//    Shader/EffekseerRenderer.ModelRenderer.ShaderDistortion_PS.h
//    Shader/model_renderer_distortion_PS.fx
//
//
// Buffer Definitions: 
//
// cbuffer PSConstantBuffer
// {
//
//   float4 g_scale;                    // Offset:    0 Size:    16
//   float4 mUVInversedBack;            // Offset:   16 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// g_sampler                         sampler      NA          NA    8        1
// g_backSampler                     sampler      NA          NA    9        1
// g_texture                         texture  float4          2d    8        1
// g_backTexture                     texture  float4          2d    9        1
// PSConstantBuffer                  cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// TEXCOORD                 0   xy          1     NONE  float   xy  
// TEXCOORD                 1   xyzw        2     NONE  float       
// TEXCOORD                 2   xyzw        3     NONE  float   xy w
// TEXCOORD                 3   xyzw        4     NONE  float   xy w
// TEXCOORD                 4   xyzw        5     NONE  float   xy w
// COLOR                    0   xyzw        6     NONE  float   xy w
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c0         cb1             0         2  ( FLT, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s8              t8               
// s1             s9              t9               
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c2, 0.5, 1, 0, 0
    def c3, -1, -0, 2, 1
    dcl t0.xy
    dcl t2
    dcl t3
    dcl t4
    dcl t5
    dcl_2d s0
    dcl_2d s1
    texld r0, t0, s0
    mul r1.w, r0.w, t5.w
    mul r0.z, r1.w, r1.w
    cmp r2, -r0.z, c3.x, c3.y
    texkill r2
    mad r0.xy, r0, c3.z, c3.x
    mul r0.xy, r0, t5
    mul r0.xy, r0, c0.x
    rcp r0.z, t3.w
    rcp r0.w, t4.w
    mul r2.xy, r0.w, t4
    mad r0.zw, t3.xyxy, r0.z, -r2.xyxy
    rcp r2.z, t2.w
    mad r2.zw, t2.xyxy, r2.z, -r2.xyxy
    mad r2.xy, r2.zwzw, r0.x, r2
    mad r0.xy, r0.zwzw, r0.y, r2
    add r0.xy, r0, c3.w
    mul r2.x, r0.x, c2.x
    mad r0.x, r0.y, -c2.x, c2.y
    mad r2.y, c1.y, r0.x, c1.x
    texld r0, r2, s1
    mov r1.xyz, r0
    mov oC0, r1

// approximately 23 instruction slots used (2 texture, 21 arithmetic)
ps_4_0
dcl_constantbuffer cb1[2], immediateIndexed
dcl_sampler s8, mode_default
dcl_sampler s9, mode_default
dcl_resource_texture2d (float,float,float,float) t8
dcl_resource_texture2d (float,float,float,float) t9
dcl_input_ps linear v1.xy
dcl_input_ps linear v3.xyw
dcl_input_ps linear v4.xyw
dcl_input_ps linear v5.xyw
dcl_input_ps linear v6.xyw
dcl_output o0.xyzw
dcl_temps 3
sample r0.xyzw, v1.xyxx, t8.xyzw, s8
mul r0.z, r0.w, v6.w
eq r0.w, r0.z, l(0.000000)
discard r0.w
div r1.xy, v5.xyxx, v5.wwww
div r1.zw, v4.xxxy, v4.wwww
div r2.xy, v3.xyxx, v3.wwww
mad r0.xy, r0.xyxx, l(2.000000, 2.000000, 0.000000, 0.000000), l(-1.000000, -1.000000, 0.000000, 0.000000)
mul r0.xy, r0.xyxx, v6.xyxx
mul r0.xy, r0.xyxx, cb1[0].xxxx
add r2.xy, -r1.xyxx, r2.xyxx
mad r0.xw, r2.xxxy, r0.xxxx, r1.xxxy
add r1.xy, -r1.xyxx, r1.zwzz
mad r0.xy, r1.xyxx, r0.yyyy, r0.xwxx
add r0.xy, r0.xyxx, l(1.000000, 1.000000, 0.000000, 0.000000)
mul r1.x, r0.x, l(0.500000)
mad r0.x, -r0.y, l(0.500000), l(1.000000)
mad r1.z, cb1[1].y, r0.x, cb1[1].x
sample r1.xyzw, r1.xzxx, t9.xyzw, s9
mov o0.xyz, r1.xyzx
mov o0.w, r0.z
ret 
// Approximately 22 instruction slots used
#endif

const BYTE g_PS[] =
{
     68,  88,  66,  67,   9,   3, 
    214,  26, 127, 213,  46,  51, 
    146, 135,  77, 151,  10,  70, 
    177, 188,   1,   0,   0,   0, 
    244,   8,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    120,   2,   0,   0, 196,   5, 
      0,   0,  64,   6,   0,   0, 
    236,   7,   0,   0, 192,   8, 
      0,   0,  65, 111, 110,  57, 
     56,   2,   0,   0,  56,   2, 
      0,   0,   0,   2, 255, 255, 
      0,   2,   0,   0,  56,   0, 
      0,   0,   1,   0,  44,   0, 
      0,   0,  56,   0,   0,   0, 
     56,   0,   2,   0,  36,   0, 
      0,   0,  56,   0,   8,   8, 
      0,   0,   9,   9,   1,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   2, 255, 255,  81,   0, 
      0,   5,   2,   0,  15, 160, 
      0,   0,   0,  63,   0,   0, 
    128,  63,   0,   0,   0,   0, 
      0,   0,   0,   0,  81,   0, 
      0,   5,   3,   0,  15, 160, 
      0,   0, 128, 191,   0,   0, 
      0, 128,   0,   0,   0,  64, 
      0,   0, 128,  63,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,   3, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      2,   0,  15, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      3,   0,  15, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      4,   0,  15, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      5,   0,  15, 176,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      1,   8,  15, 160,  66,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 176,   0,   8, 
    228, 160,   5,   0,   0,   3, 
      1,   0,   8, 128,   0,   0, 
    255, 128,   5,   0, 255, 176, 
      5,   0,   0,   3,   0,   0, 
      4, 128,   1,   0, 255, 128, 
      1,   0, 255, 128,  88,   0, 
      0,   4,   2,   0,  15, 128, 
      0,   0, 170, 129,   3,   0, 
      0, 160,   3,   0,  85, 160, 
     65,   0,   0,   1,   2,   0, 
     15, 128,   4,   0,   0,   4, 
      0,   0,   3, 128,   0,   0, 
    228, 128,   3,   0, 170, 160, 
      3,   0,   0, 160,   5,   0, 
      0,   3,   0,   0,   3, 128, 
      0,   0, 228, 128,   5,   0, 
    228, 176,   5,   0,   0,   3, 
      0,   0,   3, 128,   0,   0, 
    228, 128,   0,   0,   0, 160, 
      6,   0,   0,   2,   0,   0, 
      4, 128,   3,   0, 255, 176, 
      6,   0,   0,   2,   0,   0, 
      8, 128,   4,   0, 255, 176, 
      5,   0,   0,   3,   2,   0, 
      3, 128,   0,   0, 255, 128, 
      4,   0, 228, 176,   4,   0, 
      0,   4,   0,   0,  12, 128, 
      3,   0,  68, 176,   0,   0, 
    170, 128,   2,   0,  68, 129, 
      6,   0,   0,   2,   2,   0, 
      4, 128,   2,   0, 255, 176, 
      4,   0,   0,   4,   2,   0, 
     12, 128,   2,   0,  68, 176, 
      2,   0, 170, 128,   2,   0, 
     68, 129,   4,   0,   0,   4, 
      2,   0,   3, 128,   2,   0, 
    238, 128,   0,   0,   0, 128, 
      2,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,   3, 128, 
      0,   0, 238, 128,   0,   0, 
     85, 128,   2,   0, 228, 128, 
      2,   0,   0,   3,   0,   0, 
      3, 128,   0,   0, 228, 128, 
      3,   0, 255, 160,   5,   0, 
      0,   3,   2,   0,   1, 128, 
      0,   0,   0, 128,   2,   0, 
      0, 160,   4,   0,   0,   4, 
      0,   0,   1, 128,   0,   0, 
     85, 128,   2,   0,   0, 161, 
      2,   0,  85, 160,   4,   0, 
      0,   4,   2,   0,   2, 128, 
      1,   0,  85, 160,   0,   0, 
      0, 128,   1,   0,   0, 160, 
     66,   0,   0,   3,   0,   0, 
     15, 128,   2,   0, 228, 128, 
      1,   8, 228, 160,   1,   0, 
      0,   2,   1,   0,   7, 128, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      1,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
     68,   3,   0,   0,  64,   0, 
      0,   0, 209,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      8,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      9,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      8,   0,   0,   0,  85,  85, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   9,   0, 
      0,   0,  85,  85,   0,   0, 
     98,  16,   0,   3,  50,  16, 
     16,   0,   1,   0,   0,   0, 
     98,  16,   0,   3, 178,  16, 
     16,   0,   3,   0,   0,   0, 
     98,  16,   0,   3, 178,  16, 
     16,   0,   4,   0,   0,   0, 
     98,  16,   0,   3, 178,  16, 
     16,   0,   5,   0,   0,   0, 
     98,  16,   0,   3, 178,  16, 
     16,   0,   6,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    104,   0,   0,   2,   3,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   8,   0,   0,   0, 
      0,  96,  16,   0,   8,   0, 
      0,   0,  56,   0,   0,   7, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  58,  16, 
     16,   0,   6,   0,   0,   0, 
     24,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  58,   0,  16,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   7,  50,   0,  16,   0, 
      1,   0,   0,   0,  70,  16, 
     16,   0,   5,   0,   0,   0, 
    246,  31,  16,   0,   5,   0, 
      0,   0,  14,   0,   0,   7, 
    194,   0,  16,   0,   1,   0, 
      0,   0,   6,  20,  16,   0, 
      4,   0,   0,   0, 246,  31, 
     16,   0,   4,   0,   0,   0, 
     14,   0,   0,   7,  50,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  16,  16,   0,   3,   0, 
      0,   0, 246,  31,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  15,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,  64,   0,   0,   0,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0, 128, 191,   0,   0, 
    128, 191,   0,   0,   0,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  16,  16,   0,   6,   0, 
      0,   0,  56,   0,   0,   8, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,   6, 128, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   8,  50,   0,  16,   0, 
      2,   0,   0,   0,  70,   0, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9, 146,   0, 
     16,   0,   0,   0,   0,   0, 
      6,   4,  16,   0,   2,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,   6,   4, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   8,  50,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
    230,  10,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
    198,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,  10, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,  50,   0, 
      0,  10,  18,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  50,   0,   0,  11, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  26, 128,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  10, 128, 
     32,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0, 134,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   9,   0, 
      0,   0,   0,  96,  16,   0, 
      9,   0,   0,   0,  54,   0, 
      0,   5, 114,  32,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 130,  32, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  22,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     11,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  82,  68, 
     69,  70, 164,   1,   0,   0, 
      1,   0,   0,   0,   0,   1, 
      0,   0,   5,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
    112,   1,   0,   0, 188,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    198,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   9,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 212,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   8,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 222,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      9,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    236,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 103,  95, 115,  97, 
    109, 112, 108, 101, 114,   0, 
    103,  95,  98,  97,  99, 107, 
     83,  97, 109, 112, 108, 101, 
    114,   0, 103,  95, 116, 101, 
    120, 116, 117, 114, 101,   0, 
    103,  95,  98,  97,  99, 107, 
     84, 101, 120, 116, 117, 114, 
    101,   0,  80,  83,  67, 111, 
    110, 115, 116,  97, 110, 116, 
     66, 117, 102, 102, 101, 114, 
      0, 171, 171, 171, 236,   0, 
      0,   0,   2,   0,   0,   0, 
     24,   1,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  72,   1, 
      0,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  80,   1,   0,   0, 
      0,   0,   0,   0,  96,   1, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  80,   1,   0,   0, 
      0,   0,   0,   0, 103,  95, 
    115,  99,  97, 108, 101,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 109,  85, 
     86,  73, 110, 118, 101, 114, 
    115, 101, 100,  66,  97,  99, 
    107,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171, 171, 171, 
     73,  83,  71,  78, 204,   0, 
      0,   0,   7,   0,   0,   0, 
      8,   0,   0,   0, 176,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0, 188,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   3,   0,   0, 188,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
     15,   0,   0,   0, 188,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
     15,  11,   0,   0, 188,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
     15,  11,   0,   0, 188,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,  11,   0,   0, 197,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
     15,  11,   0,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0,  67,  79,  76,  79,  82, 
      0, 171,  79,  83,  71,  78, 
     44,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
     83,  86,  95,  84,  97, 114, 
    103, 101, 116,   0, 171, 171
};
