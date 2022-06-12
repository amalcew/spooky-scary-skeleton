#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
uniform vec3 shift;
uniform vec3 shift2;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 
in vec4 n;
in vec4 l1;
in vec4 l2;
in vec4 l3;
in vec4 v;
in vec2 iTexCoord0;
in vec2 iTexCoord1;

void main(void) {

	//Znormalizowane interpolowane wektory
	vec4 ml1 = normalize(l1); // disco light 1
	vec4 ml3 = normalize(l3); // disco light 2
	vec4 ml2 = normalize(l2); // kamera
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	//Wektor odbity
	vec4 mr1 = reflect(-ml1, mn);
	vec4 mr2 = reflect(-ml2, mn);
	vec4 mr3 = reflect(-ml2, mn);

	//Parametry powierzchni
	//vec4 kd = ic;
	vec4 kd = texture(textureMap0,iTexCoord0);
	vec4 ks = vec4(1, 1, 1, 1);

	//Obliczenie modelu oświetlenia
	float nl1 = clamp(dot(mn, ml1), 0, 1);
	float nl2 = clamp(dot(mn, ml2), 0, 1);
	float nl3 = clamp(dot(mn, ml3), 0, 1);

	float rv = pow(clamp(dot(mr2, mv), 0, 1), 150); // kamera
	float rv1 = pow(clamp(dot(mr1, mv), 0, 1), 30);
	float rv3 = pow(clamp(dot(mr3, mv), 0, 1), 30);
	pixelColor= 
		vec4(shift * nl1, kd.a) * 0.3 + vec4(shift*rv1, 0) * 0.7 + // disco 1
		vec4(shift2 * nl3, kd.a) * 0.3 + vec4(shift2*rv3, 0) * 0.7 + // disco 2
		vec4(kd.rgb * nl2, kd.a) * 0.9 + vec4(ks.rgb*rv, 0) * 0.7 // kamera + tekstura
		;
	//pixelColor = kd;
}
