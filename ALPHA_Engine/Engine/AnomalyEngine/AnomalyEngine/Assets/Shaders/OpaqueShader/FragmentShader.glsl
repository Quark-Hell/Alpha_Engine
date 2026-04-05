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
vec3 calcDiffuseLight(vec3 lColor, vec3 norm, vec3 lightDir, float strength);
vec3 calcSpecularLight(vec3 lColor, vec3 norm, vec3 lightDir);

//============================Ambient Light============================//
vec3 calcAmbientLights(float strength, vec3 lColor) {
    vec3 ambient = strength * lColor;
    return ambient;
}
//============================Ambient Light============================//

//============================Diffuse Light============================//
vec3 calcDiffuseLight(vec3 lColor, vec3 norm, vec3 lightDir, float strength) {
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lColor * diff * strength;
    return diffuse;
}
//============================Diffuse Light============================//

//============================Specular Light============================//
vec3 calcSpecularLight(vec3 lColor, vec3 norm, vec3 lightDir) {
    float NdotL = dot(norm, lightDir);
    if (NdotL <= 0.0) return vec3(0.0);

    vec3 viewDir = normalize(viewPos - frag_Pos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
    return 0.5 * spec * lColor; // Fix: убран лишний vec3 specular = vec3(0,0,0)
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

vec3 calcDirectLight(DirectLight dirLight) {
    vec3 lightDir = normalize(-dirLight.direction); // Fix: инверсия — direction задаёт куда светит источник

    vec3 norm = normalize(normal);

    vec3 diffuse = calcDiffuseLight(dirLight.color, norm, lightDir, dirLight.strength);
    vec3 specular = calcSpecularLight(dirLight.color, norm, lightDir);

    return diffuse + specular;
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

vec3 calcPointLight(PointLight pLight) {
    vec3 lightDir = normalize(pLight.position - frag_Pos);
    vec3 norm = normalize(normal);

    vec3 diffuse = calcDiffuseLight(pLight.color, norm, lightDir, pLight.strength);
    vec3 specular = calcSpecularLight(pLight.color, norm, lightDir);

    float distance = length(pLight.position - frag_Pos);
    float attenuation = 1.0 / (pLight.constant + pLight.linear * distance +
        pLight.quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}
//============================Point Light============================//

void main()
{
    vec3 directResult = vec3(0.0);
    vec3 pointResult = vec3(0.0);

    vec3 ambient = calcAmbientLights(ambientStrength, vec3(1.0));

    for (int i = 0; i < DirectLightsCount && i < MAXDIRECTLIGHT; i++) {
        directResult += calcDirectLight(directLights[i]);
    }
    for (int i = 0; i < PointLightsCount && i < MAXPOINTLIGHT; i++) {
        pointResult += calcPointLight(pointLights[i]);
    }

    vec3 lightColor = ambient + directResult + pointResult;

    vec3 diffuseTex = vec3(texture(diffuseMap, texCoords));
    vec3 emissionTex = vec3(texture(emissionMap, texCoords));

    // Fix: emission не умножается на diffuse, а складывается поверх
    vec3 result = diffuseTex * lightColor + emissionTex * 2.0;
    FragColor = vec4(result, 1.0);
}
