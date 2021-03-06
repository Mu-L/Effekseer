#version 330

precision highp float;
precision highp int;


vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
     return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v)
  { 
  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

// First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;

// Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );

  //   x0 = x0 - 0.0 + 0.0 * C.xxx;
  //   x1 = x0 - i1  + 1.0 * C.xxx;
  //   x2 = x0 - i2  + 2.0 * C.xxx;
  //   x3 = x0 - 1.0 + 3.0 * C.xxx;
  vec3 x1 = x0 - i1 + C.xxx;
  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y

// Permutations
  i = mod289(i); 
  vec4 p = permute( permute( permute( 
             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
           + i.y + vec4(0.0, i1.y, i2.y, 1.0 )) 
           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

// Gradients: 7x7 points over a square, mapped onto an octahedron.
// The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
  float n_ = 0.142857142857; // 1.0/7.0
  vec3  ns = n_ * D.wyz - D.xzx;

  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)

  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);

  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );

  //vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
  //vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));

  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);

//Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;

// Mix final noise value
  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
                                dot(p2,x2), dot(p3,x3) ) );
}


float packVec3(vec3 v) {
	uvec3 i = uvec3((v + 1.0) * 0.5 * 1023.0);
	return uintBitsToFloat(i.x | (i.y << 10) | (i.z << 20));
}

vec3 unpackVec3(float s) {
	uint bits = floatBitsToUint(s);
	vec3 v = vec3(uvec3(bits, bits >> 10, bits >> 20) & 1023u);
	return v / 1023.0 * 2.0 - 1.0;
}

float rand(vec2 seed) {
    return fract(sin(dot(seed, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 noise3(vec3 seed) {
	return vec3(snoise(seed.xyz), snoise(seed.yzx), snoise(seed.zxy));
}


uniform sampler2D i_ParticleData0; // |   Pos X   |   Pos Y   |   Pos Z   |  Dir XYZ  |
uniform sampler2D i_ParticleData1; // | LifeCount | Lifetime  |   Index   |   Seed    |
uniform vec4 DeltaTime;
//uniform vec4 Flags;

layout(location = 0) out vec4 o_ParticleData0; // |   Pos X   |   Pos Y   |   Pos Z   |  Dir XYZ  |
layout(location = 1) out vec4 o_ParticleData1; // | LifeCount | Lifetime  |   Index   |   Seed    |
//layout(location = 2) out vec4 o_Custom1;   // 

vec3 orbit(vec3 position, vec3 direction, vec3 move) {
	vec3 offset = vec3(0.0, 0.0, 0.0);
	vec3 axis = normalize(vec3(0.0, 1.0, 0.0));
	vec3 diff = position - offset;
	float distance = length(diff);
	vec3 normalDir;
	float radius;
	if (distance < 0.0001) {
		radius = 0.0001;
		normalDir = direction;
	} else {
		vec3 normal = diff - axis * dot(axis, normalize(diff)) * distance;
		radius = length(normal);
		if (radius < 0.0001) {
			normalDir = direction;
		} else {
			normalDir = normalize(normal);
		}
	}

	//float nextRadius = 0.1;
	float nextRadius = max(0.0001, radius + move.z);
	vec3 orbitDir = cross(axis, normalDir);
	float arc = 2.0 * 3.141592 * radius;
	float rotation = move.x / arc;

	vec3 rotationDir = orbitDir * sin(rotation) - normalDir * (1.0 - cos(rotation));
	vec3 velocity = rotationDir * radius + (rotationDir * 2.0 + normalDir) * radius * (nextRadius - radius);
	
	return velocity + axis * move.y;


	//float orbitLength = 2.0 * radius * 3.141592;
	//return orbitDir * 0.1 - normalDir * 0.01;
}

void main() {
	// Load data
	vec4 data0 = texelFetch(i_ParticleData0, ivec2(gl_FragCoord.xy), 0);
	vec4 data1 = texelFetch(i_ParticleData1, ivec2(gl_FragCoord.xy), 0);
	vec3 position = data0.xyz;
	vec3 direction = unpackVec3(data1.w);
	
	float DeltaTime1f = DeltaTime.x;
	// Apply aging
	data1.x += DeltaTime1f;
	float lifetimeRatio = data1.x / data1.y;
	
	// Clculate velocity
	vec3 velocity = vec3(0.0);
	//if (Flags.x) {
		velocity += direction * mix(0.01, 0.0, lifetimeRatio);
	//}
	//if (Flags.y) {
	//	vec3 orbitMove = mix(vec3(0.01, 0.0, 0.0), vec3(0.5, 0.01, -0.01), lifetimeRatio);
	//	velocity += orbit(position, direction, orbitMove);
	//}
	//if (Flags.z) {
		velocity += 0.01 * noise3(position);
	//}
	//if (Flags.w) {
		//velocity += vec3(0.0, -0.0001, 0.0) * data1.x;
		vec3 targetPosition = vec3(0.2, 0.0, 0.0);
		vec3 diff = targetPosition - position;
		velocity += normalize(diff) * 0.01;
	//}

	// Update position
	position += velocity;
	
	// Update direction
	direction = (length(velocity) < 0.0001) ? direction : normalize(velocity);
	
	// Store data
	o_ParticleData0 = vec4(position, packVec3(direction));
	o_ParticleData1 = data1;
}
