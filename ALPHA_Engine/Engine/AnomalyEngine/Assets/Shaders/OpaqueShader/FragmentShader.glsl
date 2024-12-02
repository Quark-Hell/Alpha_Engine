//#version 460
//in vec3 color;
//in vec3 normal;
//in vec3 frag_Pos;
//in vec2 texCoords;
//
//out vec4 frag_color;
//
//uniform vec3 viewPos;
//uniform float ambientStrength;
//
//uniform sampler2D diffuseMap;
//uniform sampler2D emissionMap;

//
////============================Spot Light============================//
//struct SpotLight {
//    vec3  direction;
//    vec3 color;
//	float strength;
//    vec3  position;
//
//    float cutOff;
//	float outerCutOff;
//};
//#define MAXSPOTLIGHT 16
//uniform int SpotLightsCount = 0;
//uniform SpotLight spotLights[MAXSPOTLIGHT];
//
//vec3 calcSpotLight(SpotLight sLight);
//
//vec3 calcSpotLight(SpotLight sLight){
//	vec3 lightDir = normalize(sLight.position - frag_Pos);
//	vec3 norm = normalize(normal);
//
//	vec3 diffuse = calcDiffuseLight(sLight.color, norm, lightDir, sLight.strength);
//	vec3 specular = calcSpecularLight(sLight.color, norm, lightDir);
//
//	float theta = dot(lightDir, normalize(-sLight.direction));
//
//	if(theta > sLight.cutOff)
//	{
//		return diffuse;
//	}
//	else{
//		float epsilon   = sLight.cutOff - sLight.outerCutOff;
//		float intensity = clamp((theta - sLight.outerCutOff) / epsilon, 0.0, 1.0);
//
//		diffuse  *= intensity;
//		specular *= intensity;
//
//		return diffuse;
//	}
//}
////============================Spot Light============================//
//
////============================Ambient Light============================//
//vec3 calcAmbientLights(float strength, vec3 lColor){
//   vec3 ambient = ambientStrength * lColor;
//
//   return ambient;
//}
////============================Ambient Light============================//
//
//
//void main() {
//   vec3 result = vec3(0,0,0);
//   vec3 directResult;
//   vec3 pointResult;
//   vec3 spotResult;
//
//   vec3 lightColor;
//
//   vec3 ambient = calcAmbientLights(ambientStrength, vec3(1,1,1));
//
//   for(int i = 0; i < DirectLightsCount && i < MAXDIRECTLIGHT; i++){
//	  directResult += calcDirectLight(directLights[i], normal);
//   }
//
////   for(int i = 0; i < PointLightsCount && i < MAXPOINTLIGHT; i++){
////	  pointResult += calcPointLight(pointLights[i], normal);
////   }
////
////   for(int i = 0; i < SpotLightsCount && i < MAXSPOTLIGHT; i++){
////	  spotResult += calcSpotLight(spotLights[i]);
////   }
//
//   //lightColor = ambient + spotResult + directResult + pointResult;
//   lightColor = ambient;
//   //result = vec3(texture(diffuseMap, texCoords)) * (vec3(texture(emissionMap, texCoords)) * 2 + lightColor);
//    result = vec3(texture(diffuseMap, texCoords));
//    //result = vec3(0.6f, 0.0f, 0.0f);
//
//   frag_color = vec4(result, 1.0);
//}

#version 450
in vec3 color;
in vec3 normal;
in vec3 frag_Pos;
in vec2 texCoords;

out vec4 FragColor;

uniform float ambientStrength;

uniform vec3 viewPos;

uniform sampler2D diffuseMap;
uniform sampler2D emissionMap;

vec3 calcAmbientLights(float strength, vec3 lColor);
vec3 calcDiffuseLight(vec3 ambient, vec3 norm, vec3 lightDir, float strength);
vec3 calcSpecularLight(vec3 lColor, vec3 norm, vec3 lightDir);

//============================Ambient Light============================//
vec3 calcAmbientLights(float strength, vec3 lColor){
   vec3 ambient = ambientStrength * lColor;

   return ambient;
}
//============================Ambient Light============================//

//============================Diffuse Light============================//
vec3 calcDiffuseLight(vec3 lColor, vec3 norm, vec3 lightDir, float strength){
   float diff = max(dot(norm, lightDir), 0.0);

   vec3 diffuse = lColor * diff * strength;;

   return diffuse;
}
//============================Diffuse Light============================//

//============================Specular Light============================//
vec3 calcSpecularLight(vec3 lColor, vec3 norm, vec3 lightDir){
    vec3 viewDir = normalize(viewPos - frag_Pos);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 specular = vec3(0,0,0);
    if(dot(norm, lightDir) > 0){
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
        float specularStrength = 0.5f;
        specular = specularStrength * spec * lColor;
    }

    return specular;
}
//============================Specular Light============================//

//============================Direct Light============================//
struct DirectLight {
    vec3 direction;
    vec3 color;
	float strength;

    vec3 diffuse;
    vec3 specular;
};

#define MAXDIRECTLIGHT 8
uniform int DirectLightsCount = 0;
uniform DirectLight directLights[MAXDIRECTLIGHT];
vec3 calcDirectLight(DirectLight dirLight);

vec3 calcDirectLight(DirectLight dirLight){
    vec3 lightDir = normalize(dirLight.direction);

    vec3 norm = normalize(normal);

    vec3 diffuse = calcDiffuseLight(dirLight.color, norm, lightDir, dirLight.strength);
    vec3 specular = calcSpecularLight(dirLight.color, norm, lightDir);

	vec3 result = diffuse + specular;

	return result;
}
//============================Direct Light============================//

//============================Point Light============================//
struct PointLight {
    vec3 position;
    vec3 color;

    vec3 diffuse;
    vec3 specular;

    float radius;
    float strength;

    float constant;
    float linear;
    float quadratic;
};
#define MAXPOINTLIGHT 16
uniform int PointLightsCount = 0;
uniform PointLight pointLights[MAXPOINTLIGHT];

vec3 calcPointLight(PointLight pLight);

vec3 calcPointLight(PointLight pLight){
	vec3 diffuse;
	vec3 specular;

	vec3 lightDir = pLight.position - frag_Pos;

	lightDir = normalize(lightDir);

	vec3 norm = normalize(normal);

    diffuse = calcDiffuseLight(pLight.color, norm, lightDir, pLight.strength);
    specular = calcSpecularLight(pLight.color, norm, lightDir);

    float distance    = length(pLight.position - frag_Pos);
    float attenuation = 1.0 / (pLight.constant + pLight.linear * distance +
    pLight.quadratic * (distance * distance));


    //float attenuation = smoothstep(pLight.radius, 0, length(pLight.position - frag_Pos));

	diffuse *= attenuation;
	specular *= attenuation;

	return diffuse + specular;
}
////============================Point Light============================//

void main()
{
    vec3 directResult;
    vec3 pointResult;
    //vec3 spotResult;
    vec3 lightColor;

    vec3 ambient = calcAmbientLights(ambientStrength, vec3(1,1,1));

    for(int i = 0; i < DirectLightsCount && i < MAXDIRECTLIGHT; i++){
        directResult += calcDirectLight(directLights[i]);
    }
    for(int i = 0; i < PointLightsCount && i < MAXDIRECTLIGHT; i++){
        pointResult += calcPointLight(pointLights[i]);
    }

    //lightColor = ambient + spotResult + directResult + pointResult;
    lightColor = ambient + directResult + pointResult;

    vec3 result = vec3(texture(diffuseMap, texCoords)) * (vec3(texture(emissionMap, texCoords)) * 2 + lightColor);
    FragColor = vec4(result, 1.0);
}