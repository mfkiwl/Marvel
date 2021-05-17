cbuffer mvPointLightCBuf : register(b0)
{
    int LightCount;
    float3 ambient;
    float3 viewLightPos[3];
    float3 diffuseColor[3];
    float diffuseIntensity[3];
    float attConst[3];
    float attLin[3];
    float attQuad[3];
};

struct LightVectorData
{
    float3 vec;
    float3 dir;
    float dist;
};

LightVectorData CalculateLightVectorData(const in float3 lightPos, const in float3 fragPos)
{
    LightVectorData lv;
    lv.vec = lightPos - fragPos;
    lv.dist = length(lv.vec);
    lv.dir = lv.vec / lv.dist;
    return lv;
}